#include "../lib/ThostFtdcTraderApi.h"
#include "../lib/ThostFtdcUserApiDataType.h"
#include "../lib/ThostFtdcUserApiStruct.h"
#include "MyTraderSpi.h"

#include <iostream>
using namespace std;


int main()
{
	cout << "hello world" << endl;

	CThostFtdcTraderApi* instance = CThostFtdcTraderApi::CreateFtdcTraderApi();
	
	MyTraderSpi spi(instance);

	instance->RegisterSpi(&spi);
	instance->SubscribePrivateTopic(THOST_TERT_RESUME);
	instance->SubscribePublicTopic(THOST_TERT_RESUME);
	//instance->RegisterFront("tcp://180.168.146.187:10000");
	instance->RegisterFront("tcp://180.168.146.187:10030");
	instance->Init();

	instance->Join();
	instance->Release();
	return 0;
}