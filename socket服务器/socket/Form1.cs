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
                string js = Encoding.Default.GetString(datagram);
                RichRecv.Text += sender.Client.RemoteEndPoint.ToString() + js;
                int cmd = JsonManager.GetJsonCMD(js);
                switch (cmd)
                {
                    case (int)JsonManager.CMDType.Heartbeat:
                        JsonManager.ParseCMDHeartbeat(js);
                        string str = JsonManager.MakeCMDHeartbeat();
                        server.SendAll(str);
                        break;
                    case (int)JsonManager.CMDType.DoorPwd: 
                        string pwd = JsonManager.ParseDoorPwd(js);
                        string resault;
                        if(pwd == "123456")
                        {
                            resault = JsonManager.MakeCMDDoorPwdAck(1);
                            server.SendAll(resault);
                            btnOpen.PerformClick();
                        }
                        else
                        {
                            resault = JsonManager.MakeCMDDoorPwdAck(0);
                            server.SendAll(resault);
                            btnCloseLock.PerformClick();
                        }
                        break;
                    case (int)JsonManager.CMDType.AdminPwd:
                        break;
                    case (int)JsonManager.CMDType.Confirm:
  
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
            string str = JsonManager.PackageFileToJsonString("1.jpg", (int)JsonManager.CMDType.Advertisement);
           RichSend.Text = str;
        }

        private void btnLoadFile2_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("2.jpg", (int)JsonManager.CMDType.Advertisement);
            RichSend.Text = str;
        }
        private void btnLoadFile3_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("3.jpg", (int)JsonManager.CMDType.Advertisement);
            RichSend.Text = str;
        }
        private void btnLoadQR_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("qr1.jpg", (int)JsonManager.CMDType.QR);
            RichSend.Text = str;
        }
        private void btnLoadQR2_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageFileToJsonString("qr2.jpg", (int)JsonManager.CMDType.QR);
            RichSend.Text = str;
        }

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            JsonManager.SaveJsonStringFile(RichSend.Text,"1");
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoor1(1);
            server.SendAll(str);
            server.SendAll(str);

        }

        private void btnCloseLock_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoor1(0);
            server.SendAll(str);
        }




  
        

    }
}
