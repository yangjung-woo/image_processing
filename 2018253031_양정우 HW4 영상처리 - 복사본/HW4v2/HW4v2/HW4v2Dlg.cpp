// HW4v2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HW4v2.h"
#include "HW4v2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define B_size 8
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
int dct(int ix[][B_size]);
int idct(int ax[][B_size]);
int nint( float x);
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


// CHW4v2Dlg 대화 상자



CHW4v2Dlg::CHW4v2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HW4V2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHW4v2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHW4v2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHW4v2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHW4v2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHW4v2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHW4v2Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CHW4v2Dlg 메시지 처리기

BOOL CHW4v2Dlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다
	
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
	//raw 파일 읽기 보트
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
	//raw 파일 읽기 레나
	
	FILE* infile1 = NULL;
	if (0 == fopen_s(&infile1, "lena_raw_512x512.raw", "rb")) {
		fread(rawImg, sizeof(char), 512 * 512, infile1);
		fclose(infile1);
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
	FILE* outfile1 = NULL;
	if (0 == fopen_s(&outfile1, "lena_raw_512x512.bmp", "wb")) {
		fwrite(&hfile, sizeof(char), sizeof(BITMAPFILEHEADER), outfile1);
		fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile1);
		fwrite(hRGB, sizeof(RGBQUAD), 256, outfile2);
		fwrite(rawImg, sizeof(char), hInfo.biSizeImage, outfile1);
		fclose(outfile1);
	}
	
	boat.Load(L"BOAT512.bmp");
	lena.Load(L"lena_raw_512x512.bmp");
	tmp.Load(L"lena_raw_512x512.bmp");
	dct_temp.Load(L"lena_raw_512x512.bmp");
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHW4v2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHW4v2Dlg::OnPaint()
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
HCURSOR CHW4v2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHW4v2Dlg::OnBnClickedButton1()
{
	CClientDC dc(this);
	int temp = 0;
	COLORREF temp_color;

	for (int i = 0; i < lena.GetHeight(); i++)
	{
		for (int j = 0; j < lena.GetWidth(); j++)
		{
			temp_color = lena.GetPixel(i, j);// (x,y) 0,0~ 512,512 까지 이미지 픽셀을 가져온다
			BYTE R = GetRValue(temp_color); //흑백사진은 R = G = B 이므로, I=(R+G+B)/3 즉  R 값만 가져와서 사용해도 된다
			image_map[i][j] = R;
			origin_map[i][j] = R;
			tmp.SetPixel(i, j, RGB(image_map[i][j], image_map[i][j], image_map[i][j]));
		}

	}
	lena.Draw(dc, 0, 0);
	MessageBox(_T("Lena 이미지 불러오기가  완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CHW4v2Dlg::OnBnClickedButton2()
{
	CClientDC dc(this);
	int temp = 0;
	COLORREF temp_color;

	for (int i = 0; i < boat.GetHeight(); i++)
	{
		for (int j = 0; j < boat.GetWidth(); j++)
		{
			temp_color = boat.GetPixel(i, j);// (x,y) 0,0~ 512,512 까지 이미지 픽셀을 가져온다
			BYTE R = GetRValue(temp_color); //흑백사진은 R = G = B 이므로, I=(R+G+B)/3 즉  R 값만 가져와서 사용해도 된다
			image_map[i][j] = R;
			origin_map[i][j] = R;
			tmp.SetPixel(i, j, RGB(image_map[i][j], image_map[i][j], image_map[i][j]));
		}

	}
	boat.Draw(dc, 0, 0);
	MessageBox(_T("BOAT 이미지 불러오기가  완료되었습니다"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
int nint(float x)
{
	double result;
	result = floor(x + 0.5);
	return (int)result;
}
int dct(int ix[][B_size])
{
	static float pi = 3.141592653589793238;
	float x[B_size][B_size], z[B_size][B_size], y[B_size], c[40], s[40],
		ft[4], fxy[4], yy[B_size], zz;
	int i, ii, jj;

	for (i = 0; i < 40; i++) {
		zz = pi * (float)(i + 1) / 64.0;
		c[i] = cos(zz);
		s[i] = sin(zz);
	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			x[ii][jj] = (float)ix[ii][jj];

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = x[ii][jj];

		for (jj = 0; jj < 4; jj++)
			ft[jj] = y[jj] + y[7 - jj];

		fxy[0] = ft[0] + ft[3];
		fxy[1] = ft[1] + ft[2];
		fxy[2] = ft[1] - ft[2];
		fxy[3] = ft[0] - ft[3];

		ft[0] = c[15] * (fxy[0] + fxy[1]);
		ft[2] = c[15] * (fxy[0] - fxy[1]);
		ft[1] = s[7] * fxy[2] + c[7] * fxy[3];
		ft[3] = -s[23] * fxy[2] + c[23] * fxy[3];

		for (jj = 4; jj < 8; jj++)
			yy[jj] = y[7 - jj] - y[jj];

		y[4] = yy[4];
		y[7] = yy[7];
		y[5] = c[15] * (-yy[5] + yy[6]);
		y[6] = c[15] * (yy[5] + yy[6]);

		yy[4] = y[4] + y[5];
		yy[5] = y[4] - y[5];
		yy[6] = -y[6] + y[7];
		yy[7] = y[6] + y[7];

		y[0] = ft[0];
		y[4] = ft[2];
		y[2] = ft[1];
		y[6] = ft[3];
		y[1] = s[3] * yy[4] + c[3] * yy[7];
		y[5] = s[19] * yy[5] + c[19] * yy[6];
		y[3] = -s[11] * yy[5] + c[11] * yy[6];
		y[7] = -s[27] * yy[4] + c[27] * yy[7];

		for (jj = 0; jj < B_size; jj++)
			z[ii][jj] = y[jj];

	}

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = z[jj][ii];

		for (jj = 0; jj < 4; jj++)
			ft[jj] = y[jj] + y[7 - jj];

		fxy[0] = ft[0] + ft[3];
		fxy[1] = ft[1] + ft[2];
		fxy[2] = ft[1] - ft[2];
		fxy[3] = ft[0] - ft[3];

		ft[0] = c[15] * (fxy[0] + fxy[1]);
		ft[2] = c[15] * (fxy[0] - fxy[1]);
		ft[1] = s[7] * fxy[2] + c[7] * fxy[3];
		ft[3] = -s[23] * fxy[2] + c[23] * fxy[3];

		for (jj = 4; jj < 8; jj++)
			yy[jj] = y[7 - jj] - y[jj];

		y[4] = yy[4];
		y[7] = yy[7];
		y[5] = c[15] * (-yy[5] + yy[6]);
		y[6] = c[15] * (yy[5] + yy[6]);

		yy[4] = y[4] + y[5];
		yy[5] = y[4] - y[5];
		yy[6] = -y[6] + y[7];
		yy[7] = y[6] + y[7];

		y[0] = ft[0];
		y[4] = ft[2];
		y[2] = ft[1];
		y[6] = ft[3];
		y[1] = s[3] * yy[4] + c[3] * yy[7];
		y[5] = s[19] * yy[5] + c[19] * yy[6];
		y[3] = -s[11] * yy[5] + c[11] * yy[6];
		y[7] = -s[27] * yy[4] + c[27] * yy[7];

		for (jj = 0; jj < B_size; jj++)
			y[jj] = y[jj] / 4.0;

		for (jj = 0; jj < B_size; jj++)
			z[jj][ii] = y[jj];
	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			ix[ii][jj] = nint(z[ii][jj]);

	return 0;

}

int idct(int ix[][B_size])
{
	static float pi = 3.141592653589793238;
	float x[B_size][B_size], z[B_size][B_size], y[B_size], c[40], s[40],
		ait[4], aixy[4], yy[B_size], zz;
	int i, ii, jj;

	for (i = 0; i < 40; i++) {
		zz = pi * (float)(i + 1) / 64.0;
		c[i] = cos(zz);
		s[i] = sin(zz);
	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			x[ii][jj] = (float)ix[ii][jj];

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = x[jj][ii];

		ait[0] = y[0];
		ait[1] = y[2];
		ait[2] = y[4];
		ait[3] = y[6];

		aixy[0] = c[15] * (ait[0] + ait[2]);
		aixy[1] = c[15] * (ait[0] - ait[2]);
		aixy[2] = s[7] * ait[1] - s[23] * ait[3];
		aixy[3] = c[7] * ait[1] + c[23] * ait[3];

		ait[0] = aixy[0] + aixy[3];
		ait[1] = aixy[1] + aixy[2];
		ait[2] = aixy[1] - aixy[2];
		ait[3] = aixy[0] - aixy[3];

		yy[4] = s[3] * y[1] - s[27] * y[7];
		yy[5] = s[19] * y[5] - s[11] * y[3];
		yy[6] = c[19] * y[5] + c[11] * y[3];
		yy[7] = c[3] * y[1] + c[27] * y[7];

		y[4] = yy[4] + yy[5];
		y[5] = yy[4] - yy[5];
		y[6] = -yy[6] + yy[7];
		y[7] = yy[6] + yy[7];

		yy[4] = y[4];
		yy[7] = y[7];
		yy[5] = c[15] * (-y[5] + y[6]);
		yy[6] = c[15] * (y[5] + y[6]);

		for (jj = 0; jj < 4; jj++)
			y[jj] = ait[jj] + yy[7 - jj];

		for (jj = 4; jj < 8; jj++)
			y[jj] = ait[7 - jj] - yy[jj];

		for (jj = 0; jj < B_size; jj++)
			z[jj][ii] = y[jj];

	}

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = z[ii][jj];

		ait[0] = y[0];
		ait[1] = y[2];
		ait[2] = y[4];
		ait[3] = y[6];

		aixy[0] = c[15] * (ait[0] + ait[2]);
		aixy[1] = c[15] * (ait[0] - ait[2]);
		aixy[2] = s[7] * ait[1] - s[23] * ait[3];
		aixy[3] = c[7] * ait[1] + c[23] * ait[3];

		ait[0] = aixy[0] + aixy[3];
		ait[1] = aixy[1] + aixy[2];
		ait[2] = aixy[1] - aixy[2];
		ait[3] = aixy[0] - aixy[3];

		yy[4] = s[3] * y[1] - s[27] * y[7];
		yy[5] = s[19] * y[5] - s[11] * y[3];
		yy[6] = c[19] * y[5] + c[11] * y[3];
		yy[7] = c[3] * y[1] + c[27] * y[7];

		y[4] = yy[4] + yy[5];
		y[5] = yy[4] - yy[5];
		y[6] = -yy[6] + yy[7];
		y[7] = yy[6] + yy[7];

		yy[4] = y[4];
		yy[7] = y[7];
		yy[5] = c[15] * (-y[5] + y[6]);
		yy[6] = c[15] * (y[5] + y[6]);

		for (jj = 0; jj < 4; jj++)
			y[jj] = ait[jj] + yy[7 - jj];

		for (jj = 4; jj < 8; jj++)
			y[jj] = ait[7 - jj] - yy[jj];

		for (jj = 0; jj < B_size; jj++)
			z[ii][jj] = y[jj] / 4.0;

	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			ix[ii][jj] = nint(z[ii][jj]);

	return 0;
}


void CHW4v2Dlg::OnBnClickedButton3() //dct 압축
{
	int temp_map[512][512];
	int input[B_size][B_size];
	CClientDC dc(this);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for (int q = 0; q < 512; q = q + 8) 
	{
		for (int p = 0; p < 512; p = p + 8) // x축 추가 
		{
			for (int y = 0+q; y < B_size+q; y++)
			{
				for (int x = 0 + p; x < B_size + p; x++)
				{
					input[y%8][x%8] = image_map[y][x];

				}
			}
			dct(input);
			for (int a = 0 + q; a < B_size + q; a++)
			{
				for (int b = 0 + p; b < B_size + p; b++)
				{
					image_map[a][b] = input[a % 8][b % 8];
				}
			}


		}
	}
	for (int i = 0; i < lena.GetHeight(); i++)
	{
		for (int j = 0; j < lena.GetWidth(); j++)
		{
			temp_map[i][j] = image_map[i][j];
			if (temp_map[i][j] < 0)
				temp_map[i][j] = 0;
	
			dct_temp.SetPixel(i, j, RGB(temp_map[i][j], temp_map[i][j], temp_map[i][j]));
		}

	}
	dct_temp.Draw(dc, 513, 0);

}


void CHW4v2Dlg::OnBnClickedButton4()
{
	float mse=0.0;
	int input[B_size][B_size];
	CClientDC dc(this);
	CString str;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for (int q = 0; q < 512; q = q + 8)
	{
		for (int p = 0; p < 512; p = p + 8) // x축 추가 
		{
			for (int y = 0 + q; y < B_size + q; y++)
			{
				for (int x = 0 + p; x < B_size + p; x++)
				{
					input[y % 8][x % 8] = image_map[y][x];

				}
			}
			idct(input);
			for (int a = 0 + q; a < B_size + q; a++)
			{
				for (int b = 0 + p; b < B_size + p; b++)
				{
					image_map[a][b] = input[a % 8][b % 8];
				}
			}
		}
	}
	// MSE 계산 
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			tmp.SetPixel(i, j, RGB(image_map[i][j], image_map[i][j], image_map[i][j])); //출력할 이미지 ; 

			mse = mse + (origin_map[i][j] - image_map[i][j]) * (origin_map[i][j] - image_map[i][j]);
		}
	}
	mse = mse / (512 * 512);
	str.Format(L"MSE = %f", mse);
	AfxMessageBox(str);

	tmp.Draw(dc, 513, 0);
	
}
