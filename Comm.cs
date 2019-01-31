using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using Weiz.TaskManager.Common;

namespace Weiz.TaskManager.BLL
{
    public class tData
    {
        public string sign { get; set; }
        public string data { get; set; }
    }
    public class Comm
    {

		{
			sign:"xxxxxxx"
			data:"xxxxxxxxxxx"
		}

        /// <summary>
        /// 验证远程调用
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        public static Newtonsoft.Json.Linq.JObject GetParam(string data)
        {
            string dd = AESEncrypt.DecryptByAES(data, "12345678900000001234567890000000");
            var obj = JsonConvert.DeserializeObject<tData>(dd);

            if (ComMD5.GetMd5Str(obj.data) == obj.sign)
            {
                return (Newtonsoft.Json.Linq.JObject)JsonConvert.DeserializeObject(obj.data);
            }

            return null;
        }
        /// <summary>
        /// 验证远程调用
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        public static Newtonsoft.Json.Linq.JArray GetParamArray(string data)
        {
            string dd = AESEncrypt.DecryptByAES(data, "12345678900000001234567890000000");
            var obj = JsonConvert.DeserializeObject<tData>(dd);

            if (ComMD5.GetMd5Str(obj.data) == obj.sign)
            {
                return (Newtonsoft.Json.Linq.JArray)JsonConvert.DeserializeObject(obj.data);
            }

            return null;
        }
        public static string SetParam(string data)
        {
            tData t = new tData();
            t.sign = ComMD5.GetMd5Str(data);
            t.data = data;

            return AESEncrypt.EncryptByAES(JsonConvert. 	(t), "12345678900000001234567890000000");
        }
    }
}
