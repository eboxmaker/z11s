/*
 * httpDownload.h
 *
 *  Created on: 2019年4月10日
 *      Author: Administrator
 */

#ifndef JNI_HTTPDOWNLOAD_H_
#define JNI_HTTPDOWNLOAD_H_

#include "system/Thread.h"
#include "os/UpgradeMonitor.h"

#include "http/http_client.h"
#include "readdir.h"
#include "globalvar.h"
extern dlNotify_t downloadEvent;
class DownloadThread : public Thread {
public:
	void settings(const string &url,int port,const string &path,const string &name)
	{
			this->url = url;
			this->port = port;
			this->path = path;
			this->name = name;
			this->fullName = path +"/" + name;
			LOGD("setting:%s,%d,%s",url.c_str(),port,fullName.c_str());
	}
	string waitResult()
	{
		while(1)
		{
			if(this->isRunning() == false)
			{
				if(result != "start")
					return result;
			}
		}
	}
protected:
    virtual bool threadLoop(){
    	result = "start";
        http::HttpClient http;
        LOGD("开始下载");
        //这里修改为真实服务IPhttp://127.0.0.1
        string cmd = "mkdir " + path;
        system(cmd.c_str());
        if(name == "update.img")
        {
            char buf[]="1";
            string autouFileFullName = path + "/zkautoupgrade";
			creat_file(autouFileFullName, buf, 1);
			LOGD("creat auto file:%s,",autouFileFullName.c_str());
        }

        //string err = http.Download("192.168.0.101/update.img", 8080, "/mnt/extsd/temp/update.img");
        string err = http.Download(url, port, fullName);
        result = err;
        if (err.empty()) {
        	LOGD("下载成功:%s",err.c_str());
            if(downloadEvent != NULL)
            {
            	LOGD("尝试触发");
            	downloadEvent(err);
            }
            if(name == "update.img")
            {
                Thread::sleep(5000);
    		    dev.enable = false;
    		    gSocket->disconnect();
                UpgradeMonitor::getInstance()->checkUpgradeFile(path.c_str());
            }
        }
        else
        {
            if(downloadEvent != NULL)
            	downloadEvent(err);
        	LOGD("下载失败:%s",err.c_str());
        }

        return false;
    };
private:
    string url;
    string path;
    string name;
    int port;
    string fullName;

    string result;

};
extern DownloadThread downloadThread;


#endif /* JNI_HTTPDOWNLOAD_H_ */
