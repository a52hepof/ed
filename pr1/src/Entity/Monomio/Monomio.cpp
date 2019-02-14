/*!
   \file  Monomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "Monomio.hpp"



ed::Monomio::Monomio(float coeficiente, int grado)
{
	if (grado < 0) this->grado_ = 0;
	else this->grado_ = grado;

	this->coeficiente_ = coeficiente;
}

ed::Monomio::Monomio(const ed::Monomio &monomio)
{
	(*this) = monomio;
}


float ed::Monomio::getCoeficiente() const
{
	return this->coeficiente_;
}

int ed::Monomio::getGrado() const
{
	return this->grado_;
}


bool ed::Monomio::setCoeficiente(float coeficiente)
{
	this->coeficiente_ = coeficiente;
	return true;
}

bool ed::Monomio::setGrado(int grado)
{
	if (grado < 0) return false;

	this->grado_ = grado;
	return true;
}


// Operadores de asignación

// COMPLETAR

ed::Monomio & ed::Monomio::operator=(ed::Monomio const &m)
{
	this->coeficiente_ = m.getCoeficiente();
	this->grado_ = m.getGrado();

	// Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator=(double const &x)
{
	this->grado_ = 0;
	this->coeficiente_ = x;

	return *this;
}



//////////////////////////////////////////////////////////////

// Operadores aritméticos y asignación

// COMPLETAR

ed::Monomio & ed::Monomio::operator+=(ed::Monomio const &m)
{
	// COMPLETAR


	// Se devuelve el objeto actual
	return *this;
}



// COMPLETAR EL RESTO DE OPERADORES



///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Monomio

// COMPLETAR


///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Monomio

// COMPLETAR
