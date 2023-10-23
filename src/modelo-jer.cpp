#include "modelo-jer.h"
#include "malla-ind.h"

using namespace glm;

Motherboard::Motherboard()
{

    agregar(new BaseMotherboard() );
    agregar(new Cabeza() );
}

unsigned int Motherboard::leerNumParametros() const
{
    return 0;
}

void Motherboard::actualizarEstadoParametro(unsigned int iParam, const float t_sec)
{
    std::cout << "Actualizado el estado del parametro..." << std::endl;

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

}

Cabeza::Cabeza()
{
    agregar( scale(vec3(0.5, 0.5, 0.25)) );
    agregar( translate(vec3(0.0, 1.6, 0.0)) );
    agregar( new Cubo() );

    agregar( new Boca() );
    agregar( new Nariz() );
    agregar( new OjoIzquierdo() );
    agregar( new OjoDerecho() );
}

Boca::Boca()
{
    std::cout << "Dibujando boca" << std::endl;

}

Nariz::Nariz()
{
    std::cout << "Dibujando nariz" << std::endl;
}

OjoIzquierdo::OjoIzquierdo()
{
    std::cout << "Dibujando ojo izquierdo" << std::endl;

}

OjoDerecho::OjoDerecho()
{
    std::cout << "Dibujando ojo derecho" << std::endl;

}

OjoPupila::OjoPupila()
{
    std::cout << "Dibujando ojo y pupila" << std::endl;
}