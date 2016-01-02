#include "MyTraderSpi.h"
#include <iostream>
using namespace std;

MyTraderSpi::MyTraderSpi(CThostFtdcTraderApi* instance)
{
	m_ptrTraderApi = instance;
}

MyTraderSpi::~MyTraderSpi()
{
}
void MyTraderSpi::OnFrontConnected()
{
	cout << "connected" << endl;
}

void MyTraderSpi::OnFrontDisConnected(int nReason)
{
	cout << "disconnected" << endl;
}
void MyTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspUserLogin" << endl;
}



