
// puzzleGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "puzzleGame.h"
#include "puzzleGameDlg.h"
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


// CpuzzleGameDlg 대화 상자



CpuzzleGameDlg::CpuzzleGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PUZZLEGAME_DIALOG, pParent)
	, m_rowCnt(5)
	, m_colCnt(5)
	, m_moveCnt(0)
	, m_nTime(0)
	, m_strCorect(_T(""))
	, m_bNumber(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nXSize = 0;
	m_nYSize = 0;
	m_bGameClear = FALSE;
	m_bGameStart = FALSE;
	m_bHint = FALSE;
}

void CpuzzleGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rowCnt);
	DDX_Text(pDX, IDC_EDIT2, m_colCnt);
	//  DDX_Text(pDX, IDC_EDIT5ACCURACY, m_moveCnt);
	DDX_Text(pDX, IDC_EDITMOVE, m_moveCnt);
	DDX_Text(pDX, IDC_EDITTIME, m_nTime);
	DDX_Text(pDX, IDC_EDIT5ACCURACY, m_strCorect);
	DDX_Check(pDX, IDC_CHECK1, m_bNumber);
	DDX_Control(pDX, IDC_GAMESTART, m_ctrlStartBt);
	DDX_Control(pDX, IDC_GAMESTOP, m_ctrlStopBt);
}

BEGIN_MESSAGE_MAP(CpuzzleGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GAMESTART, &CpuzzleGameDlg::OnClickedGamestart)
	ON_BN_CLICKED(IDC_GAMESTOP, &CpuzzleGameDlg::OnClickedGamestop)
	ON_BN_CLICKED(IDC_GAMEEND, &CpuzzleGameDlg::OnClickedGameend)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, &CpuzzleGameDlg::OnClickedCheck1)
END_MESSAGE_MAP()


// CpuzzleGameDlg 메시지 처리기

BOOL CpuzzleGameDlg::OnInitDialog()
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
	MoveWindow(100, 100, WINDOW_XSIZE, WINDOW_YSIZE);  // 화면 크기 지정
	m_pDC = GetDC();
	m_mainDC.CreateCompatibleDC(m_pDC);
	m_hintDC.CreateCompatibleDC(m_pDC);

	m_bitMain.LoadBitmap(IDB_BITMAIN);		// Mian 그림 읽어오기
	m_bitHint.LoadBitmap(IDB_BITHINT);		// Hint 그림 읽어오기

	m_mainDC.SelectObject(&m_bitMain);
	m_hintDC.SelectObject(&m_bitHint);

	InitialData();
	m_ctrlStartBt.EnableWindow(!m_bGameStart);		// 게임시작 여부에 따라 버튼 활성화/비활성화
	m_ctrlStopBt.EnableWindow(m_bGameStart);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CpuzzleGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CpuzzleGameDlg::OnPaint()
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
		// 게임시작 성공했을 때 원본 그림 나타냄.
		if (m_bGameClear) {
			DisplayOriginal();
		}
		else {
			DrawRectAll();
			DisplayAll();
			CorrectCount();
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CpuzzleGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CpuzzleGameDlg::OnClickedGamestart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate();
	InitialData();
	DrawRectAll();
	DisplayAll();
	MixedPicture();
	CorrectCount();
	m_bGameClear = FALSE;
	m_bGameStart = TRUE;

	// 버튼 활성화 / 비활성화.
	m_ctrlStartBt.EnableWindow(!m_bGameStart);
	m_ctrlStopBt.EnableWindow(m_bGameStart);

	//타이머 작동시작.
	SetTimer(0, 1000, NULL);
}


void CpuzzleGameDlg::OnClickedGamestop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 스탑버튼시 버튼 활성화/비활성화 후 게임진행 시간 중지.
	m_bGameStart = FALSE;
	m_ctrlStartBt.EnableWindow(!m_bGameStart);
	m_ctrlStopBt.EnableWindow(m_bGameStart);
	KillTimer(0);
}


void CpuzzleGameDlg::OnClickedGameend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CpuzzleGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int x, y, ex, ey;
	CString str;
	
	//Game이 진행 중이 아니면 Return
	if (!m_bGameStart)
		return;

	//그림이 나타는 부분 클릭한 경우
	if (m_mainRect.PtInRect(point)) {
		//좌표 값으로 x, y 계산.
		ex = x = (point.x - START_X) / (m_nXSize + 2);
		ey = y = (point.y - START_Y) / (m_nYSize + 2);
		if (EmptyPosition(ex, ey)) {
			MovePicture(x, y, ex, ey, 100);
			m_moveCnt++;

			// 전부 맞추면 성공 화면 띄우기.
			if (CorrectCount()) {
				MessageBox(_T("성공"));
				ClearGame();
			}
		}
	}

	// 힌트그림보기.
	if (m_hintRect.PtInRect(point)) {
		// 5초동안 볼 수 있도록 타이머 설정.
		SetTimer(1, 5000, NULL);
		m_bHint = TRUE;
		PreView();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CpuzzleGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 5초 후 Hint Timer 종료.
	if (nIDEvent == 1) {
		KillTimer(1);
		m_bHint = FALSE;
		PreView();
		return;
	}
	// 게임진행 시간 카운트.
	m_nTime++;
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CpuzzleGameDlg::OnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	DrawRectAll();
	DisplayAll();
}


void CpuzzleGameDlg::InitialData()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, cnt = 0;
	UpdateData(TRUE);

	// 최소 3칸 최대 7칸 으로 설정 후 벗어나면 5칸으로 셋팅.
	if (m_colCnt < 3 || m_colCnt > 7)  
		m_colCnt = 5;
	if (m_rowCnt < 3 || m_rowCnt > 7)
		m_rowCnt = 5;

	// 칸 1개 크기 계산
	m_nXSize = PIC_SIZE / m_colCnt;
	m_nYSize = PIC_SIZE / m_rowCnt;

	// 그림 출력 좌표
	m_mainRect.left = START_X - 1;
	m_mainRect.top = START_Y - 1;
	m_mainRect.right = START_X + m_colCnt * (m_nXSize + 2) + 1;
	m_mainRect.bottom = START_Y + m_rowCnt * (m_nYSize + 2) + 1;

	// 힌트 출력 좌표
	m_hintRect.left = m_mainRect.right + 20;
	m_hintRect.top = START_Y - 1;
	m_hintRect.right = m_hintRect.left + HINT_SIZE;
	m_hintRect.bottom = START_Y + HINT_SIZE;

	// 정확도, 횟수, 시간 초기화
	m_strCorect = "";
	m_moveCnt = 0;
	m_nTime = 0;

	//그림 번호를 Map배열에 저장
	for (y = 0; y < m_rowCnt; y++) {
		for (x = 0; x < m_colCnt; x++) {
			m_aMap[x][y] = cnt++;
		}
	}

	// 마지막칸 빈칸 지정.
	m_aMap[m_colCnt - 1][m_rowCnt - 1] = -1;
}


void CpuzzleGameDlg::DrawRectAll()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	m_pDC->Rectangle(m_mainRect);
	m_pDC->Rectangle(m_hintRect);

	for (x = 0; x < m_colCnt; x++) {
		for (y = 0; y < m_rowCnt; y++) {
			DrawRect(x, y);
		}
	}
	PreView();
}


void CpuzzleGameDlg::DrawRect(int nX, int nY)
{
	// TODO: 여기에 구현 코드 추가.
	m_pDC->Rectangle(START_X + nX * (m_nXSize + 2), START_Y + nY * (m_nYSize + 2),
		START_X + (nX + 1) * (m_nXSize + 2), START_Y + (nY + 1) * (m_nYSize + 2));
}


void CpuzzleGameDlg::DisplayAll()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	for (x = 0; x < m_colCnt; x++) {
		for (y = 0; y < m_rowCnt; y++) {
			DrawPicture(x, y, m_aMap[x][y]);
		}
	}
}


void CpuzzleGameDlg::DrawPicture(int nX, int nY, int nPictureNo)
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;

	// 그림 번호로 좌표값 출력.
	x = (int)(nPictureNo % m_colCnt);
	y = (int)(nPictureNo / m_rowCnt);
	
	// 한 칸에 그림 출력.
	m_pDC->BitBlt(START_X + 1 + (nX * (m_nXSize + 2)), START_Y + 1 + (nY * (m_nYSize + 2)),
		m_nXSize, m_nYSize, &m_mainDC, (x * m_nXSize), (y * m_nYSize), SRCCOPY);

	// 그림번호 출력.
	if (m_bNumber)
		DisplayNumber();
}


BOOL CpuzzleGameDlg::CorrectCount()
{
	// TODO: 여기에 구현 코드 추가.
	// 그림 맞춘 개수 카운트.
	int x, y, cnt = 0, correct = 0;
	for (y = 0; y < m_rowCnt; y++) {
		for (x = 0; x < m_colCnt; x++) {
			if (m_aMap[x][y] == cnt)
				correct++;
			cnt++;
		}
	}

	if (m_aMap[m_colCnt - 1][m_rowCnt - 1] = -1)
		correct++;
	
	// 현재 얼마나 맞췄나 나타내기.
	m_strCorect.Format(_T("%d / %d"), correct, m_colCnt * m_rowCnt);
	UpdateData(FALSE);

	// 그림 전부 맞추면 TRUE 아니면 FALSE
	if (correct == m_colCnt * m_rowCnt)
		return TRUE;
	else
		return FALSE;
}


void CpuzzleGameDlg::DisplayNumber()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	CString str;
	for (x = 0; x < m_colCnt; x++) {
		for (y = 0; y < m_rowCnt; y++) {
			str.Format(_T("%2d"), m_aMap[x][y]);
			m_pDC->TextOut(START_X + x * (m_nXSize + 2) + 2, START_Y + y * (m_nYSize + 2) + 2,str);
		}
	}
}


BOOL CpuzzleGameDlg::EmptyPosition(int& nX, int& nY)
{
	// TODO: 여기에 구현 코드 추가.
	int i;
	for (i = 0; i < m_colCnt; i++) {
		if (m_aMap[i][nY] == -1) {
			nX = i;
			return TRUE;
		}
	}
	for (i = 0; i < m_rowCnt; i++) {
		if (m_aMap[nX][i] == -1) {
			nY = i;
			return TRUE;
		}
	}
	return FALSE;
}


void CpuzzleGameDlg::MovePicture(int nX, int nY, int eX, int eY, int nTime)
{
	// TODO: 여기에 구현 코드 추가.
	int i;
	// X좌표 빈칸으로 그림이동.
	if (nX > eX) {
		for (i = eX; i < nX; i++) {
			m_aMap[i][nY] = m_aMap[i + 1][nY];
			DrawPicture(i, nY, m_aMap[i][nY]);
			DrawRect(i + 1, nY);

			//전달된 시간만큼 멈춤
			Sleep(nTime);
		}
	}
	else if (nX < eX) {
		for (i = eX; i > nX; i--) {
			m_aMap[i][nY] = m_aMap[i - 1][nY];
			DrawPicture(i, nY, m_aMap[i][nY]);
			DrawRect(i - 1, nY);

			Sleep(nTime);
		}
	}
	// Y좌표 빈칸으로 그림이동.
	else if (nY > eY) {
		for (i = eY; i < nY; i++) {
			m_aMap[nX][i] = m_aMap[nX][i + 1];
			DrawPicture(nX, i, m_aMap[nX][i]);
			DrawRect(nX, i + 1);

			Sleep(nTime);
		}
	}
	else if (nY < eY) {
		for (i = eY; i > nY; i--) {
			m_aMap[nX][i] = m_aMap[nX][i - 1];
			DrawPicture(nX, i, m_aMap[nX][i]);
			DrawRect(nX, i - 1);

			Sleep(nTime);
		}
	}
	// 빈칸 좌표값 -1 넣기.
	m_aMap[nX][nY] == -1;
}


void CpuzzleGameDlg::DisplayOriginal()
{
	// TODO: 여기에 구현 코드 추가.
	m_pDC->BitBlt(START_X + m_colCnt, START_Y + m_rowCnt, PIC_SIZE, PIC_SIZE, &m_mainDC, 0, 0, SRCCOPY);
}


void CpuzzleGameDlg::PreView()
{
	// TODO: 여기에 구현 코드 추가.

	// 힌트보기 상태가 true면 원본 그림 나타냄. false면 hint사진 출력.
	if (m_bHint) 
		m_pDC->StretchBlt(m_hintRect.left, m_hintRect.top, HINT_SIZE, HINT_SIZE, &m_mainDC, 0, 0, PIC_SIZE, PIC_SIZE, SRCCOPY);
	else
		m_pDC->StretchBlt(m_hintRect.left, m_hintRect.top, HINT_SIZE, HINT_SIZE, &m_hintDC, 0, 0, HINT_SIZE, HINT_SIZE, SRCCOPY);
}


void CpuzzleGameDlg::ClearGame()
{
	// TODO: 여기에 구현 코드 추가.
	m_bGameStart = FALSE;
	m_ctrlStartBt.EnableWindow(!m_bGameStart);
	m_ctrlStopBt.EnableWindow(m_bGameStart);
	KillTimer(0);
	m_bGameClear = true;
	DisplayOriginal();
}


void CpuzzleGameDlg::MixedPicture()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, ex, ey;
	srand((unsigned)time(NULL));
	for (int i = 0; i < m_colCnt * m_rowCnt * 10; i++) {
		ex = x = rand() % m_colCnt;
		ey = y = rand() % m_rowCnt;
		if (EmptyPosition(ex, ey)) {
			MovePicture(x, y, ex, ey, 1);
		}
	}
}
