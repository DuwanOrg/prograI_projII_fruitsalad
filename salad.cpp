#include "salad.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unistd.h>


/// Programacion de la REGLA

Regla::Regla(int puntosOriginal, int *tipos, int tiposContador)
{
	this->puntosOriginal = puntosOriginal;
	this->tipos = tipos;
	this->tiposContador = tiposContador;
	bool puntosNegativos = false;
	if (this->puntosOriginal<0)
	{
		puntosNegativos = true;
	}
	/// Calculo de randoms
	this->puntosRandom = abs(this->puntosOriginal);
	int randomFinal =0;
	if (this->puntosRandom ==1)
	{
		srand(time(0)+puntosOriginal+tiposContador);
		randomFinal = 1+(rand()%2);
	}
	if (this->puntosRandom >1 and this->puntosRandom <6)
	{		
		srand(time(0)+puntosOriginal+tiposContador);
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
		srand(time(0)+puntosOriginal+tiposContador);
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
	this->siguiente = NULL;
	this->anterior = NULL;
}

Carta::Carta()
{
	this->reglas= NULL;
	this->reglasContador=0;
	this->tipo=0;
}

Carta::Carta (int tipo, Regla *reglas, int reglascontador)
{
	this->tipo = tipo;
	this->reglas = reglas;
	this->reglasContador = reglascontador;
}
Regla* Carta::getReglas ()
{
	return this->reglas;
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

CartaNodo* CartaLista::getIndice (int indice)
{
	int tempIndice = indice;
	if (tempIndice<0)
	{
		tempIndice=0;
	}
	if (tempIndice >=this->CartaContador)
	{
		return NULL;
	}
	CartaNodo* resultado = this->primeraCarta;
	for (int i =0; i<tempIndice; i++)
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

void CartaLista::insertarListaCarta (CartaLista entrada)
{
	CartaNodo *temp = entrada.extraerPrimerNodo();
	while (temp!=NULL)
	{
		this->insertarCarta(temp->local);
		temp=entrada.extraerPrimerNodo();
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
	if (result!= NULL)
	{
		CartaNodo * nodo = result->anterior;
		if (nodo != NULL)
		{
			nodo->siguiente = NULL;	
		}
		else
		{
			this->primeraCarta = NULL;
		}
		this->ultimaCarta = nodo;
		this->CartaContador = this->CartaContador -1;
	}else
	{
		this->primeraCarta = NULL;
	}
	return result;
}
CartaNodo* CartaLista::extraerPrimerNodo ()
{
	CartaNodo * result = this->primeraCarta;
	if (result!=NULL)
	{
		CartaNodo * nodo = result->siguiente;
		if (nodo!= NULL)
		{
			nodo->anterior = NULL;
			this->primeraCarta = nodo;
		}
		else
		{
			this->primeraCarta = NULL;
			this->ultimaCarta = NULL;
		}
	}
	else
	{
		this->ultimaCarta = NULL;
	}
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
	if (indice == (this->CartaContador-1))
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
		//cout << "Todo bien";
		if (nodo->local.tipo == tipo)
		{
			contador ++;
		}
		nodo = nodo->siguiente;
	}
	return contador;
}

Carta CartaLista::MostrarUltima ()
{
	CartaNodo* ultima = this->ultimaCarta;
	return ultima->local;
}

void CartaLista::reordenar ()
{
	srand (time(NULL) );
	int shuffles = rand() % 20 + 10;
	
	for (int shuffleCount = 0; shuffleCount<shuffles; shuffleCount++)
	{
		srand (time(NULL) + shuffleCount);
		int shuffleCardsCount = (rand() % (this->getCartaContador()-2))+ 2;
		CartaLista bloque = this->extraerRango(0, shuffleCardsCount);
		srand (time(NULL) + shuffleCount);
		int index2Insert = rand() % (this->getCartaContador());
		this->insertarListaCarta(bloque, index2Insert);
		//cout<< "Estado del objeto: cartas.contador:" + Herramienta::convertToString(this->getCartaContador()) +" Bloque:"+Herramienta::convertToString(shuffleCardsCount)+ " Indice:"+Herramienta::convertToString(index2Insert)+" \n";
		usleep(10);
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
			for (int y = 0; y < cartaEnPila[i].getReglas()[j].gettiposContador(); y++)
			{
				int tipoContadorEnRegla = cartaEnPila[i].getReglas()[j].getTipoContador(cartaEnPila[i].getReglas()[j].gettipos()[y]);
				int tipoContadorenMercado = this->mercado.getCartaTipoContador(cartaEnPila[i].getReglas()[j].gettipos()[y]);
				int tempAplicarRegla = tipoContadorenMercado/tipoContadorEnRegla;
				if (tempAplicarRegla>aplicarRegla)
				{
					aplicarRegla = tempAplicarRegla;
				}
			}
			for (int aplicar = 0; aplicar<aplicarRegla; aplicar++)
			{
				puntaje = puntaje+ cartaEnPila[i].getReglas()[j].getpuntosRandom();
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
	//cout<<"Refill mercado on action: "+Herramienta::convertToString(this->mercado.getCartaContador())+"/"+Herramienta::convertToString(this->maxMercado)+" Pila:"+Herramienta::convertToString(this->pila.getCartaContador())+"\n";
	while (this->mercado.getCartaContador()<this->maxMercado)
	{
		this->mercado.insertarCarta(this->pila.extraerUltimaCarta());
	}
	//cout<<"Refill mercado ejecutado: " +Herramienta::convertToString(this->mercado.getCartaContador())+ " Pila:"+Herramienta::convertToString(this->pila.getCartaContador())+"\n";
}

///Programacion del MazoCentral

MazoCentral::MazoCentral (int columnas)
{
	this->columnaContador = columnas;
	this->columna = new Mazo[columnas];
	for (int i = 0 ; i < columnas; i++)
	{
		this->columna[i] = Mazo(3);
	}
}

MazoCentral::MazoCentral ()
{
	this->columnaContador = 3;
	this->columna = new Mazo[3];
	for (int i = 0 ; i < 3; i++)
	{
		this->columna[i] = Mazo(3);
	}
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
	reglas0[0] = Regla(2, regla0tipos, 1);
	Carta carta0 = Carta(0, reglas0, 1);
	resultado.insertarCarta(carta0);
	
	/// Carta 2
	int * regla1_1tipos = new int[1];
	regla1_1tipos[0] = 1;
	int * regla1_2tipos = new int[1];
	regla1_2tipos[0] = 2;
	int * regla1_3tipos = new int[1];
	regla1_3tipos[0] = 0;
	Regla * reglas1 = new Regla[3];
	reglas1[0] = Regla(2, regla1_1tipos, 1);
	reglas1[1] = Regla(1, regla1_2tipos, 1);
	reglas1[2] = Regla(-2, regla1_3tipos, 1);
	Carta carta1 = Carta(0, reglas1, 3);
	resultado.insertarCarta(carta1);
	
		/// Carta 3
	int * regla2_1tipos = new int[1];
	regla2_1tipos[0] = 1;
	int * regla2_2tipos = new int[1];
	regla2_2tipos[0] = 3;
	int * regla2_3tipos = new int[1];
	regla2_3tipos[0] = 2;
	Regla * reglas2 = new Regla[3];
	reglas2[0] = Regla(2, regla2_1tipos, 1);
	reglas2[1] = Regla(2, regla2_2tipos, 1);
	reglas2[2] = Regla(-4, regla2_3tipos, 1);
	Carta carta2 = Carta(0, reglas2, 3);
	resultado.insertarCarta(carta2);
	
	//carta 4
	int * regla3_1tipos = new int[1];
	regla3_1tipos[0] = 1;
	int * regla3_2tipos = new int[1];
	regla3_2tipos[0] = 2;
	int * regla3_3tipos = new int[1];
	regla3_3tipos[0] = 0;
	Regla * reglas3 = new Regla[3];
	reglas3[0] = Regla(3, regla3_1tipos, 1);
	reglas3[1] = Regla(-1, regla3_2tipos, 1);
	reglas3[2] = Regla(-1, regla3_3tipos, 1);
	Carta carta3 = Carta(0, reglas3, 3);
	resultado.insertarCarta(carta3);
	
	//carta 5
	int * regla4_1tipos = new int[1];
	regla4_1tipos[0] = 1;
	int * regla4_2tipos = new int[1];
	regla4_2tipos[0] = 4;
	int * regla4_3tipos = new int[1];
	regla4_3tipos[0] = 5;
	Regla * reglas4 = new Regla[3];
	reglas4[0] = Regla(4, regla4_1tipos, 1);
	reglas4[1] = Regla(-2, regla4_2tipos, 1);
	reglas4[2] = Regla(-2, regla4_3tipos, 1);
	Carta carta4 = Carta(0, reglas4, 3);
	resultado.insertarCarta(carta4);
	
	//carta 6
	int * regla5_1tipos = new int[1];
	regla5_1tipos[0] = 1;
	int * regla5_2tipos = new int[1];
	regla5_2tipos[0] = 3;
	Regla * reglas5 = new Regla[2];
	reglas5[0] = Regla(3, regla5_1tipos, 1);
	reglas5[1] = Regla(-2, regla5_2tipos, 1);
	Carta carta5 = Carta(0, reglas5, 2);
	resultado.insertarCarta(carta5);
	
	//cartas 7
	int * regla6_1tipos = new int[1];
	regla6_1tipos[0] = 1;
	int * regla6_2tipos = new int[1];
	regla6_2tipos[0] = 4;
	Regla * reglas6 = new Regla[2];
	reglas6[0] = Regla(1, regla6_1tipos, 1);
	reglas6[1] = Regla(1, regla6_2tipos, 1);
	Carta carta6 = Carta(0, reglas6, 2);
	resultado.insertarCarta(carta6);
	
//	carta 8
	int * regla7_1tipos = new int[1];
	regla7_1tipos[0] = 1;
	int * regla7_2tipos = new int[1];
	regla7_2tipos[0] = 2;
	Regla * reglas7 = new Regla[2];
	reglas7[0] = Regla(1, regla7_1tipos, 1);
	reglas7[1] = Regla(1, regla7_2tipos, 1);
	Carta carta7 = Carta(0, reglas7, 2);
	resultado.insertarCarta(carta7);

	///////////////////////////////reglas que se suman//////////////////////
	
	//carta 9
	int * regla8_1tipos = new int[1];
	regla8_1tipos[0] = 1;
	int * regla8_2tipos = new int[1];
	regla8_2tipos[0] = 1;
	Regla * reglas8 = new Regla[1];
	reglas8[0] = Regla(5, regla8_1tipos, 1);
	Carta carta8 = Carta(0, reglas8, 1);
	resultado.insertarCarta(carta8);
	
	// carta 10
	int * regla9_1tipos = new int[1];
	regla9_1tipos[0] = 4;
	int * regla9_2tipos = new int[1];
	regla9_2tipos[0] = 3;
	Regla * reglas9 = new Regla[1];
	reglas9[0] = Regla(5, regla9_1tipos, 1);
	Carta carta9 = Carta(0, reglas9, 1);
	resultado.insertarCarta(carta9);
	
	//carta 11
	int * regla10_1tipos = new int[1];
	regla10_1tipos[0] = 5;
	int * regla10_2tipos = new int[1];
	regla10_2tipos[0] = 2;
	Regla * reglas10 = new Regla[1];
	reglas10[0] = Regla(5, regla10_1tipos, 1);
	Carta carta10 = Carta(0, reglas10, 1);
	resultado.insertarCarta(carta10);
	
	//carta 12
	int * regla11_1tipos = new int[1];
	regla11_1tipos[0] = 1;
	int * regla11_2tipos = new int[1];
	regla11_2tipos[0] = 1;
	int * regla11_3tipos = new int[1];
	regla11_3tipos[0] = 1;
	Regla * reglas11 = new Regla[1];
	reglas11[0] = Regla(8, regla11_1tipos, 1);
	Carta carta11 = Carta(0, reglas11, 1);
	resultado.insertarCarta(carta11);
	
	//carta 13
	int * regla12_1tipos = new int[1];
	regla12_1tipos[0] = 0;
	int * regla12_2tipos = new int[1];
	regla12_2tipos[0] = 1;
	int * regla12_3tipos = new int[1];
	regla12_3tipos[0] = 5;
	Regla * reglas12 = new Regla[1];
	reglas12[0] = Regla(8, regla12_1tipos, 1);
	Carta carta12 = Carta(0, reglas12, 1);
	resultado.insertarCarta(carta12);
	
	//carta 14
	int * regla13_1tipos = new int[1];
	regla13_1tipos[0] = 4;
	int * regla13_2tipos = new int[1];
	regla13_2tipos[0] = 1;
	int * regla13_3tipos = new int[1];
	regla13_3tipos[0] = 3;
	Regla * reglas13 = new Regla[1];
	reglas13[0] = Regla(8, regla13_1tipos, 1);
	Carta carta13 = Carta(0, reglas13, 1);
	resultado.insertarCarta(carta13);
	
	/////////////////////terminan cartas que se suman/////////////////////////
	
	// carta 15
	int * regla14_1tipos = new int[1];
	regla14_1tipos[0] = 0;
	Regla * reglas14 = new Regla[1];
	reglas14[0] = Regla(2, regla14_1tipos, 1);
	Carta carta14 = Carta(1, reglas14, 1);
	resultado.insertarCarta(carta14);
	
	//carta 16
	int * regla15_1tipos = new int[1];
	regla15_1tipos[0] = 0;
	int * regla15_2tipos = new int[1];
	regla15_2tipos[0] = 4;
	int * regla15_3tipos = new int[1];
	regla15_3tipos[0] = 1;
	Regla * reglas15 = new Regla[3];
	reglas15[0] = Regla(2, regla15_1tipos, 1);
	reglas15[1] = Regla(1, regla15_2tipos, 1);
	reglas15[2] = Regla(-2, regla15_3tipos, 1);
	Carta carta15 = Carta(1, reglas15, 3);
	resultado.insertarCarta(carta15);
	
	//carta 17
	int * regla16_1tipos = new int[1];
	regla16_1tipos[0] = 0;
	int * regla16_2tipos = new int[1];
	regla16_2tipos[0] = 5;
	int * regla16_3tipos = new int[1];
	regla16_3tipos[0] = 4;
	Regla * reglas16 = new Regla[3];
	reglas16[0] = Regla(2, regla16_1tipos, 1);
	reglas16[1] = Regla(2, regla16_2tipos, 1);
	reglas16[2] = Regla(-4, regla16_3tipos, 1);
	Carta carta16 = Carta(1, reglas16, 3);
	resultado.insertarCarta(carta16);
	
	//carta 18
	int * regla17_1tipos = new int[1];
	regla15_1tipos[0] = 0;
	int * regla17_2tipos = new int[1];
	regla15_2tipos[0] = 4;
	int * regla17_3tipos = new int[1];
	regla17_3tipos[0] = 1;
	Regla * reglas17 = new Regla[3];
	reglas17[0] = Regla(3, regla17_1tipos, 1);
	reglas17[1] = Regla(-1, regla17_2tipos, 1);
	reglas17[2] = Regla(-1, regla17_3tipos, 1);
	Carta carta17 = Carta(1, reglas17, 3);
	resultado.insertarCarta(carta17);
	
	//carta 19
	int * regla18_1tipos = new int[1];
	regla18_1tipos[0] = 0;
	int * regla18_2tipos = new int[1];
	regla18_2tipos[0] = 2;
	int * regla18_3tipos = new int[1];
	regla18_3tipos[0] = 3;
	Regla * reglas18 = new Regla[3];
	reglas18[0] = Regla(4, regla18_1tipos, 1);
	reglas18[1] = Regla(-2, regla18_2tipos, 1);
	reglas18[2] = Regla(-2, regla18_3tipos, 1);
	Carta carta18 = Carta(1, reglas18, 3);
	resultado.insertarCarta(carta18);
	
	//carta 20
	int * regla19_1tipos = new int[1];
	regla19_1tipos[0] = 0;
	int * regla19_2tipos = new int[1];
	regla19_2tipos[0] = 5;
	Regla * reglas19 = new Regla[2];
	reglas19[0] = Regla(3, regla19_1tipos, 1);
	reglas19[1] = Regla(-2, regla19_2tipos, 1);
	Carta carta19 = Carta(1, reglas19, 2);
	resultado.insertarCarta(carta19);
	
	//carta 21
	int * regla20_1tipos = new int[1];
	regla20_1tipos[0] = 0;
	int * regla20_2tipos = new int[1];
	regla20_2tipos[0] = 2;
	Regla * reglas20 = new Regla[2];
	reglas20[0] = Regla(1, regla20_1tipos, 1);
	reglas20[1] = Regla(1, regla20_2tipos, 1);
	Carta carta20 = Carta(1, reglas20, 2);
	resultado.insertarCarta(carta20);
	
	//carta 22
	int * regla21_1tipos = new int[1];
	regla21_1tipos[0] = 0;
	int * regla21_2tipos = new int[1];
	regla21_2tipos[0] = 2;
	Regla * reglas21 = new Regla[2];
	reglas21[0] = Regla(1, regla21_1tipos, 1);
	reglas21[1] = Regla(1, regla21_2tipos, 1);
	Carta carta21 = Carta(1, reglas21, 2);
	resultado.insertarCarta(carta21);
	
	//carta 23
	int * regla22_1tipos = new int[1];
	regla22_1tipos[0] = 0;
	int * regla22_2tipos = new int[1];
	regla22_2tipos[0] = 4;
	Regla * reglas22 = new Regla[2];
	reglas22[0] = Regla(1, regla22_1tipos, 1);
	reglas22[1] = Regla(1, regla22_2tipos, 1);
	Carta carta22 = Carta(1, reglas22, 2);
	resultado.insertarCarta(carta22);
	
	//////////////////////////otra vez comienzo de cartas que se suman////////////////////
	
	//carta 24
	int * regla23_1tipos = new int[1];
	regla23_1tipos[0] = 3;
	int * regla23_2tipos = new int[1];
	regla23_2tipos[0] = 2;
	Regla * reglas23 = new Regla[1];
	reglas23[0] = Regla(5, regla23_1tipos, 1);
	Carta carta23 = Carta(1, reglas23, 1);
	resultado.insertarCarta(carta23);
	
	//carta 25
	int * regla24_1tipos = new int[1];
	regla24_1tipos[0] = 1;
	int * regla24_2tipos = new int[1];
	regla24_2tipos[0] = 0;
	int * regla24_3tipos = new int[1];
	regla24_3tipos[0] = 3;
	Regla * reglas24 = new Regla[1];
	reglas24[0] = Regla(8, regla24_1tipos, 1);
	Carta carta24 = Carta(1, reglas24, 1);
	resultado.insertarCarta(carta24);
	
	//carta 26
	int * regla25_1tipos = new int[1];
	regla25_1tipos[0] = 2;
	int * regla25_2tipos = new int[1];
	regla25_2tipos[0] = 0;
	int * regla25_3tipos = new int[1];
	regla25_3tipos[0] = 5;
	Regla * reglas25 = new Regla[1];
	reglas25[0] = Regla(8, regla25_1tipos, 1);
	Carta carta25 = Carta(1, reglas25, 1);
	resultado.insertarCarta(carta25);
	
	//carta 27
	int * regla26_1tipos = new int[1];
	regla26_1tipos[0] = 0;
	int * regla26_2tipos = new int[1];
	regla26_2tipos[0] = 0;
	int * regla26_3tipos = new int[1];
	regla26_3tipos[0] = 0;
	Regla * reglas26 = new Regla[1];
	reglas26[0] = Regla(8, regla26_1tipos, 1);
	Carta carta26 = Carta(1, reglas26, 1);
	resultado.insertarCarta(carta26);
	
	//////////////////////terminan cartas que se suman////////////
	
	//carta 28
	int * regla27_1tipos = new int[1];
	regla27_1tipos[0] = 2;
	Regla * reglas27 = new Regla[1];
	reglas27[0] = Regla(2, regla27_1tipos, 1);
	Carta carta27 = Carta(4, reglas27, 1);
	resultado.insertarCarta(carta27);
	
	//carta 29
	int * regla28_1tipos = new int[1];
	regla28_1tipos[0] = 2;
	int * regla28_2tipos = new int[1];
	regla28_2tipos[0] = 5;
	int * regla28_3tipos = new int[1];
	regla28_3tipos[0] = 4;
	Regla * reglas28 = new Regla[3];
	reglas28[0] = Regla(2, regla28_1tipos, 1);
	reglas28[1] = Regla(1, regla28_2tipos, 1);
	reglas28[2] = Regla(-2, regla28_3tipos, 1);
	Carta carta28 = Carta(4, reglas28, 3);
	resultado.insertarCarta(carta28);
	
	//carta 30
	int * regla29_1tipos = new int[1];
	regla29_1tipos[0] = 2;
	int * regla29_2tipos = new int[1];
	regla29_2tipos[0] = 0;
	int * regla29_3tipos = new int[1];
	regla29_3tipos[0] = 5;
	Regla * reglas29 = new Regla[3];
	reglas29[0] = Regla(2, regla29_1tipos, 1);
	reglas29[1] = Regla(2, regla29_2tipos, 1);
	reglas29[2] = Regla(-4, regla29_3tipos, 1);
	Carta carta29 = Carta(4, reglas29, 3);
	resultado.insertarCarta(carta29);
	
	//carta 31
	int * regla30_1tipos = new int[1];
	regla30_1tipos[0] = 2;
	int * regla30_2tipos = new int[1];
	regla30_2tipos[0] = 3;
	int * regla30_3tipos = new int[1];
	regla30_3tipos[0] = 1;
	Regla * reglas30 = new Regla[3];
	reglas30[0] = Regla(4, regla30_1tipos, 1);
	reglas30[1] = Regla(-2, regla30_2tipos, 1);
	reglas30[2] = Regla(-2, regla30_3tipos, 1);
	Carta carta30 = Carta(4, reglas30, 3);
	resultado.insertarCarta(carta30);
	
	//carta 32
	int * regla31_1tipos = new int[1];
	regla31_1tipos[0] = 2;
	int * regla31_2tipos = new int[1];
	regla31_2tipos[0] = 5;
	int * regla31_3tipos = new int[1];
	regla31_3tipos[0] = 4;
	Regla * reglas31 = new Regla[3];
	reglas31[0] = Regla(3, regla31_1tipos, 1);
	reglas31[1] = Regla(-1, regla31_2tipos, 1);
	reglas31[2] = Regla(-1, regla31_3tipos, 1);
	Carta carta31 = Carta(4, reglas31, 3);
	resultado.insertarCarta(carta31);
	
	/////////////////cartas que se suman/////////////
	
	//carta 33
	int * regla32_1tipos = new int[1];
	regla32_1tipos[0] = 3;
	int * regla32_2tipos = new int[1];
	regla32_2tipos[0] = 2;
	int * regla32_3tipos = new int[1];
	regla32_3tipos[0] = 0;
	Regla * reglas32 = new Regla[1];
	reglas32[0] = Regla(8, regla32_1tipos, 1);
	Carta carta32 = Carta(1, reglas32, 1);
	resultado.insertarCarta(carta32);
	
	//////////////termina cartas que se suman/////////////
	
	//carta 34
	int * regla33_1tipos = new int[1];
	regla33_1tipos[0] = 5;
	int * regla33_2tipos = new int[1];
	regla33_2tipos[0] = 1;
	int * regla33_3tipos = new int[1];
	regla33_3tipos[0] = 3;
	Regla * reglas33 = new Regla[3];
	reglas33[0] = Regla(2, regla33_1tipos, 1);
	reglas33[1] = Regla(1, regla33_2tipos, 1);
	reglas33[2] = Regla(-2, regla33_3tipos, 1);
	Carta carta33 = Carta(3, reglas33, 3);
	resultado.insertarCarta(carta33);
	
	//carta 35
	int * regla34_1tipos = new int[1];
	regla34_1tipos[0] = 5;
	int * regla34_2tipos = new int[1];
	regla34_2tipos[0] = 0;
	int * regla34_3tipos = new int[1];
	regla34_3tipos[0] = 2;
	Regla * reglas34 = new Regla[3];
	reglas34[0] = Regla(4, regla34_1tipos, 1);
	reglas34[1] = Regla(-2, regla34_2tipos, 1);
	reglas34[2] = Regla(-2, regla34_3tipos, 1);
	Carta carta34 = Carta(3, reglas34, 3);
	resultado.insertarCarta(carta34);
	
	//carta 36
	int * regla35_1tipos = new int[1];
	regla35_1tipos[0] = 5;
	int * regla35_2tipos = new int[1];
	regla35_2tipos[0] = 1;
	int * regla35_3tipos = new int[1];
	regla35_3tipos[0] = 3;
	Regla * reglas35 = new Regla[3];
	reglas35[0] = Regla(3, regla35_1tipos, 1);
	reglas35[1] = Regla(-1, regla35_2tipos, 1);
	reglas35[2] = Regla(-2, regla35_3tipos, 1);
	Carta carta35 = Carta(3, reglas35, 3);
	resultado.insertarCarta(carta35);
	
	//carta 37
	int * regla36_1tipos = new int[1];
	regla36_1tipos[0] = 4;
	int * regla36_2tipos = new int[1];
	regla36_2tipos[0] = 3;
	int * regla36_3tipos = new int[1];
	regla36_3tipos[0] = 2;
	Regla * reglas36 = new Regla[3];
	reglas36[0] = Regla(2, regla36_1tipos, 1);
	reglas36[1] = Regla(1, regla36_2tipos, 1);
	reglas36[2] = Regla(-2, regla36_3tipos, 1);
	Carta carta36 = Carta(3, reglas36, 3);
	resultado.insertarCarta(carta36);
		
	return resultado;
}

MazoCentral ConstructorMazo::cargarMarzoCentral()
{
	int columnas = 3;
	MazoCentral resultado = MazoCentral(columnas);
	
	CartaLista cartas = this->cargarCartasJson();
	cartas.reordenar();
	int columna = 0;
	int cartasContador = cartas.getCartaContador();
	for (int i = 0 ; i < cartasContador; i++)
	{
		Carta temp = cartas.extraerPrimeraCarta();
		resultado.columna[columna].insertarCartaPila(temp);
		columna++;
		if (columna >=columnas)
		{
			columna = 0;	
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
	this->siguiete();
	this->jugadores[0] = Jugador(nombre);
	this->jugadores[1] = Jugador("PC");
	
}

void GameController::siguiete ()
{
	for (int i = 0; i < this->mesa.columnaContador; i++)
	{
		this->mesa.columna[i].refillMercado();
	}
}

void GameController::tomarCartaPila (int jugador, int columna)
{
	this->jugadores[jugador].mano.insertarCartaPila(this->mesa.columna[columna].pila.extraerUltimaCarta());
}

void GameController::tomarCartaMercado (int jugador, int columna, int indiceMercado)
{
	this->jugadores[jugador].mano.insertarCartaMercado(this->mesa.columna[columna].mercado.extraerCarta(indiceMercado));
}

Impresor::Impresor()
{
	this->tiposContador = 6;
	this->tipos = new string [6];
	this->tipos[0] = "Maíz dulce";
	this->tipos[1] = "Pechuga de pollo";
	this->tipos[2] = "Chile Dulce";
	this->tipos[3] = "Cebolla";
	this->tipos[4] = "Consomé de pollo";
	this->tipos[5] = "Apio";
	
	this->tiposAbreviado = new string [6];
	this->tiposAbreviado[0] = "MaízDu";
	this->tiposAbreviado[1] = "PechPo";
	this->tiposAbreviado[2] = "ChilDu";
	this->tiposAbreviado[3] = "Ceboll";
	this->tiposAbreviado[4] = "Consom";
	this->tiposAbreviado[5] = "Apio";
}

string Impresor::traducirTipo (int i, bool abreviado)
{
	string result  ="";
	if (i>=this->tiposContador || i<0)
	{
		string index;
		stringstream ss;
		ss<<i;
		ss>>index;
		result = "Error: Nombre de carta id:" + index+ " no existe. (Out of index)";
	}
	else
	{
		if (!abreviado)
		{
			result = this->tipos[i];
		}
		else
		{
			result = this->tiposAbreviado[i];
		}
	}
	return result;
}
string Impresor::traducirRegla (Regla input, bool abreviado)
{
	string result  ="";
	result = result + "[(";
	int* reglaTipos = input.gettipos();
	for (int i = 0; i<input.gettiposContador(); i ++)
	{
		result = result + this->traducirTipo(reglaTipos[i], abreviado);
		if (i < (input.gettiposContador()-1))
		{
			result = result + "+";
		}
	}
	result = result + ")=";
	result = result + Herramienta::convertToString(input.getpuntosRandom());
	result = result + "(OR:" + Herramienta::convertToString(input.getpuntosOriginal())+")]";
	return result;
}
string Impresor::traducirCarta (Carta input, bool abreviado)
{
	string result  ="";
	result = result + this->traducirTipo(input.tipo, abreviado);
	return result;
}

string* Impresor::traducirCartaReglas (Carta input, bool abreviado)
{
	int reglasContador = input.getReglasContador();
	string * result = new string[reglasContador];
	for (int j = 0; j < reglasContador; j++)
	{
		result[j] = this->traducirRegla(input.getReglas()[j], abreviado);
	}
	return result;
}

