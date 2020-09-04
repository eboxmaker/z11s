using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace Weiz.TaskManager.Common
{
    public class ComMD5
    {
        public static String GetMd5Str(string str)
        {
            try
            {
                using (MD5CryptoServiceProvider md5Hasher = new MD5CryptoServiceProvider())
                {
                    byte[] data = md5Hasher.ComputeHash(Encoding.UTF8.GetBytes(str));
                    StringBuilder sBuilder = new StringBuilder();
                    for (int i = 0; i < data.Length; i++)
                    {
                        sBuilder.Append(data[i].ToString("x2"));
                    }
                    return sBuilder.ToString().ToLower();
                }
            }
            catch { return null; }
        }
    }
}
