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

namespace MyJson
{
    class JsonManager
    {
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
        public static string PackageFileToJsonString(string FilePath)
        {
            JObject obj = new JObject();
            string name = Path.GetFileName(FilePath);
            string data = FileToBase64(FilePath);
            obj.Add("cmd", 0);
            obj.Add("name", name);
            obj.Add("data", data);
            string jstring = JsonConvert.SerializeObject(obj);
            return jstring;
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
        public static int GetJsonCMD(string jstr)
        {
            JObject obj = new JObject();
            int cmd = -1;
            try
            {
                obj = (JObject)JsonConvert.DeserializeObject(jstr);
                cmd = Convert.ToInt16( obj["cmd"].ToString());
   
            }
            catch
            {

            }
            return cmd;  


        }
        public static string MakeCMDDoor1(int value)
        {
            JObject obj = new JObject();
            obj.Add("cmd", 1);
            obj.Add("value", value);
            string jstring = JsonConvert.SerializeObject(obj);
            return jstring;
        }
        public static string ParseDoorPwd(string js)
        {
            JObject jo = (JObject)JsonConvert.DeserializeObject(js);
            string pwd = jo["doorPwd"].ToString();
            return pwd;
        }

    }
}
