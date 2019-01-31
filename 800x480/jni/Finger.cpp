/*
 * Finger.cpp
 *
 *  Created on: 2019年1月14日
 *      Author: shentq
 */

#include "Finger.h"
#include "uart/Uart.h"
#include "utils/log.h"

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
bool Finger::Enroll_Step1(unsigned int u_id)
{
  unsigned char buf[8];

  *buf = CMD_ENROLL1;
  *(buf+1) = u_id>>8;
  *(buf+2) = u_id&0xff;
  *(buf+3) = 1;
  *(buf+4) = 0x00;

  sendPackage(5, buf);
}

/*******************************************************************************
**注册指纹
**输入两次指纹注册一个指纹模板
**参数：UserID 指纹号
*******************************************************************************/
bool Finger::Enroll_Step2(unsigned int u_id)
{
  unsigned char buf[8];

  *buf = CMD_ENROLL2;
  *(buf+1) = u_id>>8;
  *(buf+2) = u_id&0xff;
  *(buf+3) = 1;
  *(buf+4) = 0x00;

  sendPackage(5, buf);
}

/*******************************************************************************
**注册指纹
**输入三次指纹注册一个指纹模板
**参数：UserID 指纹号
*******************************************************************************/
bool Finger::Enroll_Step3(unsigned int u_id)
{
  unsigned char buf[8];

  *buf = CMD_ENROLL3;
  *(buf+1) = u_id>>8;
  *(buf+2) = u_id&0xff;
  *(buf+3) = 1;
  *(buf+4) = 0x00;

  sendPackage(5, buf);
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


	//////////////////////////////////////////////
	ack = -1;
	while(ret ==false)
	{
		ret = Enroll_Step1(u_id);
		LOGE("正在 第一步");
		Thread::sleep(1000);
	}

	ret = false;
	while(ack == -1)
	{
		LOGE("ACK:%D",ack);
		Thread::sleep(1000);
	}
	if(ack == ACK_SUCCESS)
		LOGE("第一步完成");
	else
	{
		LOGE("第一步失败:%d",ack);
		return false;
	}
	//////////////////////////////////////////////


	ack = -1;
	while(ret ==false)
	{
		ret = Enroll_Step2(u_id);
		LOGE("正在 第2步");
		Thread::sleep(1000);
	}

	ret = false;
	while(ack == -1)
	{
		LOGE("ACK:%D",ack);
		Thread::sleep(1000);
	}
	if(ack == ACK_SUCCESS)
		LOGE("第2步完成");
	else
	{
		LOGE("第2步失败:%d",ack);
		return false;
	}
	//////////////////////////////////////////////
	ack = -1;

	while(ret ==false)
	{
		ret = Enroll_Step3(u_id);
		LOGE("正在 第3步");
		Thread::sleep(1000);
	}
	while(ack == -1)
	{
		LOGE("ACK:%D",ack);
		Thread::sleep(1000);
	}
	if(ack == ACK_SUCCESS)
		LOGE("第3步完成");
	else
	{
		LOGE("第3步失败:%d",ack);
		return false;
	}

}
bool Finger::getFeatures()
{
	unsigned char buf[8];
	int i = 0;
	buf[i++] = CMD_GET_CURRENT_FEATURE;
	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;
	return sendPackage(5,buf);
}
//获取指定ID的指纹模板信息
bool Finger::getFeatures(unsigned int id)
{
	unsigned char buf[8];
	int i = 0;
	buf[i++] = CMD_GET_ID_FEATURE;
	buf[i++] = id>>8;
	buf[i++] = id&0xff;
	buf[i++] = 0;
	buf[i++] = 0;
	return sendPackage(5,buf);
}


//上传从服务器获取的人员的模板信息，并存入指定区间（10-39）
bool Finger::setIdFeatures(unsigned int id,unsigned char *sbuf)
{
	unsigned char buf[256];
	int i = 0;
	buf[i++] = CMD_SET_ID_FEATURE;
	buf[i++] = id>>8;
	buf[i++] = id&0xff;
	buf[i++] = 0;
	buf[i++] = 0;
	while( sendPackage(5,buf) == false);
	i = 0;
	buf[i++] = id>>8;
	buf[i++] = id&0xff;
	buf[i++] = 0;
	for(int j = 0; j < 193; j++)
	{
		buf[i++] = sbuf[j];
	}
	return sendPackage(5,buf);
}

/*******************************************************************************
**功能：清空 flash 指纹库
**参数：
**返回：无
*******************************************************************************/
bool Finger::clear(void)
{
  unsigned char buf[8];

  *buf = CMD_CLEAR;
  *(buf+1) = 0x00;
  *(buf+2) = 0x00;
  *(buf+3) = 0x00;
  *(buf+4) = 0x00;

  return sendPackage(5, buf);
}
bool Finger::readTimeout()
{
	  unsigned char buf[8];

	  *buf = CMD_TIMEOUT;
	  *(buf+1) = 0x00;
	  *(buf+2) = 0x00;
	  *(buf+3) = 0x01;
	  *(buf+4) = 0x00;

	  return sendPackage(5, buf);
}
bool Finger::setTimeout(unsigned char sec)
{
	  unsigned char buf[8];

	  *buf = CMD_TIMEOUT;
	  *(buf+1) = 0x00;
	  *(buf+2) = sec;
	  *(buf+3) = 0x00;
	  *(buf+4) = 0x00;

	  return sendPackage(5, buf);
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
bool Finger::sendPackage(unsigned char wLen,unsigned char *ptr)
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

  //如果3s内模块没有响应，则重置模块为空闲状态
  if(time(NULL) - lastCmdTime >= 1)
	  exeState = exeFree;

  if(exeState == exeFree)
  {
	  uart2.send(tbuf,len);
	  for(int i =0;i<len;i++)
	  {
		  LOGD("SEND:%X",tbuf[i]);
	  }
	  exeState = exeSended;
	  lastCmdTime = time(NULL);
		state = HEAD;
		counter = 0;
	  return true;
  }
  else
  {
	  LOGE("finger busy now(%d)...",exeState);
	  return false;
  }

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

void Finger::rx_event(char ch)
{
	char err = -1;
	//LOGE("rx event %D:%d(%d):%x\r\n",counter,state,cmdState,ch);
	exeState = exeRecving;
	switch(state)
	{
		case HEAD:
		if(ch == 0xf5)
		{
			if(cmdState == 0)
				state = CMD;
			else
				state = DATA;
			rbuf[counter++] = ch;
		}
		else
		{

		}
		break;

		case CMD:

			cmd = ch;
			rbuf[counter++] = ch;
			state = PARA;
			if(cmd == CMD_GET_CURRENT_FEATURE || cmd == CMD_GET_ID_FEATURE)
				cmdState = 1;
			break;

		case DATA:
			rbuf[counter++] = ch;
			if(counter == 197)
			{
				state = CHECK;
				cmdState = 0;//数据帧接收完成
			}
			else
			{

			}
			break;

		case PARA:
			rbuf[counter++] = ch;
			if(counter == 6)
			{
				state = CHECK;
			}
			else
			{

			}
			break;
		case CHECK:
			check = ch;
			rbuf[counter++] = ch;
			state = TAIL;
			break;

		case TAIL:
			if(ch == 0XF5)
			{
				rbuf[counter++] = ch;
				unsigned int temp = genCheck(counter - 3,&rbuf[1]);
				if(temp == check)
				{
					err = 0;
					LOGE("finger parse ok\n");
				}
				else
				{
					LOGE("finger check err");
				}
			}
			else
			{
				state = HEAD;
				counter = 0;
				exeState = exeFree;
				LOGE("ERR\r\n");
				break;
			}
			if(cmdState == 0)
			{
				exeState = exeFree;
				switch(cmd)
				{
				case CMD_GET_CURRENT_FEATURE:
					if(fingerCallback != NULL)
						fingerCallback(cmd,cmdState,&rbuf[4],counter - 6);
					break;
				case CMD_GET_ID_FEATURE:
					if(fingerCallback != NULL)
						fingerCallback(cmd,cmdState,&rbuf[1],counter - 3);
					break;
				case CMD_CLEAR:
				case CMD_TIMEOUT:
				case CMD_ENROLL1:
				case CMD_ENROLL2:
				case CMD_ENROLL3:
					ack = rbuf[4];
					if(fingerCallback != NULL)
						fingerCallback(cmd,cmdState,&rbuf[2],counter - 4);
					break;

				}
			}
			if(cmdState == 1)//含有数据包的命令会有数据头帧
			{
				switch(cmd)
				{
				case CMD_GET_CURRENT_FEATURE:
				case CMD_GET_ID_FEATURE:

					if(fingerCallback != NULL)
						fingerCallback(cmd,cmdState,&rbuf[2],counter - 4);
					if(rbuf[4] != ACK_SUCCESS)//后面没有数据包
					{
						cmdState = 0;

					}
					break;
				default:
					break;
				}
			}

			counter = 0;
			state = HEAD;
			break;
		default:
			break;

	}

}
Finger finger;
