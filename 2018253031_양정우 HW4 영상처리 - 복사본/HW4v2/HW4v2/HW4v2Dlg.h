
// HW4v2Dlg.h: 헤더 파일
//

#pragma once


// CHW4v2Dlg 대화 상자
class CHW4v2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CHW4v2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CImage lena;
	CImage boat;
	CImage tmp;
	CImage dct_temp;
	int image_map[512][512];
	int origin_map[512][512];
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HW4V2_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
