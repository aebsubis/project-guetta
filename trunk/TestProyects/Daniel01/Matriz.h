/// Fichero de cabecera de la clase Matriz.
/** Al utilizar templates, el código de los métodos está definido en este fichero también.
 * \file Matriz.h
 */

#ifndef MATRIZ__H
#define MATRIZ__H

#include <iostream>
#include <math.h>

using namespace std;


/// La clase Matriz representa a una matriz (matemática).
/** Dispone de operaciones básicas para las matrices como la suma, el producto, la inversa y el determinante.
 * Los índices de la matriz empiezan en 0, no en 1.
 */
template <class T>
class Matriz
{
	
	/// Operador de salida.
	/** Muestra la matriz en el flujo de salida recibido.
	 * El tipo T debe tener sobrecargado el operador de salida.
	 * \param os Flujo de salida donde se va a imprimir la matriz.
	 * \param m Matriz que va a ser mostrada.
	 * \return Devuelve el flujo de salida para poder concatenar salidas.
	 */
	friend ostream& operator<< (ostream &os, const Matriz<T> &m) { return m.pintar(os); }
	
	/// Operador de entrada.
	/** Lee la matriz desde el flujo de entrada recibido. Lee de fila en fila, comenzando por la 0.
	 * El tipo T debe tener sobrecargado el operador de entrada.
	 * \param is Flujo de entrada desde donde se leerá la matriz.
	 * \param m Matriz que va a ser leída.
	 * \return Devuelve el flujo de entrada para poder concatenar lecturas.
	 */	
	friend istream& operator>> (istream &is, Matriz<T> &m) { return m.leer(is); }
	
	public:
	
		/// Constructor por defecto.
		/** Crea una matriz nula, de 0 filas y 0 columnas.
		 */
		Matriz();
		
		/// Constructor sobrecargado.
		/** Crea una matriz. Reserva memoria y asigna unos valores por defecto a cada elemento.
		 * Este valor por defecto es el que proporcione el constructor del tipo T.
		 * \param numF Número de filas que va a tener la matriz.
		 * \param numC Número de columnas que va a tener la matriz.
		 */
		Matriz(int numF, int numC);
		
		/// Destructor.
		/** Libera la memoria reservada de la matriz.
		 */
		~Matriz();
		
		/// Constructor de copia.
		/** Dada una matriz, crea otra igual.
		 * \param m Matriz original que va a ser copiada.
		 */
		Matriz(const Matriz<T> &m);
		
		/// Operador de asignación.
		/** Dada una matriz, la asigna a la matriz que invocó el método.
		 * \param m Matriz original que va a ser asignada.
		 * \return Devuelve una referencia a la matriz que invocó el método para poder concatenar asignaciones.
		 */
		Matriz<T>& operator=(const Matriz<T> &m);
		
		/// Operador suma.
		/** Dada una matriz, suma dicha matriz con la matriz que invocó el método. Las matrices deben ser sumables.
		 * El tipo T debe tener sobrecargado la suma.
		 * \param m Matriz que se va a sumar.
		 * \return Devuelve una copia de la matriz resultante.
		 */
		Matriz<T> operator+(const Matriz<T> &m)const;
		
		/// Operador resta.
		/** Dada una matriz, resta dicha matriz con la matriz que invocó el método. Las matrices deben ser sumables.
		 * El tipo T debe tener sobrecargado la resta.
		 * \param m Matriz que se va a restar.
		 * \return Devuelve una copia de la matriz resultante.
		 */
		Matriz<T> operator-(const Matriz<T> &m)const;
		
		/// Operador producto.
		/** Dado un escalar, multiplica cada elemento por dicho escalar.
		 * El tipo T debe tener sobrecargado el producto.
		 * \param escalar Escalar que se va a multiplicar.
		 * \return Devuelve una copia de la matriz resultante.
		 */
		Matriz<T> operator*(T escalar)const;
		
		/// Operador producto.
		/** Dada una matriz, multiplica dicha matriz con la matriz que invocó el método. Las matrices deben ser multiplicables.
		 * El tipo T debe tener sobrecargado el producto y la suma.
		 * \param m Matriz con la que se va a multiplicar.
		 * \return Devuelve una copia de la matriz resultante.
		 */		
		Matriz<T> operator*(const Matriz<T> &m)const;
		
		/// Comprueba si dos matrices son iguales.
		/** Dada una matriz, comprueba si la matriz que invocó el método, y ésta, son iguales.
		 * \param m Matriz con la que se va a comparar.
		 * \return Devuelve verdadero si son iguales. Falso en caso contrario.
		 */
		bool operator==(const Matriz<T> &m)const;
		
		/// Comprueba si dos matrices son distintas.
		/** Dada una matriz, comprueba si la matriz que invocó el método, y ésta, son distintas.
		 * \param m Matriz con la que se va a comparar.
		 * \return Devuelve verdadero si son distintas. Falso en caso contrario.
		 */
		bool operator!=(const Matriz<T> &m)const;
		
		/// Obtiene una fila de la matriz.
		/** Dada un índice, devuelve la fila correspondiente.
		 * \param numF Número de fila que se va a devolver.
		 * \return Devuelve una referencia a la fila. No se debe liberar este puntero.
		 */
		T* operator[](int numF) const;
		
		/// Obtiene el determinante de la matriz.
		/** El tipo T debe tener sobrecargadas las operaciones + y *.
		 * \return Devuelve el valor del determinante de la matriz.
		 */
		T determinante()const;
		
		/// Obtiene el determinante de la matriz de forma recursiva (lentísimo, método obsoleto).
		/** El tipo T debe tener sobrecargadas las operaciones + y *.
		 * \deprecated Usar determinante().
		 * \return Devuelve el valor del determinante de la matriz.
		 */
		T determinanteRecursivo()const;
		
		/// Asignar fila.
		/** Dado un índice de fila y un vector, copia este vector a la fila seleccionada.
		 * \param numFila Fila donde se va a copiar el vector.
		 * \param vector Vector que se va a copiar.
		 */
		void asignarFila (int numFila, T* vector);
		
		/// Asignar columna.
		/** Dado un índice de columna y un vector, copia este vector a la columna seleccionada.
		 * \param numColumna Columna donde se va a copiar el vector.
		 * \param vector Vector que se va a copiar.
		 */
		void asignarColumna (int numColumna, T* vector);
		
		/// Copia una fila en el vector recibido.
		/** \param numFila Número de la fila que se va a copiar.
		 * \param vector Vector donde se va a copiar la fila. Este vector debe tener la memoria suficiente reservada.
		 */
		void copiarFila (int numFila, T* vector) const;
		
		/// Copia una columna en el vector recibido.
		/** \param numColumna Número de la columna que se va a copiar.
		 * \param vector Vector donde se va a copiar la columna. Este vector debe tener la memoria suficiente reservada.
		 */
		void copiarColumna (int numColumna, T* vector) const;
		
		/// Elimina una fila.
		/** Dada un número de fila, crea una matriz idéntica a la que invocó el método, pero sin dicha fila.
		 * La matriz que invocó el método apuntará finalmente a esta nueva matriz.
		 * \param numFila Número de la fila que se va a eliminar.
		 */
		void eliminarFila (int numFila);
		
		/// Elimina una columna.
		/** Dada un número de columna, crea una matriz idéntica a la que invocó el método, pero sin dicha columna.
		 * La matriz que invocó el método apuntará finalmente a esta nueva matriz.
		 * \param numColumna Número de la columna que se va a eliminar.
		 */
		void eliminarColumna (int numColumna);
		
		/// Intercambia dos filas.
		/** Dados dos índices de fila, las intercambia.
		 * \param fila1 Índice de una fila.
		 * \param fila2 índice de la otra fila.
		 */
		void intercambiarFilas (int fila1, int fila2);
		
		/// Intercambia dos columnas.
		/** Dados dos índices de columna, las intercambia.
		 * \param columna1 Índice de una columnas.
		 * \param columna2 índice de la otra columnas.
		 */
		void intercambiarColumnas (int columna1, int columna2);

		/// Multiplicar fila por escalar.
		/** Multiplica la fila recibida por el escalar recibido.
		 * \param numFila Índice de la fila que se va a multiplicar.
		 * \param escalar Escalar por el que se va a multiplicar cada elemento de la fila.
		 */
		void multiplicarFila (int numFila, T escalar);
		
		/// Multiplicar columna por escalar.
		/** Multiplica la columna recibida por el escalar recibido.
		 * \param numColumna Índice de la columna que se va a multiplicar.
		 * \param escalar Escalar por el que se va a multiplicar cada elemento de la columna.
		 */
		void multiplicarColumna (int numColumna, T escalar);
		
		/// Combinación lineal de dos filas.
		/** Dados dos índices de fila y un escalar, realiza la operación: fila1 = fila1 + escalar*fila2.
		 * \param fila1 Índice de la fila afectada.
		 * \param fila2 Índice de la otra fila.
		 * \param escalar Escalar por el que se multiplica la segunda fila.
		 */
		void combinarFilas (int fila1, int fila2, T escalar);
		
		/// Combinación lineal de dos columnas.
		/** Dados dos índices de columna y un escalar, realiza la operación: columna1 = columna1 + escalar*columna2.
		 * \param columna1 Índice de la columna afectada.
		 * \param columna2 Índice de la otra columna.
		 * \param escalar Escalar por el que se multiplica la segunda columna.
		 */
		void combinarColumnas (int columna1, int columna2, T escalar);
		
		/// Carga la matriz identidad en la matriz.
		/** Establece la diagonal a 1 y el resto a 0.
		 * Este método sólo puede usarse cuando T es de tipo númerico.
		 */
		void cargarIdentidad();
		
		/// Anular matriz.
		/** Anula la matriz estableciendo todos sus elementos a 0.
		 * Este método sólo puede usarse cuand T es de tipo numérico.
		 */
		void anular();
		
		/// Obtiene la inversa de la matriz.
		/** Calcula la inversa de una matriz. Esta matriz debe ser cuadrada.
		 * El tipo T debe tener sobrecargadas las operaciónes + y *.
		 * \return Devuelve la matriz inversa.
		 */
		Matriz<T> inversa()const;
		
		/// Obtiene la traspuesta de la matriz.
		 /** \return Devuelve la matriz traspuesta.
		 */
		Matriz<T> traspuesta() const;

		/// Muestra la matriz.
		/** Muestra la matriz que invocó el método en el flujo de salida recibido.
		 * El tipo T debe tener sobrecargado el operador de salida.
		 * \param os Flujo de salida donde se va a imprimir la matriz.
		 * \return Devuelve el flujo de salida para poder concatenar salidas.
		 */
		ostream& pintar(ostream &os)const;
		
		/// Lee la matriz.
		/** Lee la matriz que invocó el método en el flujo de entrada recibido. Lee de fila en fila, comenzando por la 0.
		 * El tipo T debe tener sobrecargado el operador de entrada.
		 * \param is Flujo de entrada desde donde se va a leer.
		 * \return Devuelve el flujo de entrada para poder concatenar lecturas.
		 */
		istream& leer(istream &is)const;		
		
		/// Comprueba si una matriz es simétrica.
		/** \return Devuelve verdadero si la matriz es simétrica. Falso en caso contrario.
		 */
		bool esSimetrica() const;

		/// Comprueba si una matriz es cuadrada.
		/** Una matriz es cuadrada si tiene el mismo número de filas que de columnas.
		 * \return Devuelve verdadero si la matriz es cuadrada. Falso en caso contrario.
		 */
		bool esCuadrada() const;
		
		/// Comprueba si dos matrices son sumables.
		/** Es decir, comprueba si la matriz que invocó el método y la recibida en los parámetros tienen
		 * la misma dimensión.
		 * \param m Matriz con la que se va a comparar.
		 * \return Devuelve verdadero si son sumables. Falso en caso contrario.
		 */
		bool esSumable(const Matriz<T> &m)const;
		
		/// Comprueba si dos matrices son multiplicables.
		/** Es decir, comprueba si la matriz que invocó el método tiene el mismo número de columnas
		 * que filas tiene la matriz recibida en los parámetros.
		 * \param m Matriz con la que se va a comparar.
		 * \return Devuelve verdadero si son multiplicables. Falso en caso contrario.
		 */
		bool esMultiplicable(const Matriz<T> &m)const;
		
		/// Obtiene un elemento.
		/** Dados dos índices, devuelve el elemento de esa posición.
		 * \param numF Número de fila en el que se encuentra el elemeto.
		 * \param numC Número de columna en el que se encuentra el elemento.
		 * \return Devuelve una copia del elemento que está en dicha posición.
		 */
		T getElemento(int numF, int numC)const;
		
		/// Obtiene un elemento.
		/** Dados dos índices, devuelve el elemento de esa posición.
		 * \param numF Número de fila en el que se encuentra el elemento.
		 * \param numC Número de columna en el que se encuentra el elemento.
		 * \return Devuelve la referencia del elemento que está en dicha posición. No se debe liberar este puntero.
		 */
		T *getPunteroElemento(int numF, int numC) const;
		
		/// Asigna un elemento.
		/** Dados dos índices y un elemento, asigna el valor del elemento a esa posición.
		 * \param numF Número de fila donde se va a asignar el elemento.
		 * \param numC Número de columna donde se va a asignar el elemento.
		 * \param dato Elemento que se va a asignar.
		 * \return Devuelve verdadero si se ha podido asignar. Falso en caso contrario.
		 */
		bool setElemento(int numF, int numC, T dato);
		
		/// Obtiene el número de filas de la matriz.
		/** \return Devuelve un entero con el número de filas de la matriz.
		 */
		int getNumFilas()const{return numFilas;}
		
		/// Obtiene el número de columnas de la matriz.
		/** \return Devuelve un entero con el número de columnas de la matriz.
		 */
		int getNumColumnas()const{return numColumnas;}
		
		/// Obtiene una fila de la matriz.
		/** Dada un índice, devuelve la fila correspondiente.
		 * \param numF Número de fila que se va a devolver.
		 * \return Devuelve una referencia a la fila. No se debe liberar este puntero.
		 */
		T* getFila(int numF) const;

		
	private:
	
		/// Número de filas de la matriz.
		int numFilas;
		
		/// Número de columnas de la matriz.
		int numColumnas;
		
		/// Matriz dinámica.
		T **matriz;
};





template <class T>
Matriz<T>::Matriz()
{
	numFilas = 0;
	numColumnas = 0;
	matriz = NULL;
}

template <class T>
Matriz<T>::Matriz(int numF, int numC)
{
	matriz = NULL;
	
	if(numF>0 && numC>0)
	{
		numFilas = numF;
		numColumnas = numC;
		matriz = new T* [numFilas];
		if (matriz!=NULL)
		{
			for(int i = 0; i< numFilas ; i++)
			{
				matriz[i] = new T [numColumnas];
				if (matriz[i] != NULL)
				{
					for(int j = 0 ; j < numColumnas ; j++)
					{
						matriz[i][j] = T();
					}
				}
				else
				{
					cerr << "ERROR: No hay memoria suficiente. La aplicación debería terminar." << endl;
				}
			}
		}
		else
		{
			cerr << "ERROR: No hay memoria suficiente. La aplicación debería terminar." << endl;
		}
		
	}
	else
	{
		numFilas = 0;
		numColumnas = 0;
	}
}

template <class T>
Matriz<T>::Matriz(const Matriz<T> &m)
{
	numFilas = 0;
	numColumnas = 0;
	matriz = NULL;
	
	*this = m;
}

template <class T>
Matriz<T>::~Matriz()
{
	if (matriz != NULL)
	{
		for(int i = 0 ; i < numFilas ; i++)
		{
			if (matriz[i] != NULL)
			{
				delete [] matriz[i];
				matriz[i] = NULL;
			}
		}

		delete [] matriz;
		matriz = NULL;
	}
	numFilas = 0;
	numColumnas = 0;
}

template <class T>
T Matriz<T>::getElemento(int numF, int numC)const
{
	T aux=T();
	
	if(matriz != NULL)
	{
		if(numF >= 0 && numF < numFilas)
		{
			if (matriz[numF] != NULL)
			{
				if (numC >= 0 && numC < numColumnas)
				{
					aux = matriz[numF][numC];
				}
			}
		}
	}
	return aux;
}

template <class T>
bool Matriz<T>::setElemento(int numF, int numC, T dat)
{
	bool correcto = false;
	if(matriz != NULL)
	{
		if(numF >= 0 && numF < numFilas)
		{
			if (matriz[numF] != NULL)
			{
				if (numC >= 0 && numC < numColumnas)
				{
					matriz[numF][numC] = dat;
					correcto = true;
				}
			}
		}
	}	
	return correcto;
}

template <class T>
ostream& Matriz<T>::pintar(ostream &os)const
{
	if(matriz != NULL)
	{
		cout << endl;
		for(int i = 0; i < numFilas ; i++)
		{
			if(i==0 || i+1 >= numFilas)
				cout << "(\t";
			else
				cout << "|\t";
			
			if (matriz[i] != NULL)
				for(int j = 0; j< numColumnas ; j++)
				{

					cout << matriz[i][j];

					if(j+1 < numColumnas)
						cout << "\t\t" ;
				}
			
			if(i==0 || i+1 >= numFilas)
				cout << "\t)" << endl;
			else
				cout << "\t|" << endl;
			
		}
		cout << endl;
	}
	return os;
}

template <class T>
istream& Matriz<T>::leer(istream &is)const
{
	T aux;
	if (matriz!=NULL)
	{
		for (int i=0; i<numFilas; i++)
		{
			if (matriz[i]!=NULL)
			{
				for (int j=0; j<numColumnas; j++)
				{
					is >> aux;
					matriz[i][j] = aux;
				}
			}
		}
	}
	return is;
}
	

template <class T>
bool Matriz<T>::operator==(const Matriz<T> &m)const
{
	bool iguales = true;
	
	if (matriz!=NULL && m.matriz != NULL)
	{
		
		if (numFilas == m.numFilas && numColumnas == m.numColumnas)
		{
			for(int i = 0 ; i < numFilas && iguales == true ; i++)
			{
				if (matriz[i] != NULL && m.matriz[i] != NULL)
				{
					for( int j = 0 ; j< numColumnas && iguales == true ; j++)
					{
						if(matriz[i][j] != m.matriz[i][j])
						{
							iguales = false;
						}
					}
				}
				else
				{
					if (matriz[i] != m.matriz[i])
					{
						iguales = false;
					}
				}
			}
		}
		else
		{
			iguales = false;
		}
	}
	else if (matriz != m.matriz)
		{
			iguales = false;
		}
	
	
	return iguales;
}

template <class T>
bool  Matriz<T>::operator!=(const Matriz<T> &m)const
{
	return !(*this == m);
}

template <class T>
Matriz<T>& Matriz<T>::operator=(const Matriz<T> &m)
{
	if(this != &m)
	{
			
		if (matriz != NULL)
		{
			for(int i = 0 ; i < numFilas ; i++)
			{
				if (matriz[i] != NULL)
				{
					delete [] matriz[i];
					matriz[i] = NULL;
				}
			}

			delete [] matriz;
			matriz = NULL;
		}
		
		numFilas = m.numFilas;
		numColumnas = m.numColumnas;
		
		if(numFilas > 0 && numColumnas > 0 && m.matriz!=NULL)
		{
			matriz = new T* [numFilas];
			if (matriz!=NULL)
			{
				for(int i = 0; i< numFilas ; i++)
				{
					if (m.matriz[i]!=NULL)
					{
						matriz[i] = new T [numColumnas];
						if (matriz[i] != NULL)
						{
							for(int j = 0 ; j < numColumnas ; j++)
							{
								matriz[i][j] = m.matriz[i][j];
							}
						}
						else
						{
							cerr << "ERROR: No hay memoria suficiente. La aplicación debería terminar." << endl;
						}
					}
				}
			}
			else
			{
				cerr << "ERROR: No hay memoria suficiente. La aplicación debería terminar." << endl;
			}
		}
	}
	
	return *this;
}

template <class T>
bool Matriz<T>::esSumable(const Matriz<T> &m)const
{
	return (m.numFilas == numFilas && m.numColumnas == numColumnas);
}

template <class T>
bool Matriz<T>::esMultiplicable(const Matriz<T> &m)const
{
	return (numColumnas == m.numFilas);
}

template <class T>
Matriz<T>  Matriz<T>::operator+(const Matriz<T> &m)const
{
	Matriz<T> aux(numFilas,numColumnas);
	
	if( this->esSumable(m) )
	{
		if(aux.matriz != NULL && matriz != NULL && m.matriz != NULL)
		{
			
			for(int i = 0 ; i< numFilas ; i++)
			{
				if (aux.matriz[i]!=NULL && m.matriz[i]!=NULL && matriz[i]!=NULL)
					for(int j = 0 ; j < numColumnas ; j++)
					{
						aux.matriz[i][j] = m.matriz[i][j] + matriz[i][j];
					}
			}
		}
	}
	
	return aux;
}

template <class T>
Matriz<T> Matriz<T>::operator-(const Matriz<T> &m)const
{
	Matriz<T> aux(numFilas,numColumnas);
	
	if( this->esSumable(m) )
	{
		if(aux.matriz != NULL && matriz != NULL && m.matriz != NULL)
		{
			
			for(int i = 0 ; i< numFilas ; i++)
			{
				if (aux.matriz[i]!=NULL && m.matriz[i]!=NULL && matriz[i]!=NULL)
					for(int j = 0 ; j < numColumnas ; j++)
					{
						aux.matriz[i][j] = matriz[i][j] - m.matriz[i][j];
					}
			}
		}
	}
	
	return aux;
}

template <class T>
Matriz<T> Matriz<T>::operator*(T escalar)const
{
	Matriz<T> aux(numFilas,numColumnas);
	
	if(numFilas > 0 && numColumnas > 0)
	{
		if(matriz != NULL && aux.matriz != NULL)
		{
			for(int i = 0; i < numFilas ; i++)
			{
				if (aux.matriz[i]!=NULL && matriz[i]!=NULL)
					for(int j = 0 ; j < numColumnas ; j++)
					{
						aux.matriz[i][j] = matriz[i][j] * escalar;
					}
			}
		}
	}
	
	return aux;
}

template <class T>
Matriz<T> Matriz<T>::operator*( const Matriz<T> &m )const
{
	Matriz<T> aux(numFilas,m.numColumnas);
	
	if(this->esMultiplicable(m))
	{
		if (aux.matriz!=NULL && matriz!=NULL && m.matriz!=NULL)
		{
			for(int i = 0; i < numFilas ; i++)
			{
				if (aux.matriz[i]!=NULL && matriz[i]!=NULL)
				{
					for(int j = 0; j< m.numColumnas ; j++)
					{
						for(int k = 0 ; k < numColumnas ; k++)
						{
							if (m.matriz[k]!=NULL)
							{
								aux.matriz[i][j] = aux.matriz[i][j] +(matriz[i][k] * m.matriz[k][j]);
							}
						}
					}
				}
			}
		}
	}
	
	return aux;
}

template <class T>
bool Matriz<T>::esCuadrada() const
{
	return numFilas == numColumnas;
}

template <class T>
bool Matriz<T>::esSimetrica() const
{
	bool simetrica = true;
	
	if(numFilas == numColumnas)
	{
		if (matriz!=NULL)
		{
			for(int i = 0 ; i < numFilas && simetrica == true ; i++)
			{
				if (matriz[i]!=NULL)
				{
					for(int j = 0 ; j < numColumnas && simetrica == true ; j++)
					{
						if(matriz[i][j] != matriz[j][i])
						{
							simetrica = false;
						}
					}
				}
				else
				{
					simetrica = false;
				}
			}
		}
	}
	
	return simetrica;
}

template <class T>
Matriz<T> Matriz<T>::traspuesta() const
{
	Matriz<T> aux(numFilas,numColumnas);
	
	if (aux.matriz!=NULL && matriz!=NULL)
	{
		for(int i = 0; i<numFilas ; i++)
		{
			if (aux.matriz[i]!=NULL && matriz[i]!=NULL)
				for(int j = 0; j< numColumnas ; j++)
				{
					aux.matriz[i][j] = matriz[j][i];
				}
		}
	}
	
	return aux;
}

template <class T>
T *Matriz<T>::getPunteroElemento(int numF, int numC) const
{
	T *aux=NULL;
	
	if(matriz != NULL)
	{
		if(numF >= 0 && numF < numFilas)
		{
			if (matriz[numF] != NULL)
			{
				if (numC >= 0 && numC < numColumnas)
				{
					aux = &matriz[numF][numC];
				}
			}
		}
	}
	return aux;
}

template <class T>
T* Matriz<T>::getFila(int numF) const
{
	if (numF>=0 && numF<numFilas)
	{
		return matriz[numF];
	}
	else
		return NULL;
}

template <class T>
T* Matriz<T>::operator[](int numF) const
{
	if (numF>=0 && numF<numFilas)
	{
		return matriz[numF];
	}
	else
		return NULL;	
}

template <class T>
T Matriz<T>::determinanteRecursivo() const
{
	T determinante = T();

	if (esCuadrada())
	{
		if(numFilas<=2)
		{
			if (numFilas==2)
			{
				determinante = matriz[0][0]*matriz[1][1] - matriz[1][0]*matriz[0][1];
			}
			else
			{
				determinante = matriz[0][0];
			}
		}
		else
		{
			for(int i=0; i<numFilas; i++)
			{
				Matriz<T> menor(numFilas-1, numFilas-1);

				for(int j=1; j<numFilas; j++)
				{
					int contador = 0;
					for(int k=0; k<numFilas; k++)
					{
						if(k != i)
						{
							menor.matriz[j-1][contador] = matriz[j][k];
							contador++;
						}
					}
				}
								
				determinante += pow(-1, 2+i) * matriz[0][i] * menor.determinanteRecursivo();
			}
		}
	}

	return determinante;
}

template <class T>
T Matriz<T>::determinante() const
{
	Matriz<T> copia;

	T determinante = 1;
	
	// Comprobamos que la matriz sea cuadrada.
	if (esCuadrada())
	{
		copia = *this;
		bool invertible = true;
		
		// Primera parte. Establecemos la diagonal a 1, y debajo de ella todo 0.
		for (int i=0; i<numColumnas && invertible; i++)
		{
			// Buscamos alguna fila cuyo elemento <i> sea distinto de 0.
			bool encontrada = false;
			int j=i;
			while (j<numFilas && !encontrada)
			{
				if (copia.matriz[j][i] != 0)
				{
					encontrada = true;
				}
				else
				{
					j++;
				}
			}
			
			// Si hemos encontrado alguna fila válida, la intercambiamos.
			if (encontrada)
			{
				if (i!=j)
				{
					copia.intercambiarFilas (i,j);
					determinante *= -1;
				}
				
				// Dividimos la fila <i> por el valor de ese elemento que hemos encontrado, para obtener un 1.
				determinante *= copia.matriz[i][i];
				copia.multiplicarFila (i, 1/(copia.matriz[i][i]*1.0));
				
				// Ponemos a 0 todos los elementos que estén debajo de ese elemento que hemos neutralizado a 1.
				for (int j=i+1; j<numFilas; j++)
				{					
					copia.combinarFilas(j,i,-copia.matriz[j][i]);
				}
			}
			else
			{
				// Si no hemos encontrado ninguna fila, el determinante es 0.
				invertible = false;
				determinante = 0;
			}
		}		
	}
	
	return determinante;
}

template <class T>
void Matriz<T>::asignarFila (int numFila, T* vector)
{
	if (0<=numFila && numFila <= numFilas && vector!=NULL)
	{
		for (int i=0; i<numColumnas; i++)
		{
			matriz[numFila][i] = vector[i];
		}
	}
}

template <class T>
void Matriz<T>::asignarColumna (int numColumna, T* vector)
{
	if (0<=numColumna && numColumna <= numColumnas && vector!=NULL)
	{
		for (int i=0; i<numFilas; i++)
		{
			matriz[i][numColumna] = vector[i];
		}
	}
}

template <class T>
void Matriz<T>::copiarFila (int numFila, T* vector) const
{
	if (0<=numFila && numFila <= numFilas && vector!=NULL)
	{
		for (int i=0; i<numColumnas; i++)
		{
			vector[i] = matriz[numFila][i];
		}
	}
}

template <class T>
void Matriz<T>::copiarColumna (int numColumna, T* vector) const
{
	if (0<=numColumna && numColumna <= numColumnas && vector!=NULL)
	{
		for (int i=0; i<numFilas; i++)
		{
			vector[i] = matriz[i][numColumna];
		}
	}
}

template <class T>
void Matriz<T>::eliminarFila (int numFila)
{
	Matriz<T> nueva (numFilas-1, numColumnas);
	int encontrada = 0;
	
	for (int i=0; i<numFilas-1; i++)
	{
		if (i==numFila) encontrada = 1;
		for (int j=0; j<numColumnas; j++)
		{
			nueva.matriz[i][j] = matriz[i+encontrada][j];
		}
	}

	*this = nueva;
}

template <class T>
void Matriz<T>::eliminarColumna (int numColumna)
{
	Matriz<T> nueva (numFilas, numColumnas-1);
	int encontrada = 0;
	
	for (int i=0; i<numFilas; i++)
	{
		for (int j=0; j<numColumnas-1; j++)
		{
			if (j==numColumna) encontrada = 1;
			nueva.matriz[i][j] = matriz[i][j+encontrada];
		}
		encontrada = 0;
	}

	*this = nueva;	
}

template <class T>
void Matriz<T>::intercambiarFilas (int fila1, int fila2)
{
	if (0<=fila1 && fila1<numFilas && 0<=fila2 && fila2<numFilas)
	{
		T *aux = NULL;
		aux = matriz[fila1];
		matriz[fila1] = matriz[fila2];
		matriz[fila2] = aux;
	}
}

template <class T>
void Matriz<T>::intercambiarColumnas (int columna1, int columna2)
{
	if (0<=columna1 && columna1<numColumnas && 0<=columna2 && columna2<numColumnas)
	{

		if (matriz != NULL)
		{
			T aux;
			for (int i=0; i<numFilas; i++)
			{
				if (matriz[i] != NULL)
				{
					aux = matriz[i][columna1];
					matriz[i][columna1] = matriz[i][columna2];
					matriz[i][columna2] = aux;
				}
			}
		}
	}
}

template <class T>
void Matriz<T>::multiplicarFila (int numFila, T escalar)
{
	if (0<=numFila && numFila<numFilas)
	{
		if (matriz != NULL)
		{
			if (matriz[numFila] != NULL)
			{
				for (int i=0; i<numColumnas; i++)
				{
					matriz[numFila][i] *= escalar;
				}
			}
		}
	}
}

template <class T>
void Matriz<T>::multiplicarColumna (int numColumna, T escalar)
{
	if (0<=numColumna && numColumna<numColumnas)
	{
		if (matriz != NULL)
		{
			for (int i=0; i<numFilas; i++)
			{
				if (matriz[i] != NULL)
				{
					matriz[i][numColumna] *= escalar;
				}
			}
		}
	}
}

template <class T>
void Matriz<T>::combinarFilas (int fila1, int fila2, T escalar)
{
	if (0<=fila1 && fila1<numFilas && 0<=fila2 && fila2<numFilas)
	{
		if (matriz != NULL)
		{
			if (matriz[fila1] != NULL && matriz[fila2] != NULL)
			{
				for (int i=0; i<numColumnas; i++)
				{
					matriz[fila1][i] += escalar*matriz[fila2][i];
				}
			}
		}
	}
}

template <class T>
void Matriz<T>::combinarColumnas (int columna1, int columna2, T escalar)
{
	if (0<=columna1 && columna1<numColumnas && 0<=columna2 && columna2<numColumnas)
	{
		if (matriz != NULL)
		{
			for (int i=0; i<numFilas; i++)
			{
				if (matriz[i] != NULL)
				{
					matriz[i][columna1] += escalar*matriz[i][columna2];
				}
			}
		}
	}
}

template <class T>
void Matriz<T>::cargarIdentidad()
{
	if (matriz!=NULL)
	{
		for (int i=0; i<numFilas; i++)
		{
			if (matriz[i] != NULL)
			{
				for (int j=0; j<numColumnas; j++)
				{
					if (i==j)
						matriz[i][j] = 1;
					else
						matriz[i][j] = 0;
				}
			}
		}
	}
}

template <class T>
void Matriz<T>::anular()
{
	if (matriz!=NULL)
	{
		for (int i=0; i<numFilas; i++)
		{
			if (matriz[i] != NULL)
			{
				for (int j=0; j<numColumnas; j++)
				{
					matriz[i][j] = 0;
				}
			}
		}
	}
}

template <class T>
Matriz<T> Matriz<T>::inversa()const
{
	Matriz<T> copia;
	Matriz<T> resultado;
	
	// Comprobamos que la matriz sea cuadrada.
	if (esCuadrada())
	{
		copia = *this;
		resultado = Matriz<T> (numFilas, numFilas);
		resultado.cargarIdentidad();
		bool invertible = true;
		
		// Primera parte. Establecemos la diagonal a 1, y debajo de ella todo 0.
		for (int i=0; i<numColumnas && invertible; i++)
		{
			// Buscamos alguna fila cuyo elemento <i> sea distinto de 0.
			bool encontrada = false;
			int j=i;
			while (j<numFilas && !encontrada)
			{
				if (copia.matriz[j][i] != 0)
				{
					encontrada = true;
				}
				else
				{
					j++;
				}
			}
			
			// Si hemos encontrado alguna fila válida, la intercambiamos.
			if (encontrada)
			{
				if (i!=j)
				{
					resultado.intercambiarFilas (i,j);
					copia.intercambiarFilas (i,j);
				}
				
				// Dividimos la fila <i> por el valor de ese elemento que hemos encontrado, para obtener un 1.
				resultado.multiplicarFila (i, 1/(copia.matriz[i][i]*1.0));
				copia.multiplicarFila (i, 1/(copia.matriz[i][i]*1.0));

				// Ponemos a 0 todos los elementos que estén debajo de ese elemento que hemos neutralizado a 1.
				for (int j=i+1; j<numFilas; j++)
				{					
					resultado.combinarFilas(j,i,-copia.matriz[j][i]);
					copia.combinarFilas(j,i,-copia.matriz[j][i]);
				}
				
			}
			else
			{
				// Si no hemos encontrado ninguna fila, la matriz no tiene inversa.
				invertible = false;
				resultado.anular();
			}
		}
		
		// Segunda parte. Establecemos a 0 los elmentos de arriba de la diagonal.
		for (int i=numColumnas-1; i>=1 && invertible; i--)
		{
			for (int j=i-1; j>=0; j--)
			{				
				resultado.combinarFilas(j,i,-copia.matriz[j][i]);
				copia.combinarFilas(j,i,-copia.matriz[j][i]);
			}
		}
	}
	
	return resultado;
}

#endif
