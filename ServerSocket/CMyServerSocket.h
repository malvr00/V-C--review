#pragma once

// CMyServerSocket 명령 대상

#define UM_ACCEPT (WM_USER + 2)   // Accept Message 생성

class CMyServerSocket : public CSocket
{
public:
	CMyServerSocket();
	virtual ~CMyServerSocket();
	virtual void OnAccept(int nErrorCode);
	bool ServerStart(int nPort);
};


