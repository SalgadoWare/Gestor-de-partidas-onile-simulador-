
//Alejandro Salgado Martin y Jorge Santos
#include "listaPartidas.h"
using namespace std;

bool cargarListaPartidas(tListaPartidas & listaPartidas, ifstream & archivo) 
{
	bool exito = false;
	int n_partidas;

	archivo >> n_partidas;

	if (n_partidas >= MAX_PARTIDAS_GUARDADAS)
	{
		exito = false;
	}
	else
	{
		exito = true;
		int indice = 0;
		listaPartidas.contador = n_partidas;

		while (exito && indice < listaPartidas.contador)
		{
			tPartida partida = {};

			exito = carga(partida, archivo);

			if (exito)
			{
				listaPartidas.partidas[indice] = partida;
				indice++;
			}
		}
	}

	return exito;
}

void guardarListaPartidas(const tListaPartidas & listaPartidas, ofstream & archivo)
{
	archivo << listaPartidas.contador << endl;

	for (int indice = 0; indice < listaPartidas.contador; indice++)
	{
		guarda(listaPartidas.partidas[indice], archivo);
	}
}

bool insertar(tListaPartidas & listaPartidas, const tPartida & partida)
{
	bool exito = false;

	if (listaPartidas.contador < MAX_PARTIDAS_GUARDADAS)
	{
		exito = true;
		listaPartidas.partidas[listaPartidas.contador] = partida;
		listaPartidas.contador++;
	}

	return exito;
}

int devuelveFecha(const tListaPartidas & listaPartidas, int enlace)
{
	return listaPartidas.partidas[enlace].fechaActualizacion; 
}

bool devuelveTurno(const tListaPartidas & listaPartidas, int enlace, string nombre)
{
	bool jugador1 = (nombre == listaPartidas.partidas[enlace].jugadores.Jug1);
	bool jugador2 = (nombre == listaPartidas.partidas[enlace].jugadores.Jug2);

	return
		(listaPartidas.partidas[enlace].conecta4.turno == Jugador1 && jugador1)
		|| (listaPartidas.partidas[enlace].conecta4.turno == Jugador2 && jugador2);
}