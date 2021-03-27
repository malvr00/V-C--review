
// tetrisGameDlg.h: 헤더 파일
//

#pragma once

#define COL_CNT 10			// 열 방향 BLOCK 수
#define ROW_CNT 20			// 행 방향 BLOCK 수
#define START_X 10			// 배경 저장 할 MemoryDC
#define START_Y 10			// BLOCK 저장 할 MemoeyDC
#define BLOCK_SIZE 32		// DC 저장 Pointer

// CtetrisGameDlg 대화 상자
class CtetrisGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CtetrisGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TETRISGAME_DIALOG };
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
	CBitmap m_bmBlock;					// Block BitMap 저장
	CBitmap m_bmBack;					// 배경그림 ButMap 저장
	CDC m_BackDC;						// Back 저장 할 MemoryDC
	CDC m_BlockDC;						// Block 저장 할 MemoryDC
	CDC* m_pDC;							// DC 저장 Pointer
	char m_Table[ROW_CNT][COL_CNT];		// 화면 Table[열수][행수]
	CRect m_nextRect;					// 다음그림 나타나는 사각형위치
	CRect m_mainRect;					// Main Block 나타나는 사각형위치
	BOOL m_bStart;						// Game 시작 여부
	int m_nPattern;						// 현재 Block 모양
	int m_nBitType;						// Block 종류
	int m_nRot;							// 현재 Block의 회전된 모양
	int m_nX;							// 현재 Block의 중심좌표(열 위치)
	int m_nY;							// 현재 Block의 중심좌표(행 위치)
	CButton m_ctrlStartBt;				// 시작버튼 연결 변수
	CButton m_ctrlStopBt;				// 중지버튼 연결 변수


	void DrawScr();						// 화면을 다시 그림
	void InitialGame();					// Game 자료 초기화
	void DrawBlock(bool bFlag);			// Block 그리기
	BOOL BlockDown();					// 아래로 한 칸 이동
	BOOL IsAround(int nX, int nY);		// 다음 위치가 이동가능한지 검사
	void SetTable();					// Block Setting
	void RolateBlock(bool bFlag);		// Block 회전 
	void MoveDown();					// 아래로 바닥까지 내림
	void MoveRight();					// 오른쪽으로 한 칸 이동
	void MoveLeft();					// 왼쪽으로 한 칸 이동
	afx_msg void OnClickedStartButton1();
	afx_msg void OnClickedStopButton2();
	afx_msg void OnClickedExitButton3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
