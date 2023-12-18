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
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 40));
    agregar(tapa);
    cuerpo->agregar(new MallaRevolPLY("lata-pcue.ply", 40));
    agregar(cuerpo);
}

LataPeones::LataPeones()
{   
    NodoGrafoEscena* lata = new NodoGrafoEscena();
    lata->agregar(new Lata("lata-coke.jpg"));
    agregar(lata);

  // MallaRevolPLY* peon = new MallaRevolPLY("peon.ply", 17) ;
  // agregar()
}
