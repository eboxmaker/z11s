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
            this.btnBroadcast = new System.Windows.Forms.Button();
            this.btnCloseBroadcast = new System.Windows.Forms.Button();
            this.btnAdSet = new System.Windows.Forms.Button();
            this.cbAdEnable = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbAdTime = new System.Windows.Forms.TextBox();
            this.tbAdInterval = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnModifyAdminPwd = new System.Windows.Forms.Button();
            this.tbAdminPwd = new System.Windows.Forms.TextBox();
            this.btnSyncTime = new System.Windows.Forms.Button();
            this.tbBroadcast = new System.Windows.Forms.TextBox();
            this.btnReadAdminPwd = new System.Windows.Forms.Button();
            this.btnGetID = new System.Windows.Forms.Button();
            this.btnGetDevName = new System.Windows.Forms.Button();
            this.tbDevName = new System.Windows.Forms.TextBox();
            this.btnSetDevName = new System.Windows.Forms.Button();
            this.btnConfirm = new System.Windows.Forms.Button();
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
            this.btnSendMSG.Location = new System.Drawing.Point(605, 408);
            this.btnSendMSG.Name = "btnSendMSG";
            this.btnSendMSG.Size = new System.Drawing.Size(75, 23);
            this.btnSendMSG.TabIndex = 7;
            this.btnSendMSG.Text = "发送数据";
            this.btnSendMSG.UseVisualStyleBackColor = true;
            this.btnSendMSG.Click += new System.EventHandler(this.btnSendMSG_Click);
            // 
            // RichSend
            // 
            this.RichSend.Location = new System.Drawing.Point(194, 235);
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
            this.btnLoadFile.Location = new System.Drawing.Point(12, 281);
            this.btnLoadFile.Name = "btnLoadFile";
            this.btnLoadFile.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile.TabIndex = 10;
            this.btnLoadFile.Text = "加载文件";
            this.btnLoadFile.UseVisualStyleBackColor = true;
            this.btnLoadFile.Click += new System.EventHandler(this.btnLoadFile_Click);
            // 
            // btnSaveFile
            // 
            this.btnSaveFile.Location = new System.Drawing.Point(12, 371);
            this.btnSaveFile.Name = "btnSaveFile";
            this.btnSaveFile.Size = new System.Drawing.Size(75, 23);
            this.btnSaveFile.TabIndex = 11;
            this.btnSaveFile.Text = "保存文件";
            this.btnSaveFile.UseVisualStyleBackColor = true;
            this.btnSaveFile.Click += new System.EventHandler(this.btnSaveFile_Click);
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(677, 12);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(75, 23);
            this.btnOpen.TabIndex = 12;
            this.btnOpen.Text = "开门";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // btnCloseLock
            // 
            this.btnCloseLock.Location = new System.Drawing.Point(787, 12);
            this.btnCloseLock.Name = "btnCloseLock";
            this.btnCloseLock.Size = new System.Drawing.Size(75, 23);
            this.btnCloseLock.TabIndex = 13;
            this.btnCloseLock.Text = "关门";
            this.btnCloseLock.UseVisualStyleBackColor = true;
            this.btnCloseLock.Click += new System.EventHandler(this.btnCloseLock_Click);
            // 
            // tbSendDataLength
            // 
            this.tbSendDataLength.Location = new System.Drawing.Point(499, 410);
            this.tbSendDataLength.Name = "tbSendDataLength";
            this.tbSendDataLength.Size = new System.Drawing.Size(100, 21);
            this.tbSendDataLength.TabIndex = 14;
            // 
            // btnLoadQR1
            // 
            this.btnLoadQR1.Location = new System.Drawing.Point(93, 281);
            this.btnLoadQR1.Name = "btnLoadQR1";
            this.btnLoadQR1.Size = new System.Drawing.Size(94, 23);
            this.btnLoadQR1.TabIndex = 15;
            this.btnLoadQR1.Text = "加载二维码1";
            this.btnLoadQR1.UseVisualStyleBackColor = true;
            this.btnLoadQR1.Click += new System.EventHandler(this.btnLoadQR_Click);
            // 
            // btnLoadQR2
            // 
            this.btnLoadQR2.Location = new System.Drawing.Point(93, 310);
            this.btnLoadQR2.Name = "btnLoadQR2";
            this.btnLoadQR2.Size = new System.Drawing.Size(94, 23);
            this.btnLoadQR2.TabIndex = 16;
            this.btnLoadQR2.Text = "加载二维码2";
            this.btnLoadQR2.UseVisualStyleBackColor = true;
            this.btnLoadQR2.Click += new System.EventHandler(this.btnLoadQR2_Click);
            // 
            // btnLoadFile2
            // 
            this.btnLoadFile2.Location = new System.Drawing.Point(11, 310);
            this.btnLoadFile2.Name = "btnLoadFile2";
            this.btnLoadFile2.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile2.TabIndex = 17;
            this.btnLoadFile2.Text = "加载文件";
            this.btnLoadFile2.UseVisualStyleBackColor = true;
            this.btnLoadFile2.Click += new System.EventHandler(this.btnLoadFile2_Click);
            // 
            // btnLoadFile3
            // 
            this.btnLoadFile3.Location = new System.Drawing.Point(12, 339);
            this.btnLoadFile3.Name = "btnLoadFile3";
            this.btnLoadFile3.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile3.TabIndex = 18;
            this.btnLoadFile3.Text = "加载文件";
            this.btnLoadFile3.UseVisualStyleBackColor = true;
            this.btnLoadFile3.Click += new System.EventHandler(this.btnLoadFile3_Click);
            // 
            // btnBroadcast
            // 
            this.btnBroadcast.Location = new System.Drawing.Point(681, 379);
            this.btnBroadcast.Name = "btnBroadcast";
            this.btnBroadcast.Size = new System.Drawing.Size(89, 23);
            this.btnBroadcast.TabIndex = 19;
            this.btnBroadcast.Text = "广播消息";
            this.btnBroadcast.UseVisualStyleBackColor = true;
            this.btnBroadcast.Click += new System.EventHandler(this.btnBroadcast_Click);
            // 
            // btnCloseBroadcast
            // 
            this.btnCloseBroadcast.Location = new System.Drawing.Point(791, 379);
            this.btnCloseBroadcast.Name = "btnCloseBroadcast";
            this.btnCloseBroadcast.Size = new System.Drawing.Size(75, 23);
            this.btnCloseBroadcast.TabIndex = 20;
            this.btnCloseBroadcast.Text = "关闭广播";
            this.btnCloseBroadcast.UseVisualStyleBackColor = true;
            this.btnCloseBroadcast.Click += new System.EventHandler(this.btnCloseBroadcast_Click);
            // 
            // btnAdSet
            // 
            this.btnAdSet.Location = new System.Drawing.Point(681, 197);
            this.btnAdSet.Name = "btnAdSet";
            this.btnAdSet.Size = new System.Drawing.Size(75, 23);
            this.btnAdSet.TabIndex = 21;
            this.btnAdSet.Text = "广告设置";
            this.btnAdSet.UseVisualStyleBackColor = true;
            this.btnAdSet.Click += new System.EventHandler(this.button1_Click);
            // 
            // cbAdEnable
            // 
            this.cbAdEnable.AutoSize = true;
            this.cbAdEnable.Location = new System.Drawing.Point(773, 201);
            this.cbAdEnable.Name = "cbAdEnable";
            this.cbAdEnable.Size = new System.Drawing.Size(78, 16);
            this.cbAdEnable.TabIndex = 22;
            this.cbAdEnable.Text = "checkBox1";
            this.cbAdEnable.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(681, 235);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 23;
            this.label1.Text = "进入广告时间：";
            // 
            // tbAdTime
            // 
            this.tbAdTime.Location = new System.Drawing.Point(768, 226);
            this.tbAdTime.Name = "tbAdTime";
            this.tbAdTime.Size = new System.Drawing.Size(100, 21);
            this.tbAdTime.TabIndex = 24;
            this.tbAdTime.Text = "10";
            // 
            // tbAdInterval
            // 
            this.tbAdInterval.Location = new System.Drawing.Point(768, 253);
            this.tbAdInterval.Name = "tbAdInterval";
            this.tbAdInterval.Size = new System.Drawing.Size(100, 21);
            this.tbAdInterval.TabIndex = 26;
            this.tbAdInterval.Text = "3";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(681, 262);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 12);
            this.label2.TabIndex = 25;
            this.label2.Text = "广告轮播间隔：";
            // 
            // btnModifyAdminPwd
            // 
            this.btnModifyAdminPwd.Location = new System.Drawing.Point(683, 308);
            this.btnModifyAdminPwd.Name = "btnModifyAdminPwd";
            this.btnModifyAdminPwd.Size = new System.Drawing.Size(73, 23);
            this.btnModifyAdminPwd.TabIndex = 27;
            this.btnModifyAdminPwd.Text = "设管码";
            this.btnModifyAdminPwd.UseVisualStyleBackColor = true;
            this.btnModifyAdminPwd.Click += new System.EventHandler(this.btnModifyAdminPwd_Click);
            // 
            // tbAdminPwd
            // 
            this.tbAdminPwd.Location = new System.Drawing.Point(683, 336);
            this.tbAdminPwd.Name = "tbAdminPwd";
            this.tbAdminPwd.Size = new System.Drawing.Size(185, 21);
            this.tbAdminPwd.TabIndex = 28;
            this.tbAdminPwd.Text = "123456";
            // 
            // btnSyncTime
            // 
            this.btnSyncTime.Location = new System.Drawing.Point(679, 41);
            this.btnSyncTime.Name = "btnSyncTime";
            this.btnSyncTime.Size = new System.Drawing.Size(75, 23);
            this.btnSyncTime.TabIndex = 29;
            this.btnSyncTime.Text = "同步时间";
            this.btnSyncTime.UseVisualStyleBackColor = true;
            this.btnSyncTime.Click += new System.EventHandler(this.btnSyncTime_Click);
            // 
            // tbBroadcast
            // 
            this.tbBroadcast.Location = new System.Drawing.Point(681, 408);
            this.tbBroadcast.Name = "tbBroadcast";
            this.tbBroadcast.Size = new System.Drawing.Size(187, 21);
            this.tbBroadcast.TabIndex = 30;
            this.tbBroadcast.Text = "通知：今天是考试所有课程已经停止";
            // 
            // btnReadAdminPwd
            // 
            this.btnReadAdminPwd.Location = new System.Drawing.Point(791, 308);
            this.btnReadAdminPwd.Name = "btnReadAdminPwd";
            this.btnReadAdminPwd.Size = new System.Drawing.Size(73, 23);
            this.btnReadAdminPwd.TabIndex = 31;
            this.btnReadAdminPwd.Text = "读管码";
            this.btnReadAdminPwd.UseVisualStyleBackColor = true;
            this.btnReadAdminPwd.Click += new System.EventHandler(this.btnReadAdminPwd_Click);
            // 
            // btnGetID
            // 
            this.btnGetID.Location = new System.Drawing.Point(677, 96);
            this.btnGetID.Name = "btnGetID";
            this.btnGetID.Size = new System.Drawing.Size(75, 23);
            this.btnGetID.TabIndex = 32;
            this.btnGetID.Text = "查询ID";
            this.btnGetID.UseVisualStyleBackColor = true;
            this.btnGetID.Click += new System.EventHandler(this.btnGetID_Click);
            // 
            // btnGetDevName
            // 
            this.btnGetDevName.Location = new System.Drawing.Point(787, 125);
            this.btnGetDevName.Name = "btnGetDevName";
            this.btnGetDevName.Size = new System.Drawing.Size(75, 23);
            this.btnGetDevName.TabIndex = 33;
            this.btnGetDevName.Text = "查询名称";
            this.btnGetDevName.UseVisualStyleBackColor = true;
            this.btnGetDevName.Click += new System.EventHandler(this.btnGetDevName_Click);
            // 
            // tbDevName
            // 
            this.tbDevName.Location = new System.Drawing.Point(681, 154);
            this.tbDevName.Name = "tbDevName";
            this.tbDevName.Size = new System.Drawing.Size(181, 21);
            this.tbDevName.TabIndex = 34;
            this.tbDevName.Text = "软件一";
            // 
            // btnSetDevName
            // 
            this.btnSetDevName.Location = new System.Drawing.Point(677, 125);
            this.btnSetDevName.Name = "btnSetDevName";
            this.btnSetDevName.Size = new System.Drawing.Size(75, 23);
            this.btnSetDevName.TabIndex = 35;
            this.btnSetDevName.Text = "设置名称";
            this.btnSetDevName.UseVisualStyleBackColor = true;
            this.btnSetDevName.Click += new System.EventHandler(this.btnSetDevName_Click);
            // 
            // btnConfirm
            // 
            this.btnConfirm.Location = new System.Drawing.Point(787, 96);
            this.btnConfirm.Name = "btnConfirm";
            this.btnConfirm.Size = new System.Drawing.Size(75, 23);
            this.btnConfirm.TabIndex = 36;
            this.btnConfirm.Text = "请求认证";
            this.btnConfirm.UseVisualStyleBackColor = true;
            this.btnConfirm.Click += new System.EventHandler(this.btnConfirm_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(876, 436);
            this.Controls.Add(this.btnConfirm);
            this.Controls.Add(this.btnSetDevName);
            this.Controls.Add(this.tbDevName);
            this.Controls.Add(this.btnGetDevName);
            this.Controls.Add(this.btnGetID);
            this.Controls.Add(this.btnReadAdminPwd);
            this.Controls.Add(this.tbBroadcast);
            this.Controls.Add(this.btnSyncTime);
            this.Controls.Add(this.tbAdminPwd);
            this.Controls.Add(this.btnModifyAdminPwd);
            this.Controls.Add(this.tbAdInterval);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbAdTime);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbAdEnable);
            this.Controls.Add(this.btnAdSet);
            this.Controls.Add(this.btnCloseBroadcast);
            this.Controls.Add(this.btnBroadcast);
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
        private System.Windows.Forms.Button btnBroadcast;
        private System.Windows.Forms.Button btnCloseBroadcast;
        private System.Windows.Forms.Button btnAdSet;
        private System.Windows.Forms.CheckBox cbAdEnable;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbAdTime;
        private System.Windows.Forms.TextBox tbAdInterval;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnModifyAdminPwd;
        private System.Windows.Forms.TextBox tbAdminPwd;
        private System.Windows.Forms.Button btnSyncTime;
        private System.Windows.Forms.TextBox tbBroadcast;
        private System.Windows.Forms.Button btnReadAdminPwd;
        private System.Windows.Forms.Button btnGetID;
        private System.Windows.Forms.Button btnGetDevName;
        private System.Windows.Forms.TextBox tbDevName;
        private System.Windows.Forms.Button btnSetDevName;
        private System.Windows.Forms.Button btnConfirm;
    }
}

