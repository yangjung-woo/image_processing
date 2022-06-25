
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4496)
#include <stdio.h>
#include<windows.h> //비트맵헤더파일
#include<math.h> //cos , sin 함수 이용헤더
void CalculatePosition(int* source_x, int* source_y, int output_x, int output_y, int width, int height, double angle_rad);
void RotatingImage(BYTE* image, BYTE* output, int img_width, int img_height, long imgSize, int angle);

void main()
{

	// 1번 문제 raw 이미지 생성
	int i, j;
	unsigned char OrgImg[512][512]; //
	unsigned char rawImg[512][512];
	unsigned char temp;  // 영상 상하반전용 임시 

	for (i = 0; i < 512; i++)   // 가로 0~512 픽셀 까지의 (밝기)값을 그래프를 참고하여 수정 
	{
		for (j = 0;j < 100;j++)
		{
			OrgImg[i][j] = 120;
		}
		for (j = 100; j < 200; j++)
		{
			OrgImg[i][j] = 0.15*j + 105;
		}
		for (j = 200;j < 280;j++)
		{
			OrgImg[i][j] = 1.125*j - 90;
		}
		for (j = 280;j < 300;j++)
		{
			OrgImg[i][j] = 0.75*j + 15;
		}
		for (j = 300;j < 512;j++)
		{
			OrgImg[i][j] = 240;
		}
	}

	// 새로운 raw 파일 lena_v1.row 를 생성 
	FILE *outfile = fopen("lena_v1.raw", "wb");
	fwrite(OrgImg, sizeof(unsigned char), 512 * 512, outfile);
	fclose(outfile);


	//2번문제   1에서 생성된 raw이미지를 bmp파일로 생성

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
	FILE * infile2 = fopen("lena_v1.raw", "rb");
	if (infile2 == NULL) { printf("File open error!!"); return; } //파일 open 실패시 error 출력
	fread(rawImg, sizeof(char), 512 * 512, infile2);
	fclose(infile2);

	for (i = 0;i < 256;i++) //상하 반전 ? => bmp 파일은 아래에서 위로 읽기때문에 정상출력을 위해선 상하 반전을 해야한다
	{
		for (j = 0;j < 512;j++)
		{
			temp = rawImg[i][j];
			rawImg[i][j] = rawImg[512 - i - 1][j];
			rawImg[512 - i - 1][j] = temp;
		}

	}
	FILE * outfile2 = fopen("lena_v1.bmp", "wb");
	fwrite(&hfile, sizeof(char), sizeof(BITMAPFILEHEADER), outfile2);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile2);
	fwrite(hRGB, sizeof(RGBQUAD), 256, outfile2);
	fwrite(rawImg, sizeof(char), hInfo.biSizeImage, outfile2);
	fclose(outfile2);


	//3 bmp 파일 90도 회전

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBQUAD hRGB2[256];

	FILE* fp = fopen("lena_v1.bmp", "rb");
	if (fp == NULL) return;

	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB2, sizeof(RGBQUAD), 256, fp);

	long imgSize = bih.biWidth * bih.biHeight;

	BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSize);
	fread(image, sizeof(BYTE), imgSize, fp);
	fclose(fp);

	BYTE* output = (BYTE*)malloc(sizeof(BYTE) * imgSize);

	RotatingImage(image, output, bih.biWidth, bih.biHeight, imgSize, 90);


	fp = fopen("lena_v1_90.bmp", "wb");

	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(hRGB2, sizeof(RGBQUAD), 256, fp);
	fwrite(output, sizeof(BYTE), imgSize, fp);
	fclose(fp);

	free(image);
	free(output);


}

void RotatingImage(BYTE* image, BYTE* output, int img_width, int img_height, long imgSize, int angle)
{
	int source_x = 0;
	int source_y = 0;

	//입력된 각도를 라디안 값으로 바꿈 (파이값은 근삿값으로 3.141592)
	double angle_rad = (double)angle / 180 * 3.141592 * -1;

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++)
		{
			CalculatePosition(&source_x, &source_y, x, y, img_width, img_height, angle_rad);

			//만약 가져오려는 좌표가 캔버스를 벗어나면, 그냥 검정색으로 처리
			if ((source_y < img_width && source_x < img_height))
				output[y * img_height + x] = image[source_y * img_width + source_x];
			else
				output[y * img_height + x] = 0;
		}
	}
}
void CalculatePosition(int* source_x, int* source_y, int output_x, int output_y, int width, int height, double angle_rad)
{
	//이미지 회전 중심을 이미지의 중심으로 놓기 위해 평행이동
	output_x -= (width / 2);
	output_y -= (height / 2);

	//회전된 좌표를 가지고 원본에서 가져와야할 좌료를 구함.
	double _x = cos(angle_rad) * output_x + sin(angle_rad) * output_y;
	double _y = -1 * sin(angle_rad) * output_x + cos(angle_rad) * output_y;

	//평행이동을 원래대로 복구
	*source_x = (int)_x + (width / 2);
	*source_y = (int)_y + (height / 2);
}
