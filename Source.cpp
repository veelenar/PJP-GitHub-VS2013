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

//zegar

int cl = clock();

// k¹ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
GLint pozycjax = 0.0;
GLint pozycjay = 0.0;

//obrót sciany
int rotateWallDepth = 0;
GLfloat rotateWall = 0.0;
osObrotu os = x;
//GLfloat rotateWallx = 0.0;
//GLfloat rotateWally = 0.0;
//GLfloat rotateWallz = 0.0;

// przesuniêcie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;
float kat = 0;
// wskaŸnik naciœniêcia lewego przycisku myszki

int button_state = GLUT_UP;
bool button = false;
bool pressed = false;
bool zeruj = false;
// po³o¿enie kursora myszki

int button_x, button_y;

extern void UstawKolor(int numerKoloru);

// licznik ramek (FPS)

int frames = 0;

// licznik czasu

long start_time = 0;

// tablica znaków ze wartoœci¹ FPS

char time_string[100];
char button1_string[100];
char button2_string[100];
char button3_string[100];
char button4_string[100];
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
bool timer_state = 0;
void timer(void)
{
	int sekundy, setne = 0;
	int przerwa = 0;
	if (timer_state == true)
	{
		sekundy = clock();
		setne = (sekundy-przerwa) % 1000 / 10;
		sekundy /= 1000;
		sprintf(time_string, "Czas: %2d: %2d: %2d", (sekundy / 60) % 59, sekundy % 60, setne);
	}
	else if (timer_state == false)
	{
		przerwa += clock();
	}
	if (zeruj == true)
	{
		sekundy = clock()-przerwa;
	}

	glutPostRedisplay();
}

int LosujSciane()
{
	int wall = (rand() % (int)(3));
	if (wall != 1) return wall;
	return LosujSciane();
}

osObrotu LosujOs() {
	return (osObrotu)(rand() % (int)3);
}

void LosujObrot() {
	rotateWallDepth = LosujSciane();
	os = LosujOs();

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
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(0.3, 0.3, 0.3, 1.0);

	// czyszczenie bufora koloru i g³êbi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyœci bufory
	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// w³¹czenie testu bufora g³êbokoœci
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

				// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
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

		/*if (os == osObrotu::x)
			os = osObrotu::y;
		else if (os == osObrotu::y)
			os = osObrotu::z;
		else if (os == osObrotu::z)
			os = osObrotu::x;*/

		LosujObrot();
	}

	glLoadIdentity();
	glTranslatef(0, 0, -neaar);
	RysujPrzycisk(-10.0f, 9.0f, 0.0f);
	RysujPrzycisk(10.0f, -5.5f, 0.0f);
	RysujPrzycisk(0.0f, -5.5f, 0.0f);
	RysujPrzycisk(-10.0f, -5.5f, 0.0f);
	glColor3ub(255, 255, 255);

	sprintf(button1_string, "ZERUJ");
	sprintf(button2_string, "WYMIESZAJ");
	sprintf(button3_string, "START");
	sprintf(button4_string, "STOP");
	// narysowanie napisu
	DrawString(-12.5, 9.5, time_string);
	DrawString(-10.87, 8.60, button1_string);
	DrawString(8.8, -6.0, button2_string);
	DrawString(-0.5, -6.0, button4_string);
	DrawString(-10.70, -6.0, button3_string);
	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
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
		// zapamiêtanie stanu prawego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o¿enia kursora myszki
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
			printf("x: %i; y: %i\n", button_x, button_y);
			printf("posx: %i; posy: %i\n", pozycjax, pozycjay);
			if (button_x >= 27 && button_x <= 173 && button_y >= 24 && button_y <= 60){
				/*pressed = !pressed;*/
				zeruj = true;
			}
	/*		if (!pressed)
				glutPostRedisplay();*/

			if (button_x >= 27 && button_x <= 173 && button_y >= 456 && button_y <= 492){
				timer_state = true;
			}
			if (button_x >= 324 && button_x <= 474 && button_y >= 456 && button_y <= 492){
				timer_state = false;
			}
				glutPostRedisplay();

				printf("timer state: %i\n",timer_state);
			}
		}
	}

// obs³uga ruchu kursora myszki

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
			button_x = x;
			button_y = y;
		}
	}
}



int main(int argc, char * argv[])
{
	GenerujKostkê();
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


	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}