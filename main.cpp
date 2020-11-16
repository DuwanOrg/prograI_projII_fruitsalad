#include<iostream>
#include"salad.h"

using namespace std;

main(){
//	Carta *c1=new Carta(3,-2,0,3,5,"zanahoria");//3 = zanahoria, 5 = cebolla, 0 = no verfura
//	c1->getRegla()->transformarRegla();
//	c1->getRegla()->toString();
	try
	{
		GameController controlador = GameController();
		controlador.iniJuego("Villa");
		Impresor Impresor1 = Impresor();
		while (true)
		{
			system("cls");
			for (int i = 0; i <controlador.mesa.columnaContador; i++)
			{
				//imprimir pila
				
				Carta pilaUltima = controlador.mesa.columna[i].pila.MostrarUltima();
				Regla * reglas = pilaUltima.getReglas();
				int reglasContador = pilaUltima.getReglasContador();
				cout << "COLUMNA INDICE: "+Herramienta::convertToString(i);
				cout << "\n";
				cout << Impresor1.traducirCarta(pilaUltima);
				cout << "\n";
				for (int relgasIndice = 0; relgasIndice < reglasContador; relgasIndice++)
				{
					cout<< Impresor1.traducirRegla(reglas[relgasIndice], true);
					cout<< "\n";
				}
				
				//cout<< Impresor1.traducirCarta(controlador.mesa.columna[i].pila.MostrarUltima(), true);
				
				cout<< "\n";
				//imrprimir mercado
				cout<< "Mercado:";
				cout<< "\n";
				
				Carta * mercado = controlador.mesa.columna[i].mercado.getCartas();
				int mercadoCartas = controlador.mesa.columna[i].mercado.getCartaContador();
				for (int cartasMercado = 0; cartasMercado < mercadoCartas; cartasMercado++)
				{
					cout<< Impresor1.traducirCarta(mercado[cartasMercado], true);
					cout<< "\n";	
				}
				cout << "\n\n";
			}
			
			cout << "\n\n";
			cout << "Jugador\n";
			int JugadorIndex = 0;
			
			//Imprimir nombre
			cout << controlador.jugadores[JugadorIndex].nombre + "\n";
			
			//imprimir pila
			
			Carta * pilaCartas = controlador.jugadores[JugadorIndex].mano.pila.getCartas();
			int pilaCartasContador = controlador.jugadores[JugadorIndex].mano.pila.getCartaContador();
			for (int pilaCartaIndice = 0; pilaCartaIndice < pilaCartasContador; pilaCartaIndice++)
			{
				string * reglasTexto =  Impresor1.traducirCartaReglas(pilaCartas[pilaCartaIndice], true);
				int reglasContador = pilaCartas[pilaCartaIndice].getReglasContador();
				for (int reglasIndice = 0; reglasIndice<reglasContador; reglasIndice++)
				{
					cout << "||";
					cout<< reglasTexto[reglasIndice];
					cout << "||";
				}
				cout<<"\n";
			}
			
			//imprimir mercado
			
			cout<<"mercado:";
			cout<<"\n";
			
			
			for (int tipos = 0; tipos<6; tipos ++)
			{
				cout << Impresor1.traducirTipo(tipos, true)+": ";
				cout << controlador.jugadores[JugadorIndex].mano.mercado.getCartaTipoContador(tipos);
				cout << "\n";
			}
			
			//Imprimir puntaje
			cout << "\n";
			cout << "Puntaje: " + Herramienta::convertToString(controlador.jugadores[JugadorIndex].mano.getPuntaje());
			
			cout << "\n";
			cout << "Ingrese la opcion [PILA] o [MERCADO] y presione ENTER:";
			string input;
			cin >> input;
			if (input=="PILA")
			{
				cout << "\n";
				cout << "Ingrese el indice de la Pila de la cual quiere tomar carta:";
				int indice = 0;
				cin >> indice;
				if (indice>=0 and indice <3)
				{
					controlador.tomarCartaPila(0, indice);
					cout << "\n";
					cout << "Turno finalizado con exito, presione ENTER para continuar.";
					cin;
				}
			}
			if (input=="MERCADO")
			{
				cout << "\n";
				cout << "Ingrese el indice del Mercado del cual quiere tomar carta:";
				int indiceMercado = 0;
				cin >> indiceMercado;
				cout << "\n";
				cout << "Ingrese el indice de carta que quiere tomar del mercado:";
				int indiceMercadoCarta = 0;
				cin >> indiceMercadoCarta;
				if (indiceMercado >=0 and indiceMercado < 3)
				{
					if (indiceMercadoCarta>=0 and indiceMercadoCarta < 3)
					{
						controlador.tomarCartaMercado(0, indiceMercado, indiceMercadoCarta);
						cout << "\n";
						cout << "Turno finalizado con exito, presione ENTER para continuar.";
						cin;
					}
				}
			}
			controlador.siguiete();
		}
	}
	catch (const std::exception &exc)
	{
		cout << exc.what();
	}	
	
}

