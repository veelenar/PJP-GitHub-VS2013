
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

//struct kostkaRubika{
//
//	int obrot[3];
//	elementKostki kostka[3][3][3];
//	elementKostki* GetBrick(int x, int y, int z);
//};

extern elementKostki kostka[3][3][3];

extern void GenerujKostkê();
//bool anim;
extern void WymienX(int x, int y, int z);
extern void WymienY(int x, int y, int z);
extern void WymienZ(int x, int y, int z);
extern void ObrocMacierzSciany(osObrotu os, kierunekObrotu kierunek, int numerSciany);