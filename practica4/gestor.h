
//Alejandro Salgado Martin y Jorge Santos
#include "listaPartidas.h"
#include "listaUsuarios.h"

typedef struct {
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	int enlaceUsuarioActual, enlacePartidaActual;
}tGestor;

bool arrancar(tGestor & gestor);	
/* Inicializa el gestor e intenta arrancarlo cargando la informaci�n del sistema.
Para ello abre los archivos y carga la lista de usuarios y de partidas.
Si tiene �xito, forma la lista de partidas en curso de cada uno de los usuarios y
devuelve true*/

void apagar(tGestor & gestor);
/*Esta operaci�n apaga el gestor, abriendo los ficheros	para guardar las listas de usuarios y de partidas del sistema.*/

bool iniciarSesion(tGestor & gestor, const std::string & idUsu, const std::string &clave);
//Recibe los datos de usuario necesarios para validar la cuenta (id y contrase�a) y
//	comprueba si el usuario existe y la contrase�a coincide. Devuelve cierto y actualiza el
//	usuario de la sesi�n si la operaci�n tuvo �xito.

bool crearCuenta(tGestor & gestor, const std::string & idUsu, const std::string &	clave);
 //Recibe los datos de usuario necesarios para crear una cuenta(id y contrase�a) y
//	si el id de usuario no existe y hay espacio en la lista de usuarios, crea la cuenta del usuario.
//	Devuelve cierto y actualiza el usuario de la sesi�n si la operaci�n tuvo �xito

bool tieneAvisos(const tGestor & gestor, std::string & aviso);
//Comprueba si el usuario de la sesi�n tiene avisos, y en caso afirmativo los devuelve en aviso.

void limpiarAvisos(tGestor & gestor);
//Actualiza los avisos del usuario de la sesi�na la cadena vac�a.

std::string resumenActividad(const tGestor & gestor); 
//Devuelve un string con los datos de la actividad del usuario de la sesi�n, las partidas ganadas, perdidas y empatadas,
//el nivel, la racha y si est� esperando para una nueva partida.

int partidasUsuario(const tGestor & gestor);
//Devuelve el n�mero de partidas en curso del usuario de la sesi�n.

std::string cabecera(const tGestor & gestor, int posEnCurso);
//Dada una posici�n de la lista de partidas en curso del usuario de la sesi�n, devuelve un string que contiene
//la informaci�n que se mostrar� en la lista de partidas en curso : marca('*') si tiene el turno,
//nombres de los jugadores (jugador1, jugador2) y fecha de la �ltima actualizaci�n.

void apuntaPartida(tGestor & gestor, int posParEnCurso);
//Dada una posici�n de la lista de partidas en curso del usuario de la sesi�n, 
//guarda en partida seleccionada, el �ndice de dicha partida en la lista de partidas.

void generarAccesos(tGestor & gestor);
//Recorre la lista de partidas, y para las que todav�a est�n en curso, 
//a�ade el par{ identificador, �ndice } a la lista de partidas en curso de
//cada uno de los adversarios de la partida.

bool nuevaPartida(tGestor & gestor);
//Si el usuario de la sesi�n no ha alcanzado el
//	m�ximo n�mero de partidas en curso y no est� ya en espera, busca un usuario que est�
//	esperando para una nueva partida, que sea del mismo nivel que el usuario de la sesi�n.Si
//	lo encuentra crea la nueva partida e inserta en ambos adversarios los datos de acceso.En
//	otro caso deja al usuario de la sesi�n en estado de espera para una nueva partida.

void ordenar_Fecha(tGestor & gestor);
//Ordena por la fecha de la �ltima actualizaci�n la lista de partidas en curso del usuario de la sesi�n.

void ordenar_Turno(tGestor & gestor); 
//Ordena por turno (primero aquellas en las que le toca jugar al usuario de la sesi�n) 
//la lista de partidas en curso del usuario de la sesi�n. Utiliza la ordenaci�n por inserci�n.

void mostrarPartida(const tGestor & gestor);
//Muestra el estado de la partida en curso

std::string devuelveUsuarioRival(const tGestor & gestor);
//Devuelve el string que corresponde al nombre del contrincante del usuario actual

void jugarPartida(tGestor & gestor, int col);
//Aplica la jugada col a la partida, y en caso de que la partida termine, actualiza a los adversarios, 
//seg�n termine el juego con Ganador o Bloqueo. Adem�s env�a un aviso al contrincante indicando 
//que ha perdido o empatado y la fecha.

bool esSuTurno(const tGestor & gestor); 
//Comprueba si es el turno del usuario de la sesi�n en la partida seleccionada

void abandonarPartida(tGestor & gestor);
//Abandona la partida seleccionada del usuario, y actualiza la informaci�n de los adversarios teniendo en cuenta 
//que el que abandona pierde y el otro gana. Adem�s avisa al contrincante indicando que ha ganado con la fecha