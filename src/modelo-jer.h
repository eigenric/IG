// Nombre: Ricardo, Apellidos: Ruiz Fernández de Alba, Titulación: GIM
// email: ricardoruiz@correo.ugr.es, DNI: 77168601J

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"

using namespace glm;

class Motherboard : public NodoGrafoEscena
{
protected:
    float angulo_cabeza_inicial, angulo_cuello_inicial;
    unsigned int num_parametros = 3;
    unsigned int cabeza;
    mat4x4 *pm_rotacion_cuello = nullptr;
    mat4x4 *pm_rotacion_cabeza = nullptr;

public:
    Motherboard(float angulo_cuello_inicial, float angulo_cabeza_inicial);
    unsigned int leerNumParametros() const;
    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
    void fijarRotacionCabeza(const float angulo_cabeza);
    void fijarRotacionCuello(const float angulo_cuello);
};

class BaseMotherboard : public MallaInd
{
public:
    BaseMotherboard();
};

class Cuello : public NodoGrafoEscena
{
public:
    Cuello();
};

class Cabeza : public NodoGrafoEscena
{
protected:
    unsigned int num_parametros = 1;
    unsigned int ojo_izq, ojo_der;

public:
    Cabeza();
    unsigned int leerNumParametros() const;
    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
};

class Pelo : public NodoGrafoEscena
{
public:
    Pelo();
};

class Rizos : public MallaRevol
{
public:
    Rizos(const int num_verts_perf,
          const unsigned nperfiles);
};

class Semiesfera : public MallaRevol
{
public:
    // Constructor: crea el perfil original y llama a inicializar
    // La esfera tiene el centro en el origen, el radio es la unidad
    Semiesfera(
        const int num_verts_per,
        const unsigned nperfiles);
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
protected:
    mat4x4 *pm_posicion_ojo = nullptr;
    float pos_ojo_inicial = 0.0;
    unsigned num_parametros = 1;

public:
    OjoIzquierdo(float pos_ojo_inicial);
    unsigned leerNumParametros() const;
    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
    void fijarPosicionOjo(const float pos_ojo);
};

class OjoPupila : public NodoGrafoEscena
{
protected:
    unsigned num_parametros = 1;
    float pos_pupila_inicial = 0.0;
    mat4x4 *pm_posicion_pupila = nullptr;

public:
    OjoPupila(float radio_pupila, float pos_pupila_inicial);
    unsigned leerNumParametros() const;
    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
    void fijarPosicionPupila(const float pos_pupila);
};

class CircunferenciaZ : public MallaInd
{
public:
    // Circunferencia de radio r en el plano perpendicular al eje Z
    CircunferenciaZ(float r, vec3 color);
};

#endif // MODELO_JER_HPP