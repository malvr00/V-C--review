
// CleintSocketDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CleintSocket.h"
#include "CleintSocketDlg.h"
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


// CCleintSocketDlg 대화 상자



CCleintSocketDlg::CCleintSocketDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLEINTSOCKET_DIALOG, pParent)
	, m_strIpAddress(_T("localhost"))
	, m_nPortNo(1234)
	, m_strSendData(_T(""))
	, m_strReceiveData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bConnect = FALSE;
}

void CCleintSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONNET_BT, m_ctrlConnectBt);
	DDX_Control(pDX, IDC_DISCONNET_BT, m_ctrlDisConnetBt);
	DDX_Control(pDX, IDC_SEND_BT, m_ctrlSendBT);
	DDX_Control(pDX, IDC_ADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_ADDRESS, m_strIpAddress);
	DDX_Text(pDX, IDC_PORTNO, m_nPortNo);
	DDX_Control(pDX, IDC_SEND_DATA, m_ctrlSendData);
	DDX_Text(pDX, IDC_SEND_DATA, m_strSendData);
	DDX_Control(pDX, IDC_RECEIVE_DATA, m_ctrlReceiveData);
	DDX_Text(pDX, IDC_RECEIVE_DATA, m_strReceiveData);
}

BEGIN_MESSAGE_MAP(CCleintSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNET_BT, &CCleintSocketDlg::OnClickedConnetBt)
	ON_BN_CLICKED(IDC_DISCONNET_BT, &CCleintSocketDlg::OnClickedDisconnetBt)
	ON_BN_CLICKED(IDC_SEND_BT, &CCleintSocketDlg::OnClickedSendBt)
	ON_MESSAGE(UM_RECEIVE, &CCleintSocketDlg::OnReceiveMsg)
END_MESSAGE_MAP()


// CCleintSocketDlg 메시지 처리기

BOOL CCleintSocketDlg::OnInitDialog()
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

	// 초기에 자료 저송, 연결해제 버튼은 사용 불가능 상태로 설정
	m_ctrlSendBT.EnableWindow(false);
	m_ctrlDisConnetBt.EnableWindow(false);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCleintSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCleintSocketDlg::OnPaint()
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
HCURSOR CCleintSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CCleintSocketDlg::OnReceiveMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.

	// Server에서 보내는 메세지 담음
	char buf[100];
	m_Socket.Receive(buf, 100);
	m_strReceiveData += buf;
	UpdateData(FALSE);

	// 받는글 최신 글이 먼저 보이게 설정
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);
	return LRESULT();
}


void CCleintSocketDlg::OnClickedConnetBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_Socket.Create();
	if (!m_Socket.Connect(m_strIpAddress, m_nPortNo)) {
		MessageBox(_T("Server에 접속하지 못했습니다."));
		m_Socket.Close();
		return;
	}
	// 연결버튼 사용 불능으로
	m_ctrlConnectBt.EnableWindow(FALSE);
	// 버튼의 문자 변경
	m_ctrlConnectBt.SetWindowTextW(_T("Server연결중"));

	// 자료전송버튼 활성화
	m_ctrlSendBT.EnableWindow(TRUE);

	// 연결해제버튼 활성화
	m_ctrlDisConnetBt.EnableWindow(TRUE);

	// 보내는 글로 Focus이동
	m_ctrlSendData.SetFocus();

	// 현제 접소중 표시
	m_bConnect = TRUE;
}


void CCleintSocketDlg::OnClickedDisconnetBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 연겨해제 버튼 누르면
	if (AfxMessageBox(_T("Server와의 연결을 끊을까요?"), MB_YESNO) == IDYES) {
		// Server 연결버튼 활성화
		m_ctrlConnectBt.EnableWindow(TRUE);
		m_ctrlConnectBt.SetWindowText(_T("Server 연결"));
		
		// 버튼 비활성화
		m_ctrlSendBT.EnableWindow(FALSE);
		m_ctrlDisConnetBt.EnableWindow(FALSE);

		m_ctrlIpAddress.SetFocus();
		m_Socket.Close();
		m_bConnect = false;
	}
}


void CCleintSocketDlg::OnClickedSendBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char buf[100] = "";
	int n;
	UpdateData(TRUE);
	if (!m_strSendData.IsEmpty()) {
		// CString -> char로 변결
		strcpy_s(buf, 100, CT2A(m_strSendData));
		// 전송 실패 -1, 송공은 보낸 Byte수 포함
		n = m_Socket.Send(buf, 100);
		if (n == -1)
			MessageBox(_T("전송실패"));
		// 보내는 글 창 초기화
		m_strSendData = "";
		UpdateData(FALSE);
	}
	m_ctrlSendData.SetFocus();
}


BOOL CCleintSocketDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		if (m_bConnect)
			OnClickedSendBt();
		else
			OnClickedConnetBt();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
