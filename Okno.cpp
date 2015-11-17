#include "Okno.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	POINT polozenieOkna = { 100,100 };
	POINT rozmiarOkna = { 800,600 };
	if (!okno.Inicjuj(hInstance, polozenieOkna, rozmiarOkna))
	{
		MessageBox(NULL, "Inicjacja okna nie powiod³a siê",
			"Aplikacja OpenGL", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}
	else return okno.Uruchom();

	return 0;
}

LRESULT Okno::WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY: //zamykanie okna -> koñczenie aplikacji
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_SIZE: //zmiana rozmiaru okna
		RECT rect;
		GetClientRect(hWnd, &rect);
		szerokoscObszaruUzytkownika = rect.right - rect.left;
		wysokoscObszaruUzytkownika = rect.bottom - rect.top;
		break;
	default: //automatyczne przetwarzanie komunikatów
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0L;
}

bool Okno::Inicjuj(HINSTANCE uchwytAplikacji, POINT polozenieOkna, POINT rozmiarOkna)
{
	char nazwaOkna[] = "Aplikacja OpenGL";

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //styl okna
	wc.lpfnWndProc = (WNDPROC)::WndProc; //procedura okna
	wc.cbClsExtra = 0; //dodatkowe bajty zarezrwowane za klas¹ okna
	wc.cbWndExtra = 0; //dodatkowe bajty zarezerwowane za instancjê okna
	wc.hInstance = uchwytAplikacji; //instancja aplikacji
	wc.hIcon = NULL; //uchwyt ikony
	wc.hIconSm = NULL; //uchwyt ikony
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //uchwyt kursora
	wc.hbrBackground = NULL; //uchwyt pêdzla t³a
	wc.lpszMenuName = NULL; //nazwa menu
	wc.lpszClassName = nazwaOkna; //nazwa klasy okna

	//Rejestracja klasy okna
	if (RegisterClassEx(&wc) == 0) return false;

	//Tworzenie okna
	uchwytOkna = CreateWindow(
		nazwaOkna, //nazwa klasy okna
		nazwaOkna, //nazwa okna
		WS_OVERLAPPEDWINDOW, //styl okna
		polozenieOkna.x, polozenieOkna.y, //po³o¿enie okna (x,y)
		rozmiarOkna.x, rozmiarOkna.y, //rozmiar okna (szerokoœæ, wysokoœæ)
		NULL, //uchwyt okna nadrzêdnego
		NULL, //uchwyt menu
		uchwytAplikacji, //uchwyt instancji aplikacji
		NULL); //parametr komunikatu WM_CREATE informuj¹cego o utworzeniu okna

	if (uchwytOkna == NULL) return false;

	//Pokazanie i aktualizacja okna
	ShowWindow(uchwytOkna, SW_SHOW);
	UpdateWindow(uchwytOkna);

	return true;
}

WPARAM Okno::Uruchom()
{
	//Pêtla g³ówna - obs³uga komunikatów
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//---------------------------------------

bool OknoGL::UstalFormatPikseli(HDC uchwytDC) const
{
	PIXELFORMATDESCRIPTOR opisFormatuPikseli;
	ZeroMemory(&opisFormatuPikseli, sizeof(opisFormatuPikseli));
	opisFormatuPikseli.nVersion = 1;
	opisFormatuPikseli.dwFlags = PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER; //w oknie, podwójne buforowanie
	opisFormatuPikseli.iPixelType = PFD_TYPE_RGBA; //tyo koloru RGB z kana³a alfa
	opisFormatuPikseli.cColorBits = 32; //jakoœæ kolorów, 4 bajty (po bajcie na ka¿dy kana³)
	opisFormatuPikseli.cDepthBits = 32; //g³êbokoœæ bufora g³êbi (z-buffer)
	opisFormatuPikseli.iLayerType = PFD_MAIN_PLANE;
	int formatPikseli = ChoosePixelFormat(uchwytDC, &opisFormatuPikseli);
	if (formatPikseli == 0) return false;
	if (!SetPixelFormat(uchwytDC, formatPikseli, &opisFormatuPikseli)) return false;
	return true;
}

bool OknoGL::InicjujWGL(HWND uchwytOkna)
{
	uchwytDC = ::GetDC(uchwytOkna);
	if (!UstalFormatPikseli(uchwytDC)) return false;

	uchwytRC = wglCreateContext(uchwytDC);
	if (uchwytRC == NULL) return false;
	if (!wglMakeCurrent(uchwytDC, uchwytRC)) return false;
	return true;
}

void OknoGL::UsuñWGL()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(uchwytRC);
	::ReleaseDC(uchwytOkna, uchwytDC);
}

LRESULT OknoGL::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long wynik = Okno::WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_CREATE: //Utworzenie okna
		//zmienna uchwytOkna nie jest jeszcze zainicjowana
		if (!InicjujWGL(hWnd))
		{
			MessageBox(NULL, "Pobranie kontekstu renderowania nie powiod³o siê", "Aplikacja OpenGL", MB_OK | MB_ICONERROR);
			return EXIT_FAILURE;
		}
		UmieœæInformacjeNaPaskuTytu³u(hWnd);
		UstawienieSceny();
		break;
	case WM_DESTROY: //Zamkniêcie okna
		UsuñWGL();
		break;
	case WM_SIZE: //Zmiana rozmiaru okna
		UstawienieSceny();
		break;
	case WM_PAINT: //Okno wymaga odœwie¿enia
		RysujScenê();
		ValidateRect(hWnd, NULL);
		break;
	}

	return wynik;
}

void OknoGL::UmieœæInformacjeNaPaskuTytu³u(HWND uchwytOkna)
{
	char bufor[256];
	GetWindowText(uchwytOkna, bufor, 256);
	const GLubyte* wersja = glGetString(GL_VERSION);
	strcat_s(bufor, " | OpenGL "); strcat_s(bufor, (char*)wersja);
	const GLubyte* dostawca = glGetString(GL_VENDOR);
	strcat_s(bufor, " | "); strcat_s(bufor, (char*)dostawca);
	const GLubyte* kartaGraficzna = glGetString(GL_RENDERER);
	strcat_s(bufor, " | "); strcat_s(bufor, (char*)kartaGraficzna);
	SetWindowText(uchwytOkna, bufor);
}

void OknoGL::UstawienieSceny(bool rzutowanieIzometryczne) //wartoœæ domyœlna = false
{
	glViewport(0, 0, szerokoscObszaruUzytkownika, wysokoscObszaruUzytkownika); //okno OpenGL = wnêtrze formy (domyœlnie)

	//ustawienie puntu projekcji
	glMatrixMode(GL_PROJECTION); //prze³¹czenie na macierz rzutowania
	glLoadIdentity();
	float wsp = wysokoscObszaruUzytkownika / (float)szerokoscObszaruUzytkownika;
	if (!rzutowanieIzometryczne)
		//left, right, bottom, top, znear, zfar (clipping)
		//mno¿enie macierzy rzutowania przez macierz perspektywy - ustalanie frustum
		glFrustum(-1.0f, 1.0f, wsp*-1.0f, wsp*1.0f, 1.0f, 10.0f);
	else
		glOrtho(-1.0f, 1.0f, wsp*-1.0f, wsp*1.0f, 1.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST); //z-buffer aktywny = ukrywanie przes³oniêtych powierzchni
}

void RysujSzescian(float x, float y, float z, bool koloruj)
{
	float da = 0.3;
	float da_2 = da;


	if (koloruj) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);  // zielony

	glBegin(GL_POLYGON);
	//tylna
	glVertex3f(x + da_2, y - da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glVertex3f(x - da_2, y - da_2, z - da_2);
	glEnd();

	if (koloruj) glColor4f(0.0f, 0.0f, 1.0f, 1.0f);  // niebieski

	glBegin(GL_POLYGON);
	//przednia
	glVertex3f(x + da_2, y - da_2, z + da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z + da_2);
	glEnd();

	if (koloruj) glColor4f(1.0f, 0.0f, 0.0f, 1.0f);  // czerwony

	glBegin(GL_POLYGON);
	//prawa
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x + da_2, y - da_2, z + da_2);
	glVertex3f(x + da_2, y - da_2, z - da_2);
	glEnd();

	if (koloruj) glColor3ub(255, 127, 39);	//pomaranczowy

	glBegin(GL_POLYGON);
	//lewa
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z - da_2);
	glEnd();

	if (koloruj) glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //bia³y

	glBegin(GL_POLYGON);
	//góra
	glVertex3f(x + da_2, y + da_2, z - da_2);
	glVertex3f(x + da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z + da_2);
	glVertex3f(x - da_2, y + da_2, z - da_2);
	glEnd();

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  // ¿ó³ty

	glBegin(GL_POLYGON);
	//dó³
	glVertex3f(x + da_2, y - da_2, z - da_2);
	glVertex3f(x + da_2, y - da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z + da_2);
	glVertex3f(x - da_2, y - da_2, z - da_2);
	glEnd();
}



void OknoGL::RysujScenê()
{
	const float x0 = 1.0f;
	const float y0 = 1.0f;
	const float z0 = 1.0f;

	//Przygotowanie buforów
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyœci bufory
	glLoadIdentity(); // macierz model-widok = macierz jednostkowa
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(25, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glRotatef(-50, 0, 1, 0);
	//¯ó³ty kolor werteksów
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);


	//sciana 1
	RysujSzescian(0.0, 0.0, 0.0, true);
	//RysujSzescian(0.7, 0.0, 0.0, true); // nie potrzeba - jest w srodku
	RysujSzescian(1.4, 0.0, 0.0, true);
	RysujSzescian(0.0, 0.7, 0.0, true);
	RysujSzescian(0.7, 0.7, 0.0, true);
	RysujSzescian(1.4, 0.7, 0.0, true);
	RysujSzescian(0.0, -0.7, 0.0, true);
	RysujSzescian(0.7, -0.7, 0.0, true);
	RysujSzescian(1.4, -0.7, 0.0, true);

	//sciana 2
	RysujSzescian(0.0, 0.0, 0.7, true);
	RysujSzescian(0.7, 0.0, 0.7, true);
	RysujSzescian(1.4, 0.0, 0.7, true);
	RysujSzescian(0.0, 0.7, 0.7, true);
	RysujSzescian(0.7, 0.7, 0.7, true);
	RysujSzescian(1.4, 0.7, 0.7, true);
	RysujSzescian(0.0, -0.7, 0.7, true);
	RysujSzescian(0.7, -0.7, 0.7, true);
	RysujSzescian(1.4, -0.7, 0.7, true);

	//sciana 3
	RysujSzescian(0.0, 0.0, -0.7, true);
	RysujSzescian(0.7, 0.0, -0.7, true);
	RysujSzescian(1.4, 0.0, -0.7, true);
	RysujSzescian(0.0, 0.7, -0.7, true);
	RysujSzescian(0.7, 0.7, -0.7, true);
	RysujSzescian(1.4, 0.7, -0.7, true);
	RysujSzescian(0.0, -0.7, -0.7, true);
	RysujSzescian(0.7, -0.7, -0.7, true);
	RysujSzescian(1.4, -0.7, -0.7, true);


	//Z bufora na ekran
	SwapBuffers(uchwytDC);
}