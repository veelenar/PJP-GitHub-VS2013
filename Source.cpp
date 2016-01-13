#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <glut.h>
#include <time.h>
#include <string.h>
#include "Kostka.h"


// sta�e do obs�ugi menu podr�cznego

enum
{
	FULL_WINDOW, // aspekt obrazu - ca�e okno
	ASPECT_1_1, // aspekt obrazu 1:1
	EXIT // wyj�cie
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bry�y obcinania

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble neaar = 50.0;
const GLdouble faar = 70.0;

// wsp�czynnik skalowania

GLfloat scale = 3.0;

//zegar

int cl = clock();

// k�ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
GLfloat pozycjax = 0.0;
GLfloat pozycjay = 0.0;

//obr�t sciany
int rotateWallDepth = 0;
GLfloat rotateWall = 0.0;
osObrotu os = x;
//GLfloat rotateWallx = 0.0;
//GLfloat rotateWally = 0.0;
//GLfloat rotateWallz = 0.0;

// przesuni�cie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;
float kat = 0;
// wska�nik naci�ni�cia lewego przycisku myszki

int button_state = GLUT_UP;

bool pressed = false;
// po�o�enie kursora myszki

int button_x, button_y;

extern void UstawKolor(int numerKoloru);

// licznik ramek (FPS)

int frames = 0;

// licznik czasu

long start_time = 0;

// tablica znak�w ze warto�ci� FPS

char time_string[100];
char button1_string[100];
char button2_string[100];
char button3_string[100];
char button4_string[100];
// funkcja rysuj�ca napis w wybranym miejscu

void DrawString(GLfloat x, GLfloat y, char * string)
{
	// po�o�enie napisu
	glRasterPos2f(x, y);

	// wy�wietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);

}

void RysujSzescian(float x, float y, float z, int colorx, int colory, int colorz)
{
	//bool koloruj = true;
	float da = 0.6f / 2;
	float da_2 = da - 0.01f;

	//if (koloruj) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);  // zielony

	UstawKolor(0);
	glLineWidth(3.5f);
	glBegin(GL_LINE_LOOP);
	//tylna
	glVertex3f(x + da, y - da, z - da);
	glVertex3f(x + da, y + da, z - da);
	glVertex3f(x - da, y + da, z - da);
	glVertex3f(x - da, y - da, z - da);
	glEnd();

	//if (koloruj) glColor4f(0.0f, 0.0f, 1.0f, 1.0f);  // niebieski

	glBegin(GL_LINE_LOOP);
	//przednia
	glVertex3f(x + da, y - da, z + da);
	glVertex3f(x + da, y + da, z + da);
	glVertex3f(x - da, y + da, z + da);
	glVertex3f(x - da, y - da, z + da);
	glEnd();

	UstawKolor(colorz);

	glBegin(GL_POLYGON);
	//tylna
	glVertex3f(x + da_2, y - da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glVertex3f(x - da_2, y - da_2, z - da_2);
	glEnd();

	//if (koloruj) glColor4f(0.0f, 0.0f, 1.0f, 1.0f);  // niebieski

	glBegin(GL_POLYGON);
	//przednia
	glVertex3f(x + da_2, y - da_2, z + da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z + da_2);
	glEnd();

	//if (koloruj) glColor4f(1.0f, 0.0f, 0.0f, 1.0f);  // czerwony

	UstawKolor(0);

	glBegin(GL_LINE_LOOP);
	//prawa
	glVertex3f(x + da, y + da, z - da);
	glVertex3f(x + da, y + da, z + da);
	glVertex3f(x + da, y - da, z + da);
	glVertex3f(x + da, y - da, z - da);
	glEnd();

	//if (koloruj) glColor3ub(255, 127, 39);	//pomaranczowy

	glBegin(GL_LINE_LOOP);
	//lewa
	glVertex3f(x - da, y + da, z - da);
	glVertex3f(x - da, y + da, z + da);
	glVertex3f(x - da, y - da, z + da);
	glVertex3f(x - da, y - da, z - da);
	glEnd();

	UstawKolor(colorx);

	glBegin(GL_POLYGON);
	//prawa
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x + da_2, y - da_2, z + da_2);
	glVertex3f(x + da_2, y - da_2, z - da_2);
	glEnd();

	//if (koloruj) glColor3ub(255, 127, 39);	//pomaranczowy

	glBegin(GL_POLYGON);
	//lewa
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z - da_2);
	glEnd();

	//if (koloruj) glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //bia�y

	UstawKolor(0);

	glBegin(GL_LINE_LOOP);
	//g�ra
	glVertex3f(x + da, y + da, z - da);
	glVertex3f(x + da, y + da, z + da);
	glVertex3f(x - da, y + da, z + da);
	glVertex3f(x - da, y + da, z - da);
	glEnd();

	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  // ��ty

	glBegin(GL_LINE_LOOP);
	//d�
	glVertex3f(x + da, y - da, z - da);
	glVertex3f(x + da, y - da, z + da);
	glVertex3f(x - da, y - da, z + da);
	glVertex3f(x - da, y - da, z - da);
	glEnd();

	UstawKolor(colory);

	glBegin(GL_POLYGON);
	//g�ra
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glEnd();

	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  // ��ty

	glBegin(GL_POLYGON);
	//d�
	glVertex3f(x + da_2, y - da_2, z - da_2);
	glVertex3f(x + da_2, y - da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z - da_2);
	glEnd();
}

void UstawKolor(int numerKoloru)
{
	switch (numerKoloru)
	{
	case 0:
		glColor3ub(0, 0, 0);
		//czarny - puste pole
		break;
	case 1:
		glColor3ub(7, 205, 22);
		//zielony
		break;
	case 2:
		glColor3ub(255, 255, 0);
		//zolty
		break;
	case 3:
		glColor3ub(255, 255, 255);
		//bialy
		break;
	case 4:
		glColor3ub(0, 0, 255);
		//niebieski
		break;
	case 5:
		glColor3ub(255, 0, 0);
		//czerwony
		break;
	case 6:
		glColor3ub(255, 127, 39);
		//pomaranczowy
		break;
	}
}

void timer(void)
{
	int sekundy, setne = 0;
	sekundy = clock();
	setne = sekundy % 1000 / 10;
	sekundy /= 1000;
	sprintf(time_string, "Czas: %2d: %2d: %2d", (sekundy / 60) % 59, sekundy % 60, setne);
	sprintf(button1_string, "ZERUJ"); 
	sprintf(button2_string, "WYMIESZAJ");
	sprintf(button3_string, "START");
	sprintf(button4_string, "STOP");

	glutPostRedisplay();
}

void LosujSciane()
{

}

void RysujPrzycisk(float x, float y, float z)
{

	float da = 0.6f / 2;
	UstawKolor(0);
	glLineWidth(3.5f);
	glBegin(GL_LINE_LOOP);
	//tylna
	glVertex3f(x + 2.5f, y - 1.0f, z - da);
	glVertex3f(x + 2.5f, y + da, z - da);
	glVertex3f(x - 2.5f, y + da, z - da);
	glVertex3f(x - 2.5f, y - 1.0f, z - da);
	glEnd();
}

void Display()
{
	// licznik czasu
	if (!frames++)
		start_time = clock();
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(0.3, 0.3, 0.3, 1.0);

	// czyszczenie bufora koloru i g��bi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czy�ci bufory
	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);

	//glRotatef(kat, 0.0f, 1.0f, 0.0f);
	//glRotatef(kat, 0.0f, 0.0f, 1.0f);
	timer();
	
	

	for (int x = 0; x < 3; x++){
		for (int y = 0; y < 3; y++){
			for (int z = 0; z < 3; z++){
				int *kolor = kostka[x][y][z].kolor;

				// macierz modelowania = macierz jednostkowa
				glLoadIdentity();

				// przesuni�cie uk�adu wsp�rz�dnych obiektu do �rodka bry�y odcinania
				glTranslatef(0, 0, -(neaar + faar) / 2);

				// skalowanie obiektu - klawisze "+" i "-"
				glScalef(scale, scale, scale);

				// obroty obiektu - prawa mysz
				glRotatef(rotatex, 1.0, 0, 0);
				glRotatef(rotatey, 0, 1.0, 0);





				if (os == osObrotu::x){
					if (rotateWallDepth == x){
						glRotatef(rotateWall, 1.0, 0, 0);
					}
				}
				else if (os == osObrotu::y)
				{
					if (rotateWallDepth == y){
						glRotatef(rotateWall, 0, 1.0, 0);
					}
				}
				else if (os == osObrotu::z)
				{
					if (rotateWallDepth == z){
						glRotatef(rotateWall, 0, 0, 1.0);
					}
				}

					glTranslatef(x*0.6f - 0.6f, (y*-0.6f) + 0.6, (z*-0.6f) + 0.6f);

						glRotatef((GLfloat)(90.0f * (float)(kostka[x][y][z].obrotz)), 0, 0, 1.0f);
						glRotatef((GLfloat)(90.0f * (float)(kostka[x][y][z].obroty)), 0, 1.0f, 0);
						glRotatef((GLfloat)(90.0f * (float)(kostka[x][y][z].obrotx)), 1.0f, 0, 0);
						
				RysujSzescian(0, 0, 0, kolor[0], kolor[1], kolor[2]);
			}
		}
	}

	//os = z;
	if (!pressed)
		rotateWall += 0.05;
	if (rotateWall >= 90){
		rotateWall = 0;
		
		if (os == osObrotu::z){
			ObrocMacierzSciany(os, lewo, rotateWallDepth);
		}
		else
		{
			ObrocMacierzSciany(os, prawo, rotateWallDepth);
		}
		
		rotateWallDepth++;
		if (rotateWallDepth > 2)
			rotateWallDepth = 0;

		if (os == osObrotu::x)
			os = osObrotu::y;
		else if (os == osObrotu::y)
			os = osObrotu::z;
		else if (os == osObrotu::z)
			os = osObrotu::x;

		//LosujSciane();
	}

	glLoadIdentity();
	glTranslatef(0, 0, -neaar);
	RysujPrzycisk(-10.0f, 9.0f, 0.0f);
	RysujPrzycisk(10.0f, -5.5f, 0.0f);
	RysujPrzycisk(0.0f, -5.5f, 0.0f);
	RysujPrzycisk(-10.0f, -5.5f, 0.0f);
	glColor3ub(255, 255, 255);

	// narysowanie napisu
	DrawString(-12.5, 9.5, time_string);
	DrawString(-10.87, 8.60, button1_string);
	DrawString(8.8, -6.0, button2_string);
	DrawString(-0.5, -6.0, button4_string);
	DrawString(-10.70, -6.0, button3_string);
	// skierowanie polece� do wykonania
	glFlush();

	// zamiana bufor�w koloru
	glutSwapBuffers();
}

// zmiana wielko�ci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca�e okno
	glViewport(0, 0, width, height);

	// wyb�r macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	if (width < height && width > 0)
		glFrustum(left, right, bottom * height / width, top * height / width, neaar, faar);
	else

		// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
		if (width >= height && height > 0)
			glFrustum(left * width / height, right * width / height, bottom, top, neaar, faar);
	// generowanie sceny 3D
	Display();
}

// obs�uga klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.1;
	else

		// klawisz -
		if (key == '-' && scale > 0.1)
			scale -= 0.1;

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


// obs�uga przycisk�w myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		// zapami�tanie stanu prawego przycisku myszki
		button_state = state;

		// zapami�tanie po�o�enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
	else if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
			/*if (pozycjax <= -10.0f + 2.5f && pozycjax >= -10.0f - 2.5f && pozycjay <= 9.0f && pozycjay >= 9.0f - 1.0f){*/
				pressed = !pressed;
			/*}*/
			if (!pressed)
				glutPostRedisplay();
		}
	}
}

// obs�uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (GLUT_RIGHT_BUTTON)
	{
		if (button_state == GLUT_DOWN)
		{
			rotatey += 10.1 *(right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
			button_x = x;
			rotatex -= 10.1 *(top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
			button_y = y;
		}
	}
	else if (GLUT_LEFT_BUTTON)
	{
		if (button_state == GLUT_DOWN)
		{
			pozycjax = (-10.0f + 2.5f) / glutGet(GLUT_WINDOW_WIDTH)*(x - button_x);
			button_x = x;
			pozycjay = (9.0f - 1.0f) / glutGet(GLUT_WINDOW_HEIGHT)*(button_y - y);
			button_y = y;
		}
	}
}



int main(int argc, char * argv[])
{
	GenerujKostk�();
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);


	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary g��wnego okna programu
	glutInitWindowSize(800, 600);

	// utworzenie g��wnego okna programu
#ifdef WIN32

	glutCreateWindow("Kostka Rubika");
#else
	glutCreateWindow("Kostka Rubika");
#endif

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);
	// obs�uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);


	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}