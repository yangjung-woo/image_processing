
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4496)
#include <stdio.h>
#include<windows.h> //��Ʈ���������
#include<math.h> //cos , sin �Լ� �̿����
void CalculatePosition(int* source_x, int* source_y, int output_x, int output_y, int width, int height, double angle_rad);
void RotatingImage(BYTE* image, BYTE* output, int img_width, int img_height, long imgSize, int angle);

void main()
{

	// 1�� ���� raw �̹��� ����
	int i, j;
	unsigned char OrgImg[512][512]; //
	unsigned char rawImg[512][512];
	unsigned char temp;  // ���� ���Ϲ����� �ӽ� 

	for (i = 0; i < 512; i++)   // ���� 0~512 �ȼ� ������ (���)���� �׷����� �����Ͽ� ���� 
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

	// ���ο� raw ���� lena_v1.row �� ���� 
	FILE *outfile = fopen("lena_v1.raw", "wb");
	fwrite(OrgImg, sizeof(unsigned char), 512 * 512, outfile);
	fclose(outfile);


	//2������   1���� ������ raw�̹����� bmp���Ϸ� ����

	BITMAPFILEHEADER hfile;
	BITMAPINFOHEADER hInfo;
	RGBQUAD hRGB[256];


	//���� ��� ���� �Է�
	hfile.bfType = 0x4D42; // ��Ʈ�� ���� �����ѹ� "BM"
	hfile.bfSize = (DWORD)(512 * 512 + sizeof(RGBQUAD) + sizeof(BITMAPCOREINFO) + sizeof(BITMAPFILEHEADER)); // ���� ũ�� 
	hfile.bfReserved1 = 0;
	hfile.bfReserved2 = 0;
	hfile.bfOffBits = (DWORD)(sizeof(RGBQUAD) * 256 + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)); //��Ʈ�� ������ ������ġ ���� �����ϴ�

	//������� �����Է�
	hInfo.biSize = sizeof(BITMAPINFOHEADER);	//�� ����ü�� ũ��
	hInfo.biWidth = 512;			//�ȼ������� ������ ��
	hInfo.biHeight = 512;			//������ ����
	hInfo.biPlanes = 1;				//��Ʈ �÷��� ��(�׻� 1) 
	hInfo.biBitCount = 8;			//�ȼ��� ��Ʈ��(�÷�, ��� ����)
	hInfo.biCompression = BI_RGB;	//��������  ����� RGB    BI_BITFIELDS �÷�����ũ�� ������ ����� rgb
	hInfo.biSizeImage = 512 * 512;	//������ ũ��(Byte����)		
	hInfo.biXPelsPerMeter = 0;		//���� �ػ�
	hInfo.biYPelsPerMeter = 0;		//���� �ػ�
	hInfo.biClrUsed = 256;			//���� ��� ����� 0~255
	hInfo.biClrImportant = 256;		//�߿��� ���� �ε��� 0~255

	// �ȷ�Ʈ ���� �Է�
	for (int i = 0; i < 256; i++) {
		hRGB[i].rgbRed = i;		//R����
		hRGB[i].rgbGreen = i;		//G����
		hRGB[i].rgbBlue = i;		//B����
		hRGB[i].rgbReserved = 0;	//����� ����

	}
	//raw ���� �б�
	FILE * infile2 = fopen("lena_v1.raw", "rb");
	if (infile2 == NULL) { printf("File open error!!"); return; } //���� open ���н� error ���
	fread(rawImg, sizeof(char), 512 * 512, infile2);
	fclose(infile2);

	for (i = 0;i < 256;i++) //���� ���� ? => bmp ������ �Ʒ����� ���� �б⶧���� ��������� ���ؼ� ���� ������ �ؾ��Ѵ�
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


	//3 bmp ���� 90�� ȸ��

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

	//�Էµ� ������ ���� ������ �ٲ� (���̰��� �ٻ����� 3.141592)
	double angle_rad = (double)angle / 180 * 3.141592 * -1;

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++)
		{
			CalculatePosition(&source_x, &source_y, x, y, img_width, img_height, angle_rad);

			//���� ���������� ��ǥ�� ĵ������ �����, �׳� ���������� ó��
			if ((source_y < img_width && source_x < img_height))
				output[y * img_height + x] = image[source_y * img_width + source_x];
			else
				output[y * img_height + x] = 0;
		}
	}
}
void CalculatePosition(int* source_x, int* source_y, int output_x, int output_y, int width, int height, double angle_rad)
{
	//�̹��� ȸ�� �߽��� �̹����� �߽����� ���� ���� �����̵�
	output_x -= (width / 2);
	output_y -= (height / 2);

	//ȸ���� ��ǥ�� ������ �������� �����;��� �·Ḧ ����.
	double _x = cos(angle_rad) * output_x + sin(angle_rad) * output_y;
	double _y = -1 * sin(angle_rad) * output_x + cos(angle_rad) * output_y;

	//�����̵��� ������� ����
	*source_x = (int)_x + (width / 2);
	*source_y = (int)_y + (height / 2);
}
