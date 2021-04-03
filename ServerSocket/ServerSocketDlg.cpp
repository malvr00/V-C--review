
// ServerSocketDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ServerSocket.h"
#include "ServerSocketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerSocketDlg 대화 상자



CServerSocketDlg::CServerSocketDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVERSOCKET_DIALOG, pParent)
	, m_nPortNo(1234)
	, m_strMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_BT, m_ctrlStartBt);
	DDX_Control(pDX, IDC_STOP_BT, m_ctrlStopBt);
	DDX_Text(pDX, IDC_PORTNO, m_nPortNo);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlMsg);
	DDX_Text(pDX, IDC_EDIT2, m_strMsg);
}

BEGIN_MESSAGE_MAP(CServerSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BT, &CServerSocketDlg::OnClickedStartBt)
	ON_BN_CLICKED(IDC_STOP_BT, &CServerSocketDlg::OnClickedStopBt)
	ON_MESSAGE(UM_ACCEPT, &CServerSocketDlg::OnAcceptMsg)
	ON_MESSAGE(UM_RECEIVE, &CServerSocketDlg::OnReceiveMsg)
END_MESSAGE_MAP()


// CServerSocketDlg 메시지 처리기

BOOL CServerSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CServerSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CServerSocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CServerSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerSocketDlg::OnClickedStartBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_ctrlStartBt.EnableWindow(FALSE);
	m_ctrlStartBt.SetWindowText(_T("Server 실행중"));		// Start 버튼 Text 변경

	// Server 생성 후 Listen. 도중 오류나면 false return
	if (!m_Server.ServerStart(m_nPortNo)) {
		MessageBox(_T("Server Socket 문제 발생"));
		m_ctrlStartBt.EnableWindow(TRUE);
		m_ctrlStartBt.SetWindowText(_T("Server Start"));
		return;
	}
	m_ctrlStopBt.EnableWindow(TRUE);
	m_strMsg += "Server 실행 후 대기 중 입니다.\r\n";
	UpdateData(FALSE);
}


void CServerSocketDlg::OnClickedStopBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (AfxMessageBox(_T("Server를 종료합니다!!"), MB_YESNO) == IDYES) {
		m_ctrlStopBt.EnableWindow(FALSE);
		m_ctrlStartBt.EnableWindow(TRUE);
		m_ctrlStartBt.SetWindowText(_T("Server Start"));
		m_Server.ShutDown();
		m_Server.Close();
		m_strMsg += "Server를 종료합니다. \r\n";
		UpdateData(FALSE);
	}
}


LRESULT CServerSocketDlg::OnReceiveMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char Buf1[100], Buf2[100];
	m_Client.Receive(Buf2, 100);
	sprintf_s(Buf1, "Server : %s\r\n", Buf2, 100);
	if (m_Client.Send(Buf1, 100) == -1) {
		MessageBox(_T("Message 전송 실패"));
		return -1;
	}
	// 클라이언트에서 보낸 메세지 서버에 띄움
	m_strMsg += "Client :";
	m_strMsg += Buf2;
	m_strMsg += "\r\n";
	UpdateData(FALSE);
	m_ctrlMsg.LineScroll(m_ctrlMsg.GetLineCount(), 0);
	return LRESULT();
}


LRESULT CServerSocketDlg::OnAcceptMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char Buf[100] = "안녕하세요. 저는요 \r\nEcho Server 입니다.\r\n";
	if (!m_Server.Accept(m_Client)) {		// 접속자 정보를 m_Client에게 넘김.
		MessageBox(_T("Client 연결 실패"));
		return -1;
	}
	if (m_Client.Send(Buf, 100) == -1) {
		MessageBox(_T("Message 전송 실패"));
		return -1;
	}
	m_strMsg += "누군가 접속 했습니다.\r\n";
	UpdateData(FALSE);
	m_ctrlMsg.LineScroll(m_ctrlMsg.GetLineCount(), 0);
	return LRESULT();
}
