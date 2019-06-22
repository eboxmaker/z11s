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
#define CMD_GET_ID_FEATURE			0x31//超时时间
#define CMD_SET_ID_FEATURE			0x41//超时时间




#define ACK_SUCCESS  		0x00	//操作成功
#define ACK_FAIL	  		0x01	//操作失败
#define ACK_FULL	  		0x04	//指纹数据库已满
#define ACK_NOUSER   		0x05	//无此用户
#define ACK_USER_OCCUPIED   0x06    //此ID用户已存在
#define ACK_USER_EXIST 		0x07 	//用户已存在
#define ACK_TIMEOUT  		0x08	//采集超时
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

	void getFeatures();//获取当前输入指纹的模板信息

	void getFeatures(unsigned int id);//获取指定ID的指纹模板信息
	void setIdFeatures(unsigned int id,unsigned char *buf);//上传从服务器获取的人员的模板信息，并存入指定区间（10-39）

	void clear(void);
	void deleteIdFeatures(unsigned int id);//获取指定ID的指纹模板信息

	void Enroll_Step1(unsigned int u_id);
	void Enroll_Step2(unsigned int u_id);
	void Enroll_Step3(unsigned int u_id);
	void getTimeout();
	void setTimeout(unsigned char sec);
	void sendPackage(unsigned char *ptr,unsigned char wLen);
	void rx_event(char ch);

	int parseHead(char ch);
	int parseDate(char ch);
	void parser(char ch);
	string errToString(int err);
	int ack;
	int retState;
	long timelast;
	int dataLen;

private:
	unsigned char genCheck(unsigned char wLen,unsigned char *ptr);

private:
	unsigned char rbuf[1024];
	unsigned char tbuf[512];
	unsigned char rxEnd ;              //接收返回信息结束标志
	unsigned char rxLen ;             //接收返回信息长度
	FingerState_t state;
	unsigned char cmd;
	unsigned char check;
	int cmdState;
	unsigned int counter;
	exeState_t exeState;
	long lastCmdTime;
	bool is_requesting_finger;


};
extern Finger finger;


#endif /* JNI_FINGER_H_ */
