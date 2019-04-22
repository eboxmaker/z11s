/*
 * Uart.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: guoxs
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <termio.h>
#include <sys/ioctl.h>

#include "uart/Uart.h"
#include "utils/Log.h"
#include "lib/finger.h"
#define UART_DATA_BUF_LEN			2048	// 16KB


MyUart::MyUart() :
	mIsOpen(false),
	mUartID(0),
	mDataBufPtr(NULL),
	mDataBufLen(0) {

}

MyUart::~MyUart() {
	delete[] mDataBufPtr;
	closeUart();
}

bool MyUart::openUart(const char *pFileName, UINT baudRate) {
	mUartID = open(pFileName, O_RDWR|O_NOCTTY);
	LOGD("openUart pFileName = %s, baudRate = %d，id=%d\n", pFileName, baudRate,mUartID);

	if (mUartID <= 0) {
		mIsOpen = false;
	} else {
		struct termios oldtio = { 0 };
		struct termios newtio = { 0 };
		tcgetattr(mUartID, &oldtio);

		newtio.c_cflag = baudRate|CS8|CLOCAL|CREAD;
		newtio.c_iflag = 0;	// IGNPAR | ICRNL
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;	// ICANON
		newtio.c_cc[VTIME] = 0; /* inter-character timer unused */
		newtio.c_cc[VMIN] = 1; /* blocking read until 1 character arrives */
		tcflush(mUartID, TCIOFLUSH);
		tcsetattr(mUartID, TCSANOW, &newtio);

		// 设置为非阻塞
		fcntl(mUartID, F_SETFL, O_NONBLOCK);

		mIsOpen = run("uart");
		if (!mIsOpen) {
			close(mUartID);
			mUartID = 0;
		}

		LOGD("openUart mIsOpen = %d\n", mIsOpen);
	}

	return mIsOpen;
}

void MyUart::closeUart() {
	LOGD("closeUart mIsOpen: %d...\n", mIsOpen);
	if (mIsOpen) {
		requestExit();

		close(mUartID);
		mUartID = 0;
		mIsOpen = false;
	}
}

bool MyUart::send(const BYTE *pData, UINT len) {
	if (!mIsOpen) {
		return false;
	}
	if (write(mUartID, pData, len) != (int) len) {	// fail
		LOGD("send Fail\n");
		return false;
	}

	// success
//	LOGD("send Success\n");

	return true;
}
bool MyUart::readyToRun() {
	if (mDataBufPtr == NULL) {
		mDataBufPtr = new BYTE[UART_DATA_BUF_LEN];
	}

	if (mDataBufPtr == NULL) {
		closeUart();
	}

	return (mDataBufPtr != NULL);
}

bool MyUart::threadLoop() {
	if (mIsOpen) {
		// 可能上一次解析后有残留数据，需要拼接起来
		int readNum = read(mUartID, mDataBufPtr , UART_DATA_BUF_LEN);

		if (readNum > 0) {
			for(int i = 0 ; i < readNum;i++)
			{
				//finger.rx_event(mDataBufPtr[i]);
				finger.parser(mDataBufPtr[i]);

			}

		} else {
			Thread::sleep(10);
		}

		return true;
	}

	return false;
}
MyUart uart2;


