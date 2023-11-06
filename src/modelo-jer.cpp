#include "modelo-jer.h"
#include "malla-ind.h"

using namespace glm;

Motherboard::Motherboard(float angulo_cuello_inicial, float angulo_cabeza_inicial)
{
    agregar(new BaseMotherboard() );

    angulo_cuello_inicial = angulo_cuello_inicial;
    angulo_cabeza_inicial = angulo_cabeza_inicial;
    
    unsigned int ind_rot_cuello = agregar(rotate(radians(angulo_cuello_inicial), vec3(1.0, 0.0, 0.0)));
    agregar(new Cuello());

    agregar(translate(vec3(0, 0.1, 0.0)));
    unsigned int ind_rot_cabeza = agregar(rotate(radians(angulo_cabeza_inicial), vec3(0.0, 1.0, 0.0)));
    
    cabeza = agregar(new Cabeza() );

    pm_rotacion_cuello = leerPtrMatriz(ind_rot_cuello);
    pm_rotacion_cabeza = leerPtrMatriz(ind_rot_cabeza);

}

unsigned int Motherboard::leerNumParametros() const
{
    return num_parametros;
}

void Motherboard::fijarRotacionCuello(float angulo_cuello)
{
    *pm_rotacion_cuello = rotate(radians(angulo_cuello), vec3(1.0, 0.0, 0.0));
}

void Motherboard::fijarRotacionCabeza(float angulo_cabeza)
{
    *pm_rotacion_cabeza = rotate(radians(angulo_cabeza), vec3(0.0, 1.0, 0.0));
}


void Motherboard::actualizarEstadoParametro(unsigned int iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros() -1);

    switch(iParam)
    {
        // Rotacion oscilante alrededor del eje X del cuello
        case 0: 
        {
            float v_min = -15.0f, v_max = 15.0f;
            float a = angulo_cuello_inicial;
            float b = (v_max - v_min) / 2;
            float n = 0.5;
            fijarRotacionCuello(a+b*sin(2*M_PI*n*t_sec));
            break;
        }
        // Rotacion oscilante alrededor del eje Y de la cabeza
        case 1: 
        {
            float v_min = -30.0f, v_max = 30.0f;
            float a = angulo_cabeza_inicial;
            float b = (v_max - v_min) / 2;
            float n = 0.75;
            fijarRotacionCabeza(a+b*sin(2*M_PI*n*t_sec));
            break;
        }
        // Para el movimiento de las pupilas delega en actualizarEstadoParametro de Cabeza
        case 2:
            ((Cabeza*)(entradas[cabeza].objeto))->actualizarEstadoParametro(0, t_sec);
            break;
    }

}

BaseMotherboard::BaseMotherboard()
{
    vertices = 
        {
            {-0.3, 0.0, -0.3},  // 0
            {+0.3, 0.0, -0.3},  // 1
            {-0.3, 0.0, +0.3},  // 2
            {+0.3, 0.0, +0.3},  // 3
            {-0.2, +0.3, -0.2}, // 4
            {+0.2, +0.3, -0.2}, // 5
            {-0.2, +0.3, +0.2}, // 6 
            {+0.2, +0.3, +0.2}  // 7
        };

    triangulos =
        {
            {0,2,3}, {0,1,3},
            {4,6,7}, {4,5,7},
            {2,6,7}, {2,3,7},
            {1,3,7}, {1,5,7},
            {0,1,5}, {0,4,5},
            {0,2,4}, {2,4,6}
        };

    ponerColor({0, 0, 0.7});

}

Cuello::Cuello()
{
    agregar(scale(vec3(0.132, 0.132, 0.132)));
    agregar(translate(vec3(0.0, 1.12, 0.0)));
    agregar(new Cilindro(10, 20));
    agregar(translate(vec3(0.0, 1.0, 0.0)));
    agregar(new Cilindro(10, 20));


    ponerColor({0.2823,0.2392,0.545});
}


Cabeza::Cabeza()
{
    agregar( scale(vec3(0.5, 0.5, 0.2)) );
    agregar( translate(vec3(0.0, 1.6, 0.0)) );
    agregar( new Cubo() );
    
    agregar( scale(vec3(1.2, 1.2, 1.2)) );
    agregar( translate(vec3(0.0, -0.25, 0.0)) );
    agregar( new Pelo() );

    agregar( new Boca() );
    agregar( new Nariz() );

    agregar( translate(vec3(-0.4, 0.5, 0.85)) );
    agregar( scale(vec3(1.0, 1.0, 4.16)) );
    ojo_izq = agregar( new OjoPupila(0.1, 0.0) );
    agregar( translate(vec3(0.8, 0.0, 0.0)) );
    ojo_der = agregar( new OjoPupila(0.1, 0.0) );

    ponerColor(vec3(0.6, 0.6, 1.0));
}

unsigned int Cabeza::leerNumParametros() const {
    return num_parametros;
} 


void Cabeza::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert( iParam <= leerNumParametros()-1 );

    switch(iParam) {
        case 0:
            ((OjoPupila*)(entradas[ojo_izq].objeto))->actualizarEstadoParametro(0, t_sec);
            ((OjoPupila*)(entradas[ojo_der].objeto))->actualizarEstadoParametro(0, t_sec);
            break;
    }
}

Pelo::Pelo()
{
    agregar( scale(vec3(1.0, 1.0, 2.0)) );
    agregar( translate(vec3(0.0, 0.75, 0.0)) );
    agregar( new Semiesfera(10, 50) );

    agregar( scale(vec3(0.35, 2, 0.5)) );
    agregar( translate(vec3(0.0, -1.0, 0.75)) );
    agregar( new Rizos(50, 20) );

    ponerColor({0, 0.6, 0.8});

}

Rizos::Rizos
(
    const int num_verts_perf, 
    const unsigned int nperfiles
)
{
    std::vector<glm::vec3> perfil;

    for (int i=0; i < num_verts_perf; i++)
    {
        float k = float(i)/(num_verts_perf-1);
        perfil.push_back(vec3(3.0+0.2*cos(36*k), k, 0.0));
    }

    inicializar(perfil, nperfiles, true);
}

Semiesfera::Semiesfera
(
   const int num_verts_perf,
   const unsigned nperfiles
)
{
   ponerNombre( std::string("semi esfera por revolución del perfil") );
   std::vector<glm::vec3> perfil;

   for (int i=0; i < num_verts_perf; i++)
   {
      float alpha =  M_PI / 2.0 * float(i) / (num_verts_perf -1);
      perfil.push_back(glm::vec3(cos(alpha), sin(alpha), 0));
   }

   inicializar(perfil, nperfiles);

}

Boca::Boca()
{
    agregar( translate(vec3(0.0, -0.25, 0.85)) );
    agregar( scale(vec3(0.2, 0.1, 0.2)) );
    agregar( new BocaPoligono() );
}

BocaPoligono::BocaPoligono()
{
    vertices = 
        {
            {-1.0, +1.0, 0.0},
            {+1.0, +1.0, 0.0},
            {-2.0, 0.0, 0.0},
            {-1.0, -1.0, 0.0},
            {+1.0, -1.0, 0.0},
            {+2.0, 0.0, 0.0},

            {-0.5, +0.5, 0.0},
            {+0.5, +0.5, 0.0},
            {-1.0, 0.0, 0.0},
            {-0.5, -0.5, 0.0},
            {+0.5, -0.5, 0.0},
            {+1.0, 0.0, 0.0}
        };

    triangulos =
        {  
            {0,2,6},{6,2,8},
            {8,2,3},{3,9,8},
            {9,3,4},{4,10,9},
            {4,5,10},{10,5,11},
            {11,5,1},{1,7,11},
            {1,0,7},{7,0,6}
        };

    ponerColor({0,0,1});
}

Nariz::Nariz()
{
    agregar( translate(vec3(0, 0, 0.85)) );
    agregar( scale(vec3(0.3, 0.5, 0.5)) );
    agregar(new Tetraedro({0.0, 0.0, 1.0}));
}

unsigned OjoPupila::leerNumParametros() const {
    return num_parametros;
}

OjoPupila::OjoPupila(float radio_pupila, float pos_pupila_inicial)
{  
    agregar(new CircunferenciaZ(radio_pupila*3, {0,0,1}));

    pos_pupila_inicial = pos_pupila_inicial;
    unsigned ind = agregar( translate(vec3(pos_pupila_inicial, 0.0, 0.05)) );
    
    agregar(new CircunferenciaZ(radio_pupila, {0,0,0}));

    pm_posicion_pupila = leerPtrMatriz(ind);
}


void OjoPupila::fijarPosicionPupila(const float pos_pupila)
{
    *pm_posicion_pupila = translate(vec3(pos_pupila, 0.0, 0.05) );
}

void OjoPupila::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros() -1);
    
    switch(iParam)
    {
        case 0:
            float v_min = -0.15, v_max = 0.15;
            float a = pos_pupila_inicial;
            float b = (v_max - v_min) / 2;
            float n = 1;
            fijarPosicionPupila(a+b*sin(2*M_PI*n*t_sec));
            break;
    }
}

CircunferenciaZ::CircunferenciaZ(float r, vec3 color)
{

    unsigned int num_verts = 10;

    vertices.push_back(vec3(0, 0, 0));
    for (unsigned int i=0; i < num_verts; i++)
    {
      float alpha = 2.0 * M_PI * float(i) / (num_verts -1);
      vertices.push_back(glm::vec3(r*cos(alpha), r*sin(alpha), 0));
    }

    for (unsigned int i=1; i < 2*num_verts; i++)
      triangulos.push_back({0, i, i+1});

   // Triangulo con el origen
   triangulos.push_back({0, 2*num_verts, 1});

   ponerColor(color);
   
}
