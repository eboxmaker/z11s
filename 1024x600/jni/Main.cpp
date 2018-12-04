#include "entry/EasyUIContext.h"
#include "uart/UartContext.h"
#include "manager/ConfigManager.h"
#include "net/NetManager.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

void onEasyUIInit(EasyUIContext *pContext) {
	// 初始化时打开串口
	UARTCONTEXT->openUart(CONFIGMANAGER->getUartName().c_str(), CONFIGMANAGER->getUartBaudRate());
	WifiManager *pWM = NETMANAGER->getWifiManager();

	pWM->connect("syzx", "syzx22213621362");

}

void onEasyUIDeinit(EasyUIContext *pContext) {
	UARTCONTEXT->closeUart();
}

const char* onStartupApp(EasyUIContext *pContext) {
	return "mainActivity";
}


#ifdef __cplusplus
}
#endif  /* __cplusplus */

