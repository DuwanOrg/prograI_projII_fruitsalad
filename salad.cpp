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
}

//// Programacion del mazo

Mazo::Mazo (int maxMercado)
{
	this->maxMercado=maxMercado;
	this->mercado = CartaLista();
	this->pila=CartaLista();
}

int Mazo::getPuntaje ()
{
	
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


