#include "../lib/ThostFtdcTraderApi.h"


class MyTraderSpi :public CThostFtdcTraderSpi
{
public:
	MyTraderSpi(CThostFtdcTraderApi* instance);
	~MyTraderSpi();
	virtual void OnFrontConnected();
	virtual void OnFrontDisConnected(int nReason);
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
private:
	CThostFtdcTraderApi* m_ptrTraderApi;
};



