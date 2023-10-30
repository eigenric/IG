#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"

using namespace glm;

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

class Pelo: public NodoGrafoEscena
{
    public:
        Pelo();
};

class Rizos: public MallaRevol
{
    public:
        Rizos(const int num_verts_perf,
             const unsigned nperfiles);
};

class Semiesfera: public MallaRevol
{
   public:
   // Constructor: crea el perfil original y llama a inicializar
   // La esfera tiene el centro en el origen, el radio es la unidad
   Semiesfera
   (
      const int num_verts_per,
      const unsigned nperfiles
   ) ;
};



class BocaPoligono : public MallaInd
{
    public:
        BocaPoligono();
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
        OjoPupila(float radio_pupila);
};

class CircunferenciaZ : public MallaInd
{
    public:
        // Circunferencia de radio r en el plano perpendicular al eje Z
        CircunferenciaZ(float r, vec3 color); 
};

class RectanguloZ: public MallaInd
{
    public:
        // Rectangulo en el plano perpendicular al eje Z
        RectanguloZ();
};

#endif // MODELO_JER_HPP