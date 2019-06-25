/*
 * Finger.h
 *
 *  Created on: 2019年1月14日
 *      Author: shentq
 */

#ifndef JNI_FINGER_H_
#define JNI_FINGER_H_

#include <iostream>

using namespace std;

#define MAX_USERNUM		150//共计150枚指纹
#define DATA_START			0xf5//数据包开始
#define DATA_END			0xf5//数据包结束

#define CMD_ENROLL1  		0x01//添加指纹步骤一
#define CMD_ENROLL2  		0x02//添加指纹步骤二
#define CMD_ENROLL3  		0x03//添加指纹步骤三
#define CMD_DELETE  		0x04//删除指定编号指纹
#define CMD_CLEAR  			0x05//清空所有指纹
#define CMD_USERNUMB  		0x09//取用户总数
#define CMD_IDENTIFY  		0x0b//1:1比对
#define CMD_SEARCH  		0x0c//1:N比对
#define CMD_TIMEOUT			0x2E//超时时间
#define CMD_GET_CURRENT_FEATURE			0x23//超时时间
#define CMD_GET_ID_FEATURE			0x31//下载DSP模块数据库内指定用户特征值
#define CMD_SET_ID_FEATURE			0x41//上传特征值并按指定用户号存入DSP模块数据库
#define CMD_SEARCH_FEATURE			0x43//上传指纹特征值与DSP模块数据库指纹比对1：N
#define CMD_GET_FREE				0x47//获取特定区间第一个空闲位置
#define CMD_GET_SERIAL				0x2A//取DSP模块内部序列号,也用于检测设备是否在线




#define ACK_SUCCESS  		0x00	//操作成功
#define ACK_FAIL	  		0x01	//操作失败
#define ACK_FULL	  		0x04	//指纹数据库已满
#define ACK_NOUSER   		0x05	//无此用户
#define ACK_USER_OCCUPIED   0x06    //此ID用户已存在
#define ACK_USER_EXIST 		0x07 	//用户已存在
#define ACK_TIMEOUT  		0x08	//采集超时
#define ACK_SUSPEND  		0xFF	//
typedef enum
{
	HEAD,
	CMD,
	PARA,
	DATA,
	CHECK,
	TAIL,
}FingerState_t;
typedef enum
{
	exeFree,
	exeSended,
	exeRecving,
}exeState_t;
typedef enum
{
	OnLine,
	OffLine

}FingerOnlineState_t;

typedef void (*FingerNotify_t)(unsigned char ,int ,unsigned char *, unsigned int );

extern FingerNotify_t fingerCallback;

class Finger {
public:
	Finger();
	virtual ~Finger();

	//添加一个指纹，返回添加成功与否
	bool add_featurs_sync(uint16_t *id/*返回ID*/,string &features/*指纹数据*/);

	void get_features_async();//获取当前输入指纹的模板信息

	void get_id_features_async(uint16_t id);//获取指定ID的指纹模板信息,异步模式
	bool get_id_features(uint16_t id,unsigned char *features);//获取指定ID的指纹模板信息，同步等待模式

	bool set_id_features(uint16_t id,const unsigned char *features);
	bool set_id_features(uint16_t id,string &features);

	void clear_async(void);
	bool delete_id_features(uint16_t id);//获取指定ID的指纹模板信息

	void	 get_total_num_async();
	uint16_t get_total_num();
	void search();

	uint16_t search_features(const unsigned char *features);
	uint16_t search_features(string &features);
	uint16_t search_features_base64(string &Base64FeatureString);

	bool  get_free(uint16_t start,uint16_t end,uint16_t *freeid);
	void roll_step1(unsigned int u_id);
	void roll_step2(unsigned int u_id);
	void roll_step3(unsigned int u_id);
	void get_timeout();
	void set_timeout(unsigned char sec);


	string err_to_string(int err);
	bool is_on_search(){return on_search_state;};
	void set_search_state(bool state){on_search_state = state;};

	void check_online_async();
	bool is_online(){return online_state;};
	void set_online(bool state){online_state = state;};

	void parser(char ch);

	int ack;
	int retState;
	long timelast;
	int dataLen;

private:
	unsigned char genCheck(unsigned char wLen,unsigned char *ptr);

private:
	unsigned char rbuf[256];
	unsigned char tbuf[256];
	FingerState_t state;
	int cmdState;
	unsigned char cmd;
	unsigned char check;
	unsigned int counter;
	bool on_search_state;
	bool online_state;

	void send_package(unsigned char *ptr,unsigned char wLen);

	int parse_head(char ch);
	int parse_date(char ch);

};
extern Finger finger;


#endif /* JNI_FINGER_H_ */
