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

Peon::Peon()
{
    agregar(scale(vec3(0.2, 0.2, 0.2)));
    unsigned tras = agregar(translate(vec3(0, 0, 0)));
    agregar(new MallaRevolPLY("peon.ply", 40));

    pm_tras = leerPtrMatriz(tras);
}

bool Peon::cuandoClick(const vec3& centro_oc)
{
    *pm_tras = translate(vec3(0.0, 0.0, 1.0));
    return true;
}

LataPeones::LataPeones()
{   
    NodoGrafoEscena* lata = new NodoGrafoEscena();
    lata->agregar(new Lata("lata-coke.jpg"));
    agregar(lata);

    NodoGrafoEscena* peon1 = new NodoGrafoEscena();
    peon1->agregar(translate(vec3(0, 0.2, 1)));

    Textura* textura_madera = new Textura("text-madera.jpg");
    Material* material_madera = new Material(textura_madera, 0.1, 1.0, 1.0, 100.0);

    peon1->agregar(material_madera);
    Peon* peon_madera = new Peon();
    peon_madera->ponerNombre("Peon de madera");
    peon_madera->ponerIdentificador(1);

    peon1->agregar(peon_madera);
    agregar(peon1);


    NodoGrafoEscena* peon2 = new NodoGrafoEscena();
    peon2->agregar(translate(vec3(0.0, 0.2, 1)));
    // Material blanco
    peon2->agregar(new Material(0.2, 1.0, 0.0, 5.0));

    Peon* peon_blanco = new Peon();
    peon_blanco->ponerNombre("Peon blanco");
    peon_blanco->ponerIdentificador(2);

    peon2->agregar(peon_blanco);

    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(peon2); 

    NodoGrafoEscena* peon3 = new NodoGrafoEscena();
    // Material negro
    peon3->agregar(translate(vec3(0.0, 0.2, 1)));
    peon3->agregar(new Material(0.01, 0.1, 1.0, 100));

    Peon* peon_negro = new Peon();
    peon_negro->ponerNombre("Peon negro");
    peon_negro->ponerIdentificador(3);
    peon3->agregar(peon_negro);

    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(peon3); 

}

VariasLatasPeones::VariasLatasPeones()
{   
    NodoGrafoEscena* lata1 = new NodoGrafoEscena();
    lata1->ponerNombre("Lata de Coca-Cola");
    lata1->ponerIdentificador(1);
    lata1->agregar(new Lata("lata-coke.jpg"));
    agregar(lata1);

    NodoGrafoEscena* lata2 = new NodoGrafoEscena();
    lata2->ponerNombre("Lata de Pepsi");
    lata2->ponerIdentificador(2);
    lata2->agregar(translate(vec3(1, 0, 0)));
    lata2->agregar(new Lata("lata-pepsi.jpg"));
    agregar(lata2);

    NodoGrafoEscena* lata3 = new NodoGrafoEscena();
    lata3->ponerNombre("Lata de la UGR");
    lata3->ponerIdentificador(3);
    lata3->agregar(translate(vec3(2, 0, 0)));
    lata3->agregar(new Lata("window-icon.jpg"));
    agregar(lata3);

 
    NodoGrafoEscena* peon1 = new NodoGrafoEscena();
    peon1->agregar(translate(vec3(0, 0.2, 1)));

    Textura* textura_madera = new Textura("text-madera.jpg");
    Material* material_madera = new Material(textura_madera, 0.1, 1.0, 1.0, 100.0);

    peon1->agregar(material_madera);
    Peon* peon_madera = new Peon();
    peon_madera->ponerNombre("Peon de madera");
    peon_madera->ponerIdentificador(4);

    peon1->agregar(peon_madera);
    agregar(peon1);


    NodoGrafoEscena* peon2 = new NodoGrafoEscena();
    peon2->agregar(translate(vec3(0.0, 0.2, 1)));
    // Material blanco
    peon2->agregar(new Material(0.2, 1.0, 0.0, 5.0));

    Peon* peon_blanco = new Peon();
    peon_blanco->ponerNombre("Peon blanco");
    peon_blanco->ponerIdentificador(5);

    peon2->agregar(peon_blanco);

    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(peon2); 

    NodoGrafoEscena* peon3 = new NodoGrafoEscena();
    // Material negro
    peon3->agregar(translate(vec3(0.0, 0.2, 1)));
    peon3->agregar(new Material(0.01, 0.1, 1.0, 100));

    Peon* peon_negro = new Peon();
    peon_negro->ponerNombre("Peon negro");
    peon_negro->ponerIdentificador(6);
    peon3->agregar(peon_negro);

    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(peon3); 

}
