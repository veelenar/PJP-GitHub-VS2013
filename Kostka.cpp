#include <glut.h>
#include "Kostka.h"

elementKostki kostka[3][3][3];

void GenerujKostkê(){

	for (int x = 0; x < 3; x++){
		for (int y = 0; y < 3; y++){
			for (int z = 0; z < 3; z++){
				kostka[x][y][z].iloscScian = dwie;
				kostka[x][y][z].kolor[0] = 0;
				kostka[x][y][z].kolor[1] = 0;
				kostka[x][y][z].kolor[2] = 0;
				kostka[z][y][x].numerElementu = x + y + z;
				kostka[x][y][z].obrotx = 0;
				kostka[x][y][z].obroty = 0;
				kostka[x][y][z].obrotz = 0;
			}
		}
	}

	kostka[1][1][0].iloscScian = jedna;
	kostka[1][1][2].iloscScian = jedna;
	kostka[1][0][1].iloscScian = jedna;
	kostka[1][2][1].iloscScian = jedna;
	kostka[0][1][1].iloscScian = jedna;
	kostka[2][1][1].iloscScian = jedna;

	for (int i=0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			kostka[0][i][j].kolor[0] = 6;
			kostka[2][i][j].kolor[0] = 5;
			kostka[i][0][j].kolor[1] = 3;
			kostka[i][2][j].kolor[1] = 2;
			kostka[i][j][0].kolor[2] = 4;
			kostka[i][j][2].kolor[2] = 1;

			if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 2)){
				kostka[i][j][0].iloscScian = trzy;
				kostka[i][j][2].iloscScian = trzy;
			}
		}
	}
}



void ObrocMacierzSciany(osObrotu os, kierunekObrotu kierunek, int numerSciany)
{
	elementKostki macierz[3][3];
	elementKostki obracanaMacierz[3][3];

	switch (os){
	case x:
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++){
				macierz[x][y] = kostka[numerSciany][x][y];
			}
		break;
	case y:
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++){
				macierz[x][y] = kostka[x][numerSciany][y];
			}
		break;
	case z:
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++){
				macierz[x][y] = kostka[x][y][numerSciany];
			}
		break;
	}

	if (kierunek == lewo)
	//w lewo
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < 3; j++)
		{
			obracanaMacierz[j][2 - i] = macierz[i][j];
		}
	}

	if (kierunek == prawo)
	//w prawo
	for (int j = 2; j >= 0; j--)
	{
		for (int i = 0; i < 3; i++)
		{
			obracanaMacierz[2 - j][i] = macierz[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++){
			switch (os){
			case x:

				if (kierunek == lewo)
					obracanaMacierz[i][j].obrotx -= 1;
				else if (kierunek == prawo)
					obracanaMacierz[i][j].obrotx += 1;

				if (obracanaMacierz[i][j].obrotx < 0)
					obracanaMacierz[i][j].obrotx = 3;
				if (obracanaMacierz[i][j].obrotx > 3)
					obracanaMacierz[i][j].obrotx = 0;


				kostka[numerSciany][i][j] = obracanaMacierz[i][j];

				break;
			
			case y:
				
				if (kierunek == lewo)
					obracanaMacierz[i][j].obroty -= 1;
				else if (kierunek == prawo)
					obracanaMacierz[i][j].obroty += 1;

				if (obracanaMacierz[i][j].obroty < 0)
					obracanaMacierz[i][j].obroty = 3;
				if (obracanaMacierz[i][j].obroty > 3)
					obracanaMacierz[i][j].obroty = 0;

				kostka[i][numerSciany][j] = obracanaMacierz[i][j];

				break;
			
			case z:
				if (kierunek == lewo)
					obracanaMacierz[i][j].obrotz -= 1;
				else if (kierunek == prawo)
					obracanaMacierz[i][j].obrotz += 1;

				if (obracanaMacierz[i][j].obrotz < 0)
					obracanaMacierz[i][j].obrotz = 3;
				if (obracanaMacierz[i][j].obrotz > 3)
					obracanaMacierz[i][j].obrotz = 0;

				kostka[i][j][numerSciany] = obracanaMacierz[i][j];

				break;
			}
		}
}



elementKostki* GetBrick(int x, int y, int z)
 {
	return &kostka[x + 1][y + 1][z + 1];
	}

int* GetNextBrick(int x, int y, int z, int* w)
 {//xyz obrot
	int v[3] = { w[0], w[1], w[2] };
	if (x<2)
		 {
		w[1] = -v[2];
		w[2] = v[1];
		}
	else if (y<2)
		 {
		w[0] = -v[2];
		w[2] = v[0];
		}
	else if (z<2)
		 {
		w[0] = -v[1];
		w[1] = v[0];
		}
	
		return w;
	}

void SetBrick(int* w, int kolorX, int kolorY, int kolorZ)
 {
	GetBrick(w[0], w[1], w[2])->kolor[0] = kolorX;
	GetBrick(w[0], w[1], w[2])->kolor[1] = kolorY;
	GetBrick(w[0], w[1], w[2])->kolor[2] = kolorZ;
	}

void AktualizujKolory(int x, int y, int z)
 {
	
		if (x<2)
		 {
		WymienX(x, -1, -1);
		WymienX(x, -1, 0);
		}
	else if (y<2)
		 {
		WymienY(-1, y, -1);
		WymienY(-1, y, 0);
		}
	else if (z<2)
		 {
		WymienZ(-1, -1, z);
		WymienZ(-1, 0, z);
		}
}

void WymienX(int x, int y, int z)
{
	int temp[3] = { 0 };
	int p[3], n[3];
	p[0] = n[0] = x;
	p[1] = n[1] = y;
	p[2] = n[2] = z;
	temp[0] = GetBrick(x, y, z)->kolor[0];
	temp[1] = GetBrick(x, y, z)->kolor[1];
	temp[2] = GetBrick(x, y, z)->kolor[2]; // temp 1kolor
	for (int i = 0; i<3; i++){
		GetNextBrick(x, 3, 3, n);
		SetBrick(p, GetBrick(n[0], n[1], n[2])->kolor[0],
			GetBrick(n[0], n[1], n[2])->kolor[2],
			GetBrick(n[0], n[1], n[2])->kolor[1]);
		p[0] = n[0];
		p[1] = n[1];
		p[2] = n[2];
		
	}
	GetNextBrick(x, 3, 3, n);
	SetBrick(p, temp[0],
		temp[2],
		temp[1]);
	}

void WymienY(int x, int y, int z)
 {
	int temp[3] = { 0 };
	int p[3], n[3];
	p[0] = n[0] = x;
	p[1] = n[1] = y;
	p[2] = n[2] = z;
	temp[0] = GetBrick(x, y, z)->kolor[0];
	temp[1] = GetBrick(x, y, z)->kolor[1];
	temp[2] = GetBrick(x, y, z)->kolor[2]; // temp 1kolor
	for (int i = 0; i<3; i++){
		GetNextBrick(3, y, 3, n);
		SetBrick(p, GetBrick(n[0], n[1], n[2])->kolor[2],
			GetBrick(n[0], n[1], n[2])->kolor[1],
			GetBrick(n[0], n[1], n[2])->kolor[0]);
		p[0] = n[0];
		p[1] = n[1];
		p[2] = n[2];
		
	}
	GetNextBrick(3, y, 3, n);
	SetBrick(p, temp[2],
		temp[1],
		temp[0]);
	}

void WymienZ(int x, int y, int z)
 {
	int temp[3] = { 0 };
	int p[3], n[3];
	p[0] = n[0] = x;
	p[1] = n[1] = y;
	p[2] = n[2] = z;
	temp[0] = GetBrick(x, y, z)->kolor[0];
	temp[1] = GetBrick(x, y, z)->kolor[1];
	temp[2] = GetBrick(x, y, z)->kolor[2]; // temp 1kolor
	for (int i = 0; i<3; i++){
		GetNextBrick(3, 3, z, n);
		SetBrick(p, GetBrick(n[0], n[1], n[2])->kolor[1],
			GetBrick(n[0], n[1], n[2])->kolor[0],
			GetBrick(n[0], n[1], n[2])->kolor[2]);
		p[0] = n[0];
		p[1] = n[1];
		p[2] = n[2];
		
	}
	GetNextBrick(3, 3, z, n);
	SetBrick(p, temp[1],
		temp[0],
		temp[2]);
	}
//void RysujPlaszczyzne(int x, int y, int z)//,int angle
// {
//		//ewentualny obrot
//		if (x<2)
//		 {
//		for (int j = -1; j <= 1; j++)
//			 for (int k = -1; k <= 1; k++)
//			 {
//			glTranslatef(x / 2.0f, j / 2.0f, k / 2.0f);
//			RysujSzescian(0.5, GetBrick(x, j, k));
//			}
//		}
//	else if (y<2)
//		 {
//		for (int j = -1; j <= 1; j++)
//			 for (int k = -1; k <= 1; k++)
//			 {
//			glTranslatef(j / 2.0f, y / 2.0f, k / 2.0f);
//			RysujSzescian(0.5, GetBrick(j, y, k));
//			}
//		}
//	else if (z<2)
//		 {
//		for (int j = -1; j <= 1; j++)
//			 for (int k = -1; k <= 1; k++)
//			 {
//			glTranslatef(j / 2.0f, k / 2.0f, z / 2.0f);
//			RysujSzescian(0.5, GetBrick(j, k, z));
//			}
//		}
//	}

//void animate(int* obrot)
// {
//	static float angle = 0.0f;
//	if (anim)
//		{
//		angle += 1.5f;
//		if (angle > 90)
//			 {
//			anim = false;
//			angle = 0.0f;
//			AktualizujKolory(obrot[0], obrot[1], obrot[2]);
//			}
//		if (obrot[0]<2)
//			 {
//			for (int i = -1; i<obrot[0]; i++) RysujPlaszczyzne(i, 3, 3);
//
//			glRotatef(-angle, 1, 0, 0);
//			RysujPlaszczyzne(obrot[0], 3, 3);
//
//			for (int i = obrot[0] + 1; i<2; i++) RysujPlaszczyzne(i, 3, 3);
//			}
//		else if (obrot[1]<2)
//			 {
//			for (int i = -1; i<obrot[1]; i++) RysujPlaszczyzne(3, i, 3);
//
//			glRotatef(angle, 0, 1, 0);
//			RysujPlaszczyzne(3, obrot[1], 3);
//
//			for (int i = obrot[1] + 1; i<2; i++) RysujPlaszczyzne(3, i, 3);
//			}
//		else if (obrot[2]<2)
//			 {
//			for (int i = -1; i<obrot[2]; i++) RysujPlaszczyzne(3, 3, i);
//
//			glRotatef(angle, 0, 0, 1);
//			RysujPlaszczyzne(3, 3, obrot[2]);
//
//			for (int i = obrot[2] + 1; i<2; i++) RysujPlaszczyzne(3, 3, i);
//			}
//		
//			}
//	else
//		 {
//		RysujPlaszczyzne(-1, 3, 3);
//		RysujPlaszczyzne(0, 3, 3);
//		RysujPlaszczyzne(1, 3, 3);
//		}
//	}

