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
	// login
	CThostFtdcReqUserLoginField reqUserLogin;
	TThostFtdcBrokerIDType brokerId;
	cout << "input broker id:";
	cin >> brokerId;
	strcpy(reqUserLogin.BrokerID, brokerId);

	TThostFtdcUserIDType userId;
	cout << "input user id:";
	cin >> userId;
	strcpy(reqUserLogin.UserID, userId);

	TThostFtdcPasswordType pwd;
	cout << "input password:";
	cin >> pwd;
	strcpy(reqUserLogin.Password, pwd);

	m_ptrTraderApi->ReqUserLogin(&reqUserLogin, 0);
}

void MyTraderSpi::OnFrontDisConnected(int nReason)
{
	cout << "disconnected" << endl;
}
void MyTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspUserLogin" << endl;
	cout << "error id: " << pRspInfo->ErrorID << endl;
	cout << "error message: " << pRspInfo->ErrorMsg << endl;
	
	if (pRspInfo->ErrorID != 0)
	{
		exit(-1);
	}

	// print response
	cout << "broker id:" << pRspUserLogin->BrokerID << endl;
	cout << "user id:" << pRspUserLogin->UserID << endl;
	cout << "login time:" << pRspUserLogin->LoginTime << endl;
	cout << "tradingday:" << pRspUserLogin->TradingDay << endl;
	cout << "system name:" << pRspUserLogin->SystemName << endl;
	cout << "front id:" << pRspUserLogin->FrontID << endl;
	cout << "session id:" << pRspUserLogin->SessionID << endl;
	cout << "max orderRef:" << pRspUserLogin->MaxOrderRef << endl;
	cout << "shfe time:" << pRspUserLogin->SHFETime << endl;
	cout << "dce time:" << pRspUserLogin->DCETime << endl;
	cout << "czce time:" << pRspUserLogin->CZCETime << endl;
	cout << "ffex time" << pRspUserLogin->FFEXTime << endl;
	// ReqOrderInsert
	CThostFtdcInputOrderField order;
	memset(&order, 0, sizeof(order));

}
 


