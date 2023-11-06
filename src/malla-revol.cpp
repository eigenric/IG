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
      perfil.push_back(glm::vec3(k, 1-k, 0));
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