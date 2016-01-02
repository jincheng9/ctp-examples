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
	
	// settlementinfo confirm
	cout << "ReqQrySettlementInfoConfirm" << endl;
	CThostFtdcSettlementInfoConfirmField settlement;
	strcpy(settlement.BrokerID, pRspUserLogin->BrokerID);
	strcpy(settlement.InvestorID, pRspUserLogin->UserID);
	m_ptrTraderApi->ReqSettlementInfoConfirm(&settlement, 1);
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

void MyTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspSettlementInfoConfirm" << endl;
	cout << "error id:" << pRspInfo->ErrorID << endl;
	cout << "error message:" << pRspInfo->ErrorMsg << endl;

	// ReqOrderInsert
	CThostFtdcInputOrderField order;
	memset(&order, 0, sizeof(order));

	strcpy(order.BrokerID, pSettlementInfoConfirm->BrokerID);
	strcpy(order.InvestorID, pSettlementInfoConfirm->InvestorID);
	strcpy(order.InstrumentID, "cu1605");
	strcpy(order.OrderRef, "0003");
	strcpy(order.UserID, pSettlementInfoConfirm->InvestorID);
	order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	order.Direction = THOST_FTDC_D_Buy;
	strcpy(order.CombOffsetFlag, "0");
	strcpy(order.CombHedgeFlag, "1");
	order.LimitPrice = 0;
	order.VolumeTotalOriginal = 1;
	order.TimeCondition = THOST_FTDC_TC_GFD;
	strcpy(order.GTDDate, "");
	order.VolumeCondition = THOST_FTDC_VC_AV;
	order.MinVolume = 0;
	order.ContingentCondition = THOST_FTDC_CC_Immediately;
	order.StopPrice = 0;
	order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	order.IsAutoSuspend = false;

	m_ptrTraderApi->ReqOrderInsert(&order, 2);
}

void MyTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspError..." << endl;
	cout << "error id:" << pRspInfo->ErrorID << endl;
	cout << "error message:" << pRspInfo->ErrorMsg << endl;
}