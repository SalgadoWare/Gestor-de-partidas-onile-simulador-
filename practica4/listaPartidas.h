
//Alejandro Salgado Martin y Jorge Santos
#include "partida.h"

const int MAX_PARTIDAS_GUARDADAS = 100; 

typedef tPartida tMatrizPartidas[MAX_PARTIDAS_GUARDADAS];

typedef struct {
	tMatrizPartidas partidas;
	int contador;
}tListaPartidas;

bool cargarListaPartidas(tListaPartidas & listaPartidas, std::ifstream & archivo);
 /*Carga la lista de partidas desde el flujo (ya abierto) archivo. Devuelve false 
 si la lista no se ha podido cargar correctamente*/

void guardarListaPartidas(const tListaPartidas & listaPartidas, std::ofstream & archivo);
//Guarda la lista de partidas en el flujo (ya abierto)

bool insertar(tListaPartidas & partidas, const tPartida & partida);
//Dada una partida, si hay espacio en la lista, la añade al final de la lista y devuelve true.
//Si no se ha podido insertar devuelve false

int devuelveFecha(const tListaPartidas & listaPartidas, int enlace);
//Auxiliar de ordenar_Fecha, ver en la funcion su utilidad

bool devuelveTurno(const tListaPartidas & listaPartidas, int enlace, std::string nombre);
//Dada una lista de partidas, un enlace de una de ellas y un nombre del jugador, devuelve true si es su turno
//y false si no
