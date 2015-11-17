#ifndef OPENGL_H
#define OPENGL_H

#define WIN32_LEAN_AND_MEAN
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#include <Windows.h>

class Okno
{
protected:
	HWND uchwytOkna;
	int szerokoscObszaruUzytkownika, 
		wysokoscObszaruUzytkownika;

public:
	LRESULT WndProc(
		HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);
	bool Inicjuj(
		HINSTANCE uchwytAplikacji, 
		POINT polozenieOkna, POINT rozmiarOkna);
	WPARAM Uruchom();
};

class OknoGL : public Okno
{
private:
	HGLRC uchwytRC; //uchwyt kontekstu renderowania
	HDC uchwytDC; //uchwyt prywatnego kontekstu urz¹dzenia GDI

	bool UstalFormatPikseli(HDC uchwytDC) const;
	bool InicjujWGL(HWND uchwytOkna);
	void UsuñWGL();

	void UmieœæInformacjeNaPaskuTytu³u(HWND uchwytOkna);
	void UstawienieSceny(bool rzutowanieIzometryczne = false);
	void RysujScenê();
public:
	OknoGL() : Okno(), uchwytRC(NULL), uchwytDC(NULL) {};
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
} okno;

LRESULT CALLBACK WndProc(
		HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam)
{
	return okno.WndProc(hWnd, message, wParam, lParam);
}

#endif