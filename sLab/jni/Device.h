/*
 * Device.h
 *
 *  Created on: 2020年8月27日
 *      Author: shentq
 */

#ifndef JNI_DEVICE_H_
#define JNI_DEVICE_H_


#include "storage/StoragePreferences.h"
#include "security/SecurityManager.h"
#include "lib/itoa.h"
#include "version.h"
#include "utils/log.h"
#include "lib/uid.h"


namespace std {

#define HOME_DIR	"/mnt/extsd/"
#define QR_DIR		"/mnt/extsd/qr/"
#define PIC_DIR		"/mnt/extsd/picture/"
#define DIR_TEMP	"/mnt/extsd/temp/"

#define AD_DIR		"/mnt/extsd/ad/"
#define AD_DB		"/mnt/extsd/advertisment.db"

typedef struct {
	string org;
	string department;
	string id;

	string pwdLocal;

	string serverIP;
	int serverPort;

	int	 volume;
	bool enable;
	string login_time;
}DevicePara_t;


class Device {
public:
	Device();
	virtual ~Device();
	void load()
	{
		id = Uid::get_hex_string();
		login_state = false;
		para.enable = StoragePreferences::getBool("dev.enable", true);


	    para.serverIP = StoragePreferences::getString("serverIP", "10.176.26.200");
	    para.serverPort = StoragePreferences::getInt("serverPort", 6000);
	    para.pwdLocal = StoragePreferences::getString("pwdLocal", "123456");

	    para.org = StoragePreferences::getString("organization", "none");
	    para.department = StoragePreferences::getString("department","none");
	    para.volume =  StoragePreferences::getInt("volume", 5);

	}
	string get_id(){
		return id;
	}

	void set_organization(string str){
		StoragePreferences::putString("organization", str);
		para.org = StoragePreferences::getString("organization", "none");
	}
	string& get_organization(){
		return para.org;
	}

	void set_department(string str)
	{
		StoragePreferences::putString("department", str);
		para.department = StoragePreferences::getString("department", "none");;

	}
	string& get_department(){
		return para.department;
	}


	void set_pwdLocal(string str){
	    StoragePreferences::putString("pwdLocal", str);
	    para.pwdLocal = StoragePreferences::getString("pwdLocal", "123456");
	}
	string& get_pwdLocal(){
		return para.pwdLocal;
	}



	void set_serverIP(string str){
		StoragePreferences::putString("serverIP", str);
		para.serverIP = StoragePreferences::getString("serverIP", "10.176.26.200");
	}

	string get_serverIP(){
		return para.serverIP;
	}

	void set_serverPort(int port){
		StoragePreferences::putInt("serverPort", port);
		para.serverPort = StoragePreferences::getInt("serverPort",6000);

	}
	int get_serverPort(){
		return para.serverPort;
	}
	void set_volume(int volume){

		StoragePreferences::putInt("volume", volume);
		para.volume = StoragePreferences::getInt("volume", 5);
	}
	int get_volume(){
		return para.volume;
	}

	void set_enable(bool state){
		StoragePreferences::putBool("enable", state);
		para.enable = StoragePreferences::getBool("enable", true);
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

	bool login_state;
	string id;
	DevicePara_t para;

};
extern Device dev;

} /* namespace std */

#endif /* JNI_DEVICE_H_ */
