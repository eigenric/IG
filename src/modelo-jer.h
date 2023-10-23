#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"

class BaseMotherboard;
class Cabeza;
class Boca;
class Nariz;
class OjoPupila;
class OjoIzquierdo;
class OjoDerecho;

class Motherboard : public NodoGrafoEscena
{
    public:
        Motherboard();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
};

class BaseMotherboard : public MallaInd
{
    public:
        BaseMotherboard();
};

class Cabeza : public NodoGrafoEscena
{
    public:
        Cabeza();
};

class Paralelepipedo: public MallaInd
{
    public:
        Paralelepipedo();
};

class Boca : public NodoGrafoEscena
{
    public:
        Boca();
};

class Nariz : public NodoGrafoEscena
{
    public:
        Nariz();
};

class OjoIzquierdo : public NodoGrafoEscena
{
    public:
        OjoIzquierdo();
};

class OjoDerecho : public NodoGrafoEscena
{
    public:
        OjoDerecho();
};

class OjoPupila : public NodoGrafoEscena
{
    public:
        OjoPupila();
};

#endif // MODELO_JER_HPP