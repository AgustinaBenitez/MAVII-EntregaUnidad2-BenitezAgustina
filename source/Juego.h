#pragma once

#include <vector>
#include <memory> // Para usar los Smart Pointers
#include "Proyectil.h"
#include "Catapulta.h"

// Escuchador de colisiones para los golpes de los obstáculos
class EscuchadorColisiones : public b2ContactListener {

private:

    Sound sonidoObstaculos;

public:

    EscuchadorColisiones(Sound s);
    void BeginContact(b2Contact* contacto) override;

};

class Juego {

private:

    std::unique_ptr<b2World> mundo;                     // El mundo físico que va a ser el contenedor principal
    std::vector<std::unique_ptr<ObjetoFisico>> objetos; // Lista de objetos que se actualizan y dibujan

    // Audio + escuchador
    Music musicaFondo;
    Sound sonidoDisparo;
    Sound sonidoObstaculos;
    std::unique_ptr<EscuchadorColisiones> escuchador;

    // Objetos
    Catapulta catapulta;
    Proyectil* proyectilActual = nullptr; // Referencia para el disparo

public:

    Juego();
    ~Juego();

    void Iniciar();
    void Actualizar(); // Maneja Step() e Input
    void Renderizar(); // Dibuja la escena

};

