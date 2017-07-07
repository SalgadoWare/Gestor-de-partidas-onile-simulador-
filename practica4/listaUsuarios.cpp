
//Alejandro Salgado Martin y Jorge Santos
#include "listaUsuarios.h"
using namespace std;

int buscarPosicionParaInsertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario);
//Auxiliar de la funcion insertar, devuelve la posicion donde se va a insertar un nuevo usuario,
//es una búsqueda binaria que se aprovecha de que la lista de usuarios esté ordenada alfabéticamente

bool cargarListaUsuarios(tListaUsuarios & listaUsuarios, ifstream & archivo)
{
	bool exito = false;
	int n_usuarios;
	int indice = 0;

	archivo >> n_usuarios;

	if (n_usuarios < MAX_USUARIOS)
	{
		exito = true;
		listaUsuarios.contador = n_usuarios;

		while (exito && indice < listaUsuarios.contador)
		{
			tUsuario usuario = {}; /*ya se inicializan todos los campos*/

			exito = cargarUs(usuario, archivo);

			if (exito)
			{
				listaUsuarios.usuarios[indice] = usuario;
				indice++;
			}
		}
	}

	return exito;
}

void guardarListaUsuarios(const tListaUsuarios & listaUsuarios, ofstream & archivo)
{
	archivo << listaUsuarios.contador << endl;

	for (int indice = 0; indice < listaUsuarios.contador; indice++)
	{
		guardarUs(listaUsuarios.usuarios[indice], archivo);
	}
}

bool buscar(const tListaUsuarios & listaUsuarios, const string & idUser, int &pos)
{
	int inicio = 0;
	int mitad;
	int fin = listaUsuarios.contador - 1;
	bool encontrado = false;

	while ((inicio <= fin) && !encontrado)
	{
		mitad = (inicio + fin) / 2;

		if (idUser == listaUsuarios.usuarios[mitad].nombre)
		{
			encontrado = true;
			pos = mitad;
		}
		else
		{
			if (idUser < listaUsuarios.usuarios[mitad].nombre)
			{
				fin = mitad - 1;
			}
			else
			{
				inicio = mitad + 1;
			}
		}
	}

	return encontrado;
}

bool insertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario, int &pos)
{
	bool exito = (listaUsuarios.contador < MAX_USUARIOS);

	if (exito)
	{
		pos = buscarPosicionParaInsertar(listaUsuarios, usuario);

		for (int indice = listaUsuarios.contador; indice > pos; indice--)
		{
			listaUsuarios.usuarios[indice] = listaUsuarios.usuarios[indice - 1];
		}

		listaUsuarios.usuarios[pos] = usuario;
		listaUsuarios.contador++;
	}

	return exito;
}

int buscarPosicionParaInsertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario)
{
	int inicio = 0;
	int fin = listaUsuarios.contador - 1;
	int mitad, pos;
	bool encontrado = false;

	while ((inicio <= fin) && !encontrado)
	{
		mitad = (inicio + fin) / 2;

		if (usuario.nombre > listaUsuarios.usuarios[mitad - 1].nombre
			&& usuario.nombre < listaUsuarios.usuarios[mitad].nombre)
		{
			encontrado = true;
			pos = mitad;
		}
		else
		{
			if (usuario.nombre < listaUsuarios.usuarios[mitad].nombre)
			{
				fin = mitad - 1;
			}
			else
			{
				inicio = mitad + 1;
			}
		}
	}

	if (inicio > fin)
	{
		pos = listaUsuarios.contador;
	}

	return pos;
}

bool buscarUsuarioEsperando(const tListaUsuarios & listaUsuarios, tNivel nivel, int & pos)
{
	bool encontrado = false;
	int indice = 0;

	while (!encontrado && indice < listaUsuarios.contador)
	{
		if ((listaUsuarios.usuarios[indice].espera == esperando) &&
			(partidasUsuario(listaUsuarios.usuarios[indice]) < MAX_PAR_US)
			&& (listaUsuarios.usuarios[indice].nivel == nivel))
		{
			encontrado = true;

			pos = indice;
		}
		else
		{
			indice++;
		}
	}

	return encontrado;
}

bool compruebaIDvalido(const std::string IDnuevo, const tListaUsuarios listaUsuarios)
{
	int inicio = 0, fin = listaUsuarios.contador - 1, mitad;
	bool encontrado = false;
	while ((inicio <= fin) && !encontrado)
	{
		mitad = (inicio + fin) / 2;
		if (IDnuevo == listaUsuarios.usuarios[mitad].nombre) {
			encontrado = true;
		}
		else
		{
			if (IDnuevo < listaUsuarios.usuarios[mitad].nombre)
			{
				fin = mitad - 1;
			}
			else
			{
				inicio = mitad + 1;
			}
		}
	}

	return !encontrado;
}