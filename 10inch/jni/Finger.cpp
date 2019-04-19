/*
 * Finger.cpp
 *
 *  Created on: 2019年1月14日
 *      Author: shentq
 */

#include "uart/Uart.h"
#include "utils/log.h"
#include "Finger.h"

using namespace std;


FingerNotify_t fingerCallback;

Finger::Finger() :
		ack(-1),
		exeState(exeFree),
		state(HEAD),
		cmdState(0),
		counter(0){
	// TODO 自动生成的构造函数存根
	fingerCallback = NULL;
}

Finger::~Finger() {
	// TODO 自动生成的析构函数存根
}
/*******************************************************************************
**注册指纹
**输入两次指纹注册一个指纹模板
**参数：UserID 指纹号
*******************************************************************************/
void Finger::Enroll_Step1(unsigned int u_id)
{
  unsigned char buf[8];

  *buf = CMD_ENROLL1;
  *(buf+1) = u_id>>8;
  *(buf+2) = u_id&0xff;
  *(buf+3) = 1;
  *(buf+4) = 0x00;

  sendPackage( buf ,5);
}

/*******************************************************************************
**注册指纹
**输入两次指纹注册一个指纹模板
**参数：UserID 指纹号
*******************************************************************************/
void Finger::Enroll_Step2(unsigned int u_id)
{
  unsigned char buf[8];

  *buf = CMD_ENROLL2;
  *(buf+1) = u_id>>8;
  *(buf+2) = u_id&0xff;
  *(buf+3) = 1;
  *(buf+4) = 0x00;

   sendPackage(buf ,5);
}

/*******************************************************************************
**注册指纹
**输入三次指纹注册一个指纹模板
**参数：UserID 指纹号
*******************************************************************************/
void Finger::Enroll_Step3(unsigned int u_id)
{
  unsigned char buf[8];

  *buf = CMD_ENROLL3;
  *(buf+1) = u_id>>8;
  *(buf+2) = u_id&0xff;
  *(buf+3) = 1;
  *(buf+4) = 0x00;

  sendPackage(buf ,5);
}

/*******************************************************************************
**注册指纹
**输入三次指纹注册一个指纹模板
**参数：UserID 指纹号
*******************************************************************************/
unsigned char Finger::Finger_Enroll(unsigned int u_id)
{
	bool ret = false;

	LOGE("注册%d",u_id);

//
//	//////////////////////////////////////////////
//	ack = -1;
//	while(ret ==false)
//	{
//		ret = Enroll_Step1(u_id);
//		LOGE("正在 第一步");
//		Thread::sleep(1000);
//	}
//
//	ret = false;
//	while(ack == -1)
//	{
//		LOGE("ACK:%D",ack);
//		Thread::sleep(1000);
//	}
//	if(ack == ACK_SUCCESS)
//		LOGE("第一步完成");
//	else
//	{
//		LOGE("第一步失败:%d",ack);
//		return false;
//	}
//	//////////////////////////////////////////////
//
//
//	ack = -1;
//	while(ret ==false)
//	{
//		ret = Enroll_Step2(u_id);
//		LOGE("正在 第2步");
//		Thread::sleep(1000);
//	}
//
//	ret = false;
//	while(ack == -1)
//	{
//		LOGE("ACK:%D",ack);
//		Thread::sleep(1000);
//	}
//	if(ack == ACK_SUCCESS)
//		LOGE("第2步完成");
//	else
//	{
//		LOGE("第2步失败:%d",ack);
//		return false;
//	}
//	//////////////////////////////////////////////
//	ack = -1;
//
//	while(ret ==false)
//	{
//		ret = Enroll_Step3(u_id);
//		LOGE("正在 第3步");
//		Thread::sleep(1000);
//	}
//	while(ack == -1)
//	{
//		LOGE("ACK:%D",ack);
//		Thread::sleep(1000);
//	}
//	if(ack == ACK_SUCCESS)
//		LOGE("第3步完成");
//	else
//	{
//		LOGE("第3步失败:%d",ack);
//		return false;
//	}

}
void Finger::getFeatures()
{
	int ret;
	unsigned char buf[8];
	int i = 0;
	buf[i++] = CMD_GET_CURRENT_FEATURE;
	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;

	sendPackage(buf,5);

}
//获取指定ID的指纹模板信息
void Finger::getFeatures(unsigned int id)
{
	unsigned char buf[8];
	int i = 0;
	buf[i++] = CMD_GET_ID_FEATURE;
	buf[i++] = id>>8;
	buf[i++] = id&0xff;
	buf[i++] = 0;
	buf[i++] = 0;
	sendPackage(buf,5);
}


//上传从服务器获取的人员的模板信息，并存入指定区间（10-39）
void Finger::setIdFeatures(unsigned int id,unsigned char *sbuf)
{
	unsigned char buf[256];
	int i = 0;
	buf[i++] = CMD_SET_ID_FEATURE;
	buf[i++] = id>>8;
	buf[i++] = id&0xff;
	buf[i++] = 0;
	buf[i++] = 0;
	sendPackage(buf,5) ;


	i = 0;
	buf[i++] = id>>8;
	buf[i++] = id&0xff;
	buf[i++] = 0;
	for(int j = 0; j < 193; j++)
	{
		buf[i++] = sbuf[j];
	}
	 sendPackage(buf,5);
}

/*******************************************************************************
**功能：清空 flash 指纹库
**参数：
**返回：无
*******************************************************************************/
void Finger::clear(void)
{
	int ret = -1;
  unsigned char buf[8];

  *buf = CMD_CLEAR;
  *(buf+1) = 0x00;
  *(buf+2) = 0x00;
  *(buf+3) = 0x00;
  *(buf+4) = 0x00;

   sendPackage(buf,5);

}
void Finger::getTimeout()
{
	int ret;
	unsigned char buf[8];

	*buf = CMD_TIMEOUT;
	*(buf+1) = 0x00;
	*(buf+2) = 0x00;
	*(buf+3) = 0x01;
	*(buf+4) = 0x00;

	sendPackage(buf,5);
}
void Finger::setTimeout(unsigned char sec)
{
	int ret;
	unsigned char buf[8];

	*buf = CMD_TIMEOUT;
	*(buf+1) = 0x00;
	*(buf+2) = sec;
	*(buf+3) = 0x00;
	*(buf+4) = 0x00;
	sendPackage(buf,5);
}

/*******************************************************************************
**功能: 计算校验值
**参数: 要发送的数据指针地址
**返回: 校验值
*******************************************************************************/
unsigned char Finger::genCheck(unsigned char wLen,unsigned char *ptr)
{
	unsigned char i,temp = 0;

	for(i = 0; i < wLen; i++)
	{
		temp ^= *(ptr + i);
	}
	return temp;
}

/*******************************************************************************
**功能: 发送控制指纹芯片指令
**参数: wLen 数据长度
        cpPara 发送的数据
**返回：void
*******************************************************************************/
void Finger::sendPackage(unsigned char *ptr,unsigned char wLen)
{
  unsigned int i=0,len=0;


  tbuf[0] = DATA_START;//指令包
  for(i = 0; i < wLen; i++)      // data in packet
  {
	  tbuf[1+i] = *(ptr+i);
  }
  tbuf[wLen + 1] = genCheck(wLen, ptr);         //Generate checkout data
  tbuf[wLen + 2] = DATA_END;
  len = wLen + 3;
  uart2.send(tbuf,len);
  LOGD("发送一帧数据");
}

string Finger::errToString(int err)
{
	string errStr;
	switch(err)
	{
	case ACK_SUCCESS:
		errStr = "OK";
		break;
	case ACK_FAIL:
		errStr = "opt err";
		break;
	case ACK_FULL:
		errStr = "flash full";
		break;
	case ACK_NOUSER:
		errStr = "no user";
		break;

	case ACK_USER_OCCUPIED:
		errStr = "user occupied";
		break;

	case ACK_USER_EXIST:
		errStr = "user exist";
		break;

	case ACK_TIMEOUT:
		errStr = "timeout";
		break;
	default:
		errStr = "UNKOWN";
		break;
	}
	return errStr;

}
int Finger::parseHead(char ch)
{
	static bool isHaveDate = false;

	switch(state)
	{
		case HEAD:
			if(ch == 0xf5)
			{
				rbuf[counter++] = ch;
				state = CMD;
			}
			retState = 1;
			break;
		case CMD:
			rbuf[counter++] = ch;
			state = PARA;
			retState = 2;
			break;
		case PARA:
			rbuf[counter++] = ch;
			if(counter == 6)
				state = CHECK;
			retState = 3;
			break;
		case CHECK:
			check = ch;
			rbuf[counter++] = ch;
			state = TAIL;
			retState = 4;
			break;
		case TAIL:
			if(ch == 0XF5)
			{

				rbuf[counter++] = ch;
				unsigned int temp = genCheck(counter - 3,&rbuf[1]);
				if(temp == check)
				{
					cmd = rbuf[1];
					ack = rbuf[4];

					if(fingerCallback != NULL)
						fingerCallback(cmd,cmdState,&rbuf[2],2);
					LOGD("finger parse ok\n");
					if(cmd == CMD_GET_CURRENT_FEATURE || cmd == CMD_GET_ID_FEATURE)
					{
						if(rbuf[4] == ACK_SUCCESS || rbuf[4] == ACK_TIMEOUT)
						{
							dataLen  = ((rbuf[2])<<8) + rbuf[3];

							cmdState = 1;
						}
					}
					retState = 0;
				}
				else
				{
					LOGE("finger check err");
					retState = 5;
				}
			}
			else
			{
				LOGE("ERR\r\n");
				retState = 6;
			}
			counter = 0;
			state = HEAD;
			break;
		default:
			cmdState = 0;
			counter = 0;
			state = HEAD;
			break;
	}
	return retState;

}
int Finger::parseDate(char ch)
{

	static bool isHaveDate = false;

	switch(state)
	{
		case HEAD:
			if(ch == 0xf5)
			{
				rbuf[counter++] = ch;
				if(dataLen != 0)
					state = DATA;
				else
					state = CHECK;
			}
			retState = 1;
			break;
		case DATA:
			rbuf[counter++] = ch;
			if(counter == dataLen + 1)
				state = CHECK;
			retState = 3;
			break;
		case CHECK:
			check = ch;
			rbuf[counter++] = ch;
			state = TAIL;
			retState = 4;
			break;
		case TAIL:
			if(ch == 0XF5)
			{
				rbuf[counter++] = ch;
				unsigned int temp = genCheck(counter - 3,&rbuf[1]);
				if(temp == check)
				{
					if(fingerCallback != NULL)
						fingerCallback(cmd,cmdState,&rbuf[1],dataLen);

					cmdState = 0;
					LOGD("finger parse ok\n");
					retState = 0;
				}
				else
				{
					LOGE("finger check err");
					retState = 5;
				}
			}
			else
			{
				cmdState = 0;
				counter = 0;
				state = HEAD;
				LOGE("帧结构出错\r\n");
				retState = 6;

			}
			counter = 0;
			state = HEAD;
			break;
		default:
			cmdState = 0;
			counter = 0;
			state = HEAD;
			break;
	}
	return retState;
}
void Finger::parser(char ch)
{
	//LOGD("rx event %D:%d(%d):%x\r\n",counter,state,cmdState,ch);
	switch(cmdState)
	{
		case 0:
			retState = parseHead(ch);
			break;
		case 1:
			retState = parseDate(ch);
			break;
		default:
			LOGD("异常错误");
			break;

	}

}


Finger finger;
