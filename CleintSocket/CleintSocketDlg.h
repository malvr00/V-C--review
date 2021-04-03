
// CleintSocketDlg.h: 헤더 파일
//

#pragma once

#include "CMySocket.h"

// CCleintSocketDlg 대화 상자
class CCleintSocketDlg : public CDialogEx
{
// 생성입니다.
public:
	CCleintSocketDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLEINTSOCKET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CMySocket m_Socket;			// 접속자 클라이언트 소켓.
public:
	LRESULT OnReceiveMsg(WPARAM wParam, LPARAM lParam);   // Receive 메세지 처리 함수


	bool m_bConnect;			// 메세지가로체기에서 활용.

	CButton m_ctrlConnectBt;
	CButton m_ctrlDisConnetBt;
	CButton m_ctrlSendBT;
	CEdit m_ctrlIpAddress;
	CString m_strIpAddress;
	int m_nPortNo;
	CEdit m_ctrlSendData;
	CString m_strSendData;
	CEdit m_ctrlReceiveData;
	CString m_strReceiveData;

	afx_msg void OnClickedConnetBt();		// Server 연결
	afx_msg void OnClickedDisconnetBt();	// Server 연결 끊기
	afx_msg void OnClickedSendBt();			// Message 보내기
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
