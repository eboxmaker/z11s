namespace socket
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
            this.btnClear = new System.Windows.Forms.Button();
            this.btnLoadFile = new System.Windows.Forms.Button();
            this.btnSaveFile = new System.Windows.Forms.Button();
            this.btnOpen = new System.Windows.Forms.Button();
            this.btnCloseLock = new System.Windows.Forms.Button();
            this.tbSendDataLength = new System.Windows.Forms.TextBox();
            this.btnLoadQR1 = new System.Windows.Forms.Button();
            this.btnLoadQR2 = new System.Windows.Forms.Button();
            this.btnLoadFile2 = new System.Windows.Forms.Button();
            this.btnLoadFile3 = new System.Windows.Forms.Button();
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
            this.tbServerPort.Text = "6000";
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
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(596, 168);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 9;
            this.btnClear.Text = "清空数据";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnLoadFile
            // 
            this.btnLoadFile.Location = new System.Drawing.Point(13, 263);
            this.btnLoadFile.Name = "btnLoadFile";
            this.btnLoadFile.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile.TabIndex = 10;
            this.btnLoadFile.Text = "加载文件";
            this.btnLoadFile.UseVisualStyleBackColor = true;
            this.btnLoadFile.Click += new System.EventHandler(this.btnLoadFile_Click);
            // 
            // btnSaveFile
            // 
            this.btnSaveFile.Location = new System.Drawing.Point(13, 353);
            this.btnSaveFile.Name = "btnSaveFile";
            this.btnSaveFile.Size = new System.Drawing.Size(75, 23);
            this.btnSaveFile.TabIndex = 11;
            this.btnSaveFile.Text = "保存文件";
            this.btnSaveFile.UseVisualStyleBackColor = true;
            this.btnSaveFile.Click += new System.EventHandler(this.btnSaveFile_Click);
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(13, 382);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(75, 23);
            this.btnOpen.TabIndex = 12;
            this.btnOpen.Text = "开门";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // btnCloseLock
            // 
            this.btnCloseLock.Location = new System.Drawing.Point(94, 382);
            this.btnCloseLock.Name = "btnCloseLock";
            this.btnCloseLock.Size = new System.Drawing.Size(75, 23);
            this.btnCloseLock.TabIndex = 13;
            this.btnCloseLock.Text = "关门";
            this.btnCloseLock.UseVisualStyleBackColor = true;
            this.btnCloseLock.Click += new System.EventHandler(this.btnCloseLock_Click);
            // 
            // tbSendDataLength
            // 
            this.tbSendDataLength.Location = new System.Drawing.Point(499, 384);
            this.tbSendDataLength.Name = "tbSendDataLength";
            this.tbSendDataLength.Size = new System.Drawing.Size(100, 21);
            this.tbSendDataLength.TabIndex = 14;
            // 
            // btnLoadQR1
            // 
            this.btnLoadQR1.Location = new System.Drawing.Point(94, 263);
            this.btnLoadQR1.Name = "btnLoadQR1";
            this.btnLoadQR1.Size = new System.Drawing.Size(94, 23);
            this.btnLoadQR1.TabIndex = 15;
            this.btnLoadQR1.Text = "加载二维码1";
            this.btnLoadQR1.UseVisualStyleBackColor = true;
            this.btnLoadQR1.Click += new System.EventHandler(this.btnLoadQR_Click);
            // 
            // btnLoadQR2
            // 
            this.btnLoadQR2.Location = new System.Drawing.Point(94, 292);
            this.btnLoadQR2.Name = "btnLoadQR2";
            this.btnLoadQR2.Size = new System.Drawing.Size(94, 23);
            this.btnLoadQR2.TabIndex = 16;
            this.btnLoadQR2.Text = "加载二维码2";
            this.btnLoadQR2.UseVisualStyleBackColor = true;
            this.btnLoadQR2.Click += new System.EventHandler(this.btnLoadQR2_Click);
            // 
            // btnLoadFile2
            // 
            this.btnLoadFile2.Location = new System.Drawing.Point(12, 292);
            this.btnLoadFile2.Name = "btnLoadFile2";
            this.btnLoadFile2.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile2.TabIndex = 17;
            this.btnLoadFile2.Text = "加载文件";
            this.btnLoadFile2.UseVisualStyleBackColor = true;
            this.btnLoadFile2.Click += new System.EventHandler(this.btnLoadFile2_Click);
            // 
            // btnLoadFile3
            // 
            this.btnLoadFile3.Location = new System.Drawing.Point(13, 321);
            this.btnLoadFile3.Name = "btnLoadFile3";
            this.btnLoadFile3.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile3.TabIndex = 18;
            this.btnLoadFile3.Text = "加载文件";
            this.btnLoadFile3.UseVisualStyleBackColor = true;
            this.btnLoadFile3.Click += new System.EventHandler(this.btnLoadFile3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(683, 417);
            this.Controls.Add(this.btnLoadFile3);
            this.Controls.Add(this.btnLoadFile2);
            this.Controls.Add(this.btnLoadQR2);
            this.Controls.Add(this.btnLoadQR1);
            this.Controls.Add(this.tbSendDataLength);
            this.Controls.Add(this.btnCloseLock);
            this.Controls.Add(this.btnOpen);
            this.Controls.Add(this.btnSaveFile);
            this.Controls.Add(this.btnLoadFile);
            this.Controls.Add(this.btnClear);
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
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnLoadFile;
        private System.Windows.Forms.Button btnSaveFile;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Button btnCloseLock;
        private System.Windows.Forms.TextBox tbSendDataLength;
        private System.Windows.Forms.Button btnLoadQR1;
        private System.Windows.Forms.Button btnLoadQR2;
        private System.Windows.Forms.Button btnLoadFile2;
        private System.Windows.Forms.Button btnLoadFile3;
    }
}

