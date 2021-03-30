
// tetrisGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "tetrisGame.h"
#include "tetrisGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Block 모양 지정
POINT Pattern[7][16] = {
	{	{ 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 },    { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 },
		{ 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 },    { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 } },
	{   { 0, 0 }, { 1, 0 }, { -1, 0 }, { -2, 0 },     { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, -1 },
		{ 0, 0 }, { 1, 0 }, { -1, 0 }, { -2, 0 },     { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, -1 } },
	{	{ 0, 0 }, { -1, 0 }, { 0, -1 }, { 1, -1 },    { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, -1 },
		{ 0, 0 }, { -1, 0 }, { 0, -1 }, { 1, -1 },    { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, -1 } },
	{	{ 0, 0 }, { -1, -1 }, { 0, -1 }, { 1, 0 },    { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, -1 },
		{ 0, 0 }, { -1, -1 }, { 0, -1 }, { 1, 0 },    { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, -1 } },
	{	{ -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 },     { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 },
		{ -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 },   { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 } },
	{	{ -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 },       { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 },
		{ -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 },  { -1, 1 }, { -1, 0 }, { -1, -1 }, { 0, 1 } },
	{	{ 0, 0 }, { -1, 0 }, { 1, 0 }, { 0, 1 },      { 0, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 },
		{ 0, 0 }, { -1, 0 }, { 1, 0 }, { 0, -1 },     { 0, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } }
};

POINT nextPattern[7][4] = {
	{	{-1, 0},{0,0},{-1,1},{0,1}		},
	{	{-1,1}, {0,1},{1,1}, {-2,1}		},
	{	{0,1},{-1,1},{0,0},{1,0}		},
	{	{0,1},{-1,0},{0,0},{1,1}		},
	{	{-1,1},{-1,0},{0,1},{1,1}		},
	{	{1,1},{0,1},{-1,1},{1,0}		},
	{	{0,1},{-1,1},{1,1},{0,0}		} };
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


// CtetrisGameDlg 대화 상자



CtetrisGameDlg::CtetrisGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TETRISGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nX = COL_CNT / 2;
	m_nY = 0;
	m_nPattern = 0;
	m_nRot = 0;
	m_bStart = FALSE;
	m_nBitType = 4;

	// 게임진행 할 화면 지정
	m_mainRect.left = START_X;
	m_mainRect.top = START_Y;
	m_mainRect.right = START_X + BLOCK_SIZE * COL_CNT + 4;
	m_mainRect.bottom = START_Y + BLOCK_SIZE * ROW_CNT + 4;

	// 다음 Block 나타날 공간
	m_nextRect.left = START_X + BLOCK_SIZE * COL_CNT + 20;
	m_nextRect.top = START_Y + 30;
	m_nextRect.right = m_nextRect.left + 130;
	m_nextRect.bottom = m_nextRect.top + 80;
	//next Block No 초기화
	m_nNextPattern = 0;
	// 점수 초기화
	m_nScore = 0;
}

void CtetrisGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlStartBt);
	DDX_Control(pDX, IDC_BUTTON2, m_ctrlStopBt);
}

BEGIN_MESSAGE_MAP(CtetrisGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtetrisGameDlg::OnClickedStartButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtetrisGameDlg::OnClickedStopButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CtetrisGameDlg::OnClickedExitButton3)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CtetrisGameDlg 메시지 처리기

BOOL CtetrisGameDlg::OnInitDialog()
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
	
	// 화면 크기 지정
	MoveWindow(100, 100, m_mainRect.right + 180, m_mainRect.bottom + 45);
	m_pDC = GetDC();

	// Block bitmap Load
	m_bmBlock.LoadBitmap(IDB_BLOCK);
	m_BlockDC.CreateCompatibleDC(m_pDC);
	m_BlockDC.SelectObject(&m_bmBlock);

	// BackGround bitmap Load
	m_bmBack.LoadBitmap(IDB_BACK);
	m_BackDC.CreateCompatibleDC(m_pDC);
	m_BackDC.SelectObject(&m_bmBack);

	// Number bitmap Load
	m_bmNumber.LoadBitmap(IDB_NUMBER);
	m_NumberDC.CreateCompatibleDC(m_pDC);
	m_NumberDC.SelectObject(&m_bmNumber);

	srand((unsigned)time(NULL));
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);

	// 배열 -1로 초기화
	memset((void *)m_Table, -1, sizeof(m_Table));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CtetrisGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtetrisGameDlg::OnPaint()
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
		DrawScr();
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtetrisGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtetrisGameDlg::DrawScr()
{
	// TODO: 여기에 구현 코드 추가.
	int row, col;

	// main 및 다음블럭 나타낼 테두리 그리기
	m_pDC->Rectangle(m_mainRect);
	m_pDC->Rectangle(m_nextRect);

	for (row = 0; row < ROW_CNT; row++) {
		for (col = 0; col < COL_CNT; col++) {
			if (m_Table[row][col] == -1) {		//  '-1'이면 배경화면 그림 출력, 아니면 블럭 출력
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE,  BLOCK_SIZE, &m_BackDC, 
					col * BLOCK_SIZE, row * BLOCK_SIZE, SRCCOPY);
			}
			else {	
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, 
					m_Table[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
			}
		}
	}
	DisplayScore(m_nScore);
	NextBlock(m_bStart);
}


void CtetrisGameDlg::InitialGame()
{
	// TODO: 여기에 구현 코드 추가.

	// 게임시작 전 모든 data 초기화
	memset((void*)m_Table, -1, sizeof(m_Table));
	DrawScr();
	m_nPattern = rand() % 7; // 패턴 랜덤하게 설정
	m_nRot = 0;
	m_nY = 1;
	m_nX = COL_CNT / 2;
	m_bStart = TRUE;
	
	// block 도형 그리기
	DrawBlock(TRUE);
	// block 타이머 작동
	SetTimer(1, 500, NULL);
}


void CtetrisGameDlg::DrawBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < 4; i++) {
		if (bFlag) {
			m_pDC->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
				&m_BlockDC, m_nPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
		else {
			m_pDC->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
				&m_BackDC, (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE, (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE, SRCCOPY);
		}
	}
}


BOOL CtetrisGameDlg::BlockDown()
{
	// TODO: 여기에 구현 코드 추가.

	// 아래로 한 칸 내린 경우 이미 채워진 블럭을 만나면
	if (!IsAround(m_nX, m_nY + 1)) {
		SetTable();
		return FALSE;
	}
	DrawBlock(FALSE);
	m_nY++;
	DrawBlock(TRUE);
	m_nScore++;
	DisplayScore(m_nScore);
	return TRUE;
}


BOOL CtetrisGameDlg::IsAround(int nX, int nY)
{
	// TODO: 여기에 구현 코드 추가.

	int i, row, col;
	for (i = 0; i < 4; i++) {
		col = nX + Pattern[m_nPattern][i + m_nRot * 4].x;
		row = nY + Pattern[m_nPattern][i + m_nRot * 4].y;
		// 이동할 위치가 경계를 벗어나면 거짓
		if (col < 0 || col > COL_CNT - 1 || row < 1 || row > ROW_CNT - 1) {
			return FALSE;
		}
		// 이동할 위치에 이미 블럭이 있으면 거짓
		if (m_Table[row][col] != -1) {
			return FALSE;
		}
	}
	return TRUE;
}


void CtetrisGameDlg::SetTable()
{
	// TODO: 여기에 구현 코드 추가.
	int i, row, col, sw;

	// 현재 위치에 블록을 쌓음
	for (i = 0; i < 4; i++) {
		m_Table[m_nY + Pattern[m_nPattern][i + m_nRot * 4].y][m_nX + Pattern[m_nPattern][i + m_nRot * 4].x] = m_nPattern;
	}
	
	// 다채 워진 행은 지움, 가장아래부터 전부 비교.
	for (row = ROW_CNT - 1; row >= 0; row--) {
		sw = 0;
		for (col = 0; col < COL_CNT; col++) {
			if (m_Table[row][col] == -1)
				sw = -1;
		}
		// 현재 행 다 채워졌으면
		if (sw == 0) {
			for (i = row; i > 0; i--) {
				for (col = 0; col < COL_CNT; col++) {
					// 한행 아래로 내리기
					m_Table[i][col] = m_Table[i - 1][col];
				}
			}
			for (col = 0; col < COL_CNT; col++) {
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
					&m_BackDC, col * BLOCK_SIZE, row * BLOCK_SIZE, SRCCOPY);
				Sleep(20);
			}
			// 다 채워지면 10점
			m_nScore += 10;
			DisplayScore(m_nScore);

			DrawScr();
			Sleep(100);

			//내려온 행 다시검사
			row++; 
		}
	}
	m_nX = COL_CNT / 2;
	m_nY = 1;
	m_nPattern = m_nNextPattern;
	NextBlock(FALSE);
	m_nNextPattern = rand() % 7;
	NextBlock(TRUE);
	m_nRot = 1;
	if (!IsAround(m_nX, m_nY + 1)) {
		KillTimer(1);
		MessageBox(_T("으악"));
		m_ctrlStartBt.EnableWindow(TRUE);
		m_ctrlStopBt.EnableWindow(FALSE);
		return;
	}
}


void CtetrisGameDlg::RolateBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int nRot = m_nRot;
	DrawBlock(FALSE);
	if (++m_nRot > 3)
		m_nRot = 0;
	// 이동할 수 없으면 원위치
	if (!IsAround(m_nX, m_nY))
		m_nRot = nRot;
	DrawBlock(TRUE);
}


void CtetrisGameDlg::MoveDown()
{
	// TODO: 여기에 구현 코드 추가.
	while (BlockDown()) {
		Sleep(30);
	}
}


void CtetrisGameDlg::MoveRight()
{
	// TODO: 여기에 구현 코드 추가.
	if (!IsAround(m_nX + 1, m_nY))
		return;
	DrawBlock(FALSE);
	m_nX++;
	DrawBlock(TRUE);
}


void CtetrisGameDlg::MoveLeft()
{
	// TODO: 여기에 구현 코드 추가.
	if (!IsAround(m_nX - 1, m_nY))
		return;
	DrawBlock(FALSE);
	m_nX--;
	DrawBlock(TRUE);
}


void CtetrisGameDlg::OnClickedStartButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InitialGame();
	m_ctrlStartBt.EnableWindow(FALSE);
	m_ctrlStopBt.EnableWindow(TRUE);
	m_ctrlStopBt.SetFocus();
}


void CtetrisGameDlg::OnClickedStopButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bStart = FALSE;
	KillTimer(1);
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);
}


void CtetrisGameDlg::OnClickedExitButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ReleaseDC(m_pDC);
	OnOK();
}


void CtetrisGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	BlockDown();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CtetrisGameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && m_bStart) {
		switch (pMsg->wParam) {
		case VK_LEFT:
			MoveLeft();
			return TRUE;
		case VK_RIGHT:
			MoveRight();
			return TRUE;
		case VK_DOWN:
			BlockDown();
			return TRUE;
		case VK_UP:
			RolateBlock(FALSE);
			return TRUE;
		case VK_SPACE:
		case VK_RETURN:
			MoveDown();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CtetrisGameDlg::DisplayScore(int nScore)
{
	// TODO: 여기에 구현 코드 추가.
	int i, temp = nScore;
	CClientDC dc(this);
	for (i = 7; i >= 0; i--) {
		if (temp > 0) {
			dc.BitBlt(m_nextRect.left + i * 13, m_nextRect.bottom + 70, 13, 23, &m_NumberDC, 0, (temp % 10) * 23, SRCCOPY);
			temp /= 10;
		}
		else {
			dc.BitBlt(m_nextRect.left + i * 13, m_nextRect.bottom + 70, 13, 23, &m_NumberDC, 0, 11*23, SRCCOPY);
			temp /= 10;
		}
	}
	
}


void CtetrisGameDlg::NextBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int i, x = 50, y = 10;
	// 출력 위치 보정
	if (m_nNextPattern == 0)
		x = 65;
	else if (m_nNextPattern == 1)
		x = 65, y = 0;

	// 참이면 NextBlock을 그리고 거짓이면 지움.
	if (bFlag) {
		for (i = 0; i < 4; i++) {
			m_pDC->BitBlt(m_nextRect.left + x + (nextPattern[m_nNextPattern][i].x) * BLOCK_SIZE,
				m_nextRect.top + y + (nextPattern[m_nNextPattern][i].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_nNextPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
	}
	else {
		m_pDC->Rectangle(m_nextRect);
	}
}
