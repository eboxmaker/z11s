/*
 * Device.h
 *
 *  Created on: 2019年6月21日
 *      Author: shentq
 */

#ifndef JNI_DEVICE_H_
#define JNI_DEVICE_H_

#include "objectType.h"
#include "storage/StoragePreferences.h"
#include "security/SecurityManager.h"
#include "lib/itoa.h"
#include "version.h"
#include "utils/log.h"

namespace std {

typedef struct {
	string organization;
	string name;
	string id;

	string pwdLocal;
	string pwdDoor;

	string serverIP;
	int serverPort;

	int	   heartbeatInterval;

	int	 volume;
	bool confirmState;
	bool enable;
}DevicePara_t;


class Device {
public:
	Device();
	virtual ~Device();
	void load()
	{
	    version = VERSION;
		id = get_id_inner();
		confirmState = false;

		para.enable = StoragePreferences::getBool("dev.enable", true);


	    para.serverIP = StoragePreferences::getString("dev.serverIP", "192.168.1.1");
	    para.serverPort = StoragePreferences::getInt("dev.serverPort", 6000);
	    para.pwdLocal = StoragePreferences::getString("dev.pwdLocal", "123456");

	    para.organization = StoragePreferences::getString("dev.organization", "none");
	    para.name = StoragePreferences::getString("dev.name","none");

	    para.heartbeatInterval = StoragePreferences::getInt("dev.heartbeatInterval", 5);

	    para.volume =  StoragePreferences::getInt("dev.volume", 5);

	}

	string& get_id(){
		return id;
	}
	string& get_version(){
		return version;
	}


	void set_organization(string str){
		StoragePreferences::putString("dev.organization", str);
		para.organization = StoragePreferences::getString("dev.organization", "NULL");
	}
	string get_organization(){
		return para.organization;
	}

	void set_name(string str)
	{
		StoragePreferences::putString("dev.name", str);
		para.name = StoragePreferences::getString("dev.name", "NULL");;

	}
	string& get_name(){
		return para.name;
	}


	void set_pwdLocal(string str){
	    StoragePreferences::putString("dev.pwdLocal", str);
	    para.pwdLocal = StoragePreferences::getString("dev.pwdLocal", "123456");
	}
	string& get_pwdLocal(){
		return para.pwdLocal;
	}

	void set_serverIP(string str){
		StoragePreferences::putString("dev.serverIP", str);
		para.serverIP = StoragePreferences::getString("dev.serverIP", "192.168.1.1");
	}

	string get_serverIP(){
		return para.serverIP;
	}

	void set_serverPort(int port){
		StoragePreferences::putInt("dev.serverPort", port);
		para.serverPort = StoragePreferences::getInt("dev.serverPort",6000);

	}
	int get_serverPort(){
		return para.serverPort;
	}

	void set_heartbeatInterval(int value){
		if(value < 3) value = 3;
		if(value > 10)value = 10;
		StoragePreferences::putInt("dev.heartbeatInterval", para.heartbeatInterval);
		para.heartbeatInterval = StoragePreferences::getInt("dev.heartbeatInterval", 5);

	};
	int get_heartbeatInterval(){
		return para.heartbeatInterval;
	};

	void set_volume(int volume){

		StoragePreferences::putInt("dev.volume", volume);
		para.volume = StoragePreferences::getInt("dev.volume", 5);
	}
	int get_volume(){
		return para.volume;
	}

	void set_enable(bool state){
		StoragePreferences::putBool("dev.enable", state);
		para.enable = StoragePreferences::getBool("dev.enable", true);
	};
	void set_enable_temp(bool state){
		para.enable = state;
	};
	bool get_enable(){
		return para.enable;
	}

//	void set_(string &str);
//	string get_();
//
//	void set_(string &str);
//	string get_();

	bool confirmState;
	string id;
	string version;


private:
	DevicePara_t para;


	string get_id_inner()
	{
		XdataULong_t id;
		char buf1[32];
		char buf2[32];

		bool ret = SECURITYMANAGER->getDevID(id.bytes);

		ultoa(id.value,buf1,10);
		ultoa(id.value>>32,buf2,10);
		string str = buf2;
		str += buf1;
		return str;
	}
};

} /* namespace std */

#endif /* JNI_DEVICE_H_ */
