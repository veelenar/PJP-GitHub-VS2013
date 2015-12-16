
enum iloscScian {
	jedna,
	dwie,
	trzy
};

enum osObrotu
{
	x = 0,
	y = 1,
	z = 2
};

enum kierunekObrotu
{
	lewo = 1,
	prawo = 0
};

struct elementKostki
{
	int kolor[3];
	iloscScian iloscScian;
	int numerElementu;
	int obrotx;
	int obroty;
	int obrotz;
};

extern elementKostki kostka[3][3][3];

extern void GenerujKostkê();
extern void ObrocMacierzSciany(osObrotu os, kierunekObrotu kierunek, int numerSciany);
extern void Kostka_Ob_Sciany(osObrotu os, kierunekObrotu kierunek, int numerSciany);