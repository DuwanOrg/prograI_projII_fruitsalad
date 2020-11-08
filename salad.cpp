#include "salad.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <cmath>
#include <iostream>

/// Programacion de la REGLA

Regla::Regla(int puntosOriginal, int *tipos)
{
	this->puntosOriginal = puntosOriginal;
	this->tipos = tipos;
	this->tiposContador = sizeof(this->tipos);
	bool puntosNegativos = false;
	if (this->puntosOriginal>0)
	{
		puntosNegativos = true;
	}
	/// Calculo de randoms
	this->puntosRandom = abs(this->puntosOriginal);
	int randomFinal =0;
	if (this->puntosRandom =1)
	{
		srand(time(0));
		randomFinal = 1+(rand()%2);
	}
	if (this->puntosRandom >1 and this->puntosRandom <6)
	{
		srand(time(0));
		if ((rand()%2)==1)
		{
			randomFinal =this->puntosRandom+1;
		}
		else
		{
			randomFinal =this->puntosRandom-1;
		}
	}
	if (this->puntosRandom>5)
	{
		srand(time(0));
		if ((rand()%2)==1)
		{
			randomFinal = this->puntosRandom+2;
		}
		else
		{
			randomFinal = this->puntosRandom-2;
		}
	}
	this->puntosRandom = randomFinal;
	/// Calculo de randoms
	if (puntosNegativos)
	{
		this->puntosRandom = (this->puntosRandom * -1);
	}
}

int* Regla::gettipos()
{
	return this->tipos;
}

Regla::getpuntosOriginal()
{
	return this->puntosOriginal;
}

Regla::gettiposContador()
{
	return this->tiposContador;
}

Regla::getpuntosRandom()
{
	return this->puntosRandom;
}

int Regla::getTipoContador(int tipo)
{
	int contador=0;
	for (int i=0; i< this->tiposContador; i ++)
	{
		if (this->tipos[i]==tipo)
		{
			contador++;
		}
	}
	return contador;
}

Regla::Regla()
{
	this->puntosOriginal = 0;
	this->puntosRandom = 0;
	this->tipos = new int[0];
	this->tiposContador = 0;
}

/// Programacion de la CARTA


CartaNodo::CartaNodo ()
{
	
}

Carta::Carta()
{
	this->reglas= NULL;
	this->reglasContador=0;
	this->tipo=0;
}

Carta::Carta (int tipo, Regla *reglas)
{
	this->tipo = tipo;
	this->reglas = reglas;
	this->reglasContador = sizeof(this->reglas);
}
Regla* Carta::getReglas ()
{
	return this->reglas;
}
Regla Carta::getRegla (int indice)
{
	return this->reglas[indice];
}
Carta::getReglasContador ()
{
	return this->reglasContador;
}


///// Programacion de la carta lista

CartaLista::CartaLista()
{
	this->CartaContador =0;
	this->primeraCarta = NULL;
	this->ultimaCarta = NULL;
}

int CartaLista::getCartaContador ()
{
	return this->CartaContador;
}

void CartaLista::insertarCarta (Carta entrada)
{
	CartaNodo *temp = new CartaNodo();
	temp->local = entrada;
	if (this->ultimaCarta!=NULL)
	{
		temp->siguiente = NULL;
		CartaNodo *ultima = this->ultimaCarta;
		temp->anterior=ultima;
		ultima->siguiente=temp;
		this->ultimaCarta = temp;
	}
	else
	{
		this->primeraCarta = temp;
		this->ultimaCarta = temp;
	}
	this->CartaContador = this->CartaContador+1;
}

void CartaLista::insertarListaCarta (CartaLista entrada)
{
	CartaNodo *temp = entrada.extraerPrimerNodo();
	while (temp!=NULL)
	{
		this->insertarCarta(temp->local);
		temp=entrada.extraerPrimerNodo();
	}
}
CartaNodo* CartaLista::getIndice (int indice)
{
	if (indice<0)
	{
		indice=0;
	}
	if (indice >=this->CartaContador)
	{
		return NULL;
	}
	CartaNodo* resultado = this->primeraCarta;
	for (int i =0; i<indice; indice++)
	{
		resultado = resultado->siguiente;
	}
	return resultado;
}
void CartaLista::insertarCarta (Carta entrada, int indice)
{

	CartaNodo *temp = new CartaNodo();
	temp->local = entrada;
	CartaNodo* nodosiguiente = this->getIndice(indice);
	if (nodosiguiente!=NULL)
	{
		CartaNodo* nodoanterior = nodosiguiente->anterior;
		nodosiguiente->anterior = temp;
		temp->siguiente=nodosiguiente;
		if(nodoanterior!=NULL)
		{
			nodoanterior->siguiente=temp;
			temp->anterior=nodoanterior;
		}
		else
		{
			this->primeraCarta=temp;
		}
		this->CartaContador = this->CartaContador+1;
	}
	else
	{
		this->insertarCarta(entrada);
	}

}
void CartaLista::insertarListaCarta (CartaLista entrada, int indice)
{
	int tempindice = indice;
	CartaNodo *temp = entrada.extraerPrimerNodo();
	while (temp!=NULL)
	{
		this->insertarCarta(temp->local, tempindice);
		temp=entrada.extraerPrimerNodo();
		tempindice++;
	}
}
CartaNodo* CartaLista::extraerUltimoNodo ()
{
	CartaNodo * result = this->ultimaCarta;
	CartaNodo * nodo = result->anterior;
	nodo->siguiente = NULL;
	this->ultimaCarta = nodo;
	this->CartaContador = this->CartaContador -1;
	return result;
}
CartaNodo* CartaLista::extraerPrimerNodo ()
{
	CartaNodo * result = this->primeraCarta;
	CartaNodo * nodo = result->siguiente;
	nodo->anterior = NULL;
	this->primeraCarta = nodo;
	this->CartaContador = this->CartaContador -1;
	return result;
}
Carta CartaLista::extraerUltimaCarta ()
{
	CartaNodo * nodo = this->extraerUltimoNodo();
	return nodo->local;
}
Carta CartaLista::extraerPrimeraCarta ()
{
	CartaNodo * nodo = this->extraerPrimerNodo();
	return nodo->local;
}
Carta CartaLista::extraerCarta (int indice)
{
	CartaNodo * nodo = this->extraerNodo(indice);
	return nodo->local;
}
CartaNodo* CartaLista::extraerNodo (int indice)
{
	if (indice<=0)
	{
		return this->extraerPrimerNodo();
	}
	if (indice >=this->CartaContador)
	{
		return NULL;
	}
	if (indice = (this->CartaContador-1))
	{
		return this->extraerUltimoNodo();
	}
	CartaNodo* resultado = this->getIndice(indice);
	CartaNodo* siguiente = resultado->siguiente;
	CartaNodo* anterior = resultado->anterior;
	siguiente->anterior=anterior;
	anterior->siguiente=siguiente;
	this->CartaContador = this->CartaContador -1;
	return resultado;
}
CartaLista CartaLista::extraerRango (int indice, int cantidad)
{
	CartaLista result = CartaLista();
	CartaNodo * nodo = NULL;
	for(int i =0; i<cantidad; i++)
	{
		nodo=this->extraerNodo(indice);
		if (nodo==NULL)
		{
			return result;
		}
		result.insertarCarta(nodo->local);
	}
	return result;
}

Carta* CartaLista::getCartas ()
{
	int total = this->getCartaContador();
	Carta* resultado = new Carta[total];
	CartaNodo *nodo = this->primeraCarta;
	int contador = 0;
	while (nodo!=NULL)
	{
		resultado[contador]=nodo->local;
		nodo=nodo->siguiente;
		contador++;
	}
	return resultado;
}

int CartaLista::getCartaTipoContador (int tipo)
{
	int contador = 0;
	CartaNodo* nodo = this->primeraCarta;
	while (nodo!=NULL)
	{
		if (nodo->local.tipo == tipo)
		{
			contador ++;
		}
	}
}

//// Programacion del mazo

Mazo::Mazo (int maxMercado)
{
	this->maxMercado=maxMercado;
	this->mercado = CartaLista();
	this->pila=CartaLista();
}

Mazo::Mazo ()
{
	this->maxMercado=36;
	this->mercado = CartaLista();
	this->pila=CartaLista();
}

int Mazo::getPuntaje ()
{
	int puntaje = 0;
	Carta* cartaEnPila = this->pila.getCartas();
	for (int i =0; i < this->pila.getCartaContador(); i++)
	{
		for (int j  = 0; j< cartaEnPila[i].getReglasContador(); j ++)
		{
			int aplicarRegla = 0;
			for (int y = 0; y < cartaEnPila[i].getRegla(j).gettiposContador(); y++)
			{
				int tipoContadorEnRegla = cartaEnPila[i].getRegla(j).getTipoContador(cartaEnPila[i].getRegla(j).gettipos()[y]);
				int tipoContadorenMercado = this->mercado.getCartaTipoContador(cartaEnPila[i].getRegla(j).gettipos()[y]);
				int tempAplicarRegla = tipoContadorenMercado/tipoContadorEnRegla;
				if (tempAplicarRegla>aplicarRegla)
				{
					aplicarRegla = tempAplicarRegla;
				}
			}
			for (int aplicar = 0; aplicar<aplicarRegla; aplicar++)
			{
				puntaje = puntaje+ cartaEnPila[i].getRegla(j).getpuntosRandom();
			}
		}
	}
	return puntaje;
}

void Mazo::insertarCartaMercado (Carta nueva)
{
	this->mercado.insertarCarta(nueva);
}

void Mazo::insertarCartaPila (Carta nueva)
{
	this->pila.insertarCarta(nueva);
}

void Mazo::refillMercado ()
{
	while (this->mercado.getCartaContador()<this->maxMercado)
	{
		this->mercado.insertarCarta(this->pila.extraerUltimaCarta());
	}
}

///Programacion del MazoCentral

MazoCentral::MazoCentral (int columnas)
{
	this->columnaContador = columnas;
	this->columna = new Mazo[columnas];
}

MazoCentral::MazoCentral ()
{
	this->columnaContador = 3;
	this->columna = new Mazo[3];
}

Mazo MazoCentral::getColunma (int indice)
{
	return this->columna[indice];
}


/// Programacion del Jugador
Jugador::Jugador(string Nombre)
{
	this->nombre = Nombre;
	this->mano = Mazo();
	this->turnoContador = 0;
}

Jugador::Jugador()
{
	this->nombre = "Default";
	this->mano = Mazo();
	this->turnoContador = 0;
}

/// Programacion del constructor de mazoz

CartaLista ConstructorMazo::cargarCartasJson()
{
	CartaLista resultado;
	resultado = CartaLista();
	
	/// Carta 1
	int * regla0tipos = new int[1];
	regla0tipos[0] = 1;
	Regla * reglas0 = new Regla[1];
	reglas0[0] = Regla(2, regla0tipos);
	Carta carta0 = Carta(0, reglas0);
	resultado.insertarCarta(carta0);
	
	/// Carta 2
	int * regla1_1tipos = new int[1];
	regla1_1tipos[0] = 1;
	int * regla1_2tipos = new int[1];
	regla1_2tipos[0] = 2;
	int * regla1_3tipos = new int[1];
	regla1_3tipos[0] = 0;
	Regla * reglas1 = new Regla[3];
	reglas1[0] = Regla(2, regla1_1tipos);
	reglas1[1] = Regla(1, regla1_2tipos);
	reglas1[2] = Regla(-2, regla1_3tipos);
	Carta carta1 = Carta(0, reglas1);
	resultado.insertarCarta(carta1);
		
	return resultado;
}

MazoCentral ConstructorMazo::cargarMarzoCentral()
{
	int columnas = 3;
	MazoCentral resultado = MazoCentral(columnas);
	
	CartaLista cartas = this->cargarCartasJson();
	int columna = 0;
	int cartasContador = cartas.getCartaContador();
	for (int i = 0 ; i < cartasContador; i++)
	{
		resultado.columna[columna].insertarCartaPila(cartas.extraerPrimeraCarta());
		columna++;
		if (columna >=columnas)
		{
			columnas = 0;	
		}
	}
	return resultado;
}


GameController::GameController ()
{
	this->mesa = MazoCentral(3);
	this->jugadores = new Jugador[2];
	this->JugadoresCotador = 2;
	int TurnoJugadorIndice = 0;
	bool PilaBloqueada = false;
	int indiceJugadorComputadora = 1;
}


void GameController::iniJuego (string nombre)
{
	ConstructorMazo constructor = ConstructorMazo();
	this->mesa = constructor.cargarMarzoCentral();
	this->jugadores[0] = Jugador(nombre);
	this->jugadores[1] = Jugador("PC");
	
}

void GameController::siguiete ()
{
	for (int i = 0; i < this->mesa.columnaContador; i++)
	{
		this->mesa.getColunma(i).refillMercado();
	}
}

void GameController::tomarCartaPila (int jugador, int columna)
{
	this->jugadores[jugador].mano.insertarCartaPila(this->mesa.columna[columna].pila.extraerUltimaCarta());
}

void GameController::tomarCartaMercado (int jugador, int columna, int indiceMercado)
{
	this->jugadores[jugador].mano.insertarCartaMercado(this->mesa.columna[columna].pila.extraerCarta(indiceMercado));
}


