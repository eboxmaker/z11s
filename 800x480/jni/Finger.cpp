/*
 * Finger.cpp
 *
 *  Created on: 2019年1月14日
 *      Author: shentq
 */

#include "Finger.h"
#include "uart/Uart.h"
#include "utils/log.h"

Finger::Finger() :
		busy(false),
		state(HEAD),
		cmdState(0),
		counter(0){
	// TODO 自动生成的构造函数存根

}

Finger::~Finger() {
	// TODO 自动生成的析构函数存根
}
void Finger::getFeatures()
{
	unsigned char buf[8];
	int i = 0;
	buf[i++] = 0x23;
	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;
	makePackage(5,buf);
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
void Finger::makePackage(unsigned char wLen,unsigned char *ptr)
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
  if(busy == false)
  {
	  uart2.send(tbuf,len);
	  busy = true;
  }
  else
  {
	  LOGE("finger busy now...");
  }

}

void Finger::rx_event(char ch)
{
	LOGE("rx event %D:%d(%d):%x\r\n",counter,state,cmdState,ch);

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
			if(cmd == 0x23)
				cmdState = 1;
			break;

		case DATA:
			rbuf[counter++] = ch;
			if(counter == 197)
			{
				state = CHECK;
				cmdState = 0;
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
					LOGE("finger parse ok\n");
				else
					LOGE("finger check err");
			}
			else
			{
				LOGE("ERR\r\n");
			}
			counter = 0;
			state = HEAD;
			busy = false;
			break;

		default:
			break;

	}
}
Finger finger;
