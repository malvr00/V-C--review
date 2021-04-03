#pragma once

// CMySocket 명령 대상

#define UM_RECEIVE (WM_USER + 1)		// 내가 만든 Receive Message

class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnReceive(int nErrorCode);
};


