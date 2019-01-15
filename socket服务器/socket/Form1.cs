using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MyFun;
using System.Net.Sockets;
using System.Threading;
using MyJson;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace socket
{
    public partial class Form1 : Form
    {
        public static  Form1 mainForm;
        static AsyncTcpServer server;
        private delegate void InvokeCallback(TcpClient tcp);
        int ServerPort = 6000;
        int IPNum = 0;
        bool serverOpenFlag = false;
        public Form1()
        {
            mainForm = this;
            InitializeComponent();
            ServerPort = Convert.ToInt32(tbServerPort.Text);
            string[] str = IPHelper.GetLocalIP(ref IPNum);
            for (int i = 0; i < IPNum;i++ )
            {
                cbLocalIPList.Items.Add(str[i]);
            }
            cbLocalIPList.SelectedIndex = 0;
        }

        private void btnStartServer_Click(object sender, EventArgs e)
        {
            ListBoxConnections.Items.Clear();
            ServerPort = Convert.ToInt32(tbServerPort.Text);
            if (serverOpenFlag == false)
            {
                server = new AsyncTcpServer(ServerPort);
                server.Encoding = Encoding.UTF8;
                server.ClientConnected +=
                  new EventHandler<TcpClientConnectedEventArgs>(server_ClientConnected);
                server.ClientDisconnected +=
                  new EventHandler<TcpClientDisconnectedEventArgs>(server_ClientDisconnected);
                server.PlaintextReceived +=
                  new EventHandler<TcpDatagramReceivedEventArgs<string>>(server_PlaintextReceived);

                server.DelegateClientConnected = new AsyncTcpServer.ActionDelegate(DelegateClientConnected);
                server.DelegateClientDisconnected = new AsyncTcpServer.ActionDelegate(DelegateClientDisconnected);
                server.DelegateReceived = new AsyncTcpServer.RecvDelegate(DelegateRecvData);

                server.Start();
                btnStartServer.Text = "关闭服务器";
                serverOpenFlag = true;
            }
            else
            {
                server.Stop();
                  btnStartServer.Text = "开启服务器";
                  serverOpenFlag = false;
                for(int i = 0; i < server.clients.Count; i++)
                {
                    ListBoxConnections.Items.Add(server.clients[i].TcpClient.Client.RemoteEndPoint.ToString());
                }

            }

        }
        public void DelegateClientConnected(TcpClient tcp)
        {
            if (ListBoxConnections.InvokeRequired)
            {
                this.Invoke(server.DelegateClientConnected, new object[] { tcp });
            }
            else
            {
                ListBoxConnections.Items.Add(tcp.Client.RemoteEndPoint.ToString());
            }
        }
        public void DelegateClientDisconnected(TcpClient tcp)
        {
            if (ListBoxConnections.InvokeRequired)
            {
                this.Invoke(server.DelegateClientDisconnected, new object[] { tcp });
            }
            else
            {
                ListBoxConnections.Items.Remove(tcp.Client.RemoteEndPoint.ToString());
            }
        }
        public void DelegateRecvData(TcpClient sender, byte[] datagram)
        {
            if (ListBoxConnections.InvokeRequired)
            {
                this.Invoke(server.DelegateReceived, new object[] { sender, datagram });
            }
            else
            {
                string resault;
                string js = Encoding.UTF8.GetString(datagram);
                RichRecv.Text += sender.Client.RemoteEndPoint.ToString() + js;
                JsonManager.CMDType cmd = JsonManager.GetJsonCMD(js);
                JsonManager.StatusType status = JsonManager.GetJsonStatus(js);
                switch (cmd)
                {
                    case JsonManager.CMDType.Heartbeat:
                        JsonManager.ParseCMDHeartbeat(js);
                         resault = JsonManager.MakeCMDHeartbeat(JsonManager.StatusType.StatusOK);
                         server.SendAll(resault);
                        break;
                    case JsonManager.CMDType.SetHeartbeat:
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeSetHeartbeat(0, JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }
                        break;
                    case JsonManager.CMDType.DoorPwd: 
                        string pwd = JsonManager.ParseDoorPwd(js);
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            if (pwd == "123456")
                            {
                                resault = JsonManager.MakeCMDDoorPwd(pwd, JsonManager.StatusType.StatusOK);
                                server.SendAll(resault);
                                btnOpen.PerformClick();
                            }
                            else
                            {
                                resault = JsonManager.MakeCMDDoorPwd(pwd, JsonManager.StatusType.StatusErr);
                                server.SendAll(resault);
                                btnCloseLock.PerformClick();
                            }
                        }

                        break;
                    case JsonManager.CMDType.AdminPwd:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeAdminPwd("set ok",JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }

                        break;
                    case JsonManager.CMDType.Confirm:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeConfirm(JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }

                        break;
                    case JsonManager.CMDType.SyncDateTime:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeCMDSyncDateTime(JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }

                        break;
                    case JsonManager.CMDType.Plan:
                        resault = JsonManager.MakePlan();
                        server.SendAll(resault);
                        break;
                    case JsonManager.CMDType.AdSet:
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            bool enable = cbAdEnable.Checked;
                            int time = Convert.ToInt16(tbAdTime.Text);
                            int interval = Convert.ToInt16(tbAdInterval.Text);

                            resault = JsonManager.MakeAdSet(enable, time, interval, JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }
                        break;
                    case JsonManager.CMDType.DevName:
                        string name = JsonManager.ParseDevName(js);
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeDevName(name, JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }

                        break;
                    case JsonManager.CMDType.DevID:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeDevID(JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }

                        break;

                    case JsonManager.CMDType.Person:
                        string[] fingers = {"1111111111","wwwwwwwwwww","124e2qerfwf"};
                        if (status == JsonManager.StatusType.StatusRead)
                        {
                            resault = JsonManager.MakePerson("123", "张云峰", 0, fingers, JsonManager.StatusType.StatusOK);
                            server.SendAll(resault);
                        }

                        break;
                }
                    
            }
        }
        
        private void btnGetClientNum_Click(object sender, EventArgs e)
        {

        }

        private void btnSendMSG_Click(object sender, EventArgs e)
        {
            server.SendAll(RichSend.Text);
            tbSendDataLength.Text = RichSend.Text.Length.ToString();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            RichRecv.Clear();
        }








        void server_ClientConnected(object sender, TcpClientConnectedEventArgs e)
        {
          // ListBoxConnections.Items.Add(e.TcpClient.Client.RemoteEndPoint.ToString());
            string str = e.TcpClient.Client.RemoteEndPoint.ToString();
        }

        void server_ClientDisconnected(object sender, TcpClientDisconnectedEventArgs e)
        {
            //Logger.Debug(string.Format(CultureInfo.InvariantCulture, 
            //"TCP client {0} has disconnected.", 
            //e.TcpClient.Client.RemoteEndPoint.ToString()));
        }

        void server_PlaintextReceived(object sender, TcpDatagramReceivedEventArgs<string> e)
        {
            //if (e.Datagram != "Received")
            //{
            //Console.Write(string.Format("Client : {0} --> ", 
            //    e.TcpClient.Client.RemoteEndPoint.ToString()));
            //Console.WriteLine(string.Format("{0}", e.Datagram));
            //server.Send(e.TcpClient, "Server has received you text : " + e.Datagram);
            //}
        }

        private void btnLoadFile_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("1.jpg", (int)JsonManager.CMDType.AdPic);
           RichSend.Text = str;
        }

        private void btnLoadFile2_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("2.jpg", (int)JsonManager.CMDType.AdPic);
            RichSend.Text = str;
        }
        private void btnLoadFile3_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("3.jpg", (int)JsonManager.CMDType.AdPic);
            RichSend.Text = str;
        }
        private void btnLoadQR_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("qr.jpg", (int)JsonManager.CMDType.QRCode);
            RichSend.Text = str;
        }
        private void btnLoadQR2_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("qr.jpg", (int)JsonManager.CMDType.QRCode);
            RichSend.Text = str;
        }

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            JsonManager.SaveJsonStringFile(RichSend.Text,"1");
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoor1("unlock",JsonManager.StatusType.StatusSet);
            server.SendAll( str );

        }

        private void btnCloseLock_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoor1("lock", JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }
        private void btnReadDoorState_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoor1("lock", JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }

        private void btnBroadcast_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeBroadcast(tbBroadcast.Text, JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnCloseBroadcast_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeBroadcast("",JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }
        private void btnReadBroadcast_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeBroadcast("", JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            bool enable = cbAdEnable.Checked;
            int time = Convert.ToInt16(tbAdTime.Text);
            int interval = Convert.ToInt16(tbAdInterval.Text);

            string str = JsonManager.MakeAdSet(enable,time,interval,JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnSyncTime_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDSyncDateTime(JsonManager.StatusType.StatusSet);
            server.SendAll(str);

        }

        private void btnModifyAdminPwd_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeAdminPwd(tbAdminPwd.Text,JsonManager.StatusType.StatusSet);
            server.SendAll(str);

        }

        private void btnReadAdminPwd_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeAdminPwd("read",JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }

        private void btnGetID_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDevID(JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }

        private void btnGetDevName_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDevName("",JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }

        private void btnSetDevName_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDevName(tbDevName.Text, JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnConfirm_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeConfirm( JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnDeletAdPic_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDeleteAdPic(tbAdName.Text,JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }
        private void btnDelQRCode_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDeleteQRCode(tbQRCodeName.Text, JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnSetHeartbeatInterval_Click(object sender, EventArgs e)
        {
            int interval = Convert.ToInt16(tbHeartInterval.Text);
            string str = JsonManager.MakeSetHeartbeat(interval,JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }
        private void btnReadHearInterval_Click(object sender, EventArgs e)
        {
            int interval = Convert.ToInt16(tbHeartInterval.Text);
            string str = JsonManager.MakeSetHeartbeat(interval, JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }

        private void btnSetDoorPwd_Click(object sender, EventArgs e)
        {
            //int interval = Convert.ToInt16(tbHeartInterval.Text);
            string str = JsonManager.MakeDoorPwd(tbDoorPwd.Text, JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnReadDoorPwd_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDoorPwd(tbDoorPwd.Text, JsonManager.StatusType.StatusRead);
            server.SendAll(str);
        }


 

 








  
        

    }
}
