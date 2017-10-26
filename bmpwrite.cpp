#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <windows.h>

int N, M, color;

void fillheader(char header[]) {
	int filesize;
	// BITMAPFILEHEADER 
	BITMAPFILEHEADER bfh;
	ZeroMemory(&bfh, sizeof(bfh));

	bfh.bfType = 0x4d42; // сигнатура, должно быть 'BM' 
	bfh.bfSize = color ? 54 + M*ceil(3 * N / 4.0) * 4 : 54 + 1024 + M*N; // исправить размер файла 
	bfh.bfReserved1 = 0; // 
	bfh.bfReserved2 = 0; // 
	bfh.bfOffBits = color ? 54 : 54 + 256 * 4; // начало пиксельных данных, чб добавляет размер палитры 
	memcpy(header, &bfh, 14); // копируем в массив header 

							  // BITMAPINFOHEADER; 
	BITMAPINFOHEADER bih;
	ZeroMemory(&bih, 40);

	bih.biSize = 40; // размер структуры BITMAPINFOHEADER 
	bih.biWidth = N; // ширина 
	bih.biHeight = M; // высота, положит означает что данные надо записывать снизу вверх 
	bih.biPlanes = 1; // 
	bih.biBitCount = color ? 24 : 8; // число бит на пиксель 
	memcpy(header + 14, &bih, 40); // копируем в массив header 
}


void filldata(char data[], int **r, int **g, int **b) {
	int i, j;
	int linesize;
	if (color == 2)
	{
		linesize = ceil(3 * N / 4.0) * 4;
		for (i = M - 1; i >= 0; i--)
		{
			for (j = 0; j < N; j++)
			{

				data[(M - 1 - i) * linesize + j * 3] = b[i][j];
				data[(M - 1 - i) * linesize + j * 3 + 1] = g[i][j];
				data[(M - 1 - i) * linesize + j * 3 + 2] = r[i][j];
			}
		}
	}
	else {
		linesize = ceil(N / 4.0) * 4;
		//тут перевернутую дает, но почему то 3х3 нормально выглядит
		/*for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
		data[i * linesize + (j)] = b[i][j];
		k++;
		}
		}*/
		for (i = M - 1; i >= 0; i--) {
			for (j = 0; j < N; j++) {
				data[(M - 1 - i) * linesize + (j)] = b[i][j];
			}
		}
	}
	// заполнить данные. 
	// учесть: записывать снизу вверх, в цветном файле порядок b, g, r 
	// в случае чб есть только b 
}

void fillpalette(char palette[]) {
	if (color == 2) return;
	int i, j = 0;
	for (i = 0; i < 1024; i += 4)
	{
		palette[i] = j;
		palette[i + 1] = j;
		palette[i + 2] = j;
		palette[i + 3] = 0;
		j++;
	}
}


int main(char argc, char* argv[]) {
	int i, j, **r = 0, **g = 0, **b = 0;
	std::ifstream f;
	char *filename;
	if (argc > 1) filename = argv[1]; else filename = "inputgray.txt";
	f = std::ifstream(filename);
	if (f.fail()) {
		std::cerr << "could not open file\n";
		return -1;
	}

	f >> N >> M >> color;

	// âûäåëÿåì ïàìÿòü ïîä îäèí (äëÿ ÷á) èëè òðè (äëÿ öâ) ìàññèâà MxN 
	b = new int*[M]; for (i = 0; i < M; i++) b[i] = new int[N];
	if (color) {
		g = new int*[M]; for (i = 0; i < M; i++) g[i] = new int[N];
		r = new int*[M]; for (i = 0; i < M; i++) r[i] = new int[N];
	}

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			if (color)
				f >> r[i][j] >> g[i][j] >> b[i][j];
			else
				f >> b[i][j];
		}
	}
	f.close();

	char *bmpfilename = new char[strlen(filename) + 4];
	strcpy(bmpfilename, filename);
	strcat(bmpfilename, ".bmp");
	FILE* bmpfile = fopen(bmpfilename, "wb");
	char header[54];
	char palette[4 * 256];

	int datasize = color ? M * ceil(3 * N / 4.0) * 4 : M * ceil(N / 4.0) * 4;   // !!!!!!! ðàçìåð ïèêñåëüíûõ äàííûõ, ÷òîáû ðàçìåð ñòðîêè áûë êðàòåí 4 áàéòàì
																				// èñïðàâèòü äëÿ ÷á ñëó÷àÿ, ñåé÷àñ çàãëóøêà â âèäå 1.
	char* data = new char[datasize];

	fillheader(header);         // çàïîëíèòü çàãîëîâêè
	fillpalette(palette);       // çàïîëíèòü ïàëèòðó (åñëè íàäî)
	filldata(data, r, g, b);    // çàïîëíèòü ìàññèâ ïèêñåëüíûõ äàííûõ

	fwrite(header, 1, 54, bmpfile);             // çàïèñàòü çàãîëîâêè
	if (!color) {
		fwrite(palette, 1, 4 * 256, bmpfile);   // åñëè ÷á, çàïèñàòü ïàëèòðó
	}
	fwrite(data, 1, datasize, bmpfile);         // çàïèñàòü ïèêñåëüíûå äàííûå

	fclose(bmpfile);
}