
//Alejandro Salgado Martin y Jorge Santos
#include "gestor.h"
#include <iostream>
using namespace std;

void actualizarPorVictoria(tGestor & gestor);
void actualizarPorEmpate(tGestor & gestor);
//Ambas funciones son auxiliares de jugarPartida, actualizan los campos necesarios en un final de partida

bool arrancar(tGestor & gestor)
{
	gestor = {};

	ifstream flujoLecturaPartidas, flujoLecturaUsuarios;

	flujoLecturaPartidas.open("partidas.txt");
	flujoLecturaUsuarios.open("usuarios.txt");

	bool exito = flujoLecturaPartidas.is_open() && flujoLecturaUsuarios.is_open();

	if (exito)
	{
		bool exitoEnCargaDeListaPartidas = cargarListaPartidas(gestor.listaPartidas, flujoLecturaPartidas);
		bool exitoEnCargaDeListaUsuarios = cargarListaUsuarios(gestor.listaUsuarios, flujoLecturaUsuarios);

		flujoLecturaPartidas.close();
		flujoLecturaUsuarios.close();

		exito = exitoEnCargaDeListaPartidas && exitoEnCargaDeListaUsuarios;

		if (exito)
		{
			generarAccesos(gestor);
		}
	}

	return exito;
}

void apagar(tGestor & gestor)
{
	ofstream flujoGuardarPartidas, flujoGuardarUsuarios;

	flujoGuardarPartidas.open("partidas.txt");
	flujoGuardarUsuarios.open("usuarios.txt");

	guardarListaPartidas(gestor.listaPartidas, flujoGuardarPartidas);
	guardarListaUsuarios(gestor.listaUsuarios, flujoGuardarUsuarios);

	flujoGuardarPartidas.close();
	flujoGuardarUsuarios.close();
}

bool iniciarSesion(tGestor & gestor, const std::string & idUsu, const std::string & clave)
{
	int pos;
	bool exito = false;

	if (buscar(gestor.listaUsuarios, idUsu, pos))
	{
		if (iniciarSesion(gestor.listaUsuarios.usuarios[pos], clave))
		{
			exito = true;
			gestor.enlaceUsuarioActual = pos;
		}
	}

	return exito;
}

bool crearCuenta(tGestor & gestor, const std::string & idUsu, const std::string &	clave)
{
	bool exito = (gestor.listaUsuarios.contador < MAX_USUARIOS) && compruebaIDvalido(idUsu, gestor.listaUsuarios);

	if (exito)
	{
		tUsuario nuevoUsuario;
		int pos;

		iniciar(nuevoUsuario, idUsu, clave);
		exito = insertar(gestor.listaUsuarios, nuevoUsuario, pos);
	}

	return exito;
}

bool tieneAvisos(const tGestor & gestor, std::string & aviso)
{
	bool exito = tieneAvisos(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]);

	if (exito)
	{
		aviso = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].avisos;
	}

	return exito;
}

void limpiarAvisos(tGestor & gestor)
{
	limpiarAvisos(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]);
}

string resumenActividad(const tGestor & gestor)
{
	return resumenActividad(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]);
}

int partidasUsuario(const tGestor & gestor)
{
	return partidasUsuario(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]);
}

string cabecera(const tGestor & gestor, int posEnCurso)
{
	string nombreJug1partida = gestor.listaPartidas.partidas[posEnCurso].jugadores.Jug1;
	string nombreJug2partida = gestor.listaPartidas.partidas[posEnCurso].jugadores.Jug2;
	string nombre = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;
	ostringstream flujo;
	string cabecera;

	if (devuelveTurno(gestor.listaPartidas, posEnCurso, nombre))
	{
		flujo << "*   ";
	}
	else
	{
		flujo << "    ";
	}

	int fecha = gestor.listaPartidas.partidas[posEnCurso].fechaActualizacion;

	flujo << setw(10) << nombreJug1partida << setw(20) << nombreJug2partida <<
		setw(30) << stringFecha(fecha, true) << endl;

	cabecera = flujo.str();

	return cabecera;
}

void generarAccesos(tGestor & gestor)
{
	for (int indice = 0; indice < gestor.listaPartidas.contador; indice++)
	{
		if (gestor.listaPartidas.partidas[indice].estadoPartida == Jugando)
		{
			string jugador1 = gestor.listaPartidas.partidas[indice].jugadores.Jug1;
			string jugador2 = gestor.listaPartidas.partidas[indice].jugadores.Jug2;
			tParIdEn registro;
			registro.enlace = indice;
			registro.identificadorPartida = gestor.listaPartidas.partidas[indice].iden;

			int enlaceUsuario1;
			buscar(gestor.listaUsuarios, jugador1, enlaceUsuario1);

			int enlaceUsuario2;
			buscar(gestor.listaUsuarios, jugador2, enlaceUsuario2);

			insertar(gestor.listaUsuarios.usuarios[enlaceUsuario1].listaAccesoPartidas, registro);
			insertar(gestor.listaUsuarios.usuarios[enlaceUsuario2].listaAccesoPartidas, registro);
		}
	}
}

bool nuevaPartida(tGestor & gestor)
{
	tNivel nivel = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nivel;
	int pos;
	int partidasUser = partidasUsuario(gestor);

	bool exito = (partidasUser < MAX_PAR_US &&  gestor.listaPartidas.contador < MAX_PARTIDAS_GUARDADAS
		&& buscarUsuarioEsperando(gestor.listaUsuarios, nivel, pos));
	/*Hacemos todas las comprobaciones necesarias para que el programa sea eficiente,
	aunque en funciones posteriores también se haga*/

	if (exito)
	{
		tPartida newGame = {};
		string jug1 = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;
		string jug2 = gestor.listaUsuarios.usuarios[pos].nombre;

		nueva(newGame, jug1, jug2);

		tParIdEn registro;
		registro.identificadorPartida = newGame.iden;
		registro.enlace = gestor.listaPartidas.contador;

		nuevaPartida(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], registro);
		nuevaPartida(gestor.listaUsuarios.usuarios[pos], registro);

		exito = insertar(gestor.listaPartidas, newGame);
	}

	if (!exito)
	{
		gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].espera = esperando;
	}

	return exito;
}

void apuntaPartida(tGestor & gestor, int posParEnCurso)
{
	gestor.enlacePartidaActual = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
		.listaAccesoPartidas.partidasUsuario[posParEnCurso].enlace;
}

void ordenar_Fecha(tGestor & gestor)
{
	//Utilizamos el algoritmo de inserccion con intercambios (Natural)

	int contador = partidasUsuario(gestor);

	for (int indice = 1; indice < contador; indice++)
	{
		int pos = indice;

		while ((pos > 0) &&
			(devuelveFecha(gestor.listaPartidas, devuelveEnlace
				(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].listaAccesoPartidas, pos - 1))
				< (devuelveFecha(gestor.listaPartidas, devuelveEnlace
					(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].listaAccesoPartidas, pos)))))
		{
			tParIdEn tmp = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos];
			/*tmp es el dato que intercambaimos; el enlace y el identificador.*/

			gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos]
				= gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos - 1];

			gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos - 1] = tmp;

			pos--;
		}
	}

	/*Realmente el algoritmo compara fechas de actualizacion y ordena la lista de acceso de partidas segun su magnitud
	de mayor a menor, para ello utiliza int devuelveFecha(const tListaPartidas & listaPartidas, int pos), que dada una
	lista de partidas del sistema, y una posicion, devuelve su fecha de actualizacion. La posicion dada a esta funcion es
	el enlace que tiene la lista de acceso en pos, por ello llama a
	int devuelveEnlace(const tListaAccesoPartidas & listaPartidas, int pos), pues el algoritmo recorre las posiciones
	de la lista de acceso*/

	/*devuelveEnlace está en el modulo ListaAccesoPartidas y devuelveFecha en el modulo listaPartidas*/
}

void ordenar_Turno(tGestor & gestor)
{
	//Utilizamos el algoritmo de inserccion con intercambios (Natural)

	int contador = partidasUsuario(gestor);
	string nombreUs = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;

	for (int indice = 1; indice < contador; indice++)
	{
		int pos = indice;

		while ((pos > 0) &&
			(!devuelveTurno(gestor.listaPartidas, devuelveEnlace
				(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].listaAccesoPartidas, pos - 1), nombreUs)
				&& (devuelveTurno(gestor.listaPartidas, devuelveEnlace
					(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].listaAccesoPartidas, pos), nombreUs))))
		{
			tParIdEn tmp = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos];
			/*tmp es el dato que intercambaimos; el enlace y el identificador.*/

			gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos]
				= gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos - 1];

			gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual]
				.listaAccesoPartidas.partidasUsuario[pos - 1] = tmp;

			pos--;
		}
	}

	/*El algoritmo recorre las partidas de acceso del usuario actual, ordena los elementos de esta forma;
	primero los que sí tienen turno, y luego los que no, para ello llama a la funcion
	bool devuelveTurno(const tListaPartidas & listaPartidas, int enlace, string nombre) que devuelve un booleano
	indicándolo, recibe una lista de partidas, el enlace de la partida a examinar y el nombre del usuario a examinar.
	El enlace de la partida a examinar lo determina int devuelveEnlace(const tListaAccesoPartidas & listaPartidas, int pos)
	que dada una posicion en la lista de partidas de acceso devuelve su enlace*/

	/*devuelveEnlace está en el modulo ListaAccesoPartidas y devuelveTurno en el modulo listaPartidas*/
}

void mostrarPartida(const tGestor & gestor)
{
	mostrar
		(gestor.listaPartidas.partidas[gestor.enlacePartidaActual].conecta4,
			gestor.listaPartidas.partidas[gestor.enlacePartidaActual].jugadores.Jug1,
			gestor.listaPartidas.partidas[gestor.enlacePartidaActual].jugadores.Jug2);
}

string devuelveUsuarioRival(const tGestor & gestor)
{
	string usuarioRival;

	if (gestor.listaPartidas.partidas[gestor.enlacePartidaActual].jugadores.Jug1
		== gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre)
	{
		usuarioRival = gestor.listaPartidas.partidas[gestor.enlacePartidaActual].jugadores.Jug2;
	}
	else
	{
		usuarioRival = gestor.listaPartidas.partidas[gestor.enlacePartidaActual].jugadores.Jug1;
	}

	return usuarioRival;
}

bool esSuTurno(const tGestor & gestor)
{
	string nombreUsActual = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;

	return devuelveTurno(gestor.listaPartidas, gestor.enlacePartidaActual, nombreUsActual);
}

void jugarPartida(tGestor & gestor, int col)
{
	if (!aplicarJugada(gestor.listaPartidas.partidas[gestor.enlacePartidaActual], col))
	{
		cout << " No es posible colocar la ficha aqui " << endl << endl;
	}
	else
	{
		mostrarPartida(gestor);

		tEstado estadoJuego = gestor.listaPartidas.partidas[gestor.enlacePartidaActual].conecta4.estado;

		switch (estadoJuego)
		{
		case Jugando:
			cout << endl;
			break;

		case Ganador:
		{
			actualizarPorVictoria(gestor);
		}

		break;

		case Bloqueo:
		{
			actualizarPorEmpate(gestor);
		}
		break;

		default:
			break;
		}
	}
}

void actualizarPorVictoria(tGestor & gestor)
{
	string nombreContrincante = devuelveUsuarioRival(gestor);
	string idPartida = gestor.listaPartidas.partidas[gestor.enlacePartidaActual].iden;
	int fecha = fechaActual();
	string aviso = "Has ganado la partida contra " + nombreContrincante + " el " + stringFecha(fecha, true);
	string nombreUsActual = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;
	int pos = -1;

	cout << " Enhorabuena, has ganado la partida !! " << endl << endl;
	aplicarFinPartida(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], idPartida, Gana);
	actualizarAvisos(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], aviso);


	if (buscar(gestor.listaUsuarios, nombreContrincante, pos))
	{
		string aviso = "Has perdido la partida contra " + nombreUsActual + " el " + stringFecha(fecha, true);
		aplicarFinPartida(gestor.listaUsuarios.usuarios[pos], idPartida, Pierde);
		actualizarAvisos(gestor.listaUsuarios.usuarios[pos], aviso);
	}
	else
	{
		cout << " Error inesperado " << endl << endl;
	}

	gestor.listaPartidas.partidas[gestor.enlacePartidaActual].estadoPartida = terminada;
}

void actualizarPorEmpate(tGestor & gestor)
{
	string nombreContrincante = devuelveUsuarioRival(gestor);
	string idPartida = gestor.listaPartidas.partidas[gestor.enlacePartidaActual].iden;
	int fecha = fechaActual();
	string aviso = "Has empatado la partida contra " + nombreContrincante + " el " + stringFecha(fecha, true);
	string nombreUsActual = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;
	int pos = -1;

	cout << " Lastima, se ha bloqueado el tablero, hay empate " << endl << endl;
	aplicarFinPartida(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], idPartida, Empata);
	actualizarAvisos(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], aviso);


	if (buscar(gestor.listaUsuarios, nombreContrincante, pos))
	{
		string aviso = "Has emparado la partida contra " + nombreUsActual + " el " + stringFecha(fecha, true);
		aplicarFinPartida(gestor.listaUsuarios.usuarios[pos], idPartida, Pierde);
		actualizarAvisos(gestor.listaUsuarios.usuarios[pos], aviso);
	}
	else
	{
		cout << " Error inesperado " << endl << endl;
	}

	gestor.listaPartidas.partidas[gestor.enlacePartidaActual].estadoPartida = terminada;
}

void abandonarPartida(tGestor & gestor)
{
	abandonar(gestor.listaPartidas.partidas[gestor.enlacePartidaActual]);

	string idPartida = gestor.listaPartidas.partidas[gestor.enlacePartidaActual].iden;

	aplicarFinPartida(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], idPartida, Pierde);

	string usuarioRival = devuelveUsuarioRival(gestor);
	int fecha = fechaActual();
	string s_fecha = stringFecha(fecha, true);
	string aviso = "Has perdido por abandono la partida contra " + usuarioRival + " el " + s_fecha;

	actualizarAvisos(gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual], aviso);

	int pos = -1;

	if (buscar(gestor.listaUsuarios, usuarioRival, pos))
	{
		aplicarFinPartida(gestor.listaUsuarios.usuarios[pos], idPartida, Gana);
		string usuarioActual = gestor.listaUsuarios.usuarios[gestor.enlaceUsuarioActual].nombre;
		string aviso = "Has ganado por abandono la partida contra " + usuarioActual + " el " + s_fecha;
		actualizarAvisos(gestor.listaUsuarios.usuarios[pos], aviso);
	}
	else
	{
		cout << " Error inesperado " << endl << endl;
	}
}