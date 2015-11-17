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