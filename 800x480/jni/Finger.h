/*
 * Finger.h
 *
 *  Created on: 2019年1月14日
 *      Author: shentq
 */

#ifndef JNI_FINGER_H_
#define JNI_FINGER_H_




#define TRUE  0x01
#define FALSE  0x00

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

#define ACK_SUCCESS  		0x00	//操作成功
#define ACK_FAIL	  		0x01	//操作失败
#define ACK_FULL	  		0x04	//指纹数据库已满
#define ACK_NOUSER   		0x05	//无此用户
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

class Finger {
public:
	Finger();
	virtual ~Finger();

	unsigned char genCheck(unsigned char wLen,unsigned char *ptr);
	void makePackage(unsigned char wLen,unsigned char *ptr);
	void rx_event(char ch);
	void getFeatures();
private:
	unsigned char rbuf[4096];
	unsigned char tbuf[4096];
	unsigned char rxEnd ;              //接收返回信息结束标志
	unsigned char rxLen ;             //接收返回信息长度
	FingerState_t state;
	unsigned char cmd;
	unsigned char check;
	unsigned char cmdState;
	unsigned int counter;
	bool 	busy;
};
extern Finger finger;


#endif /* JNI_FINGER_H_ */
