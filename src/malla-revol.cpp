// Nombre: Ricardo, Apellidos: Ruiz Fernández de Alba, Titulación: GIM
// email: ricardoruiz@correo.ugr.es, DNI: 77168601J

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias,  // número de copias del perfil
   const bool semi
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 


   vector<glm::vec3> aristas;
   vector<float> d_i;

   // Aristas
   for (size_t i=0; i < perfil.size()-1; i++)
   {
      aristas.push_back(perfil[i+1]-perfil[i]);
      d_i.push_back(glm::length(aristas[i]));
   }

   float suma_distancias = 0.0;
   for (size_t i=0; i < d_i.size(); i++)
      suma_distancias += d_i[i];


   vector<float> t_i;

   // Calculo de las coordenadas de texturas
   float suma_d_j;
   for (size_t i=0; i < perfil.size(); i++)
   {
      suma_d_j = 0.0;
      for (uint j=0; j < i; j++)
         suma_d_j += d_i[j];
      
      t_i.push_back(suma_d_j / suma_distancias);
   }

   vector<glm::vec3> normales_aristas;
   // Calculo de las normales de las aristas del perfil
   for (size_t i=0; i < aristas.size(); i++)
   {
      glm::vec3 normal_arista = vec3(aristas[i].y, -aristas[i].x, 0);

      if (glm::length(normal_arista) != 0.0)
         normal_arista = glm::normalize(normal_arista);

      normales_aristas.push_back(normal_arista);
   }

   // Cálculo de las normales de los vértices del perfil
   vector<glm::vec3> normales_vertices;
   glm::vec3 normal_vertice;

   // n_0 = m_0
   normales_vertices.push_back(normales_aristas[0]);
   for (size_t i=1; i < perfil.size()-1; i++)
   {
      
      normal_vertice = normales_aristas[i-1]+normales_aristas[i];

      // Modulo 1
      if (glm::length(normal_vertice) != 0.0)
         normal_vertice = glm::normalize(normal_vertice);

      normales_vertices.push_back(normal_vertice);
   }
   // n_{n-1} = m_{n-2}
   normales_vertices.push_back(normales_aristas[perfil.size()-2]);
   
   for (size_t i=0; i < num_copias; i++)
   {
      float theta;
      if (!semi) // Complete circunference Default
         theta = 2.0*M_PI*float(i) / float(num_copias -1);
      else
         theta = M_PI*float(i) / float(num_copias -1);

      for (size_t j=0; j < perfil.size(); j++)
      {
         
         float r = perfil[j].x;
         float x_rot = r*cos(theta);
         float y_rot = perfil[j].y;
         float z_rot = -r*sin(theta);
         vec3 vert_rot(x_rot, y_rot, z_rot);

         vertices.push_back(vert_rot);

         // Rotacion de la normal
         float r_normal = normales_vertices[j].x;
         float x_normal_rot = r_normal*cos(theta);
         float y_normal_rot = normales_vertices[j].y;
         float z_normal_rot = -r_normal*sin(theta);
         vec3 normal_rot(x_normal_rot, y_normal_rot, z_normal_rot);

         // Modulo 1
         if (glm::length(normal_rot) != 0.0)
            normal_rot = glm::normalize(normal_rot);
         
         nor_ver.push_back(normal_rot);

         // Coordenadas de textura
         float s = float(i) / (num_copias-1);
         float t = 1 - t_i[j];
         vec2 cc_tt_ver_actual(s,t);

         cc_tt_ver.push_back(cc_tt_ver_actual);
      }
   }

   for (size_t i=0; i < num_copias-1; i++)
   {
      for (size_t j=0; j < perfil.size()-1; j++)
      {
         unsigned int m = perfil.size();
         unsigned int k = i*m+ j; 
         uvec3 triangulo_1(k, k+m, k+m+1),
               triangulo_2(k, k+m+1, k+1);
               
         triangulos.push_back(triangulo_1);
         triangulos.push_back(triangulo_2);
      }
   }

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

Cilindro::Cilindro
(
   const int num_verts_perf,
   const unsigned nperfiles
)
{
   ponerNombre( std::string("cilindro por revolución del perfil") );
   std::vector<glm::vec3> perfil;

   for (int i=0; i < num_verts_perf; i++)
   {
      float k = float(i)/(num_verts_perf-1);
      perfil.push_back(glm::vec3(1, k, 0));
   }

   inicializar(perfil, nperfiles);

}


Cono::Cono
(
   const int num_verts_perf,
   const unsigned nperfiles
)
{
   ponerNombre( std::string("cono por revolución del perfil") );
   std::vector<glm::vec3> perfil;
   
   for (int i=0; i < num_verts_perf; i++)
   {
      float k = float(i)/(num_verts_perf-1);
      perfil.push_back(glm::vec3(1-k, k, 0));
   }

   inicializar(perfil, nperfiles);
}

Esfera::Esfera
(
   const int num_verts_perf,
   const unsigned nperfiles
)
{
   ponerNombre( std::string("esfera por revolución del perfil") );
   std::vector<glm::vec3> perfil;

   for (int i=0; i < num_verts_perf; i++)
   {
      float alpha = -M_PI / 2.0 + float(i) / (num_verts_perf -1) * M_PI;
      perfil.push_back(glm::vec3(cos(alpha), sin(alpha), 0));
   }

   inicializar(perfil, nperfiles);
}

Toro::Toro
(
   const int n_p,  // Poligono regular de n_p vértices
   const float r_p,   // Radio del polígono regular
   const float r_t,   // Centrado a distancia r_t 
   const unsigned n_t // Numero de copias
)
{
   assert(r_p > 0 && r_t > 0);
   assert(n_p > 2 && n_t > 2);

   ponerNombre( std::string("toro por revolución del perfil") );
   std::vector<glm::vec3> perfil;

   float angulo;
   for (int i = 0; i <= n_p; i++)
   {
      angulo = 2.0f*M_PI * i/ n_p;
      perfil.push_back({r_t+r_p*cosf(angulo),r_p*sinf(angulo), 0});
   }  

   inicializar(perfil, n_t);
}