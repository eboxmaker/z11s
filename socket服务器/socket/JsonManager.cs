﻿using AES;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Weiz.TaskManager.Common;

namespace MyJson
{

    class JsonManager
    {

        static string key = "12345678900000001234567890000000";

    public enum CMDType  //枚举类型，体会xml注释的样子
    {
        CMDUpdate,
        CMDReboot,
        CMDVersion,
        DevID,
        Register,
        	Heartbeat,
	        SetHeartbeat,
            OrgName,
            DevName,

            SyncDateTime,
            AdminPwd,

            FingerKey,
	        DoorPwd,
            DoorCtr,
            DoorState,

            CourseInfo,
            Plan,
            Broadcast, 
        
            QRCode,
            DelQRCode,

            AdPic,
            AdRead,
            DelAdPic,
            AdClear,
            AdSet,


            Person,
            PersonGetByLevel,

            FingerGet,
            FingerSet,


            CMDErr,
    }
    public struct Person
    {
        internal string id;
        internal string name;
        internal int level;
        internal string[] fingers;
        internal string picture_name;
    };
        //同
    public enum StatusType  //枚举类型，体会xml注释的样子
    {
        StatusSet = 0,
        StatusGet,
        StatusOK,
        StatusErr
    }
    public enum StatusConfirmType  //枚举类型，体会xml注释的样子
    {
        StatusReqDev2Ser = 0,
        StatusParaSer2Dev,
        StatusAckDev2Ser,
        StatusOKSer2Dev,
        StatusErr,
    }

        //同
       // public JObject jo;

        public static JObject OpenFile(string path)
        {
            JObject obj;
            FileStream fs = File.OpenRead(path);
            if (fs == null)
                obj = null;
            else
            {
                int len = (int)fs.Length;
                byte[] byteArray = new byte[len];
                int ReadedLength = fs.Read(byteArray, 0, len);
                string js = Encoding.Default.GetString(byteArray);
                obj = (JObject)JsonConvert.DeserializeObject(js);
            }
            return obj;
        }
        //public static string OpenFile(string path)
        //{
        //    string jstr;
        //    FileStream fs = File.OpenRead(path);
        //    if (fs == null)
        //        jstr = null;
        //    else
        //    {
        //        int len = (int)fs.Length;
        //        byte[] byteArray = new byte[len];
        //        int ReadedLength = fs.Read(byteArray, 0, len);
        //        jstr = Encoding.Default.GetString(byteArray);
        //    }
        //    return jstr;
        //}
        
        public DataTable JobjectToDataTable(JObject obj)
        {
            DataTable dt = new DataTable();
            return dt;
        }
        public static string Serialize(string str)
        {
            //格式化json字符串
            JsonSerializer serializer = new JsonSerializer();
            TextReader tr = new StringReader(str);
            JsonTextReader jtr = new JsonTextReader(tr);
            object obj = serializer.Deserialize(jtr);
            if (obj != null)
            {
                StringWriter textWriter = new StringWriter();
                JsonTextWriter jsonWriter = new JsonTextWriter(textWriter)
                {
                    Formatting = Formatting.Indented,
                    Indentation = 4,
                    IndentChar = ' '
                };
                serializer.Serialize(jsonWriter, obj);
                return textWriter.ToString();
            }
            else
            {
                return str;
            }
        }
        public static string Serialize(JObject obj)
        {
            //格式化json字符串
            JsonSerializer serializer = new JsonSerializer();

            StringWriter textWriter = new StringWriter();
            JsonTextWriter jsonWriter = new JsonTextWriter(textWriter)
            {
                Formatting = Formatting.Indented,
                Indentation = 4,
                IndentChar = ' '
            };
            serializer.Serialize(jsonWriter, obj);
            return textWriter.ToString();
        }
        private static byte[] GetByte(JObject obj)
        {
            string js = Serialize(obj);
            byte[] bytes = Encoding.Default.GetBytes(js);
            return bytes;
        }
        public static bool Save(JObject obj, string filepath)
        {
            FileStream fs = File.Create(filepath);
            byte[] byteArray = GetByte(obj);
            fs.Write(byteArray, 0, (int)byteArray.Length);
            fs.Flush();
            fs.Close();
            return true;
        }


        public static bool Save(string jstr, string filepath)
        {
            FileStream fs = File.Create(filepath);
            byte[] byteArray = Encoding.Default.GetBytes(jstr);
            fs.Write(byteArray, 0, (int)byteArray.Length);
            fs.Flush();
            fs.Close();
            return true;
        }

        public static DataTable toDataTable(string jstring)
        {
            DataTable dt=new DataTable();
            JArray ay = new JArray();
            JObject json = JObject.Parse(jstring);

            dt.Columns.Add("RPN",typeof(string));
            dt.Columns.Add("refname", typeof(string));
            dt.Columns.Add("package", typeof(string));
            dt.Columns.Add("flash", typeof(string));
            dt.Columns.Add("ram", typeof(string));
            dt.Columns.Add("iONb", typeof(string));
            dt.Columns.Add("frequency", typeof(string));
            ay = JArray.Parse(json["MCUs"].ToString());
            for (int i = 0; i < ay.Count;i++ )
            {
                JArray aay = JArray.Parse(ay[i]["subpackages"].ToString());
                for(int j = 0 ; j < aay.Count;j++)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = ay[i]["RPN"].ToString();
                    dr[1] = aay[j]["refname"].ToString();
                    dr[2] = aay[j]["package"].ToString();

                    dr[3] = ay[i]["flash"].ToString();
                    dr[4] = ay[i]["ram"].ToString();
                    dr[5] = aay[j]["iONb"].ToString();
                    dr[6] = ay[i]["frequency"].ToString();
                    dt.Rows.Add(dr);

                }
            }
            return dt;

        }


        /// <summary> 
        /// Datatable转换为Json 
        /// </summary> 
        /// <param name="table">Datatable对象</param> 
        /// <returns>Json字符串</returns> 
        public static string ToJson(DataTable dt)
        {
            StringBuilder jsonString = new StringBuilder();
            jsonString.Append("[");
            DataRowCollection drc = dt.Rows;
            for (int i = 0; i < drc.Count; i++)
            {
                jsonString.Append("{");
                for (int j = 0; j < dt.Columns.Count; j++)
                {
                    string strKey = dt.Columns[j].ColumnName;
                    string strValue = drc[i][j].ToString();
                    Type type = dt.Columns[j].DataType;
                    jsonString.Append("\"" + strKey + "\":");
                  //  strValue = StringFormat(strValue, type);
                    if (j < dt.Columns.Count - 1)
                    {
                        jsonString.Append(strValue + ",");
                    }
                    else
                    {
                        jsonString.Append(strValue);
                    }
                }
                jsonString.Append("},");
            }
            jsonString.Remove(jsonString.Length - 1, 1);
            jsonString.Append("]");
            return jsonString.ToString();
        }

        private static string FileToBase64(string FilePath)
        {
            FileStream fs = new FileStream(FilePath, FileMode.Open, FileAccess.Read);
            int nBytes = (int)fs.Length;
            byte[] byteArray = new byte[nBytes];
            int nByteReaded = fs.Read(byteArray, 0, nBytes);
            string x = Convert.ToBase64String(byteArray);
            return x;
        }
        public static string PackageFileToJsonString(string FilePath, int FileType)
        {
            JObject obj = new JObject();
            string name = Path.GetFileName(FilePath);
            string data = FileToBase64(FilePath);
            obj.Add("cmd", FileType);
            obj.Add("name", name);
            obj.Add("dataLength", data.Length);
            obj.Add("data", data);
            obj.Add("status", (int)StatusType.StatusSet);
            string jstring = JsonConvert.SerializeObject(obj);
            return jstring;
        }
        public static string PackageAdFileToJsonString(string FilePath,int dispTime)
        {
            JObject obj = new JObject();
            string name = Path.GetFileName(FilePath);
            string data = FileToBase64(FilePath);
            obj.Add("cmd", (int)CMDType.AdPic);
            obj.Add("name", name);
            obj.Add("displayTime", dispTime);
            obj.Add("dataLength", data.Length);
            obj.Add("data", data);
            obj.Add("status", (int)StatusType.StatusSet);
            string jstring = JsonConvert.SerializeObject(obj);
            return jstring;
        }
        public static string MakeCourseInfoString(string FilePath)
        {
            JObject obj = new JObject();
            string name = Path.GetFileName(FilePath);
            string data = FileToBase64(FilePath);
            obj.Add("cmd",  (int)CMDType.CourseInfo);
            obj.Add("name", "李建义");
            obj.Add("class", "B12345");
            obj.Add("num", "40");
            obj.Add("course", "编译原理");
            obj.Add("pic.name", FilePath);
            obj.Add("pic.data", data);
            obj.Add("pic.dataLength", data.Length);
            obj.Add("status", (int)StatusType.StatusSet);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static bool SaveJsonStringFile(string JSFile,string Dircetoy)
        {
            JObject obj = JObject.Parse(JSFile);

            string name = obj["name"].ToString();
            string data = obj["data"].ToString();
            
            byte[] bArray =  Convert.FromBase64String(data);

            FileStream fs = new FileStream(Dircetoy + name, FileMode.OpenOrCreate,FileAccess.Write);

            fs.Write(bArray,0,(int)bArray.Length);
            fs.Flush();
            fs.Close();
            return true;
        }
        public static string UnicodeToString(string srcText)
        {
            string dst = "";
            string src = srcText;
            int len = srcText.Length / 6;
            for (int i = 0; i <= len - 1; i++)
            {
                string str = "";
                str = src.Substring(0, 6).Substring(2);
                src = src.Substring(6);
                byte[] bytes = new byte[2];
                bytes[1] = byte.Parse(int.Parse(str.Substring(0, 2), System.Globalization.NumberStyles.HexNumber).ToString());
                bytes[0] = byte.Parse(int.Parse(str.Substring(2, 2), System.Globalization.NumberStyles.HexNumber).ToString());
                dst += Encoding.Unicode.GetString(bytes);
            }
            return dst;
        }

        public static string Package(string jstr)
        {

            string enstr = AESEncrypt.Encrypt(jstr, key);
            string md5 = ComMD5.GetMd5Str(jstr);
            JObject obj = new JObject();
            obj.Add("sign", md5);
            obj.Add("data", enstr);
            string jstring = JsonConvert.SerializeObject(obj);
            return jstring;
        }
        public static string unPackage(string jstr)
        {
            JObject obj = new JObject();
            string md5;
            string js = "";

            try
            {
                obj = (JObject)JsonConvert.DeserializeObject(jstr);
                md5 = obj["sign"].ToString();
                string data = obj["data"].ToString();
                js = AESEncrypt.Decrypt(data, key);
                string checkMD5 = ComMD5.GetMd5Str(js);
                if (md5 == checkMD5)
                {
                    return js;
                }
                else
                    js = "";
            }
            catch
            {

            }
            return js;
        }
        public static CMDType GetJsonCMD(string jstr)
        {
            JObject obj = new JObject();
            CMDType cmd = CMDType.CMDErr;

           

            try
            {
                obj = (JObject)JsonConvert.DeserializeObject(jstr);
                cmd = (CMDType)Convert.ToInt16(obj["cmd"].ToString());
   
            }
            catch
            {

            }
            return cmd;  
        }
        public static StatusType GetJsonStatus(string jstr)
        {
            JObject obj = new JObject();
            StatusType status = StatusType.StatusErr;
            try
            {
                obj = (JObject)JsonConvert.DeserializeObject(jstr);
                status = (StatusType)Convert.ToInt16(obj["status"].ToString());

            }
            catch
            {

            }
            return status;
        }
        public static StatusConfirmType GetJsonStatusConfirm(string jstr,ref string id)
        {
            JObject obj = new JObject();
            StatusConfirmType status = StatusConfirmType.StatusErr;
            try
            {
                obj = (JObject)JsonConvert.DeserializeObject(jstr);
                status = (StatusConfirmType)Convert.ToInt16(obj["status"].ToString());
                id = obj["id"].ToString();

            }
            catch
            {

            }
            return status;
        }
        public static string ParseCMDHeartbeat(string js)
        {

            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string str = jo["value"].ToString();
            return str;
        }
        public static string MakeSetHeartbeat(int interval,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.SetHeartbeat);
            obj.Add("heartbeatInterval", interval);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string ParseSetHeartbeat(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string pwd = jo["interval"].ToString();
            return pwd;
        }
        public static string MakeCMDHeartbeat(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.Heartbeat);
            obj.Add("value", "hello");
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeCMDDoorCtr(string isLock,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DoorCtr);
            obj.Add("doorCtr", isLock);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string MakeCMDDoorState(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DoorState);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string ParseCMDDoorState(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string doorState = jo["doorState"].ToString();
            return doorState;
        }
        public static string MakeDoorPwd(string pwd,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DoorPwd);
            obj.Add("password", pwd);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string ParseDoorPwd(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string pwd = jo["password"].ToString();
            return pwd;
        }
        public static string ParseFingerKey(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string id = jo["id"].ToString();
            return id;
        }
        public static string MakeCMDDoorPwd(string pwd,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DoorPwd);
            obj.Add("password", pwd);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeCMDFingerKey(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.FingerKey);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string ParseSyncDateTime(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string pwd = jo["status"].ToString();
            return pwd;
        }
        public static string MakeCMDSyncDateTime(StatusType status)
        {
            string dateTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.SyncDateTime);
            obj.Add("dateTime", dateTime);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakePlan(StatusType status)
        {
            string dateTime = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss");
            JObject obj = new JObject();
            var ja = new JArray();
            string[] class_ = { "B19521,B18253,B19537,B52645", "B19521,B18253,B19537", "B19521,B18253", "B19521", "B19521,B18253", "B19521" };
            string[] name = { "张云峰", "李建义", "性一览", "刘喜梅", "朱杰", "尹国才", "刘喜梅", "朱杰", "尹国才", "刘喜梅", "朱杰", "尹国才" };
            string[] course = { "嵌入式基础教学", "PHP开发", "C语言实训项目集合", "航天系统测试", "物联网概论", "尹国才", "刘喜梅", "朱杰", "尹国才", "刘喜梅", "朱杰", "尹国才" };
            obj.Add("cmd", (int)CMDType.Plan);

            for (int i = 0; i < 3; i++)
            {
                JObject jo = new JObject();
                jo.Add("uint", "第" + i.ToString()+"单元");
                jo.Add("startTime", "08:00");
                jo.Add("endTime", "08:30");
                jo.Add("teacher", name[i]);
                jo.Add("class", class_[i]);
                jo.Add("course", course[i]);
                ja.Add(jo);
            } 
            obj.Add("plan",ja);
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }
        public static string MakePlan2(StatusType status)
        {
            string dateTime = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss");
            JObject obj = new JObject();
            var ja = new JArray();

            string[] name = { "刘喜梅", "朱杰", "", "刘喜梅", "朱杰", "张云峰", "李建义", "性一览", "尹国才", "刘喜梅", "朱杰", "尹国才" };
            string[] class_ = { "B19521\nB18253,B19537", "B19521\nB18253", "", "B19521", "B19521,B18253,B19537,B52645", "B19521" };
            string[] course = { "航天系统测试", "物联网概论", "", "刘喜梅", "朱杰", "尹国才", "刘喜梅", "朱杰", "尹国才" };
            obj.Add("cmd", (int)CMDType.Plan);

            for (int i = 0; i < 6; i++)
            {
                JObject jo = new JObject();
                jo.Add("uint", "第" + (i+1).ToString() + "单元");
                jo.Add("startTime", "8:00");
                jo.Add("endTime", "10:30");
                jo.Add("teacher", name[i]);
                jo.Add("class", class_[i]);
                jo.Add("course", course[i]);
                ja.Add(jo);
            }
            obj.Add("plan", ja);
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }
        public static string ParsePlan(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string status = jo["status"].ToString();
            return status;

        }
        public static string MakeBroadcast(string msg,StatusType status)
        {
            string dateTime = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss");
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.Broadcast);
            obj.Add("data", msg);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string MakeAdSet(bool enable,int idleTime,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.AdSet);
            obj.Add("enable", enable);
            obj.Add("idleTime", idleTime);
            obj.Add("status",(int) status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string MakeAdminPwd(string pwd,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.AdminPwd);
            obj.Add("pwd", pwd);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string MakeConfirm(string id,StatusConfirmType status)
        {
            string dateTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");

            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.Register);
            if(status == StatusConfirmType.StatusParaSer2Dev)
            {
                obj.Add("organization", "北华航天工业学院");
                obj.Add("name", "软三");
                obj.Add("id", id);
                obj.Add("heartbeatInterval", 5);
                //obj.Add("dateTime", dateTime);

            }
            if(status == StatusConfirmType.StatusOKSer2Dev)
            {
                obj.Add("organization", "北华航天工业学院");
                obj.Add("name", "软三");
                obj.Add("id", "3832001749591935784");
                obj.Add("heartbeatInterval", 5);
                //obj.Add("dateTime", dateTime);
            }
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeOrgName(string organization, StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.OrgName);
            obj.Add("organization", organization);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string ParseOrgName(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string organization = jo["organization"].ToString();
            return organization;
        }

        public static string MakeDevName(string name,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DevName);
            obj.Add("name", name);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string ParseDevName(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string name = jo["name"].ToString();
            return name;
        }

        public static string MakeDevID(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DevID);
            obj.Add("id", "");
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }

        public static string MakeDeleteAdPic(string fileName,StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DelAdPic);
            obj.Add("name", fileName);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeAdClear( StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.AdClear);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeAdRead(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.AdRead);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeDeleteQRCode(string fileName, StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.DelQRCode);
            obj.Add("name", fileName);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }


        public static string MakePerson(string id, string name, int level, string[] fingers, string FilePath, StatusType status)
        {
            JObject obj = new JObject();

            string picname = Path.GetFileName(FilePath);
            string data = FileToBase64(FilePath);

            var ja = new JArray();
            
            obj.Add("cmd", (int)CMDType.Person);
            obj.Add("id",id);
            obj.Add("name", name);
            obj.Add("level", level);
            obj.Add("pic.name", picname);
            obj.Add("pic.data", data);
            obj.Add("pic.dataLength", data.Length);

            for (int i = 0; i < fingers.Length; i++)
            {
                JObject jo = new JObject();
                jo.Add("finger",fingers[i]);
                ja.Add(jo);
            }
            obj.Add("fingers", ja);
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;

        }

        public static string MakePerson(Person ps, StatusType status)
        {
            JObject obj = new JObject();

            string picname = Path.GetFileName(ps.picture_name);
            string data = FileToBase64(ps.picture_name);

            var ja = new JArray();

            obj.Add("cmd", (int)CMDType.Person);
            obj.Add("id", ps.id);
            obj.Add("name", ps.name);
            obj.Add("level", ps.level);


            for (int i = 0; i < ps.fingers.Length; i++)
            {
                JObject jo = new JObject();
                jo.Add("finger", ps.fingers[i]);
                ja.Add(jo);
            }
            obj.Add("fingers", ja);
            obj.Add("pic_name", ps.picture_name);
            obj.Add("pic_data", data);
            obj.Add("pic_dataLength", data.Length);    
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }

        public static string MakePersonGetByLevel(int level, int num, StatusType status)
        {
            JObject obj = new JObject();

            obj.Add("cmd", (int)CMDType.PersonGetByLevel);
            obj.Add("level", level);
            obj.Add("num", num);
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }

        public static void ParsePersonGetByLevel(string js,ref int level, ref int num)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            level = Convert.ToInt16(jo["level"].ToString());
            string str = jo["num"].ToString();
            num = Convert.ToInt16(str);
            return ;
        }
        public static string MakeFinger(string id, string name, int level, string[] fingers, string FilePath, StatusType status)
        {
            JObject obj = new JObject();

            string picname = Path.GetFileName(FilePath);
            string data = FileToBase64(FilePath);

            var ja = new JArray();

            obj.Add("cmd", (int)CMDType.FingerGet);
            obj.Add("id", id);
            obj.Add("name", name);
            obj.Add("level", level);
            obj.Add("pic.name", picname);
            obj.Add("pic.data", data);
            obj.Add("pic.dataLength", data.Length);

            for (int i = 0; i < fingers.Length; i++)
            {
                JObject jo = new JObject();
                jo.Add("finger", fingers[i]);
                ja.Add(jo);
            }
            obj.Add("fingers", ja);
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }

        public static string MakeFingerGet(Person ps, StatusType status)
        {
            JObject obj = new JObject();

            string picname = Path.GetFileName(ps.picture_name);
            string data = FileToBase64(ps.picture_name);

            var ja = new JArray();

            obj.Add("cmd", (int)CMDType.FingerGet);
            obj.Add("id", ps.id);
            obj.Add("name", ps.name);
            obj.Add("level", ps.level);

            for (int i = 0; i < ps.fingers.Length; i++)
            {
                JObject jo = new JObject();
                jo.Add("finger", ps.fingers[i]);
                ja.Add(jo);
            }
            obj.Add("fingers", ja);
            obj.Add("status", (int)status);
            obj.Add("pic_name", ps.picture_name);
            obj.Add("pic_data", data);
            obj.Add("pic_dataLength", data.Length);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }

        public static string MakeFingerSet(Person ps, StatusType status)
        {
            JObject obj = new JObject();

            string picname = Path.GetFileName(ps.picture_name);
            string data = FileToBase64(ps.picture_name);

            var ja = new JArray();

            obj.Add("cmd", (int)CMDType.FingerSet);
            obj.Add("id", ps.id);
            obj.Add("name", ps.name);
            obj.Add("level", ps.level);
            obj.Add("pic.name", ps.picture_name);
            obj.Add("pic.data", data);
            obj.Add("pic.dataLength", data.Length);

            for (int i = 0; i < ps.fingers.Length; i++)
            {
                JObject jo = new JObject();
                jo.Add("finger", ps.fingers[i]);
                ja.Add(jo);
            }
            obj.Add("fingers", ja);
            obj.Add("status", (int)status);

            string jstring = JsonConvert.SerializeObject(obj);

            string str = Package(jstring);
            return str;
        }

        public static string parseFingerGet(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string idstr = jo["id"].ToString();
            //int id = Convert.ToInt32(idstr);
            return idstr;
        }
        public static string parseFingerSet(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string idstr = jo["id"].ToString();
            //int id = Convert.ToInt32(idstr);
            return idstr;
        }
        public static string MakeVersion(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.CMDVersion);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeReboot(StatusType status)
        {
            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.CMDReboot);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }
        public static string MakeUpdate(string url, int port, StatusType status)
        {

            JObject obj = new JObject();
            obj.Add("cmd", (int)CMDType.CMDUpdate);
            obj.Add("url", url);
            obj.Add("port", port);
            obj.Add("status", (int)status);
            string jstring = JsonConvert.SerializeObject(obj);
            string str = Package(jstring);
            return str;
        }


    }
}
