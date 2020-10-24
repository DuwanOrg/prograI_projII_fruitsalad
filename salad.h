#include <iostream>
#include <graphics.h>
using namespace std;

class Area {
private:
	int id;
protected:
	int x;
	int y;
	int ancho;
	int alto;
	int mx,my;
public:
	Area();
	Area(int x, int y, int ancho, int alto);
	bool mouseClick(int mx, int my);
};

class Boton{
private:
	char* texto;
public:
	Boton(char* ruta, char* texto,int x, int y, int ancho, int alto):ImagenDeArchivo(ruta,ancho,alto){
		this->texto = texto;
		this->x = x;
		this->y = y;
	}
	void dibujar();
};


class Carta{
	private:
		
	public:
		Carta(int r1, int r2, int r3, int v1, int v2, int v3);
	
};

class Regla: public Carta{
	private:
		int r1Orig;
		int r2Orig;
		int r3Orig;
		int r1Nuev;
		int r2Nuev;
		int r3Nuev;
		int verdura1;
		int verdura2;
		int verdura3;
		
	public:
		Regla(int v1, int v2, int v3);
		void transformarRegla();
		int aplicartransformacion(int val);
};
