
// V1Dlg.h: 헤더 파일
//

#pragma once


// CV1Dlg 대화 상자
class CV1Dlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;
	CImage R_image;
	CImage S_image;
	CImage P_image;
	CImage Boat_image;
	CImage F_image;
	CImage Noise_image;
	CImage Mid_image;
	CImage Low_image;
public:
	CV1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	int image_map[512][512];
	int eq;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_V1_DIALOG };
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
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton11();
};
