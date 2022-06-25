

#include "pch.h"
#include "framework.h"
#include "V1.h"
#include "V1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <algorithm>

using namespace std;
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


// CV1Dlg 대화 상자



CV1Dlg::CV1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_V1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CV1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CV1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CV1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CV1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CV1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CV1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CV1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CV1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON10, &CV1Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON8, &CV1Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CV1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON9, &CV1Dlg::OnBnClickedButton9)
	
END_MESSAGE_MAP()


// CV1Dlg 메시지 처리기

BOOL CV1Dlg::OnInitDialog()
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
	m_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 
	R_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 
	S_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 
	P_image.Load(L"lena_bmp_512x512_new.bmp"); //이미지 불러와서 
	F_image.Load(L"lena_bmp_512x512_new.bmp");
	Mid_image.Load(L"lena_bmp_512x512_new.bmp");
	Noise_image.Load(L"lena_bmp_512x512_new.bmp");
	Low_image.Load(L"lena_bmp_512x512_new.bmp");
	unsigned char rawImg[512][512];
	unsigned char temp;
	BITMAPFILEHEADER hfile;
	BITMAPINFOHEADER hInfo;
	RGBQUAD hRGB[256];


	//파일 헤드 정보 입력
	hfile.bfType = 0x4D42; // 비트맵 파일 매직넘버 "BM"
	hfile.bfSize = (DWORD)(512 * 512 + sizeof(RGBQUAD) + sizeof(BITMAPCOREINFO) + sizeof(BITMAPFILEHEADER)); // 파일 크기 
	hfile.bfReserved1 = 0;
	hfile.bfReserved2 = 0;
	hfile.bfOffBits = (DWORD)(sizeof(RGBQUAD) * 256 + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)); //비트맵 데이터 시작위치 가장 우측하단

	//영상헤드 정보입력
	hInfo.biSize = sizeof(BITMAPINFOHEADER);	//이 구조체의 크기
	hInfo.biWidth = 512;			//픽셀단위로 영상의 폭
	hInfo.biHeight = 512;			//영상의 높이
	hInfo.biPlanes = 1;				//비트 플레인 수(항상 1) 
	hInfo.biBitCount = 8;			//픽셀당 비트수(컬러, 흑백 구별)
	hInfo.biCompression = BI_RGB;	//압축유무  비압축 RGB    BI_BITFIELDS 컬러마스크가 지정된 비압축 rgb
	hInfo.biSizeImage = 512 * 512;	//영상의 크기(Byte단위)		
	hInfo.biXPelsPerMeter = 0;		//가로 해상도
	hInfo.biYPelsPerMeter = 0;		//세로 해상도
	hInfo.biClrUsed = 256;			//실제 사용 색상수 0~255
	hInfo.biClrImportant = 256;		//중요한 색상 인덱스 0~255

	// 팔레트 정보 입력
	for (int i = 0; i < 256; i++) {
		hRGB[i].rgbRed = i;		//R성분
		hRGB[i].rgbGreen = i;		//G성분
		hRGB[i].rgbBlue = i;		//B성분
		hRGB[i].rgbReserved = 0;	//예약된 변수

	}
	//raw 파일 읽기
	FILE* infile2 = NULL;
	if (0 == fopen_s(&infile2, "BOAT512.raw.raw", "rb")) {
		fread(rawImg, sizeof(char), 512 * 512, infile2);
		fclose(infile2);
		}
	

	for (int i = 0; i < 256; i++) //상하 반전 ? => bmp 파일은 아래에서 위로 읽기때문에 정상출력을 위해선 상하 반전을 해야한다
	{
		for (int j = 0; j < 512; j++)
		{
			temp = rawImg[i][j];
			rawImg[i][j] = rawImg[512 - i - 1][j];
			rawImg[512 - i - 1][j] = temp;
		}

	}



	FILE* outfile2 = NULL;
	if (0 == fopen_s(&outfile2, "BOAT512.bmp", "wb")) {
	fwrite(&hfile, sizeof(char), sizeof(BITMAPFILEHEADER), outfile2);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile2);
	fwrite(hRGB, sizeof(RGBQUAD), 256, outfile2);
	fwrite(rawImg, sizeof(char), hInfo.biSizeImage, outfile2);
	fclose(outfile2);
	}
	
	Boat_image.Load(L"BOAT512.bmp");
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CV1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CV1Dlg::OnPaint()
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
HCURSOR CV1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CV1Dlg::OnBnClickedButton1()
{
	CClientDC dc(this);
	int temp = 0;
	COLORREF temp_color;
	
	for (int i = 0; i < m_image.GetHeight(); i++)
	{
		for (int j = 0; j< m_image.GetWidth(); j++)
		{
			temp_color = m_image.GetPixel(i, j);// (x,y) 0,0~ 512,512 까지 이미지 픽셀을 가져온다
			BYTE R = GetRValue(temp_color); //흑백사진은 R = G = B 이므로, I=(R+G+B)/3 즉  R 값만 가져와서 사용해도 된다
			image_map[i][j] = R;
		
		}

	}
	m_image.Draw(dc, 0, 0);
	MessageBox(_T("Lena 이미지 불러오기가  완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton2()
{
	CClientDC dc(this);

	int robert_map_x[512][512];
	int robert_map_y[512][512];
	int edge_count = 0;
	CString str;
	
	for (int y = 0; y < R_image.GetHeight(); y++)
	{
		for (int x = 0; x < R_image.GetHeight(); x++)
		{
			robert_map_x[x][y] = 0;
			robert_map_y[x][y]=0;
		}
	}
	for (int i = 1; i < R_image.GetHeight(); i++)
	{
		for (int j = 1; j < R_image.GetWidth(); j++)
		{
			robert_map_x[i][j] = image_map[i][j] - image_map[i + 1][j - 1];
			
			if (robert_map_x[i][j] < 0)
				robert_map_x[i][j] = 0;
			if (robert_map_x[i][j] > 255)
				robert_map_x[i][j] = 255;
			robert_map_y[i][j] = image_map[i][j] - image_map[i - 1][j - 1];
			if (robert_map_y[i][j] < 0)
				robert_map_y[i][j] = 0;
			if (robert_map_y[i][j] > 255)
				robert_map_y[i][j] = 255;
			
			if ((abs(robert_map_y[i][j]) + abs(robert_map_x[i][j]))> 150)
				edge_count++;
			
			R_image.SetPixel(i, j, RGB(abs(robert_map_y[i][j])+ abs(robert_map_x[i][j]), abs(robert_map_y[i][j])+ abs(robert_map_x[i][j]), abs(robert_map_y[i][j])+ abs(robert_map_x[i][j])));

		} 
	}
	str.Format(L"검출된 에지수= %d", edge_count);
	AfxMessageBox(str);

	R_image.Draw(dc, 513, 0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton3() //sobel
{
	CClientDC dc(this);
	int sobel_map_x[512][512];
	int sobel_map_y[512][512];
	int edge_count = 0;
	CString str;
	for (int y = 0; y < S_image.GetHeight(); y++)
	{
		for (int x = 0; x < S_image.GetHeight(); x++)
		{
			sobel_map_x[x][y] = 0;
			sobel_map_y[x][y] = 0;
		}
	}
	for (int i = 1; i < S_image.GetHeight(); i++)
	{
		for (int j = 1; j < S_image.GetWidth(); j++)
		{

			sobel_map_x[i][j] = (image_map[i - 1][j - 1] + 2 * image_map[i - 1][j] + image_map[i - 1][j + 1]) - (image_map[i + 1][j - 1] + 2 * image_map[i + 1][j] + image_map[i + 1][j + 1]);
			if (sobel_map_x[i][j] < 0)
				sobel_map_x[i][j] = 0;
			if (sobel_map_x[i][j] > 255)
				sobel_map_x[i][j] = 255;
			sobel_map_y[i][j] = (image_map[i - 1][j + 1] + 2 * image_map[i][j + 1] + image_map[i + 1][j + 1]) - (image_map[i - 1][j - 1] + 2 * image_map[i][j - 1] + image_map[i + 1][j - 1]);
			if (sobel_map_y[i][j] < 0)
				sobel_map_y[i][j] = 0;
			if (sobel_map_y[i][j] > 255)
				sobel_map_y[i][j] = 255;
			if (  (abs(sobel_map_y[i][j]) + abs(sobel_map_x[i][j])) > 150)
				edge_count++;
			S_image.SetPixel(i, j, RGB(abs(sobel_map_y[i][j]) + abs(sobel_map_x[i][j]), abs(sobel_map_y[i][j]) + abs(sobel_map_x[i][j]), abs(sobel_map_y[i][j]) + abs(sobel_map_x[i][j])));
		}
	}
	str.Format(L"검출된 에지수= %d", edge_count);
	AfxMessageBox(str);

	S_image.Draw(dc, 513, 0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton4() //prewitt
{
	
	CClientDC dc(this);
	int prewit_map_x[512][512];
	int prewit_map_y[512][512];
	int edge_count = 0;
	CString str;
	for (int y = 0; y < P_image.GetHeight(); y++)
	{
		for (int x = 0; x < P_image.GetHeight(); x++)
		{
			prewit_map_x[x][y] = 0;
			prewit_map_y[x][y] = 0;
		}
	}
	for (int i = 1; i < P_image.GetHeight(); i++)
	{
		for (int j = 1; j < P_image.GetWidth(); j++)
		{

			prewit_map_x[i][j] = (image_map[i - 1][j - 1] +  image_map[i - 1][j] + image_map[i - 1][j + 1]) - (image_map[i + 1][j - 1] +  image_map[i + 1][j] + image_map[i + 1][j + 1]);
			if (prewit_map_x[i][j] < 0)
				prewit_map_x[i][j] = 0;
			if (prewit_map_x[i][j] > 255)
				prewit_map_x[i][j] = 255;
			prewit_map_y[i][j] = (image_map[i - 1][j + 1] +  image_map[i][j + 1] + image_map[i + 1][j + 1]) - (image_map[i - 1][j - 1] +  image_map[i][j - 1] + image_map[i + 1][j - 1]);
			if (prewit_map_y[i][j] < 0)
				prewit_map_y[i][j] = 0;
			if (prewit_map_y[i][j] > 255)
				prewit_map_y[i][j] = 255;

			if ((abs(prewit_map_y[i][j]) + abs(prewit_map_x[i][j])) > 150)
				edge_count++;
			P_image.SetPixel(i, j, RGB(abs(prewit_map_y[i][j]) + abs(prewit_map_x[i][j]), abs(prewit_map_y[i][j]) + abs(prewit_map_x[i][j]), abs(prewit_map_y[i][j]) + abs(prewit_map_x[i][j])));
		}
	}
	str.Format(L"검출된 에지수= %d", edge_count);
	AfxMessageBox(str);
	P_image.Draw(dc, 513, 0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton5() //보트 이미지 
{
	CClientDC dc(this);
	int temp = 0;
	COLORREF temp_color;
	for (int y = 0; y < Boat_image.GetHeight(); y++)
	{
		for (int x = 0; x < Boat_image.GetWidth(); x++)
		{
			temp_color = Boat_image.GetPixel(x, y);// (x,y) 0,0~ 512,512 까지 이미지 픽셀을 가져온다
			BYTE R = GetRValue(temp_color); //흑백사진은 R = G = B 이므로, I=(R+G+B)/3 즉  R 값만 가져와서 사용해도 된다
			image_map[x][y] = R;
		}

	}
	Boat_image.Draw(dc, 0, 0);
	MessageBox(_T("보트 이미지 불러오기가 완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton7() //노이즈 추가
{
	CClientDC dc(this);
	int temp = 0;
	int a = 0;
	int b = 0;
	int aver = 0;
	int variance = 0;
	
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			a =a+ image_map[i][j];
		}
	}
	aver = a / (512 * 512);
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			b = b+ (image_map[i][j]- aver)*(image_map[i][j] - aver);
		}
	}
	variance = b /( 512 * 512);
	double stddev_noise = sqrt(variance / pow(10.0, ((double)8 / 10)));
	static int ready = 0;
	static float gstore;
	float v1, v2, r, fac, gaus , mummy;
	int r1, r2;

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			if (ready == 0)
			{
				do {
					r1 = rand();
					r2 = rand();
					v1 = 2. * ((float)r1 / (float)RAND_MAX - 0.5);
					v2 = 2. * ((float)r2 / (float)RAND_MAX - 0.5);
					r = v1 * v1 + v2 * v2;
				} while (r > 1.0);
				fac = (float)sqrt((double)(-2 * log(r) / r));
				gstore = v1 * fac;
				gaus = v2 * fac;
				ready = 1;

			}
			else {
				ready = 0;
				gaus = gstore;
			}

			mummy = gaus * stddev_noise;
			temp = image_map[i][j] + mummy;
			Noise_image.SetPixel(i, j, RGB(temp, temp, temp));
			image_map[i][j] = temp;
		}
	}
	Noise_image.Draw(dc, 0, 0);
	MessageBox(_T("노이즈 추가가 완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton10() //미디언 필터 적용
{
	CClientDC dc(this);
	int midian[9];
	int sum = 0;
	for (int i = 1; i < 511; i++)
	{
		for (int j = 1; j< 511; j++)
		{
			midian[0] = image_map[i - 1][j - 1];
			midian[1] = image_map[i ][j - 1];
			midian[2] = image_map[i + 1][j - 1];

			midian[3] = image_map[i -1][j];
			midian[4] = image_map[i][j];
			midian[5] = image_map[i +1][j];

			midian[6] = image_map[i - 1][j + 1];
			midian[7] = image_map[i][j + 1];
			midian[8] = image_map[i + 1][j + 1];
	
			sort(midian, midian + 9);
			image_map[i][j] = midian[4];
			Mid_image.SetPixel(i, j, RGB(midian[4], midian[4], midian[4]));
			sum = sum + image_map[i][j];
		}
	}
	eq = sum / (512 * 512);



	Mid_image.Draw(dc, 0, 0);
	MessageBox(_T("미디언 필터 적용이 완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton8() //5x5 에지디텍션 
{
	CClientDC dc(this);
	CString str;
	float five_mapx[512][512];
	float five_mapy[512][512];

	int edge_count = 0;

	for (int y = 0; y < F_image.GetHeight(); y++)
	{
		for (int x = 0; x < F_image.GetHeight(); x++)
		{
			five_mapx[x][y] = 0;
			five_mapy[x][y] = 0;
		}
	}
	for (int i = 2; i < F_image.GetHeight(); i++)
	{
		for (int j = 2; j < F_image.GetWidth(); j++)
		{

			five_mapx[i][j] =
				(0.267 * image_map[i - 2][j - 2] + 0.364 * image_map[i - 1][j - 2] +0.373 * image_map[i - 2][j - 1] + 0.562 * image_map[i - 1][j - 1] +0.463 * image_map[i - 2][j] + image_map[i - 1][j] +
				0.373 * image_map[i - 2][j + 1] + 0.562 * image_map[i - 1][j + 1] +
				0.267 * image_map[i - 2][j + 2] + 0.364 * image_map[i - 1][j + 2]) -
				
				(0.364 * image_map[i + 1][j - 2] + 0.267 * image_map[i + 2][j - 2] +
					0.562 * image_map[i + 1][j - 1] + 0.373 * image_map[i + 2][j - 1] +
					image_map[i + 1][j] + 0.463 * image_map[i + 2][j] +
					0.562 * image_map[i + 1][j + 1] + 0.373 * image_map[i + 2][j + 1] +
					0.364 * image_map[i + 1][j + 2] + 0.267 * image_map[i + 2][j + 2]);
			if (five_mapx[i][j] < 0)
				five_mapx[i][j] = 0;
			if (five_mapx[i][j] > 255)
				five_mapx[i][j] = 255;

			five_mapy[i][j]= 
					(0.267 * image_map[i - 2][j - 2] + 0.364 * image_map[i - 2][j - 1] +
					0.373 * image_map[i - 1][j - 2] + 0.562 * image_map[i - 1][j - 1] +
					0.463 * image_map[i][j-2] + image_map[i ][j-1] +
					0.373 * image_map[i +1][j -2] + 0.562 * image_map[i +1][j -1] +
					0.267 * image_map[i + 2][j - 2] + 0.364 * image_map[i+2][j - 1]) 
				-

					(0.364 * image_map[i - 2][j + 1] + 0.267 * image_map[i - 2][j +2] +
					0.562 * image_map[i -1][j + 1] + 0.373 * image_map[i -1][j + 2] +
					image_map[i ][j+1] + 0.463 * image_map[i][j+2] +
					0.562 * image_map[i + 1][j + 1] + 0.373 * image_map[i + 2][j + 2] +
					0.364 * image_map[i + 2][j + 1] + 0.267 * image_map[i + 2][j + 2]);
			if (five_mapy[i][j] < 0)
				five_mapy[i][j] = 0;
			if (five_mapy[i][j] > 255)
				five_mapy[i][j] = 255;

			if ((abs(five_mapy[i][j]) + abs(five_mapx[i][j])) > 150)
				edge_count++;
			


			
			F_image.SetPixel(i, j, RGB(abs(five_mapx[i][j]) + abs(five_mapy[i][j]), abs(five_mapx[i][j]) + abs(five_mapy[i][j]), abs(five_mapx[i][j]) + abs(five_mapy[i][j])));
		}
	}
	str.Format(L"검출된 에지수= %d", edge_count);
	AfxMessageBox(str);
	F_image.Draw(dc, 513, 0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton6() //저주파 통과 필터 
{
	CClientDC dc(this);
	int sum = 0;
	for (int i = 1; i < 511; i++)
	{
		for (int j = 1; j < 511; j++)
		{
			image_map[i][j] = (image_map[i - 1][j - 1] + image_map[i][j - 1] + image_map[i + 1][j - 1] + image_map[i - 1][j] + image_map[i][j] + image_map[i + 1][j] + image_map[i - 1][j + 1] + image_map[i][j + 1] + image_map[i + 1][j + 1]) / 9;

			Low_image.SetPixel(i, j, RGB(image_map[i][j], image_map[i][j], image_map[i][j]));
			sum = sum + image_map[i][j];
		}
	}
	eq = sum / (512 * 512);
	Low_image.Draw(dc, 0, 0);
	MessageBox(_T("저주파 통과 필터 적용이 완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CV1Dlg::OnBnClickedButton9() //MSE 계산 
{
	CString str;
	int mse = 0;
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			mse = mse + (image_map[i][j] - eq) * (image_map[i][j] - eq);
		}
	}
	mse = mse / (512 * 512);
	str.Format(L"MSE = %d", mse);
	AfxMessageBox(str);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



