#pragma once


#include <vector>
#include <memory> // Para usar los Smart Pointers
#include "Proyectil.h"
#include "Catapulta.h"

class Juego {

private:

    std::unique_ptr<b2World> mundo;                     // El mundo físico que va a ser el contenedor principal
    std::vector<std::unique_ptr<ObjetoFisico>> objetos; // Lista de objetos que se actualizan y dibujan

    // Audio
    //Music musicaFondo;
    //Sound sonido1;
    //Sound sonido2;

    // Objetos
    Catapulta catapulta();

public:

    Juego();
    ~Juego();

    void Iniciar();
    void Actualizar(); // Maneja Step() e Input
    void Renderizar(); // Dibuja la escena

};

