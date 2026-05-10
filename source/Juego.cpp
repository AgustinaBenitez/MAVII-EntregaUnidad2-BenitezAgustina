#include "Juego.h"
#include "Suelo.h"

// Implementación del escuchador
EscuchadorColisiones::EscuchadorColisiones(Sound s) : sonidoObstaculos(s) {}

void EscuchadorColisiones::BeginContact(b2Contact* contacto) {
    PlaySound(sonidoObstaculos);
}

Juego::Juego() {

    // Inicializo gravedad
    b2Vec2 gravedad(0.0f, 9.8f);

    // Inicializo mundo físico
    mundo = std::make_unique<b2World>(gravedad);

}

void Juego::Iniciar() {

    InitWindow(1000, 600, "MAVII - Entrega Guía Unidad 2 - Benitez Agustina");

    InitAudioDevice();

    SetTargetFPS(60);

    // Cargo música de fondo
    musicaFondo = LoadMusicStream("assets/Loonboon.mp3");
    musicaFondo.looping = true;     // Para que se repita infinitamente
    PlayMusicStream(musicaFondo);   // Le doy Play solo acá (una sola vez)

    // Cargo los sonidos
    sonidoDisparo = LoadSound("assets/Splat.mp3");
    sonidoObstaculos = LoadSound("assets/Obstaculos.wav");

    // Configuro el escuchador de colisiones
    escuchador = std::make_unique<EscuchadorColisiones>(sonidoObstaculos);
    mundo->SetContactListener(escuchador.get());

    // Creo el suelo inicial (Cuerpo Estático)
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 500, 580 }, 0.0f, 1000.0f, 40.0f, b2_staticBody, DARKGRAY));

    // Cargo catapulta
    catapulta.Iniciar();

    // Creo proyectil en la parte inferior izquierda 
    //objetos.emplace_back(std::make_unique<Proyectil>(mundo.get(), b2Vec2{ 100, 350 }, 0.0f, 20.0f, b2_dynamicBody, GREEN));

    // Creo proyectil (el guisante). Lo guardo en una variable temporal para tener el puntero
    auto guisante = std::make_unique<Proyectil>(mundo.get(), b2Vec2{ 110, 420 }, 0.0f, 15.0f, b2_dynamicBody, GREEN);
    proyectilActual = guisante.get(); // Guardo la dirección de memoria
    objetos.emplace_back(std::move(guisante)); // Lo muevo al vector

}

void Juego::Actualizar() {

    UpdateMusicStream(musicaFondo); // OBLIGATORIO para que suene la música

    // Avanzo la simulación física
    mundo->Step(1.0f / 60.0f, 8, 3);

    // Creo proyectil al presionar ESPACIO
    if (IsKeyPressed(KEY_SPACE)) {

        PlaySound(sonidoDisparo);

        // Aplicamos el impulso (X positivo a la derecha, Y negativo hacia arriba)
        // El valor depende de la masa (densidad) [cite: 8, 9, 10, 269, 270]
        b2Vec2 impulso(1000.0f, -800.0f); // Ajustar estos números según la potencia que quieras
        proyectilActual->AplicarImpulso(impulso);

    }

}

void Juego::Renderizar() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Box2D calcula, Raylib dibuja el resultado visual
        for (const auto& obj : objetos) {
            obj->Dibujar();
        }

        //Dibujo la catapulta
        catapulta.Dibujar();

        //Dibujo los obstáculos

        // Muestro carteles e instrucciones

    EndDrawing();

}

Juego::~Juego() {

    // Limpio los objetos explícitamente AHORA.
    // Esto fuerza a que todos los DestroyBody se ejecuten mientras el mundo sigue vivo.
    objetos.clear();

    // Descargo los recursos de Raylib
    UnloadMusicStream(musicaFondo);
    UnloadSound(sonidoDisparo);
    UnloadSound(sonidoObstaculos);
    

}





