// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 

using namespace std;

// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')

   if (tieneColor()) {
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
  
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //
   if (dvao == nullptr) {
      DescrVBOAtribs* p_dvbo_posiciones = new DescrVBOAtribs(ind_atrib_posiciones, vertices);

      dvao = new DescrVAO(numero_atributos_cauce, p_dvbo_posiciones);

      DescrVBOInds* indices_triangulos = new DescrVBOInds(triangulos);
      dvao->agregar(indices_triangulos);

      if (!col_ver.empty()) {
         DescrVBOAtribs* colores = new DescrVBOAtribs(ind_atrib_colores, col_ver);
         dvao->agregar(colores);
      } 
      
      if (!nor_ver.empty()) {
         DescrVBOAtribs* norm = new DescrVBOAtribs(ind_atrib_normales, nor_ver);
         dvao->agregar(norm);
      } 
      if (!cc_tt_ver.empty()) {
         DescrVBOAtribs* text = new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver);
         dvao->agregar(text);
      } 

      dvao->crearVAO();
   }

   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'

   dvao->draw(GL_TRIANGLES);

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
   if (tieneColor())
      cauce->popColor();



}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
   //    2. Dibujar la malla (únicamente visualizará los triángulos)
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   // ....
   if (!col_ver.empty())
      dvao->habilitarAtrib(ind_atrib_colores, false);
   
   if (!nor_ver.empty())
      dvao->habilitarAtrib(ind_atrib_normales, false);

   if (!cc_tt_ver.empty())
      dvao->habilitarAtrib(ind_atrib_coord_text, false);

   dvao->draw(GL_TRIANGLES);

   if (!col_ver.empty())
      dvao->habilitarAtrib(ind_atrib_colores, true);
   
   if (!nor_ver.empty())
      dvao->habilitarAtrib(ind_atrib_normales, true);

   if (!cc_tt_ver.empty())
      dvao->habilitarAtrib(ind_atrib_coord_text, true);
}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo(const std::string& nombre)
:  MallaInd()
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
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

// ****************************************************************************
// Clase CuboColores
CuboColores::CuboColores()
: Cubo("Cubo Colores 8 vértices")
{

   col_ver =
      {
         { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, +1.0 }, // 1
         { 0.0, +1.0, 0.0 }, // 2
         { 0.0, +1.0, +1.0 }, // 3
         { +1.0, 0.0, 0.0 }, // 4
         { +1.0, 0.0, +1.0 }, // 5
         { +1.0, +1.0, 0.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      };
   triangulos =
      {  
         {4,5,6}, {5,6,7}, // X+ (+4)
         {2,3,6}, {3,6,7}, // Y+ (+2)
         {1,3,5}, {3,5,7},  // Z+ (+1)
         {0,1,3}, {0,3,2}, // X-
         {0,5,1}, {0,4,5}, // Y-
         {0,6,4}, {0,2,6}, // Z-
      } ;

}


// ****************************************************************************
// Clase Tetraedro

Tetraedro::Tetraedro()
: MallaInd("tetraedo 4 vértices")
{


   vertices =
      {  { -0.75, 0.0, -0.5 }, // 0
         { +0.75, 0.0, -0.5 }, // 1
         { +0.0, 0.0, +0.75 }, // 2
         {  0.0, 0.75, 0.0 }, // 3
      } ;

   triangulos = 
      {
         {0, 1, 2}, {0, 1, 3},
         {0, 2, 3}, {1, 2, 3}
      };
   
   ponerColor({0.69, 0.055, 0.404});

}
// -----------------------------------------------------------------------------------------------

EstrellaZ::EstrellaZ(unsigned int n)
: MallaInd(string("estrella en plano XY de ") + to_string(n) + string(" puntas"))
{
   // Centro de la estrella de color blanco
   vertices.push_back({0.5, 0.5, 0});
   col_ver.push_back({1.0, 1.0, 1.0});


   for (unsigned int i=0; i < n; i++)
   {
      // Vértices de las puntas
      float alpha = 2.0*float(i)*M_PI / n;
      glm::vec3 v_punta(0.5 + 0.5*cos(alpha), 0.5+0.5*sin(alpha), 0);

      vertices.push_back(v_punta);
      col_ver.push_back(v_punta); // RGB a partir de coordenadas

      // Vértices intermedios (Ángulo mitad entre dos puntas)
      float theta = M_PI * (2*float(i)+1)/ n;
      glm::vec3 v_inter(0.5 + 0.5/3*cos(theta), 0.5 + 0.5/3*sin(theta), 0);

      vertices.push_back(v_inter);
      col_ver.push_back(v_inter);
   }

   
   for (unsigned int i=1; i < 2*n; i++)
      triangulos.push_back({0, i, i+1});

   // Triangulo con el origen
   triangulos.push_back({0, 2*n, 1});


}

// Variantes

EstrellaX::EstrellaX(unsigned int n)
: MallaInd(string("estrella en plano YZ de ") + to_string(n) + string(" puntas"))
{
   // Centro de la estrella de color blanco
   vertices.push_back({0, 0.5, 0.5 });
   col_ver.push_back({1.0, 1.0, 1.0});


   for (unsigned int i=0; i < n; i++)
   {
      // Vértices de las puntas
      float alpha = 2.0*float(i)*M_PI / n;
      glm::vec3 v_punta(0, 0.5 + 0.5*cos(alpha), 0.5+0.5*sin(alpha));

      vertices.push_back(v_punta);
      col_ver.push_back(v_punta); // RGB a partir de coordenadas

      // Vértices intermedios (Ángulo mitad entre dos puntas)
      float theta = M_PI * (2*float(i)+1)/ n;
      glm::vec3 v_inter(0, 0.5 + 0.5/3*cos(theta), 0.5 + 0.5/3*sin(theta));

      vertices.push_back(v_inter);
      col_ver.push_back(v_inter);
   }

   
   for (unsigned int i=1; i < 2*n; i++)
      triangulos.push_back({0, i, i+1});

   // Triangulo con el origen
   triangulos.push_back({0, 2*n, 1});
}

EstrellaY::EstrellaY(unsigned int n)
: MallaInd(string("estrella en el eje XZ de ") + to_string(n) + string(" puntas"))
{
   // Centro de la estrella de color blanco
   vertices.push_back({0.5, 0, 0.5 });
   col_ver.push_back({1.0, 1.0, 1.0});


   for (unsigned int i=0; i < n; i++)
   {
      // Vértices de las puntas
      float alpha = 2.0*float(i)*M_PI / n;
      glm::vec3 v_punta(0.5 + 0.5*cos(alpha), 0, 0.5+0.5*sin(alpha));

      vertices.push_back(v_punta);
      col_ver.push_back(v_punta); // RGB a partir de coordenadas

      // Vértices intermedios (Ángulo mitad entre dos puntas)
      float theta = M_PI * (2*float(i)+1)/ n;
      glm::vec3 v_inter(0.5 + 0.5/3*cos(theta), 0, 0.5 + 0.5/3*sin(theta));

      vertices.push_back(v_inter);
      col_ver.push_back(v_inter);
   }

   
   for (unsigned int i=1; i < 2*n; i++)
      triangulos.push_back({0, i, i+1});

   // Triangulo con el origen
   triangulos.push_back({0, 2*n, 1});
}

// -----------------------------------------------------------------------------------------------

CasaX::CasaX()
: MallaInd("casa de colores con tejado a dos aguas")
{
   vertices =
      {  {  0.0,  0.0,  0.0 }, // 0
         {  0.0,  0.0, +0.5 }, // 1
         {  0.0, +0.5,  0.0 }, // 2
         {  0.0, +0.5, +0.5 }, // 3
         { +0.8,  0.0,  0.0 }, // 4
         { +0.8,  0.0, +0.5 }, // 5
         { +0.8, +0.5,  0.0 }, // 6
         { +0.8, +0.5, +0.5 }, // 7
         // Tejado
         { +0.8, +0.75,  0.25 }, // 8
         {  0.0, +0.75,  0.25 }  // 9
      } ;
      
   col_ver =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, +1.0 }, // 1
         { 0.0, +1.0, 0.0 }, // 2
         { 0.0, +1.0, +1.0 }, // 3
         { +1.0, 0.0, 0.0 }, // 4
         { +1.0, 0.0, +1.0 }, // 5
         { +1.0, +1.0, 0.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         // Tejado
         { +1.0, +1.0, 0.0 },
         {  0.0, +1.0, 0.0 }
      } ;
    

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)

         // Tejado
         {3,7,8}, {3,8,9},
         {6,7,8}, {2,3,9},
         {2,6,8}, {2,8,9}
      } ;
}

// -----------------------------------------------------------------------------------------------

MallaTriangulo::MallaTriangulo()
: MallaInd("malla para un triángulo de base 1 y altura raíz 2")
{
   vertices = 
         {
            {-0.5, 0, 0},
            {+0.5, 0, 0},
            { 0, sqrt(2), 0}
         };
   triangulos = {{0,1,2}};
}


MallaCuadrado::MallaCuadrado()
: MallaInd("malla para un cuadrado de lado 2 con centro en el origen")
{
   vertices =
         {
            {-1, -1, 0},
            {-1, +1, 0},
            {+1, -1, 0},
            {+1, +1, 0}
         };

   triangulos =
         {
            {0,1,2}, {1,2,3}
         };
}

MallaPiramideL::MallaPiramideL()
: MallaInd("malla para una pirámide con base en forma de L")
{
   vertices =
         {
            {-0.5, 0.0, 0.0}, // 0
            {-0.5, 0.0, 1.0}, // 1
            { 0.0, 0.0, 0.5}, // 2
            { 0.0, 0.0, 1.0}, // 3
            { 1.0, 0.0, 0.0}, // 4
            { 1.0, 0.0, 0.5}, // 5
            { -0.25, 1.0, 0.25} // 6
         };

   triangulos = 
         {
            {0,1,2}, {1,2,3},
            {0,2,4}, {2,4,5},
            {0,1,6}, {1,3,6},
            {2,3,6}, {2,5,6},
            {4,5,6}, {0,4,6}
         };
}