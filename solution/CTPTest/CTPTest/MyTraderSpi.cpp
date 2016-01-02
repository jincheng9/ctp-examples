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

	strcpy(order.BrokerID, pRspUserLogin->BrokerID);
	strcpy(order.InvestorID, pRspUserLogin->UserID);
	strcpy(order.InstrumentID, "cu1605");
	strcpy(order.OrderRef, "0002");
	strcpy(order.UserID, pRspUserLogin->UserID);
	order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	order.Direction = THOST_FTDC_D_Buy;
	strcpy(order.CombOffsetFlag, "0");
	strcpy(order.CombHedgeFlag, "1");
	order.LimitPrice = 39000;
	order.VolumeTotalOriginal = 3;
	order.TimeCondition = THOST_FTDC_TC_GFD;
	strcpy(order.GTDDate, "");
	order.VolumeCondition = THOST_FTDC_VC_AV;
	order.MinVolume = 0;
	order.ContingentCondition = THOST_FTDC_CC_Immediately;
	order.StopPrice = 0;
	order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	order.IsAutoSuspend = false;

	m_ptrTraderApi->ReqOrderInsert(&order, 1);

}

void MyTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspOrderInsert" << endl;
	cout << "error id:" << pRspInfo->ErrorID << endl;
	cout << "error message:" << pRspInfo->ErrorMsg << endl;
}

void MyTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) 
{
	cout << "OnRtnOrder" << endl;
	cout << "orderSysID:" << pOrder->OrderSysID << endl;
}

void MyTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	cout << "OnRtnTrade..." << endl;
	cout << "orderSysID:" << pTrade->OrderSysID << endl;
}

void MyTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	cout << "OnErrRtnOrderInsert" << endl;
	cout << "error id:" << pRspInfo->ErrorID << endl;
	cout << "error message:" << pRspInfo->ErrorMsg << endl;
}