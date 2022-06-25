
// V2Dlg.h: 헤더 파일
//

#pragma once


// CV2Dlg 대화 상자
class CV2Dlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;// lena 이미지 
	CImage equl_image;// 평활화 된이미지 
	CImage str_image;// 스트레칭 된이미지 
	CImage endin_image;// 엔드인서치 된이미지 
	int equl_histogram[256]; //평활화  히스토그램
	int str_histogram[256]; //스트레칭 히스토그램
	int endin_histogram[256]; //엔드인 서치 히스토그램
	
public:
	CV2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	int high = -1;
	int low = 2641145;
	int histogram[256]; //원본 히스토그램
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_V2_DIALOG };
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
};
