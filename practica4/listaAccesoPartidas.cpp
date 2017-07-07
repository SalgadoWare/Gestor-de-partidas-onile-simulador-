
//Alejandro Salgado Martin y Jorge Santos
#include "listaAccesoPartidas.h"
using namespace std;

void iniciar(tListaAccesoPartidas & lista)
{
	lista.contador = 0;
}

bool insertar(tListaAccesoPartidas & lista, tParIdEn par)
{
	bool exito = !llena(lista);

	if (exito)
	{
		lista.partidasUsuario[lista.contador] = par;
		lista.contador++;
	}

	return exito;
}

int devuelveEnlace(const tListaAccesoPartidas & listaPartidas, int pos)
{
	return listaPartidas.partidasUsuario[pos].enlace;
}

bool eliminar(tListaAccesoPartidas & lista, const string & id)
{
	bool encontrado = false;
	int indice = 0;

	while (!encontrado && indice < lista.contador)
	{
		if (id == lista.partidasUsuario[indice].identificadorPartida)
		{
			encontrado = true;

			for (indice; indice < lista.contador - 1; indice++)
			{
				lista.partidasUsuario[indice] = lista.partidasUsuario[indice + 1];
			}

			lista.contador--;
		}
		else
		{
			indice++;
		}
	}

	return encontrado;
}

bool llena(const tListaAccesoPartidas & lista)
{
	return lista.contador >= MAX_PAR_US;
}