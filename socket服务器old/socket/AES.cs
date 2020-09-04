using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace AES
{
    public class AESEncrypt
    {
        const string AES_IV = "1234567890000000";//16位    

        /// <summary>  
        /// AES加密算法  
        /// </summary>  
        /// <param name="input">明文字符串</param>  
        /// <param name="key">密钥（32位）</param>  
        /// <returns>字符串</returns>  
        public static string EncryptByAES(string input, string key)
        {
            byte[] keyBytes = Encoding.UTF8.GetBytes(key.Substring(0, 32));
            using (AesCryptoServiceProvider aesAlg = new AesCryptoServiceProvider())
            {
                aesAlg.Key = keyBytes;
                aesAlg.IV = Encoding.UTF8.GetBytes(AES_IV.Substring(0, 16));

                ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);
                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                    {
                        using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                        {
                            swEncrypt.Write(input);
                        }
                        byte[] bytes = msEncrypt.ToArray();
                        return ByteArrayToHexString(bytes);
                       // return Convert.ToBase64String(bytes);
                    }
                }
            }
        }

        /// <summary>  
        /// AES解密  
        /// </summary>  
        /// <param name="input">密文字节数组</param>  
        /// <param name="key">密钥（32位）</param>  
        /// <returns>返回解密后的字符串</returns>  
        public static string DecryptByAES(string input, string key)
        {
            byte[] inputBytes = HexStringToByteArray(input);
            byte[] keyBytes = Encoding.UTF8.GetBytes(key.Substring(0, 32));
            using (AesCryptoServiceProvider aesAlg = new AesCryptoServiceProvider())
            {
                aesAlg.Key = keyBytes;
                aesAlg.IV = Encoding.UTF8.GetBytes(AES_IV.Substring(0, 16));

                ICryptoTransform decryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV);
                using (MemoryStream msEncrypt = new MemoryStream(inputBytes))
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, decryptor, CryptoStreamMode.Read))
                    {
                        using (StreamReader srEncrypt = new StreamReader(csEncrypt))
                        {
                            return srEncrypt.ReadToEnd();
                        }
                    }
                }
            }
        }
        ///// <summary>
        ///// AES解密
        ///// </summary>
        ///// <param name="decryptStr">密文</param>
        ///// <param name="key">密钥</param>
        ///// <returns></returns>
        //public static string Decrypt(string decryptStr, string key)
        //{
        //    byte[] keyArray = UTF8Encoding.UTF8.GetBytes(key);
        //    byte[] toEncryptArray = Convert.FromBase64String(decryptStr);
        //    RijndaelManaged rDel = new RijndaelManaged();
        //    rDel.Key = keyArray;
        //    rDel.Mode = CipherMode.ECB;
        //    rDel.Padding = PaddingMode.PKCS7;
        //    ICryptoTransform cTransform = rDel.CreateDecryptor();
        //    byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);
        //    return UTF8Encoding.UTF8.GetString(resultArray);
        //}
        /// <summary>
        /// 将指定的16进制字符串转换为byte数组
        /// </summary>
        /// <param name="s">16进制字符串(如：“7F 2C 4A”或“7F2C4A”都可以)</param>
        /// <returns>16进制字符串对应的byte数组</returns>
        public static byte[] HexStringToByteArray(string s)
        {
            s = s.Replace(" ", "");
            byte[] buffer = new byte[s.Length / 2];
            for (int i = 0; i < s.Length; i += 2)
                buffer[i / 2] = (byte)Convert.ToByte(s.Substring(i, 2), 16);
            return buffer;
        }

        /// <summary>
        /// 将一个byte数组转换成一个格式化的16进制字符串
        /// </summary>
        /// <param name="data">byte数组</param>
        /// <returns>格式化的16进制字符串</returns>
        public static string ByteArrayToHexString(byte[] data)
        {
            StringBuilder sb = new StringBuilder(data.Length * 3);
            foreach (byte b in data)
            {
                //16进制数字
                sb.Append(Convert.ToString(b, 16).PadLeft(2, '0'));
                //16进制数字之间以空格隔开
                //sb.Append(Convert.ToString(b, 16).PadLeft(2, '0').PadRight(3, ' '));
            }
            return sb.ToString().ToUpper();
        }
        public static string Encrypt(string toEncrypt,string key)
        {
            // 256-AES key    
            byte[] keyArray = Encoding.UTF8.GetBytes(key);
            byte[] ivArray = Encoding.UTF8.GetBytes(AES_IV);
            byte[] toEncryptArray = Encoding.UTF8.GetBytes(toEncrypt);

            RijndaelManaged rDel = new RijndaelManaged();
            rDel.Key = keyArray;
            rDel.IV = ivArray;
            rDel.Mode = CipherMode.CBC;
            rDel.Padding = PaddingMode.Zeros;

            ICryptoTransform cTransform = rDel.CreateEncryptor();
            byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

            return ByteArrayToHexString(resultArray);
        }
        public static string Decrypt(string toDecrypt,string key)
        {
            // 256-AES key    
            byte[] keyArray = Encoding.UTF8.GetBytes(key);
            byte[] ivArray = Encoding.UTF8.GetBytes(AES_IV);
            byte[] toEncryptArray = HexStringToByteArray(toDecrypt);

            RijndaelManaged rDel = new RijndaelManaged();
            rDel.Key = keyArray;
            rDel.IV = ivArray;
            rDel.Mode = CipherMode.CBC;
            rDel.Padding = PaddingMode.Zeros;

            ICryptoTransform cTransform = rDel.CreateDecryptor();
            byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

            string js =  UTF8Encoding.UTF8.GetString(resultArray);
            js = js.Replace("\0","");
            return js;
        }


        /// <summary>  
        /// AES加密
        /// </summary>  
        /// <param name="encryptStr">明文</param>  
        /// <param name="key">密钥</param>  
        /// <returns></returns>
        public static string Encrypt1(string encryptStr, string key)
        {
            var _aes = new AesCryptoServiceProvider();
            _aes.BlockSize = 16;
            _aes.KeySize = 256;
            _aes.Key = Encoding.UTF8.GetBytes(key);
            _aes.IV = (byte[])(object)new sbyte[16];//Encoding.UTF8.GetBytes(IV);
            _aes.Padding = PaddingMode.PKCS7;
            _aes.Mode = CipherMode.CBC;

            var _crypto = _aes.CreateEncryptor(_aes.Key, _aes.IV);
            byte[] encrypted = _crypto.TransformFinalBlock(Encoding.UTF8.GetBytes(encryptStr), 0, Encoding.UTF8.GetBytes(encryptStr).Length);

            _crypto.Dispose();

            return System.Convert.ToBase64String(encrypted);
        }
        /// <summary>  
        /// AES解密
        /// </summary>  
        /// <param name="decryptStr">密文</param>  
        /// <param name="key">密钥</param>  
        /// <returns></returns>  
        public static string Decrypt1(string decryptStr, string key)
        {
            var _aes = new AesCryptoServiceProvider();
            _aes.BlockSize = 128;
            _aes.KeySize = 256;
            _aes.Key = Encoding.UTF8.GetBytes(key);
            _aes.IV = (byte[])(object)new sbyte[16];//Encoding.UTF8.GetBytes(IV);
            _aes.Padding = PaddingMode.PKCS7;
            _aes.Mode = CipherMode.CBC;

            var _crypto = _aes.CreateDecryptor(_aes.Key, _aes.IV);
            byte[] decrypted = _crypto.TransformFinalBlock(
                System.Convert.FromBase64String(decryptStr), 0, System.Convert.FromBase64String(decryptStr).Length);
            _crypto.Dispose();
            return Encoding.UTF8.GetString(decrypted);
        }
    }
}
