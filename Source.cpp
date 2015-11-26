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


// sta³e do obs³ugi menu podrêcznego

enum
{
	FULL_WINDOW, // aspekt obrazu - ca³e okno
	ASPECT_1_1, // aspekt obrazu 1:1
	EXIT // wyjœcie
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bry³y obcinania

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble neaar = 50.0;
const GLdouble faar = 70.0;

// wspó³czynnik skalowania

GLfloat scale = 3.0;

int cl = clock();
// k¹ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesuniêcie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;
float kat = 0;
// wskaŸnik naciœniêcia lewego przycisku myszki

int button_state = GLUT_UP;

// po³o¿enie kursora myszki

int button_x, button_y;

extern void UstawKolor(int numerKoloru);

// licznik ramek (FPS)

int frames = 0;

// licznik czasu

long start_time = 0;

// tablica znaków ze wartoœci¹ FPS

char time_string[100] = "FPS:";

// funkcja rysuj¹ca napis w wybranym miejscu

void DrawString(GLfloat x, GLfloat y, char * string)
{
	// po³o¿enie napisu
	glRasterPos2f(x, y);

	// wyœwietlenie napisu
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

	//if (koloruj) glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //bia³y

	UstawKolor(0);

	glBegin(GL_LINE_LOOP);
	//góra
	glVertex3f(x + da, y + da, z - da);
	glVertex3f(x + da, y + da, z + da);
	glVertex3f(x - da, y + da, z + da);
	glVertex3f(x - da, y + da, z - da);
	glEnd();

	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  // ¿ó³ty

	glBegin(GL_LINE_LOOP);
	//dó³
	glVertex3f(x + da, y - da, z - da);
	glVertex3f(x + da, y - da, z + da);
	glVertex3f(x - da, y - da, z + da);
	glVertex3f(x - da, y - da, z - da);
	glEnd();

	UstawKolor(colory);

	glBegin(GL_POLYGON);
	//góra
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glEnd();

	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  // ¿ó³ty

	glBegin(GL_POLYGON);
	//dó³
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

	glutPostRedisplay();
}

void Display()
{
	// licznik czasu
	if (!frames++)
		start_time = clock();
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// czyszczenie bufora koloru i g³êbi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyœci bufory
	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();



	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(neaar + faar) / 2);

	// przesuniêcie obiektu - ruch myszk¹
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	glRotatef(kat, 0.0f, 1.0f, 0.0f);
	glRotatef(kat, 0.0f, 0.0f, 1.0f);
	GenerujKostkê();
	timer();
	// w³¹czenie testu bufora g³êbokoœci
	glEnable(GL_DEPTH_TEST);

	for (int x = 0; x < 3; x++){
		for (int y = 0; y < 3; y++){
			for (int z = 0; z < 3; z++){
				int *kolor = kostka[x][y][z].kolor;
				RysujSzescian(x*0.6f - 0.6f, (y*-0.6f) + 0.6, (z*-0.6f) + 0.6f, kolor[0], kolor[1], kolor[2]);
			}
		}
	}



	glLoadIdentity();

	glTranslatef(0, 0, -neaar);
	glColor3ub(255, 255, 255);

	// narysowanie napisu
	DrawString(-12.5, 9.5, time_string);

	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}

void obroty(void)
{
	// zwiêkszenie k¹ta o 5 stopni po wykryciu
	// bezczynnoœci systemu
	if (kat == 360) kat = 0;
	kat += 0.09;
	// wymuszenie ponownego przerysowania okna
	glutPostRedisplay();
}
// zmiana wielkoœci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	if (width < height && width > 0)
		glFrustum(left, right, bottom * height / width, top * height / width, neaar, faar);
	else

		// szerokoœæ okna wiêksza lub równa wysokoœci okna
		if (width >= height && height > 0)
			glFrustum(left * width / height, right * width / height, bottom, top, neaar, faar);
	// generowanie sceny 3D
	Display();
}

// obs³uga klawiatury

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


// obs³uga przycisków myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		// zapamiêtanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o¿enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs³uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 10.1 *(right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
		button_x = x;
		rotatex += 10.1 *(top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}



int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);


	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary g³ównego okna programu
	glutInitWindowSize(800, 600);

	// utworzenie g³ównego okna programu
#ifdef WIN32

	glutCreateWindow("Kostka Rubika");
#else
	glutCreateWindow("Kostka Rubika");
#endif

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// obs³uga przycisków myszki
	glutMouseFunc(MouseButton);

	// obs³uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	glutIdleFunc(obroty);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}