using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyFun
{
    class IPHelper
    {
        public static string[] GetLocalIP(ref int num)
        {

                string HostName = Dns.GetHostName(); //得到主机名
                IPHostEntry IpEntry = Dns.GetHostEntry(HostName);
                num = IpEntry.AddressList.Length;
                string[] iplist = new string[num];
                num = 0;
                for (int i = 0; i < IpEntry.AddressList.Length; i++)
                {

                    if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetworkV6)
                    { 
                    }
                    else
                    {
                        iplist[num] = IpEntry.AddressList[i].ToString();
                        num++;
                    }
                        
                    //从IP地址列表中筛选出IPv4类型的IP地址
                    //AddressFamily.InterNetwork表示此IP为IPv4,
                    //AddressFamily.InterNetworkV6表示此地址为IPv6类型
                    //if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetwork)
                    //{
                    //    return IpEntry.AddressList[i].ToString();
                    //}
                }
                return iplist;
            
        }
    }
}
