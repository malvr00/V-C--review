
// ServerSocketDlg.h: 헤더 파일
//

#pragma once
#include "CMyServerSocket.h"
#include "CMySocket.h"

// CServerSocketDlg 대화 상자
class CServerSocketDlg : public CDialogEx
{
// 생성입니다.
public:
	CServerSocketDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERSOCKET_DIALOG };
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

	CMyServerSocket m_Server;			// Server Socket
	CMySocket m_Client;				// Client Socket
public:
	afx_msg void OnClickedStartBt();
	afx_msg void OnClickedStopBt();
	CButton m_ctrlStartBt;
	CButton m_ctrlStopBt;
	int m_nPortNo;
	CEdit m_ctrlMsg;
	CString m_strMsg;

	afx_msg LRESULT OnReceiveMsg(WPARAM wParam, LPARAM lParam);		// Client Receive Message 처리
	afx_msg LRESULT OnAcceptMsg(WPARAM wParam, LPARAM lParam);		// Server Socket Accept Message 처리
};
