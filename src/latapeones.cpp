// Nombre: Ricardo, Apellidos: Ruiz Fernández de Alba, Titulación: GIM
// email: ricardoruiz@correo.ugr.es, DNI: 77168601J


#include "latapeones.h"

Lata::Lata(const std::string& nombreArchivoJPG)
{
    NodoGrafoEscena* base = new NodoGrafoEscena();
    NodoGrafoEscena* cuerpo = new NodoGrafoEscena();
    NodoGrafoEscena* tapa = new NodoGrafoEscena();

    Material* material_tapa_base = new Material(0.5, 1.0, 1.0, 100.0);
    tapa->agregar(material_tapa_base);
    base->agregar(material_tapa_base);

    Textura* textura_cuerpo = new Textura(nombreArchivoJPG);
    Material* material_cuerpo = new Material(textura_cuerpo, 0.5, 1.0, 1.0, 100.0);
    cuerpo->agregar(material_cuerpo);

    base->agregar(new MallaRevolPLY("lata-pinf.ply", 40));
    agregar(base);
    cuerpo->agregar(new MallaRevolPLY("lata-pcue.ply", 40));
    agregar(cuerpo);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 40));
    agregar(tapa);
}

LataPeones::LataPeones()
{   
    NodoGrafoEscena* lata = new NodoGrafoEscena();
    lata->agregar(new Lata("lata-coke.jpg"));
    agregar(lata);

    MallaRevolPLY* peon = new MallaRevolPLY("peon.ply", 17) ;
    Textura* textura_madera = new Textura("text-madera.jpg");
    Material* material_madera = new Material(textura_madera, 0.1, 1.0, 1.0, 100.0);

    agregar(scale(vec3(0.25, 0.25, 0.25)));
    agregar(translate(vec3(0, 1.5, 3.0)));

    agregar(material_madera);
    agregar(peon);

    agregar(translate(vec3(2.25, 0, 0)));
    Material* material_blanco = new Material(0.1, 1.0, 0.0, 100.0);
    agregar(material_blanco);
    agregar(peon);

    agregar(translate(vec3(2.25, 0.0, 0.0)));
    Material* material_negro = new Material(0.1, 0.1, 1.0, 100.0);
    agregar(material_negro);
    agregar(peon);

}
