
// V2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "V2.h"
#include "V2Dlg.h"
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


// CV2Dlg 대화 상자



CV2Dlg::CV2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_V2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CV2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CV2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CV2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CV2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CV2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CV2Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CV2Dlg 메시지 처리기

BOOL CV2Dlg::OnInitDialog()
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
	m_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 m_image 에 저장
	equl_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 m_image 에 저장
	str_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 m_image 에 저장
	endin_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 m_image 에 저장

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CV2Dlg::OnPaint()
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
HCURSOR CV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CV2Dlg::OnBnClickedButton1() //이미지 불러오기
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}
void CV2Dlg::OnBnClickedButton2() //히스토그램 생성 
{
	CClientDC dc(this);
	COLORREF temp_color;
	int color_count = 0;
	for (int y = 0; y < m_image.GetHeight(); y++)
	{
		for (int x = 0; x < m_image.GetWidth(); x++)
		{
			temp_color = dc.GetPixel(x, y);// (x,y) 0,0~ 512,512 까지 이미지 픽셀을 가져온다
			BYTE R = GetRValue(temp_color); //흑백사진은 R = G = B 이므로, I=(R+G+B)/3 즉  R 값만 가져와서 사용해도 된다
			
			if (high<int(R)) high = int(R); //최대값 밝기
			if (low > int(R)) low = int(R); //최소값 밝기 추후 엔드인 서치에 사용, high 와 low 는 public 전역변수로 V2Dlg.h 에 선언되어 있다
			
			histogram[R]++; // (run time 감소를 위해)public 전역변수로 V2Dlg.h 에 선언되어 있다
			//주의!! 초기화 되지 않기 때문에 히스토그램 생성을 2회이상 누르면 히스토그램의 N이 커집니다  
		}
	}
	for (int i = 0; i < 256; i++)//히스토그램 그리기 
	{
		dc.Rectangle(1025 + i  , (3000 - histogram[i]) / 20  , 1026+ i, 150);
	}
	MessageBox(_T("히스토그램 생성 이 완료되었습니다"));
}


void CV2Dlg::OnBnClickedButton3() //평활화
{
	CClientDC dc(this);
	COLORREF temp_color;
	long int sum = 0;
	int temp = 0;
	int sum_of_pixel[256] = { 0, };
	for (int i = 0; i < 256; i++)
	{
		sum = sum + histogram[i];
		sum_of_pixel[i] = sum;
	}
	long int total_pixel = sum_of_pixel[255];// 262144
	for (int y = 0; y < m_image.GetHeight(); y++)
	{
		for (int x = 0; x < m_image.GetWidth(); x++)
		{
			temp_color = m_image.GetPixel(x, y);
			BYTE G = GetGValue(temp_color);
			temp = int(((sum_of_pixel[G] * 255) / total_pixel) + 0.5); // nomalize 정규화 한후 LUT를 통과한 값 temp
			equl_histogram[temp]++;
			equl_image.SetPixel(x, y, RGB(temp, temp, temp));
		}
	}
	equl_image.Draw(dc, 513, 0);

	for (int i = 0; i < 256; i++)
	{
		dc.Rectangle(1025 + i, (6000 - equl_histogram[i]) / 20, 1026 + i, 300);
		equl_histogram[i] = 0;// 사용후 초기화
	}
	MessageBox(_T(" 평활화가 완료되었습니다"));
}


void CV2Dlg::OnBnClickedButton4()// 스트레칭 
{
	CClientDC dc(this);
	COLORREF temp_color;
	int temp = 0;
	
	for (int y = 0; y < m_image.GetHeight(); y++)
	{
		for (int x = 0; x < m_image.GetWidth(); x++)
		{
			temp_color = m_image.GetPixel(x, y);
			BYTE G = GetGValue(temp_color);
			if (high - low > 0) //오류 방지용
			{
				temp = int((G - low) * 255 / (high - low));
			}
			str_histogram[temp]++;
			str_image.SetPixel(x, y, RGB(temp, temp, temp));
		}
	}
	str_image.Draw(dc, 513, 0);
	for (int i = 0; i < 256; i++)
	{
		dc.Rectangle(1290 + i, (6000 - str_histogram[i]) / 20, 1291 + i, 300);
		str_histogram[i] = 0; //사용후 초기화 
	}
	MessageBox(_T("스트레칭이 완료되었습니다"));
}


void CV2Dlg::OnBnClickedButton5() //엔드인 서치
{
	CClientDC dc(this);
	COLORREF temp_color;
	int temp = 0;
	int low_end = 50;
	int high_end = 190;
	for (int y = 0; y < m_image.GetHeight(); y++)
	{
		for (int x = 0; x < m_image.GetWidth(); x++)
		{
			temp_color = m_image.GetPixel(x, y);
			BYTE G = GetGValue(temp_color);
			if (high_end < G)
			{
				temp = 255;
			}
			else if (low_end < G) // low_end<G<= high end
			{
				temp = int((G - low_end) * 255 / (high_end - low_end));
			}
			else
			{
				temp = 0;
			}
			endin_histogram[temp]++;
			endin_image.SetPixel(x, y, RGB(temp, temp, temp));
		}
	}
	endin_image.Draw(dc, 513, 0);
	for (int i = 0; i < 256; i++)
	{
		dc.Rectangle(1290 + i, (3000 - endin_histogram[i]) / 20, 1291 + i, 150);
		endin_histogram[i] = 0; //사용후 초기화 
	}
	MessageBox(_T("엔드인 서치가 완료되었습니다"));
}
