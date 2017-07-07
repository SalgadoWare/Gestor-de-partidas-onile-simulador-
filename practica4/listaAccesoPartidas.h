
//Alejandro Salgado Martin y Jorge Santos
#include <string>

const int MAX_PAR_US = 10;

typedef struct {
	std::string identificadorPartida;
	int enlace;
}tParIdEn;

typedef tParIdEn tPartidasUs[MAX_PAR_US];

typedef struct {
	tPartidasUs partidasUsuario;
	int contador;
}tListaAccesoPartidas;


void iniciar(tListaAccesoPartidas & lista);
 //Inicia la lista vacía.

bool insertar(tListaAccesoPartidas & lista, tParIdEn par);
//Dado un elemento, si la lista no está llena lo inserta al final de la lista y devuelve true.En otro caso
//devuelve false.

int devuelveEnlace(const tListaAccesoPartidas & listaPartidas, int pos);
//Auxiliar de ordenar_Fecha, ver en la funcion su utilidad

bool llena(const tListaAccesoPartidas & lista);
//Comprueba si la lista está llena

bool eliminar(tListaAccesoPartidas & lista, const std::string & id);
//Dado un identificador de partida, lo busca en la lista y si lo encuentra lo elimina de la lista.
//Si no lo encuentra, devuelve false, en otro caso devuelve true. La partida se elimina unicamente en la 
//lista de acceso de partidas de cada usuario