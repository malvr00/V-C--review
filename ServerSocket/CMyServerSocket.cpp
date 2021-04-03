// CMyServerSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ServerSocket.h"
#include "CMyServerSocket.h"


// CMyServerSocket

CMyServerSocket::CMyServerSocket()
{
}

CMyServerSocket::~CMyServerSocket()
{
}


// CMyServerSocket 멤버 함수


void CMyServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	AfxGetMainWnd()->SendMessage(UM_ACCEPT);
	CSocket::OnAccept(nErrorCode);
}

bool CMyServerSocket::ServerStart(int nPort)
{
	// TODO: 여기에 구현 코드 추가.
	if (!Create(nPort)) {		// Server Socket 준비
		return false;			// 오류 발생시 false return
	}
	if (!Listen()) {			// socket 작동 시작 : 접속자가 있는지 기다림
		return false;			// 누군가 접속하면 OnAccept() 호출
	}
	return true;
}
