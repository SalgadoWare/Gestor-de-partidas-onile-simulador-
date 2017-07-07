
//Alejandro Salgado Martin y Jorge Santos
#include "usuario.h"

const int MAX_USUARIOS = 10; 

typedef tUsuario tMatrizUsuarios[MAX_USUARIOS];

typedef struct {
	tMatrizUsuarios usuarios;
	int contador;
}tListaUsuarios;

bool cargarListaUsuarios(tListaUsuarios & listaUsuarios, std::ifstream & archivo);
/* Carga la lista de usuarios desde el flujo (ya abierto)*/

void guardarListaUsuarios(const tListaUsuarios & listaUsuarios, std::ofstream & archivo);
/*Guarda la lista de usuarios en el flujo(ya abierto)*/

bool buscar(const tListaUsuarios & listaUsuarios, const std::string & idUser, int &pos);
/* Dado un identificador de usuario	y la lista, devuelve, si dicho identificador existe en la lista,
su posición y el valor true, y si no existe en la lista, la posición que lecorrespondería y el valor false.*/

bool insertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario, int &pos);
// Añade un usuario en la posición de la lista que le corresponde, si hay sitio para ello
//	y no hay otro usuario con el mismo identificador.Además devuelve un booleano
//	indicando si la operación tuvo éxito o no, y la posición donde se ha insertado.

bool buscarUsuarioEsperando(const tListaUsuarios & usuarios, tNivel nivel, int & pos);
//Devuelve true y la posición del primer usuario del nivel dado que está esperando
//para iniciar una partida. Si no existe devuelve false.

bool compruebaIDvalido(const std::string IDnuevo, const tListaUsuarios listaUsuarios);
//Auxiliar de crearCuenta, comprueba que el ID introducido no exita ya en la lista de Usuarios