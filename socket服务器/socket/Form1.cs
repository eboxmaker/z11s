using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MyFun;
using System.Net.Sockets;
using MyJson;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using AES;
using System.IO;
using System.Threading;


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
        Thread th;
        static int[] person_index;
        static int person_num;
        static TcpClient person_sender;
        static int totalPersonNum = 10;

        string[] fingers = {
                    "DQgSYgEKpV9hDBzMIRyPn2Evj51BOx0DgQ8gYAInhB+CKx+YojQeWYI+nxjCQJaEYg0QjCEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "EgwT4CEPHF6BD4yg4RQfGuEXkd8BGQffwSUEH6EsIwCBLw9cgTOd16E+k9khCB7JIhMSiWIVm8eiFgsKAjWWw8I2kAVCQx5BogAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "DBQEHsEdkQXhJogGgQgMSQIKnMOiHhrsoiiQA0IvmlUiNBmrwjSiVEI3lJaCOaHqYgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "CggJ3eESDUaBFZhDgRsEBwElDZpBPAYD4Qocw6IplIJCMqCVAjka7AIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "BwgFLGEXBtWBLg8p4S+EKsFAimkhFA9pgkMfqOIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "CggUF+EPiRnBEY6DYSYY1yExH1ZhPiBAYQkKg8ItisLiOyGXwiiEGgEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "BggU0OETi+xBHZJTYTGEF4E+lFShDR7mwgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "CwgIGAEfmWrhJKIn4SuXlME0m9PBOxQAARWSVcIakIBiHRgTYh2FGEI1BBiCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    "EAgL5GESDU4hFBrNgRgGaAEYl6VBLBpOoTCcZAEyIWNhNJglQToS5yEKm6PCDYQPYhojI6Ieh6eiHxqkgjKO6AIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg==",
                    /*尹国才*/"BggSZUEbDRFhNRVRwSwS6UJBhCuiPaGmQgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABXGg=="
                    };


        static JsonManager.Person[] person = new JsonManager.Person[totalPersonNum];


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
            for (int i = 0; i < totalPersonNum; i++)
            {
                person[i].id = "20180920" + i.ToString("D2");
                person[i].name = "USER" + i.ToString("D2");
                if (i < 2)
                {
                    person[i].level = 0;

                }
                else if (i == 2)
                    person[i].level = 1;
                else
                    person[i].level = 2;

                person[i].fingers = new string[1];
                person[i].fingers[0] = fingers[i];

                person[i].picture_name = "touxiang" + i.ToString() + ".jpg";
            }

            //person[0].fingers = new string[3];
            //person[0].fingers[0] = fingers[0];
            //person[0].fingers[1] = fingers[1];
            //person[0].fingers[2] = fingers[2];

            //person[1].fingers = new string[2];
            //person[1].fingers[0] = fingers[3];
            //person[1].fingers[1] = fingers[4];

            //person[2].fingers = new string[5];
            //person[2].fingers[0] = fingers[5];
            //person[2].fingers[1] = fingers[6];
            //person[2].fingers[2] = fingers[7];
            //person[2].fingers[3] = fingers[8];
            //person[2].fingers[4] = fingers[9];


        }
        public static void theardSendPerson()
        {
            for(int i = 0 ; i < person_num; i++)
            {
                string resault = JsonManager.MakePerson(person[person_index[i]], JsonManager.StatusType.StatusSet);
                server.Send(person_sender, resault);
            }

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

                string id;
                string resault;
                string enjs = Encoding.UTF8.GetString(datagram);

                string js = JsonManager.unPackage(enjs);

                //RichRecv.Text += sender.Client.RemoteEndPoint.ToString() + js;
                RichRecv.Text +=  js;
                JsonManager.CMDType cmd = JsonManager.GetJsonCMD(js);
                JsonManager.StatusType status = JsonManager.GetJsonStatus(js);
                switch (cmd)
                {
                    case JsonManager.CMDType.Heartbeat:
                        JsonManager.ParseCMDHeartbeat(js);
                         resault = JsonManager.MakeCMDHeartbeat(JsonManager.StatusType.StatusOK);
                         server.Send(sender,resault);
                        // server.SendAll(resault);
                        break;
                    case JsonManager.CMDType.SetHeartbeat:
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeSetHeartbeat(0, JsonManager.StatusType.StatusOK);

                            server.Send(sender, resault);
                        }
                        break;
                    case JsonManager.CMDType.DoorPwd: 
                        string pwd = JsonManager.ParseDoorPwd(js);
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            if (pwd == "123456")
                            {
                                resault = JsonManager.MakeCMDDoorPwd(pwd, JsonManager.StatusType.StatusOK);
                                server.Send(sender, resault);
                            }
                            else
                            {
                                resault = JsonManager.MakeCMDDoorPwd(pwd, JsonManager.StatusType.StatusErr);
                                server.Send(sender, resault);
                            }
                        }

                        break;
                    case JsonManager.CMDType.FingerKey:
                        id = JsonManager.ParseFingerKey(js);
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeCMDFingerKey(JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);

                            resault = JsonManager.MakeCMDDoorCtr("unlock", JsonManager.StatusType.StatusSet);
                            server.Send(sender, resault);
                        }
                        break;
                    case JsonManager.CMDType.DoorCtr:
                        if (status == JsonManager.StatusType.StatusOK)
                        {

                        }
                        break;

                    case JsonManager.CMDType.DoorState:
                        string doorState = JsonManager.ParseCMDDoorState(js);
                        if (status == JsonManager.StatusType.StatusOK)
                        {

                        }

                        break;
                    case JsonManager.CMDType.AdminPwd:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeAdminPwd("set ok",JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }

                        break;
                    case JsonManager.CMDType.Register:
                         id = "";
                        JsonManager.StatusConfirmType cStatus = JsonManager.GetJsonStatusConfirm(js,ref id);

                        if (cStatus == JsonManager.StatusConfirmType.StatusReqDev2Ser)
                        {
                            resault = JsonManager.MakeConfirm(id,JsonManager.StatusConfirmType.StatusParaSer2Dev);
                            server.Send(sender, resault);
                        }
                        if(cStatus ==  JsonManager.StatusConfirmType.StatusAckDev2Ser)
                        {
                            resault = JsonManager.MakeConfirm(id,JsonManager.StatusConfirmType.StatusOKSer2Dev);
                            server.Send(sender, resault);

                            for (int i = 0; i < totalPersonNum; i++)
                            {
                                resault = JsonManager.MakePerson(person[i], JsonManager.StatusType.StatusSet);
                                server.Send(sender, resault);
                            }
                        }

                        break;
                    case JsonManager.CMDType.SyncDateTime:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeCMDSyncDateTime(JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }

                        break;
                    case JsonManager.CMDType.Plan:
                        if (status == JsonManager.StatusType.StatusGet)
                        {
                            resault = JsonManager.MakePlan(JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }

                        break;
                    case JsonManager.CMDType.AdSet:
                        if(status == JsonManager.StatusType.StatusSet)
                        {
                            bool enable = cbAdEnable.Checked;
                            int time = Convert.ToInt16(tbAdTime.Text);

                            resault = JsonManager.MakeAdSet(enable, time, JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }
                        break;
                    case JsonManager.CMDType.OrgName:
                        string org = JsonManager.ParseOrgName(js);
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeOrgName(org, JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }

                        break;
                    case JsonManager.CMDType.DevName:
                        string name = JsonManager.ParseDevName(js);
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeDevName(name, JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }

                        break;
                    case JsonManager.CMDType.DevID:
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeDevID(JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }

                        break;

                    case JsonManager.CMDType.Person:

                        //if (status == JsonManager.StatusType.StatusRead)
                        //{
                        //    resault = JsonManager.MakePerson(person[0], JsonManager.StatusType.StatusOK);
                        //server.Send(sender, resault);
                        //}
                        //if (status == JsonManager.StatusType.StatusSet)
                        //{
                        //    resault = JsonManager.MakePerson(person[0], JsonManager.StatusType.StatusOK);
                        //server.Send(sender, resault);
                        //}
                        break;
                    case JsonManager.CMDType.PersonGetByLevel:
                        int level = 0;
                        int num = 0;
                        person_num = 0;
                        JsonManager.ParsePersonGetByLevel(js,ref level, ref num);
                        if (status == JsonManager.StatusType.StatusGet)
                        {
                            
                                for (int i = 0; i < person.Length; i++ )
                                {
                                    if(person[i].level == level)
                                    {
                                        person_num++;
                                    }
                                }
                                person_index = new int[person_num];
                                int j = 0;
                                for (int i = 0; i < person.Length; i++)
                                {
                                    if (person[i].level == level)
                                    {
                                        person_index[j++] = i;
                                    }
                                }
                                resault = JsonManager.MakePersonGetByLevel(level, person_num, JsonManager.StatusType.StatusOK);



                            server.Send(sender, resault);

                            for (int i = 0; i < person_num; i++)
                            {
                                resault = JsonManager.MakePerson(person[person_index[i]], JsonManager.StatusType.StatusSet);
                                server.Send(sender, resault);
                            }


                            //if (person_num > 0)
                            //{
                            //    person_sender = sender;
                            //    ThreadStart childref = new ThreadStart(theardSendPerson);
                            //    Console.WriteLine("In Main: Creating the Child thread");
                            //    th = new Thread(childref);
                            //    //th.Start();
                            //}
                        }
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakePerson(person[0], JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }
                        break;
                    case JsonManager.CMDType.FingerGet:
                        string idtemp = JsonManager.parseFingerGet(js);
                        int id_temp = Convert.ToInt32(idtemp);
                        id_temp = id_temp % 10;
                        if (status == JsonManager.StatusType.StatusGet)
                        {
                            resault = JsonManager.MakeFingerGet(person[id_temp], JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeFingerGet(person[id_temp], JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }
                        break;
                    case JsonManager.CMDType.FingerSet:
                        string idtemp2 = JsonManager.parseFingerSet(js);
                        int id_temp2 = Convert.ToInt32(idtemp2);
                        id_temp2 = id_temp2 % 10;
                        if (status == JsonManager.StatusType.StatusGet)
                        {
                            resault = JsonManager.MakeFingerSet(person[id_temp2], JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }
                        if (status == JsonManager.StatusType.StatusSet)
                        {
                            resault = JsonManager.MakeFingerSet(person[id_temp2], JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
                        }
                        break;
                    case JsonManager.CMDType.CMDVersion:


                        break;


                    case JsonManager.CMDType.CMDUpdate:
                        if (status == JsonManager.StatusType.StatusGet)
                        {
                            resault = JsonManager.MakeUpdate(tbDownLoadUrl.Text, Convert.ToInt32(tbDownLoadPort.Text), JsonManager.StatusType.StatusOK);
                            server.Send(sender, resault);
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
            string str = JsonManager.Package(RichSend.Text);
                
                //AESEncrypt.Encrypt(, "12345678900000001234567890000000");
            server.SendAll(str);
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
            string str = JsonManager.PackageAdFileToJsonString("1.jpg", 2);
           RichSend.Text = str;
        }

        private void btnLoadFile2_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageAdFileToJsonString("2.jpg", 5);
            RichSend.Text = str;
        }
        private void btnLoadFile3_Click(object sender, EventArgs e)
        {
            string str = JsonManager.PackageAdFileToJsonString("3.jpg", 10);
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
            string jstr = JsonManager.MakeCMDDoorCtr("unlock", JsonManager.StatusType.StatusSet);
            server.SendAll(jstr);

        }

        private void btnCloseLock_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoorCtr("lock", JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }
        private void btnReadDoorState_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCMDDoorState( JsonManager.StatusType.StatusGet);
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
            string str = JsonManager.MakeBroadcast("", JsonManager.StatusType.StatusGet);
            server.SendAll(str);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            bool enable = cbAdEnable.Checked;
            int time = Convert.ToInt16(tbAdTime.Text);

            string str = JsonManager.MakeAdSet(enable,time,JsonManager.StatusType.StatusSet);
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
            string str = JsonManager.MakeAdminPwd("read",JsonManager.StatusType.StatusGet);
            server.SendAll(str);
        }

        private void btnGetID_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDevID(JsonManager.StatusType.StatusGet);
            server.SendAll(str);
        }

        private void btnGetDevName_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDevName("",JsonManager.StatusType.StatusGet);
            server.SendAll(str);
        }

        private void btnSetDevName_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeDevName(tbDevName.Text, JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnConfirm_Click(object sender, EventArgs e)
        {
            //string str = JsonManager.MakeConfirm( JsonManager.StatusType.StatusSet);
            //server.SendAll(str);
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
            string str = JsonManager.MakeSetHeartbeat(interval, JsonManager.StatusType.StatusGet);
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
            string str = JsonManager.MakeDoorPwd(tbDoorPwd.Text, JsonManager.StatusType.StatusGet);
            server.SendAll(str);
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            string dd = AESEncrypt.Encrypt("{\"cmd\":0,\"value\":\"hello\",\"status\":0}", "12345678900000001234567890000000");
            tbAesTest.Text = dd;
            tbENcoderLen.Text = dd.Length.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string dd = AESEncrypt.Decrypt(tbAesTest.Text, "12345678900000001234567890000000");
            tbAesTest.Text = dd;
        }

        private void btnGetKeyHex_Click(object sender, EventArgs e)
        {
            byte[] keyBytes = Encoding.UTF8.GetBytes("12345678900000001234567890000000");

            tbAesTest.Text = AESEncrypt.ByteArrayToHexString(keyBytes);
        }

        private void btnGetIVHex_Click(object sender, EventArgs e)
        {
            byte[] keyBytes = Encoding.UTF8.GetBytes("1234567890000000");

            tbAesTest.Text = AESEncrypt.ByteArrayToHexString(keyBytes);
        }

        private void btnSendCourseInfo_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeCourseInfoString("touxiang.jpg");
            server.SendAll(str);

        }

        private void btnReadVersion_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeVersion(JsonManager.StatusType.StatusGet);
            server.SendAll(str);
        }

        private void btnReboot_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeReboot(JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnSendFile_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeUpdate(tbDownLoadUrl.Text,Convert.ToInt32(tbDownLoadPort.Text),JsonManager.StatusType.StatusSet);
            server.SendAll(str);

             FileStream fs = File.OpenRead("1.jpg");
             if (fs != null)
             {
                 int len = (int)fs.Length;
                 byte[] byteArray = new byte[len];
                 int ReadedLength = fs.Read(byteArray, 0, len);
                 server.SendAll(byteArray);
                 tbSendDataLength.Text = len.ToString();

             }
        }

        private void btnAdClear_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakeAdClear(JsonManager.StatusType.StatusSet);
            server.SendAll(str);

        }

        private void btnAdRead_Click(object sender, EventArgs e)
        {
            
            string str = JsonManager.MakeAdRead(JsonManager.StatusType.StatusSet);
            //server.SendAll(str);
            server.Send(server.clients[0].TcpClient,str);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakePlan(JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            string str = JsonManager.MakePlan2(JsonManager.StatusType.StatusSet);
            server.SendAll(str);
        }

        private void btnDeletAdPic_MouseUp(object sender, MouseEventArgs e)
        {

        }

        private void btnSendPerson_Click(object sender, EventArgs e)
        {
            //int id = Convert.ToInt16(tbPersonId.Text);
            //string resault = JsonManager.MakeFingerGet(person[id], JsonManager.StatusType.StatusSet);
            //server.SendAll(resault);
        }

        private void btnSendPerson_Click_1(object sender, EventArgs e)
        {
            int id = Convert.ToInt16(tbPersonId.Text);
            string resault = JsonManager.MakePerson(person[id], JsonManager.StatusType.StatusSet);
            server.SendAll(resault);
        }
        


 

 








  
        

    }
}
