#include <iostream>
#include <graphics.h>
#include <fstream>

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

//class Boton{
//private:
//	char* texto;
//public:
//	Boton(char* ruta, char* texto,int x, int y, int ancho, int alto):ImagenDeArchivo(ruta,ancho,alto){
//		this->texto = texto;
//		this->x = x;
//		this->y = y;
//	}
//	void dibujar();
//};



class Regla{
	private:
		int *tipos;
		int tiposContador;
		int puntosOriginal;
		int puntosRandom;
		
	public:
		Regla(int puntosOriginal, int *tipos);
		int* gettipos ();
		int getTipoContador (int tipo);
		int gettiposContador ();
		int getpuntosOriginal ();
		int getpuntosRandom ();
};

class Carta{
	private:
		int reglasContador;
		Regla *reglas;
	public:
		int tipo;
		Carta (int tipo, Regla *reglas);
		Regla getRegla (int indice);
		int getReglasContador ();
		Regla *getReglas ();
		Carta ();
};

class CartaNodo
{
	public:
		CartaNodo ();
		Carta local;
		CartaNodo * siguiente;
		CartaNodo * anterior;
		
};

class CartaLista
{
	private:
		CartaNodo * primeraCarta;
		CartaNodo * ultimaCarta;
		int CartaContador;
		CartaNodo* getIndice (int indice);
	public:
		void insertarCarta (Carta entrada);
		void insertarListaCarta (CartaLista entrada);
		void insertarCarta (Carta entrada, int indice);
		void insertarListaCarta (CartaLista entrada, int indice);
		CartaLista extraerRango (int indice, int cantidad);
		CartaNodo* extraerUltimoNodo ();
		CartaNodo* extraerPrimerNodo ();
		Carta extraerUltimaCarta ();
		Carta extraerPrimeraCarta ();
		Carta extraerCarta (int indice);
		CartaNodo* extraerNodo (int indice);
		Carta * getCartas ();
		int getCartaContador ();
		int getCartaTipoContador(int tipo);
		CartaLista ();
};

class Mazo
{
	private:
		int maxMercado;
	public:
		Mazo (int maxMercado);
		Mazo ();
		CartaLista mercado; //Lista
		CartaLista pila; //Lista
		int getPuntaje ();
		void insertarCartaMercado (Carta nueva);
		void insertarCartaPila (Carta nueva);
		void refillMercado ();
};

class MazoCentral
{
	public:
		Mazo * columna;
		int columnaContador;
		MazoCentral (int columnas);
		Mazo getColunma (int indice);
};

class Jugador
{
	public:
		string nombre;
		string turnoContador;
		Mazo mano;
		Jugador (string Nombre);
		
};

class ConstructorMazo 
{
	public:
		CartaLista cargarCartasJson ();
		MazoCentral cargarMarzoCentral ();
};

class GameController
{
	public:
		MazoCentral mesa;
		Jugador * jugadores;
		int JugadoresCotador;
		int TurnoJugadorIndice;
		bool PilaBloqueada;
		int indiceJugadorComputadora
		void nuevoJugador (string name);
		void iniJuego ();
		void crearCartas ();
		void siguiete ();
		void tomarCartaPila (int jugador, int columna);
		void tomarCartaMercado (int jugador, int columna, int indiceMercado);
};
