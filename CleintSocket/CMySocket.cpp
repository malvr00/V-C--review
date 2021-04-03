// CMySocket.cpp: 구현 파일
//

#include "pch.h"
#include "CleintSocket.h"
#include "CMySocket.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 멤버 함수


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	AfxGetMainWnd()->PostMessage(UM_RECEIVE);

	CSocket::OnReceive(nErrorCode);
}
