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
}



