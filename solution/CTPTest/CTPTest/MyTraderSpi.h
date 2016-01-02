#include "../lib/ThostFtdcTraderApi.h"


class MyTraderSpi :public CThostFtdcTraderSpi
{
public:
	MyTraderSpi(CThostFtdcTraderApi* instance);
	~MyTraderSpi();
	virtual void onFrontConnected();
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
private:
	CThostFtdcTraderApi* m_ptrTraderApi;
};



