
// puzzleGameDlg.h: 헤더 파일
//

#pragma once

#define PIC_SIZE 500		// 주 그림 크기
#define HINT_SIZE 300		// 힌트 그림 크기
#define START_X 7			// 그림 나타날 좌측 상당 위치
#define START_Y 7			
#define WINDOW_XSIZE 860	// 창크기
#define WINDOW_YSIZE 580

// CpuzzleGameDlg 대화 상자
class CpuzzleGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CpuzzleGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUZZLEGAME_DIALOG };
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
public:
	CDC* m_pDC;				// DC 저장 Pointer
	CDC m_mainDC;			// 그림 저장 memoryDC
	CDC m_hintDC;			// 힌트 그림 저장

	CBitmap m_bitMain;		// 그림 저장
	CBitmap m_bitHint;		// 힌트 그림 저장

	int m_aMap[9][9];		// 그림 번호 저장 배열

	BOOL m_bGameClear;		// 게임 성공 여부
	BOOL m_bGameStart;		// 게임 진행 중
	BOOL m_bHint;			// 힌트 보기 상태
	CRect m_mainRect;		// 그림 나타내는 main 부분
	CRect m_hintRect;		// 힌트 나타내는 부분
	int m_nXSize;			// 사각형 1개의 X크기
	int m_nYSize;			// 사각형 1개의 Y크기

	//control 연걸된 member 변수
	int m_rowCnt;			// 열
	int m_colCnt;			// 행
	int m_moveCnt;			// 그림이동 횟수
	int m_nTime;			// 게임 진행 시간
	CString m_strCorect;	// 정확도 출력용 변수
	BOOL m_bNumber;			// 그림번호 번호 보이기
	CButton m_ctrlStartBt;	// 게임 시작 버튼
	CButton m_ctrlStopBt;	// 게임 종료 버튼

	afx_msg void OnClickedGamestart();
	afx_msg void OnClickedGamestop();
	afx_msg void OnClickedGameend();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedCheck1();

	void InitialData();													// 자료초기화
	void DrawRectAll();												    // 모든 칸에 테두리 그리기
	void DrawRect(int nX, int nY);										// 테두리 하나 그리기
	void DisplayAll();													// 모든 칸에 그림 그리기
	void DrawPicture(int nX, int nY, int nPictureNo);					// 한 칸 그림 그리기
	BOOL CorrectCount();												// 정확도 계산
	void DisplayNumber();												// 그림번호 나타내기
	BOOL EmptyPosition(int& nX, int& nY);								// 빈칸이 있는지 확인
	void MovePicture(int nX, int nY, int eX, int eY, int nTime);		// 그림 이동
	void DisplayOriginal();												// 원본 그림 나타내기
	void PreView();														// 힌트 나타내기
	void ClearGame();													// 성공
	void MixedPicture();												// 그림 섞기
};
