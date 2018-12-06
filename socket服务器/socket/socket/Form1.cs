using Communication;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace socket
{
    public partial class Form1 : Form
    {
        public static  Form1 mainForm;
        private delegate void InvokeCallback(string msg);
        int ServerPort = 80;
        int IPNum = 0;
        getLocalIPList getip = new getLocalIPList();
        MyTcpServer server = new MyTcpServer();
        bool serverOpenFlag = false;
        public Form1()
        {
            mainForm = this;
            InitializeComponent();
            ServerPort = Convert.ToInt32(tbServerPort.Text);
            string[] str = getip.GetLocalIP(ref IPNum);
            for (int i = 0; i < IPNum;i++ )
            {
                cbLocalIPList.Items.Add(str[i]);
            }
            cbLocalIPList.SelectedIndex = 0;

            server.AddConnections = new MyTcpServer.TestDelegate(AddConnections);
            server.DeletConnections = new MyTcpServer.TestDelegate(DeletConnections);
        }

        private void btnStartServer_Click(object sender, EventArgs e)
        {
            ServerPort = Convert.ToInt32(tbServerPort.Text);
            if (serverOpenFlag == false)
            {
                server.OpenServer(ServerPort);
                btnStartServer.Text = "关闭服务器";
                serverOpenFlag = true;
            }
            else
            {
                server.CloseServer();
                  btnStartServer.Text = "开启服务器";
                  serverOpenFlag = false;

            }

        }
        public  void AddConnections( string msg )
        {
            if (ListBoxConnections.InvokeRequired)
            {
                this.Invoke(server.AddConnections, new object[] { msg });
            }
            else
            {
                ListBoxConnections.Items.Add(msg);
            }
        }
        public void DeletConnections(string msg)
        {
            if (ListBoxConnections.InvokeRequired)
            {
                this.Invoke(server.AddConnections, new object[] { msg });
            }
            else
            {
                ListBoxConnections.Items.Add(msg);
            }
        }
        private void btnGetClientNum_Click(object sender, EventArgs e)
        {

            var result = from pair in server.dic_ClientSocket orderby pair.Key select pair;
            foreach (KeyValuePair<string, MySession> pair in result)
            {

                ListBoxConnections.Items.Add( pair.Key.ToString());
               // lis .WriteLine();
            }
           // server.dic_ClientSocket.GetEnumerator();
        }

        private void btnSendMSG_Click(object sender, EventArgs e)
        {
            byte[] data = System.Text.Encoding.Default.GetBytes(RichSend.Text);
            
            string key = ListBoxConnections.SelectedItem.ToString();
            server.dic_ClientSocket[key].Send(data);
        }

        private void btnReadBuf_Click(object sender, EventArgs e)
        {
            byte[] data = System.Text.Encoding.Default.GetBytes(RichSend.Text);

            string key = ListBoxConnections.SelectedItem.ToString();
            int len =  server.dic_ClientSocket[key].available();
            RichRecv.Text += System.Text.Encoding.Default.GetString(server.dic_ClientSocket[key].GetBuffer(0, len));
        }
    }
}
