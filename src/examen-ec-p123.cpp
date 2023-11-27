// Nombre: Ricardo, Apellidos: Ruiz Fernández de Alba, Titulación: GIM
// email: ricardoruiz@correo.ugr.es, DNI: 77168601J

#include "examen-ec-p123.h"

using namespace std;

P1MallaCubo::P1MallaCubo()
: MallaInd("P1 Malla Cubo")
{

    vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         // Nuevos vértices
         { +0.0, -1.0, +0.0},  // 8
         { +0.0, +1.0, +0.0},  // 9
    } ;

   col_ver =
      {
         { +1.0, +1.0, +1.0 }, // 0
         { +1.0, +1.0, +1.0 }, // 1
         { +1.0, +1.0, +1.0 }, // 2
         { +1.0, +1.0, +1.0 }, // 3
         { +1.0, +1.0, +1.0 }, // 4
         { +1.0, +1.0, +1.0 }, // 5
         { +1.0, +1.0, +1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         // Colores nuevos vértices
         { +0.0, +1.0, +1.0},
         { +1.0, 0.0, 0.0}
      };


   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {5,4,7}, {4,6,7}, // X+ (+4)

         // Cara Inferior
         {0,1,8}, {1,5,8},
         {4,8,5}, {0,8,4},

         // Cara Superior
         {2,3,9}, {3,7,9},
         {7,6,9}, {2,9,6},

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}


P2Rejilla::P2Rejilla(unsigned int n, unsigned int m)
: MallaInd("malla para una rejilla escalada en el plano XZ de dimensión " + to_string(n) + "x" + to_string(m))
{
   assert( n > 1 && m > 1 );

   for (unsigned int i=0; i < m; i++)
   {
      for (unsigned int j=0; j < n; j++)
      {
        float factor = 1 + 3*float(i)/(m-1);
         vertices.push_back({factor*float(j)/(n-1), 0, 1.4*float(i)/(m-1)});
      }
   }

   for (unsigned int i=0; i < m-1; i++)
   {
      for (unsigned int j=0; j < n-1; j++)
      {
        if ( (i+j) % 2 == 0)
        {
            triangulos.push_back({i*n+j, (i+1)*n+j, (i+1)*n+j+1});
            triangulos.push_back({i*n+j, (i+1)*n+j+1, i*n+j+1});
        } else {
            triangulos.push_back({i*n+j, (i+1)*n+j, i*n+j+1});
            triangulos.push_back({i*n+j+1, (i+1)*n+j, (i+1)*n+j+1});
        }
      }
   }
}

P3Cuadrado::P3Cuadrado()
{
    vertices = {
        {-1.0, 0.0, -1.0},
        {-1.0, 0.0, +1.0},
        {+1.0, 0.0, -1.0},
        {+1.0, 0.0, +1.0}
    };

    triangulos = {
        {0,1,3}, {0, 3, 2}
    };
}

P3Caja::P3Caja()
{
    NodoGrafoEscena* cara = new NodoGrafoEscena();
    P3Cuadrado* cuadrado = new P3Cuadrado();
    cara->agregar(scale(vec3(0.5, 1.0, 1.0)));
    cara->agregar(cuadrado);

    // Cara Inferior
    agregar(cara);
    agregar(translate(vec3(1.0, 0.0, 0.0)));
    agregar(cara);

    // Cara Derecha
    agregar(rotate(float(M_PI)/2.0f, vec3(0.0, 0.0, 1.0)));
    agregar(translate(vec3(0.5, -0.5, 0.0)));
    agregar(cara);

    // Cara Izquierda
    agregar(translate(vec3(0.0, 2.0, 0.0)));
    agregar(cara);

    // Cara Trasera
    agregar(rotate(float(M_PI)/2.0f, vec3(1.0, 0.0, 0.0)));
    agregar(translate(vec3(0.0, 1.0, 1.0)));
    agregar(cara);

    // Cara Delantera
    agregar(translate(vec3(0.0, -2.0, 0.0)));
    agregar(cara);


    NodoGrafoEscena* esferaInterior = new NodoGrafoEscena();
    esferaInterior->agregar(scale(vec3(0.35, 0.35, 0.35)));
    esferaInterior->agregar(new Esfera(50, 20));

    agregar(translate(vec3(0.0, 1.0, 0.0)));
    unsigned int ind_posicion_esfera = agregar(translate(vec3(0.0, 0.0, 0.0)));
    agregar(esferaInterior);

    agregar(rotate(float(M_PI)/2.0f, vec3(0.0, 0.0, 1.0)));
    agregar(translate(vec3(-0.5, -0.5, 0.0)));
    //unsigned int ind_rot_puerta1 = agregar(rotate(float(M_PI)/2.0f, vec3(0.0, 0.0, 1.0)));
    agregar(cara);

    agregar(translate(vec3(1.0, 0, 0.0)));
    agregar(cara);

    pm_posicion_esfera = leerPtrMatriz(ind_posicion_esfera);

}


unsigned int P3Caja::leerNumParametros() const
{
    return num_parametros;
}

void P3Caja::fijarPosicionEsfera(const float posicion_esfera)
{
    *pm_posicion_esfera = translate(vec3(0.0, posicion_esfera, 0.0));
}

// void P3Caja::fijarRotacionApertura(const float angulo_apertura)
// {
//     *pm_rotacion_apertura = rotate(0.0f, vec3(0.0, 1.0, 0.0));
// }

void P3Caja::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros() -1);
    
    switch(iParam)
    {
        case 0:
        {
            float v_min = 0, v_max = 1.0;
            float a = 0;
            float b = (v_max - v_min) / 2;
            float n = 1;
            fijarPosicionEsfera(a+b*sin(2*M_PI*n*t_sec));
            break;
        }
    }
}