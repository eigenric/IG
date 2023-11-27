// Nombre: Ricardo, Apellidos: Ruiz Fernández de Alba, Titulación: GIM
// email: ricardoruiz@correo.ugr.es, DNI: 77168601J

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"


class P1MallaCubo : public MallaInd
{
   public:
      P1MallaCubo();
};

class P2Rejilla: public MallaInd
{
   public:
      P2Rejilla(unsigned int n, unsigned int m);
};

class P3Cuadrado: public MallaInd
{
    public:
        P3Cuadrado();
};

class P3Caja: public NodoGrafoEscena
{
    protected:
        // Se ha implementado la animacion de la esfera
        unsigned int num_parametros = 1;
        mat4x4 *pm_rotacion_apertura = nullptr;
        mat4x4 *pm_posicion_esfera = nullptr;

    public:
        P3Caja();
        unsigned int leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        void fijarRotacionApertura(const float angulo_apertura);
        void fijarPosicionEsfera(const float posicion_esfera);
};

#endif