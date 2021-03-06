#include <glut.h>
#include "Kostka.h"

elementKostki kostka[3][3][3];

void GenerujKostk�(){

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
			kostka[0][i][j].kolor[0] = 5;
			kostka[2][i][j].kolor[0] = 6;
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
	elementKostki macierz[3][3][3];
	elementKostki obracanaMacierz[3][3][3];

	switch (os){
	case x:
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++){
				macierz[numerSciany][x][y] = kostka[numerSciany][x][y];
			}
		break;
	case y:
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++){
				macierz[x][numerSciany][y] = kostka[x][numerSciany][y];
			}
		break;
	case z:
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++){
				macierz[x][y][numerSciany] = kostka[x][y][numerSciany];
			}
		break;
	}

	switch (os){
	case x:
		if (kierunek == lewo)
			//w lewo
			for (int i = 2; i >= 0; i--)
			{
				for (int j = 0; j < 3; j++)
				{
					obracanaMacierz[numerSciany][j][2 - i] = macierz[numerSciany][i][j];
				}
			}

		else if (kierunek == prawo)
			//w prawo
			for (int j = 2; j >= 0; j--)
			{
				for (int i = 0; i < 3; i++)
				{
					obracanaMacierz[numerSciany][2 - j][i] = macierz[numerSciany][i][j];
				}
			}
		break;
	case y:
		if (kierunek == lewo)
			//w lewo
			for (int i = 2; i >= 0; i--)
			{
				for (int j = 0; j < 3; j++)
				{
					obracanaMacierz[j][numerSciany][2 - i] = macierz[i][numerSciany][j];
				}
			}

		else if (kierunek == prawo)
			//w prawo
			for (int j = 2; j >= 0; j--)
			{
				for (int i = 0; i < 3; i++)
				{
					obracanaMacierz[2 - j][numerSciany][i] = macierz[i][numerSciany][j];
				}
			}
		break;
	case z:
		if (kierunek == lewo)
			//w lewo
			for (int i = 2; i >= 0; i--)
			{
				for (int j = 0; j < 3; j++)
				{
					obracanaMacierz[j][2 - i][numerSciany] = macierz[i][j][numerSciany];
				}
			}

		else if (kierunek == prawo)
			//w prawo
			for (int j = 2; j >= 0; j--)
			{
				for (int i = 0; i < 3; i++)
				{
					obracanaMacierz[2 - j][i][numerSciany] = macierz[i][j][numerSciany];
				}
			}
		break;
	}
	///////////////////////////////////////////////////////////////////
	// Obr�t  kosteczek                                              //
	///////////////////////////////////////////////////////////////////
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++){
			switch (os){
			case x:

				if (kierunek == lewo){
					obracanaMacierz[numerSciany][i][j].obrotx -= 1;
				}
				else if (kierunek == prawo){
					obracanaMacierz[numerSciany][i][j].obrotx += 1;
				}
				if (obracanaMacierz[numerSciany][i][j].obrotx < 0)
				{
					obracanaMacierz[numerSciany][i][j].obrotx = 3;
				}
				if (obracanaMacierz[numerSciany][i][j].obrotx > 3){
					obracanaMacierz[numerSciany][i][j].obrotx = 0;
				}


				kostka[numerSciany][i][j] = obracanaMacierz[numerSciany][i][j];


				break;

			case y:

				if (kierunek == prawo)
				{

					obracanaMacierz[i][numerSciany][j].obroty += 1;
				}
				else if (kierunek == lewo)
				{

					obracanaMacierz[i][numerSciany][j].obroty -= 1;
				}

				if (obracanaMacierz[i][numerSciany][j].obroty < 0){
					obracanaMacierz[i][numerSciany][j].obroty = 3;
				}
				if (obracanaMacierz[i][numerSciany][j].obroty > 3)
				{
					obracanaMacierz[i][numerSciany][j].obroty = 0;
				}

				kostka[i][numerSciany][j] = obracanaMacierz[i][numerSciany][j];

				break;

			case z:
				if (kierunek == prawo)
				{
					obracanaMacierz[i][j][numerSciany].obrotz += 1;
				}
				else if (kierunek == lewo)
				{

					obracanaMacierz[i][j][numerSciany].obrotz -= 1;
				}

				if (obracanaMacierz[i][j][numerSciany].obrotz < 0)
				{
					obracanaMacierz[i][j][numerSciany].obrotz = 3;
				}
				if (obracanaMacierz[i][j][numerSciany].obrotz > 3)
				{
					obracanaMacierz[i][j][numerSciany].obrotz = 0;
				}

				kostka[i][j][numerSciany] = obracanaMacierz[i][j][numerSciany];
		

				break;
			}
		}
}
//void ObrocMacierzSciany(osObrotu os, kierunekObrotu kierunek, int numerSciany)
//{
//	elementKostki obracanaMacierz[3][3][3];
//
//	if (kierunek == lewo)
//		//w lewo
//		for (int i = 2; i >= 0; i--)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				for (int k = 0; k < 3; k++)
//				{
//					obracanaMacierz[j][2 - i][k] = kostka[i][j][k];
//				}
//			}
//		}
//
//	if (kierunek == prawo)
//		//w prawo
//		for (int j = 2; j >= 0; j--)
//		{
//			for (int i = 0; i < 3; i++)
//			{
//				for (int k = 0; k < 3; k++)
//				{
//					obracanaMacierz[2 - j][i][k] = kostka[i][j][k];
//				}
//			}
//		}
//
//	for (int i = 0; i < 3; i++)
//		for (int j = 0; j < 3; j++){
//			switch (os){
//			case x:
//
//				if (kierunek == lewo){
//					kostka[numerSciany][i][j].obrotx -= 1;
//				}
//				else if (kierunek == prawo){
//					kostka[numerSciany][i][j].obrotx += 1;
//				}
//
//				if (kostka[numerSciany][i][j].obrotx < 0)
//				{
//					kostka[numerSciany][i][j].obrotx = 3;
//				}
//
//				if (kostka[numerSciany][i][j].obrotx > 3)
//				{
//					kostka[numerSciany][i][j].obrotx = 0;
//				}
//
//
//				kostka[numerSciany][i][j] = obracanaMacierz[numerSciany][i][j];
//
//
//				break;
//
//			case y:
//
//				if (kierunek == lewo)
//				{
//					kostka[i][numerSciany][j].obroty -= 1;
//				}
//				else if (kierunek == prawo)
//				{
//					kostka[i][numerSciany][j].obroty += 1;
//				}
//
//				if (kostka[i][numerSciany][j].obroty < 0){
//					kostka[i][numerSciany][j].obroty = 3;
//				}
//				if (kostka[i][numerSciany][j].obroty > 3)
//				{
//					kostka[i][numerSciany][j].obroty = 0;
//				}
//
//				kostka[i][numerSciany][j] = obracanaMacierz[i][numerSciany][j];
//
//				break;
//
//			case z:
//				if (kierunek == lewo)
//				{
//					kostka[i][j][numerSciany].obrotz -= 1;
//				}
//				else if (kierunek == prawo)
//				{
//					kostka[i][j][numerSciany].obrotz += 1;
//				}
//
//				if (kostka[i][j][numerSciany].obrotz < 0)
//				{
//					kostka[i][j][numerSciany].obrotz = 3;
//				}
//				if (kostka[i][j][numerSciany].obrotz > 3)
//				{
//					kostka[i][j][numerSciany].obrotz = 0;
//				}
//
//				kostka[i][j][numerSciany] = obracanaMacierz[i][j][numerSciany];
//
//
//				break;
//			}
//		}
//}

//void Kostka_Ob_Sciany(osObrotu os, kierunekObrotu kierunek, int numerSciany){
//	int i, j;
//	if (os == x)
//	{
//		for (i = 0; i < 3; i++)
//		{
//			for (j = 0; j < 3; j++)
//			{
//				kostka[numerSciany][j][2 - i].kolor[0] = kostka[numerSciany][i][j].kolor[2];
//				kostka[numerSciany][j][2 - i].kolor[0] = kostka[numerSciany][i][j].kolor[2];
//			}
//			kostka[numerSciany][i][2].kolor[2] = kostka[numerSciany][0][i].kolor[0];
//			kostka[numerSciany][2][2 - i].kolor[1] = kostka[numerSciany][i][2].kolor[1];
//			kostka[numerSciany][i][0].kolor[2] = kostka[numerSciany][2][i].kolor[0];
//			kostka[numerSciany][0][2 - i].kolor[1] = kostka[numerSciany][i][0].kolor[1];
//		}
//	}
//	else if (os == y)
//	{
//		for (i = 0; i < 3; i++)
//		{
//			for (j = 0; j < 3; j++)
//			{
//				kostka[2 - j][numerSciany][i].kolor[1] = kostka[i][numerSciany][j].kolor[0];
//				kostka[2 - j][numerSciany][i].kolor[1] = kostka[i][numerSciany][j].kolor[0];
//			}
//			kostka[2][numerSciany][i].kolor[0] = kostka[i][numerSciany][0].kolor[2];
//			kostka[2 - i][numerSciany][2].kolor[2] = kostka[2][numerSciany][i].kolor[0];
//			kostka[0][numerSciany][i].kolor[0] = kostka[i][numerSciany][2].kolor[2];
//			kostka[2 - i][numerSciany][0].kolor[2] = kostka[0][numerSciany][i].kolor[0];
//		}
//	}
//	else if (os == z)
//	{
//		for (i = 0; i < 3; i++)
//		{
//			for (j = 0; j < 3; j++)
//			{
//				kostka[j][2 - i][numerSciany].kolor[2] = kostka[i][j][numerSciany].kolor[1];
//				kostka[j][2 - i][numerSciany].kolor[2] = kostka[i][j][numerSciany].kolor[1];
//			}
//			kostka[i][0][numerSciany].kolor[2] = kostka[2][i][numerSciany].kolor[0];
//			kostka[0][2 - i][numerSciany].kolor[0] = kostka[i][0][numerSciany].kolor[1];
//			kostka[i][2][numerSciany].kolor[1] = kostka[0][i][numerSciany].kolor[0];
//			kostka[2][2 - i][numerSciany].kolor[0] = kostka[i][2][numerSciany].kolor[1];
//		}
//	}
//}