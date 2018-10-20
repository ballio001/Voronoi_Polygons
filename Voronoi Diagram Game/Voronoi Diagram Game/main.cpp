// Voronoi Diagram Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <string>
#include "MyBitmap.h"
#include "Voronoi.h"


int main(int argc, char* argv[]) {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	srand(GetTickCount());

	MyBitmap bmp;
	bmp.Create(512, 512); //how big it is
	bmp.SetPenColor(0);

	Voronoi v;
	v.Make(&bmp, 50);

	BitBlt(GetDC(GetConsoleWindow()), 20, 20, 512, 512, bmp.hdc(), 0, 0, SRCCOPY);
	bmp.SaveBitmap("v.bmp");

	system("pause");

	return 0;
}

