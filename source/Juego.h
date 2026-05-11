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

    // Mundo físico (contenedor) + objetos
    std::unique_ptr<b2World> mundo;
    std::vector<std::unique_ptr<ObjetoFisico>> objetos;

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
    void Actualizar();
    void Renderizar();
    void Reiniciar();

};

