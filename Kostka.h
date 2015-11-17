
enum iloscScian {
	jedna,
	dwie,
	trzy
};

struct elementKostki
{
	int kolor[3];
	iloscScian iloscScian;
	int numerElementu;
};


extern elementKostki kostka[3][3][3];

extern void GenerujKostkê();