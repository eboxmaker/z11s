/*
 * UartContext.h
 *
 *  Created on: Sep 5, 2017
 *      Author: guoxs
 */

#ifndef _MYUART_H_
#define _MYUART_H_

#include <vector>
#include "system/Thread.h"
#include "uart/CommDef.h"

class MyUart : public Thread {
public:
	MyUart();
	virtual ~MyUart();

	bool openUart(const char *pFileName, UINT baudRate);
	void closeUart();

	bool isOpen() { return mIsOpen; }

	bool send(const BYTE *pData, UINT len);


protected:
	virtual bool readyToRun();
	virtual bool threadLoop();

private:
	bool mIsOpen;
	int mUartID;

	// 用于拼接缓存数据，可能存在上一包数据解析未完全，残留有数据
	BYTE *mDataBufPtr;
	int mDataBufLen;
};
extern MyUart uart2;

#endif /* _UART_UARTCONTEXT_H_ */
