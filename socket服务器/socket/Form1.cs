﻿using System;
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
                RichRecv.Text += sender.Client.RemoteEndPoint.ToString() + Encoding.Default.GetString(datagram);
            }
        }
        
        private void btnGetClientNum_Click(object sender, EventArgs e)
        {

        }

        private void btnSendMSG_Click(object sender, EventArgs e)
        {

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
        
    }
}
