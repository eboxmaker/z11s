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
            this.btnDeletAdPic = new System.Windows.Forms.Button();
            this.btnSetHeartbeatInterval = new System.Windows.Forms.Button();
            this.tbHeartInterval = new System.Windows.Forms.TextBox();
            this.btnReadDoorState = new System.Windows.Forms.Button();
            this.btnReadHearInterval = new System.Windows.Forms.Button();
            this.tbAdName = new System.Windows.Forms.TextBox();
            this.btnSetDoorPwd = new System.Windows.Forms.Button();
            this.tbDoorPwd = new System.Windows.Forms.TextBox();
            this.btnReadDoorPwd = new System.Windows.Forms.Button();
            this.btnReadBroadcast = new System.Windows.Forms.Button();
            this.tbQRCodeName = new System.Windows.Forms.TextBox();
            this.btnDelQRCode = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.tbAesTest = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.tbENcoderLen = new System.Windows.Forms.TextBox();
            this.btnGetKeyHex = new System.Windows.Forms.Button();
            this.btnGetIVHex = new System.Windows.Forms.Button();
            this.btnSendCourseInfo = new System.Windows.Forms.Button();
            this.btnReadVersion = new System.Windows.Forms.Button();
            this.btnReboot = new System.Windows.Forms.Button();
            this.btnSendFile = new System.Windows.Forms.Button();
            this.tbDownLoadUrl = new System.Windows.Forms.TextBox();
            this.tbDownLoadPort = new System.Windows.Forms.TextBox();
            this.btnAdClear = new System.Windows.Forms.Button();
            this.btnAdRead = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.btnSendPersonTemp = new System.Windows.Forms.Button();
            this.btnSendPerson = new System.Windows.Forms.Button();
            this.tbPersonId = new System.Windows.Forms.TextBox();
            this.button5 = new System.Windows.Forms.Button();
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
            // RichRecv
            // 
            this.RichRecv.Location = new System.Drawing.Point(139, 12);
            this.RichRecv.Name = "RichRecv";
            this.RichRecv.Size = new System.Drawing.Size(477, 219);
            this.RichRecv.TabIndex = 6;
            this.RichRecv.Text = "";
            // 
            // btnSendMSG
            // 
            this.btnSendMSG.Location = new System.Drawing.Point(605, 523);
            this.btnSendMSG.Name = "btnSendMSG";
            this.btnSendMSG.Size = new System.Drawing.Size(75, 23);
            this.btnSendMSG.TabIndex = 7;
            this.btnSendMSG.Text = "发送数据";
            this.btnSendMSG.UseVisualStyleBackColor = true;
            this.btnSendMSG.Click += new System.EventHandler(this.btnSendMSG_Click);
            // 
            // RichSend
            // 
            this.RichSend.Location = new System.Drawing.Point(139, 408);
            this.RichSend.Name = "RichSend";
            this.RichSend.Size = new System.Drawing.Size(477, 109);
            this.RichSend.TabIndex = 8;
            this.RichSend.Text = "";
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(519, 352);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(97, 23);
            this.btnClear.TabIndex = 9;
            this.btnClear.Text = "清空数据";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnLoadFile
            // 
            this.btnLoadFile.Location = new System.Drawing.Point(12, 396);
            this.btnLoadFile.Name = "btnLoadFile";
            this.btnLoadFile.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile.TabIndex = 10;
            this.btnLoadFile.Text = "加载文件";
            this.btnLoadFile.UseVisualStyleBackColor = true;
            this.btnLoadFile.Click += new System.EventHandler(this.btnLoadFile_Click);
            // 
            // btnSaveFile
            // 
            this.btnSaveFile.Location = new System.Drawing.Point(12, 486);
            this.btnSaveFile.Name = "btnSaveFile";
            this.btnSaveFile.Size = new System.Drawing.Size(75, 23);
            this.btnSaveFile.TabIndex = 11;
            this.btnSaveFile.Text = "保存文件";
            this.btnSaveFile.UseVisualStyleBackColor = true;
            this.btnSaveFile.Click += new System.EventHandler(this.btnSaveFile_Click);
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(622, 12);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(75, 23);
            this.btnOpen.TabIndex = 12;
            this.btnOpen.Text = "开门";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // btnCloseLock
            // 
            this.btnCloseLock.Location = new System.Drawing.Point(703, 12);
            this.btnCloseLock.Name = "btnCloseLock";
            this.btnCloseLock.Size = new System.Drawing.Size(75, 23);
            this.btnCloseLock.TabIndex = 13;
            this.btnCloseLock.Text = "关门";
            this.btnCloseLock.UseVisualStyleBackColor = true;
            this.btnCloseLock.Click += new System.EventHandler(this.btnCloseLock_Click);
            // 
            // tbSendDataLength
            // 
            this.tbSendDataLength.Location = new System.Drawing.Point(499, 525);
            this.tbSendDataLength.Name = "tbSendDataLength";
            this.tbSendDataLength.Size = new System.Drawing.Size(100, 21);
            this.tbSendDataLength.TabIndex = 14;
            // 
            // btnLoadQR1
            // 
            this.btnLoadQR1.Location = new System.Drawing.Point(13, 208);
            this.btnLoadQR1.Name = "btnLoadQR1";
            this.btnLoadQR1.Size = new System.Drawing.Size(94, 23);
            this.btnLoadQR1.TabIndex = 15;
            this.btnLoadQR1.Text = "加载二维码1";
            this.btnLoadQR1.UseVisualStyleBackColor = true;
            this.btnLoadQR1.Click += new System.EventHandler(this.btnLoadQR_Click);
            // 
            // btnLoadQR2
            // 
            this.btnLoadQR2.Location = new System.Drawing.Point(13, 233);
            this.btnLoadQR2.Name = "btnLoadQR2";
            this.btnLoadQR2.Size = new System.Drawing.Size(94, 23);
            this.btnLoadQR2.TabIndex = 16;
            this.btnLoadQR2.Text = "加载二维码1";
            this.btnLoadQR2.UseVisualStyleBackColor = true;
            this.btnLoadQR2.Click += new System.EventHandler(this.btnLoadQR2_Click);
            // 
            // btnLoadFile2
            // 
            this.btnLoadFile2.Location = new System.Drawing.Point(11, 425);
            this.btnLoadFile2.Name = "btnLoadFile2";
            this.btnLoadFile2.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile2.TabIndex = 17;
            this.btnLoadFile2.Text = "加载文件";
            this.btnLoadFile2.UseVisualStyleBackColor = true;
            this.btnLoadFile2.Click += new System.EventHandler(this.btnLoadFile2_Click);
            // 
            // btnLoadFile3
            // 
            this.btnLoadFile3.Location = new System.Drawing.Point(12, 454);
            this.btnLoadFile3.Name = "btnLoadFile3";
            this.btnLoadFile3.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile3.TabIndex = 18;
            this.btnLoadFile3.Text = "加载文件";
            this.btnLoadFile3.UseVisualStyleBackColor = true;
            this.btnLoadFile3.Click += new System.EventHandler(this.btnLoadFile3_Click);
            // 
            // btnBroadcast
            // 
            this.btnBroadcast.Location = new System.Drawing.Point(636, 494);
            this.btnBroadcast.Name = "btnBroadcast";
            this.btnBroadcast.Size = new System.Drawing.Size(89, 23);
            this.btnBroadcast.TabIndex = 19;
            this.btnBroadcast.Text = "广播消息";
            this.btnBroadcast.UseVisualStyleBackColor = true;
            this.btnBroadcast.Click += new System.EventHandler(this.btnBroadcast_Click);
            // 
            // btnCloseBroadcast
            // 
            this.btnCloseBroadcast.Location = new System.Drawing.Point(731, 494);
            this.btnCloseBroadcast.Name = "btnCloseBroadcast";
            this.btnCloseBroadcast.Size = new System.Drawing.Size(75, 23);
            this.btnCloseBroadcast.TabIndex = 20;
            this.btnCloseBroadcast.Text = "关闭广播";
            this.btnCloseBroadcast.UseVisualStyleBackColor = true;
            this.btnCloseBroadcast.Click += new System.EventHandler(this.btnCloseBroadcast_Click);
            // 
            // btnAdSet
            // 
            this.btnAdSet.Location = new System.Drawing.Point(642, 411);
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
            this.cbAdEnable.Location = new System.Drawing.Point(734, 415);
            this.cbAdEnable.Name = "cbAdEnable";
            this.cbAdEnable.Size = new System.Drawing.Size(78, 16);
            this.cbAdEnable.TabIndex = 22;
            this.cbAdEnable.Text = "checkBox1";
            this.cbAdEnable.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(642, 449);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 23;
            this.label1.Text = "进入广告时间：";
            // 
            // tbAdTime
            // 
            this.tbAdTime.Location = new System.Drawing.Point(729, 440);
            this.tbAdTime.Name = "tbAdTime";
            this.tbAdTime.Size = new System.Drawing.Size(100, 21);
            this.tbAdTime.TabIndex = 24;
            this.tbAdTime.Text = "10";
            // 
            // btnModifyAdminPwd
            // 
            this.btnModifyAdminPwd.Location = new System.Drawing.Point(814, 467);
            this.btnModifyAdminPwd.Name = "btnModifyAdminPwd";
            this.btnModifyAdminPwd.Size = new System.Drawing.Size(42, 23);
            this.btnModifyAdminPwd.TabIndex = 27;
            this.btnModifyAdminPwd.Text = "设置";
            this.btnModifyAdminPwd.UseVisualStyleBackColor = true;
            this.btnModifyAdminPwd.Click += new System.EventHandler(this.btnModifyAdminPwd_Click);
            // 
            // tbAdminPwd
            // 
            this.tbAdminPwd.Location = new System.Drawing.Point(640, 467);
            this.tbAdminPwd.Name = "tbAdminPwd";
            this.tbAdminPwd.Size = new System.Drawing.Size(168, 21);
            this.tbAdminPwd.TabIndex = 28;
            this.tbAdminPwd.Text = "123456";
            // 
            // btnSyncTime
            // 
            this.btnSyncTime.Location = new System.Drawing.Point(784, 39);
            this.btnSyncTime.Name = "btnSyncTime";
            this.btnSyncTime.Size = new System.Drawing.Size(75, 23);
            this.btnSyncTime.TabIndex = 29;
            this.btnSyncTime.Text = "同步时间";
            this.btnSyncTime.UseVisualStyleBackColor = true;
            this.btnSyncTime.Click += new System.EventHandler(this.btnSyncTime_Click);
            // 
            // tbBroadcast
            // 
            this.tbBroadcast.Location = new System.Drawing.Point(691, 523);
            this.tbBroadcast.Name = "tbBroadcast";
            this.tbBroadcast.Size = new System.Drawing.Size(301, 21);
            this.tbBroadcast.TabIndex = 30;
            this.tbBroadcast.Text = "通知：今天是考试所有课程已经停止";
            // 
            // btnReadAdminPwd
            // 
            this.btnReadAdminPwd.Location = new System.Drawing.Point(865, 467);
            this.btnReadAdminPwd.Name = "btnReadAdminPwd";
            this.btnReadAdminPwd.Size = new System.Drawing.Size(74, 23);
            this.btnReadAdminPwd.TabIndex = 31;
            this.btnReadAdminPwd.Text = "读取管密码";
            this.btnReadAdminPwd.UseVisualStyleBackColor = true;
            this.btnReadAdminPwd.Click += new System.EventHandler(this.btnReadAdminPwd_Click);
            // 
            // btnGetID
            // 
            this.btnGetID.Location = new System.Drawing.Point(622, 38);
            this.btnGetID.Name = "btnGetID";
            this.btnGetID.Size = new System.Drawing.Size(75, 23);
            this.btnGetID.TabIndex = 32;
            this.btnGetID.Text = "查询ID";
            this.btnGetID.UseVisualStyleBackColor = true;
            this.btnGetID.Click += new System.EventHandler(this.btnGetID_Click);
            // 
            // btnGetDevName
            // 
            this.btnGetDevName.Location = new System.Drawing.Point(865, 239);
            this.btnGetDevName.Name = "btnGetDevName";
            this.btnGetDevName.Size = new System.Drawing.Size(75, 23);
            this.btnGetDevName.TabIndex = 33;
            this.btnGetDevName.Text = "查询名称";
            this.btnGetDevName.UseVisualStyleBackColor = true;
            this.btnGetDevName.Click += new System.EventHandler(this.btnGetDevName_Click);
            // 
            // tbDevName
            // 
            this.tbDevName.Location = new System.Drawing.Point(634, 241);
            this.tbDevName.Name = "tbDevName";
            this.tbDevName.Size = new System.Drawing.Size(139, 21);
            this.tbDevName.TabIndex = 34;
            this.tbDevName.Text = "软件一";
            // 
            // btnSetDevName
            // 
            this.btnSetDevName.Location = new System.Drawing.Point(784, 239);
            this.btnSetDevName.Name = "btnSetDevName";
            this.btnSetDevName.Size = new System.Drawing.Size(75, 23);
            this.btnSetDevName.TabIndex = 35;
            this.btnSetDevName.Text = "设置名称";
            this.btnSetDevName.UseVisualStyleBackColor = true;
            this.btnSetDevName.Click += new System.EventHandler(this.btnSetDevName_Click);
            // 
            // btnConfirm
            // 
            this.btnConfirm.Location = new System.Drawing.Point(703, 38);
            this.btnConfirm.Name = "btnConfirm";
            this.btnConfirm.Size = new System.Drawing.Size(75, 23);
            this.btnConfirm.TabIndex = 36;
            this.btnConfirm.Text = "请求认证";
            this.btnConfirm.UseVisualStyleBackColor = true;
            this.btnConfirm.Click += new System.EventHandler(this.btnConfirm_Click);
            // 
            // btnDeletAdPic
            // 
            this.btnDeletAdPic.Location = new System.Drawing.Point(779, 158);
            this.btnDeletAdPic.Name = "btnDeletAdPic";
            this.btnDeletAdPic.Size = new System.Drawing.Size(156, 23);
            this.btnDeletAdPic.TabIndex = 37;
            this.btnDeletAdPic.Text = "删除广告文件";
            this.btnDeletAdPic.UseVisualStyleBackColor = true;
            this.btnDeletAdPic.Click += new System.EventHandler(this.btnDeletAdPic_Click);
            this.btnDeletAdPic.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btnDeletAdPic_MouseUp);
            // 
            // btnSetHeartbeatInterval
            // 
            this.btnSetHeartbeatInterval.Location = new System.Drawing.Point(783, 210);
            this.btnSetHeartbeatInterval.Name = "btnSetHeartbeatInterval";
            this.btnSetHeartbeatInterval.Size = new System.Drawing.Size(75, 23);
            this.btnSetHeartbeatInterval.TabIndex = 38;
            this.btnSetHeartbeatInterval.Text = "设置心跳";
            this.btnSetHeartbeatInterval.UseVisualStyleBackColor = true;
            this.btnSetHeartbeatInterval.Click += new System.EventHandler(this.btnSetHeartbeatInterval_Click);
            // 
            // tbHeartInterval
            // 
            this.tbHeartInterval.Location = new System.Drawing.Point(634, 210);
            this.tbHeartInterval.Name = "tbHeartInterval";
            this.tbHeartInterval.Size = new System.Drawing.Size(139, 21);
            this.tbHeartInterval.TabIndex = 39;
            this.tbHeartInterval.Text = "10";
            // 
            // btnReadDoorState
            // 
            this.btnReadDoorState.Location = new System.Drawing.Point(784, 10);
            this.btnReadDoorState.Name = "btnReadDoorState";
            this.btnReadDoorState.Size = new System.Drawing.Size(75, 23);
            this.btnReadDoorState.TabIndex = 40;
            this.btnReadDoorState.Text = "读取门";
            this.btnReadDoorState.UseVisualStyleBackColor = true;
            this.btnReadDoorState.Click += new System.EventHandler(this.btnReadDoorState_Click);
            // 
            // btnReadHearInterval
            // 
            this.btnReadHearInterval.Location = new System.Drawing.Point(864, 210);
            this.btnReadHearInterval.Name = "btnReadHearInterval";
            this.btnReadHearInterval.Size = new System.Drawing.Size(75, 23);
            this.btnReadHearInterval.TabIndex = 41;
            this.btnReadHearInterval.Text = "读取心跳";
            this.btnReadHearInterval.UseVisualStyleBackColor = true;
            this.btnReadHearInterval.Click += new System.EventHandler(this.btnReadHearInterval_Click);
            // 
            // tbAdName
            // 
            this.tbAdName.Location = new System.Drawing.Point(630, 158);
            this.tbAdName.Name = "tbAdName";
            this.tbAdName.Size = new System.Drawing.Size(139, 21);
            this.tbAdName.TabIndex = 42;
            this.tbAdName.Text = "1.jpg";
            // 
            // btnSetDoorPwd
            // 
            this.btnSetDoorPwd.Location = new System.Drawing.Point(783, 268);
            this.btnSetDoorPwd.Name = "btnSetDoorPwd";
            this.btnSetDoorPwd.Size = new System.Drawing.Size(75, 23);
            this.btnSetDoorPwd.TabIndex = 44;
            this.btnSetDoorPwd.Text = "设置门密码";
            this.btnSetDoorPwd.UseVisualStyleBackColor = true;
            this.btnSetDoorPwd.Click += new System.EventHandler(this.btnSetDoorPwd_Click);
            // 
            // tbDoorPwd
            // 
            this.tbDoorPwd.Location = new System.Drawing.Point(634, 270);
            this.tbDoorPwd.Name = "tbDoorPwd";
            this.tbDoorPwd.Size = new System.Drawing.Size(139, 21);
            this.tbDoorPwd.TabIndex = 43;
            this.tbDoorPwd.Text = "123456";
            // 
            // btnReadDoorPwd
            // 
            this.btnReadDoorPwd.Location = new System.Drawing.Point(865, 268);
            this.btnReadDoorPwd.Name = "btnReadDoorPwd";
            this.btnReadDoorPwd.Size = new System.Drawing.Size(75, 23);
            this.btnReadDoorPwd.TabIndex = 45;
            this.btnReadDoorPwd.Text = "读取门密码";
            this.btnReadDoorPwd.UseVisualStyleBackColor = true;
            this.btnReadDoorPwd.Click += new System.EventHandler(this.btnReadDoorPwd_Click);
            // 
            // btnReadBroadcast
            // 
            this.btnReadBroadcast.Location = new System.Drawing.Point(827, 494);
            this.btnReadBroadcast.Name = "btnReadBroadcast";
            this.btnReadBroadcast.Size = new System.Drawing.Size(89, 23);
            this.btnReadBroadcast.TabIndex = 46;
            this.btnReadBroadcast.Text = "读取广播";
            this.btnReadBroadcast.UseVisualStyleBackColor = true;
            this.btnReadBroadcast.Click += new System.EventHandler(this.btnReadBroadcast_Click);
            // 
            // tbQRCodeName
            // 
            this.tbQRCodeName.Location = new System.Drawing.Point(630, 181);
            this.tbQRCodeName.Name = "tbQRCodeName";
            this.tbQRCodeName.Size = new System.Drawing.Size(139, 21);
            this.tbQRCodeName.TabIndex = 48;
            this.tbQRCodeName.Text = "qr.jpg";
            // 
            // btnDelQRCode
            // 
            this.btnDelQRCode.Location = new System.Drawing.Point(779, 181);
            this.btnDelQRCode.Name = "btnDelQRCode";
            this.btnDelQRCode.Size = new System.Drawing.Size(156, 23);
            this.btnDelQRCode.TabIndex = 47;
            this.btnDelQRCode.Text = "删除二维码";
            this.btnDelQRCode.UseVisualStyleBackColor = true;
            this.btnDelQRCode.Click += new System.EventHandler(this.btnDelQRCode_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(139, 348);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 49;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // tbAesTest
            // 
            this.tbAesTest.Location = new System.Drawing.Point(139, 379);
            this.tbAesTest.Name = "tbAesTest";
            this.tbAesTest.Size = new System.Drawing.Size(477, 21);
            this.tbAesTest.TabIndex = 50;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(220, 350);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 51;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // tbENcoderLen
            // 
            this.tbENcoderLen.Location = new System.Drawing.Point(301, 352);
            this.tbENcoderLen.Name = "tbENcoderLen";
            this.tbENcoderLen.Size = new System.Drawing.Size(64, 21);
            this.tbENcoderLen.TabIndex = 52;
            // 
            // btnGetKeyHex
            // 
            this.btnGetKeyHex.Location = new System.Drawing.Point(371, 350);
            this.btnGetKeyHex.Name = "btnGetKeyHex";
            this.btnGetKeyHex.Size = new System.Drawing.Size(75, 23);
            this.btnGetKeyHex.TabIndex = 54;
            this.btnGetKeyHex.Text = "btnGetKeyHex";
            this.btnGetKeyHex.UseVisualStyleBackColor = true;
            this.btnGetKeyHex.Click += new System.EventHandler(this.btnGetKeyHex_Click);
            // 
            // btnGetIVHex
            // 
            this.btnGetIVHex.Location = new System.Drawing.Point(452, 352);
            this.btnGetIVHex.Name = "btnGetIVHex";
            this.btnGetIVHex.Size = new System.Drawing.Size(61, 23);
            this.btnGetIVHex.TabIndex = 53;
            this.btnGetIVHex.Text = "button4";
            this.btnGetIVHex.UseVisualStyleBackColor = true;
            this.btnGetIVHex.Click += new System.EventHandler(this.btnGetIVHex_Click);
            // 
            // btnSendCourseInfo
            // 
            this.btnSendCourseInfo.Location = new System.Drawing.Point(623, 65);
            this.btnSendCourseInfo.Name = "btnSendCourseInfo";
            this.btnSendCourseInfo.Size = new System.Drawing.Size(74, 23);
            this.btnSendCourseInfo.TabIndex = 55;
            this.btnSendCourseInfo.Text = "课程信息";
            this.btnSendCourseInfo.UseVisualStyleBackColor = true;
            this.btnSendCourseInfo.Click += new System.EventHandler(this.btnSendCourseInfo_Click);
            // 
            // btnReadVersion
            // 
            this.btnReadVersion.Location = new System.Drawing.Point(865, 10);
            this.btnReadVersion.Name = "btnReadVersion";
            this.btnReadVersion.Size = new System.Drawing.Size(75, 23);
            this.btnReadVersion.TabIndex = 56;
            this.btnReadVersion.Text = "查询版本";
            this.btnReadVersion.UseVisualStyleBackColor = true;
            this.btnReadVersion.Click += new System.EventHandler(this.btnReadVersion_Click);
            // 
            // btnReboot
            // 
            this.btnReboot.Location = new System.Drawing.Point(865, 38);
            this.btnReboot.Name = "btnReboot";
            this.btnReboot.Size = new System.Drawing.Size(75, 23);
            this.btnReboot.TabIndex = 57;
            this.btnReboot.Text = "重启";
            this.btnReboot.UseVisualStyleBackColor = true;
            this.btnReboot.Click += new System.EventHandler(this.btnReboot_Click);
            // 
            // btnSendFile
            // 
            this.btnSendFile.Location = new System.Drawing.Point(626, 94);
            this.btnSendFile.Name = "btnSendFile";
            this.btnSendFile.Size = new System.Drawing.Size(75, 23);
            this.btnSendFile.TabIndex = 58;
            this.btnSendFile.Text = "系统更新";
            this.btnSendFile.UseVisualStyleBackColor = true;
            this.btnSendFile.Click += new System.EventHandler(this.btnSendFile_Click);
            // 
            // tbDownLoadUrl
            // 
            this.tbDownLoadUrl.Location = new System.Drawing.Point(630, 123);
            this.tbDownLoadUrl.Name = "tbDownLoadUrl";
            this.tbDownLoadUrl.Size = new System.Drawing.Size(216, 21);
            this.tbDownLoadUrl.TabIndex = 59;
            this.tbDownLoadUrl.Text = "10.176.2.176/download/update.img";
            // 
            // tbDownLoadPort
            // 
            this.tbDownLoadPort.Location = new System.Drawing.Point(884, 123);
            this.tbDownLoadPort.Name = "tbDownLoadPort";
            this.tbDownLoadPort.Size = new System.Drawing.Size(51, 21);
            this.tbDownLoadPort.TabIndex = 60;
            this.tbDownLoadPort.Text = "8081";
            // 
            // btnAdClear
            // 
            this.btnAdClear.Location = new System.Drawing.Point(874, 408);
            this.btnAdClear.Name = "btnAdClear";
            this.btnAdClear.Size = new System.Drawing.Size(75, 23);
            this.btnAdClear.TabIndex = 61;
            this.btnAdClear.Text = "清空广告";
            this.btnAdClear.UseVisualStyleBackColor = true;
            this.btnAdClear.Click += new System.EventHandler(this.btnAdClear_Click);
            // 
            // btnAdRead
            // 
            this.btnAdRead.Location = new System.Drawing.Point(875, 437);
            this.btnAdRead.Name = "btnAdRead";
            this.btnAdRead.Size = new System.Drawing.Size(75, 23);
            this.btnAdRead.TabIndex = 62;
            this.btnAdRead.Text = "读取广告";
            this.btnAdRead.UseVisualStyleBackColor = true;
            this.btnAdRead.Click += new System.EventHandler(this.btnAdRead_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(785, 68);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(74, 23);
            this.button3.TabIndex = 63;
            this.button3.Text = "发送课程表";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(865, 68);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(74, 23);
            this.button4.TabIndex = 64;
            this.button4.Text = "发送课程表";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // btnSendPersonTemp
            // 
            this.btnSendPersonTemp.Location = new System.Drawing.Point(716, 326);
            this.btnSendPersonTemp.Name = "btnSendPersonTemp";
            this.btnSendPersonTemp.Size = new System.Drawing.Size(74, 23);
            this.btnSendPersonTemp.TabIndex = 65;
            this.btnSendPersonTemp.Text = "下发临时人";
            this.btnSendPersonTemp.UseVisualStyleBackColor = true;
            this.btnSendPersonTemp.Click += new System.EventHandler(this.btnSendPerson_Click);
            // 
            // btnSendPerson
            // 
            this.btnSendPerson.Location = new System.Drawing.Point(636, 326);
            this.btnSendPerson.Name = "btnSendPerson";
            this.btnSendPerson.Size = new System.Drawing.Size(74, 23);
            this.btnSendPerson.TabIndex = 66;
            this.btnSendPerson.Text = "下发固定人";
            this.btnSendPerson.UseVisualStyleBackColor = true;
            this.btnSendPerson.Click += new System.EventHandler(this.btnSendPerson_Click_1);
            // 
            // tbPersonId
            // 
            this.tbPersonId.Location = new System.Drawing.Point(635, 299);
            this.tbPersonId.Name = "tbPersonId";
            this.tbPersonId.Size = new System.Drawing.Size(155, 21);
            this.tbPersonId.TabIndex = 67;
            this.tbPersonId.Text = "1";
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(796, 326);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(74, 23);
            this.button5.TabIndex = 68;
            this.button5.Text = "删除固定人";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(995, 556);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.tbPersonId);
            this.Controls.Add(this.btnSendPerson);
            this.Controls.Add(this.btnSendPersonTemp);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.btnAdRead);
            this.Controls.Add(this.btnAdClear);
            this.Controls.Add(this.tbDownLoadPort);
            this.Controls.Add(this.tbDownLoadUrl);
            this.Controls.Add(this.btnSendFile);
            this.Controls.Add(this.btnReboot);
            this.Controls.Add(this.btnReadVersion);
            this.Controls.Add(this.btnSendCourseInfo);
            this.Controls.Add(this.btnGetKeyHex);
            this.Controls.Add(this.btnGetIVHex);
            this.Controls.Add(this.tbENcoderLen);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.tbAesTest);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tbQRCodeName);
            this.Controls.Add(this.btnDelQRCode);
            this.Controls.Add(this.btnReadBroadcast);
            this.Controls.Add(this.btnReadDoorPwd);
            this.Controls.Add(this.btnSetDoorPwd);
            this.Controls.Add(this.tbDoorPwd);
            this.Controls.Add(this.tbAdName);
            this.Controls.Add(this.btnReadHearInterval);
            this.Controls.Add(this.btnReadDoorState);
            this.Controls.Add(this.tbHeartInterval);
            this.Controls.Add(this.btnSetHeartbeatInterval);
            this.Controls.Add(this.btnDeletAdPic);
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
        private System.Windows.Forms.Button btnDeletAdPic;
        private System.Windows.Forms.Button btnSetHeartbeatInterval;
        private System.Windows.Forms.TextBox tbHeartInterval;
        private System.Windows.Forms.Button btnReadDoorState;
        private System.Windows.Forms.Button btnReadHearInterval;
        private System.Windows.Forms.TextBox tbAdName;
        private System.Windows.Forms.Button btnSetDoorPwd;
        private System.Windows.Forms.TextBox tbDoorPwd;
        private System.Windows.Forms.Button btnReadDoorPwd;
        private System.Windows.Forms.Button btnReadBroadcast;
        private System.Windows.Forms.TextBox tbQRCodeName;
        private System.Windows.Forms.Button btnDelQRCode;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox tbAesTest;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox tbENcoderLen;
        private System.Windows.Forms.Button btnGetKeyHex;
        private System.Windows.Forms.Button btnGetIVHex;
        private System.Windows.Forms.Button btnSendCourseInfo;
        private System.Windows.Forms.Button btnReadVersion;
        private System.Windows.Forms.Button btnReboot;
        private System.Windows.Forms.Button btnSendFile;
        private System.Windows.Forms.TextBox tbDownLoadUrl;
        private System.Windows.Forms.TextBox tbDownLoadPort;
        private System.Windows.Forms.Button btnAdClear;
        private System.Windows.Forms.Button btnAdRead;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button btnSendPersonTemp;
        private System.Windows.Forms.Button btnSendPerson;
        private System.Windows.Forms.TextBox tbPersonId;
        private System.Windows.Forms.Button button5;
    }
}

