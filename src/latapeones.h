// Nombre: Ricardo, Apellidos: Ruiz Fernández de Alba, Titulación: GIM
// email: ricardoruiz@correo.ugr.es, DNI: 77168601J

#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP

#include "malla-ind.h"
#include "grafo-escena.h"
#include "malla-revol.h"

class Lata : public NodoGrafoEscena
{
    public:
        Lata(const std::string& nombreArchivoJPG);
};

class Peon : public NodoGrafoEscena
{
    public:
        Peon();
};

class LataPeones : public NodoGrafoEscena
{
    public:
        LataPeones();
};

#endif