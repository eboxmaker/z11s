﻿namespace socket
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnStartServer = new System.Windows.Forms.Button();
            this.tbServerPort = new System.Windows.Forms.TextBox();
            this.cbLocalIPList = new System.Windows.Forms.ComboBox();
            this.ListBoxConnections = new System.Windows.Forms.ListBox();
            this.tbClientNum = new System.Windows.Forms.TextBox();
            this.btnGetClientNum = new System.Windows.Forms.Button();
            this.RichRecv = new System.Windows.Forms.RichTextBox();
            this.btnSendMSG = new System.Windows.Forms.Button();
            this.RichSend = new System.Windows.Forms.RichTextBox();
            this.btnReadBuf = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnStartServer
            // 
            this.btnStartServer.Location = new System.Drawing.Point(12, 65);
            this.btnStartServer.Name = "btnStartServer";
            this.btnStartServer.Size = new System.Drawing.Size(75, 23);
            this.btnStartServer.TabIndex = 0;
            this.btnStartServer.Text = "启动服务器";
            this.btnStartServer.UseVisualStyleBackColor = true;
            this.btnStartServer.Click += new System.EventHandler(this.btnStartServer_Click);
            // 
            // tbServerPort
            // 
            this.tbServerPort.Location = new System.Drawing.Point(12, 38);
            this.tbServerPort.Name = "tbServerPort";
            this.tbServerPort.Size = new System.Drawing.Size(100, 21);
            this.tbServerPort.TabIndex = 1;
            this.tbServerPort.Text = "80";
            // 
            // cbLocalIPList
            // 
            this.cbLocalIPList.FormattingEnabled = true;
            this.cbLocalIPList.Location = new System.Drawing.Point(12, 12);
            this.cbLocalIPList.Name = "cbLocalIPList";
            this.cbLocalIPList.Size = new System.Drawing.Size(121, 20);
            this.cbLocalIPList.TabIndex = 2;
            // 
            // ListBoxConnections
            // 
            this.ListBoxConnections.FormattingEnabled = true;
            this.ListBoxConnections.ItemHeight = 12;
            this.ListBoxConnections.Location = new System.Drawing.Point(13, 105);
            this.ListBoxConnections.Name = "ListBoxConnections";
            this.ListBoxConnections.Size = new System.Drawing.Size(120, 88);
            this.ListBoxConnections.TabIndex = 3;
            // 
            // tbClientNum
            // 
            this.tbClientNum.Location = new System.Drawing.Point(13, 199);
            this.tbClientNum.Name = "tbClientNum";
            this.tbClientNum.Size = new System.Drawing.Size(100, 21);
            this.tbClientNum.TabIndex = 4;
            // 
            // btnGetClientNum
            // 
            this.btnGetClientNum.Location = new System.Drawing.Point(13, 225);
            this.btnGetClientNum.Name = "btnGetClientNum";
            this.btnGetClientNum.Size = new System.Drawing.Size(100, 23);
            this.btnGetClientNum.TabIndex = 5;
            this.btnGetClientNum.Text = "获取客户端数量";
            this.btnGetClientNum.UseVisualStyleBackColor = true;
            this.btnGetClientNum.Click += new System.EventHandler(this.btnGetClientNum_Click);
            // 
            // RichRecv
            // 
            this.RichRecv.Location = new System.Drawing.Point(194, 12);
            this.RichRecv.Name = "RichRecv";
            this.RichRecv.Size = new System.Drawing.Size(477, 150);
            this.RichRecv.TabIndex = 6;
            this.RichRecv.Text = "";
            // 
            // btnSendMSG
            // 
            this.btnSendMSG.Location = new System.Drawing.Point(605, 382);
            this.btnSendMSG.Name = "btnSendMSG";
            this.btnSendMSG.Size = new System.Drawing.Size(75, 23);
            this.btnSendMSG.TabIndex = 7;
            this.btnSendMSG.Text = "发送数据";
            this.btnSendMSG.UseVisualStyleBackColor = true;
            this.btnSendMSG.Click += new System.EventHandler(this.btnSendMSG_Click);
            // 
            // RichSend
            // 
            this.RichSend.Location = new System.Drawing.Point(194, 209);
            this.RichSend.Name = "RichSend";
            this.RichSend.Size = new System.Drawing.Size(477, 167);
            this.RichSend.TabIndex = 8;
            this.RichSend.Text = "";
            // 
            // btnReadBuf
            // 
            this.btnReadBuf.Location = new System.Drawing.Point(596, 168);
            this.btnReadBuf.Name = "btnReadBuf";
            this.btnReadBuf.Size = new System.Drawing.Size(75, 23);
            this.btnReadBuf.TabIndex = 9;
            this.btnReadBuf.Text = "读取数据";
            this.btnReadBuf.UseVisualStyleBackColor = true;
            this.btnReadBuf.Click += new System.EventHandler(this.btnReadBuf_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(683, 417);
            this.Controls.Add(this.btnReadBuf);
            this.Controls.Add(this.RichSend);
            this.Controls.Add(this.btnSendMSG);
            this.Controls.Add(this.RichRecv);
            this.Controls.Add(this.btnGetClientNum);
            this.Controls.Add(this.tbClientNum);
            this.Controls.Add(this.ListBoxConnections);
            this.Controls.Add(this.cbLocalIPList);
            this.Controls.Add(this.tbServerPort);
            this.Controls.Add(this.btnStartServer);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnStartServer;
        private System.Windows.Forms.TextBox tbServerPort;
        private System.Windows.Forms.ComboBox cbLocalIPList;
        private System.Windows.Forms.ListBox ListBoxConnections;
        private System.Windows.Forms.TextBox tbClientNum;
        private System.Windows.Forms.Button btnGetClientNum;
        private System.Windows.Forms.RichTextBox RichRecv;
        private System.Windows.Forms.Button btnSendMSG;
        private System.Windows.Forms.RichTextBox RichSend;
        private System.Windows.Forms.Button btnReadBuf;
    }
}

