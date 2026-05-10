#include "Juego.h"

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
    //musicaFondo = LoadMusicStream("assets/musicaFondo.mp3");
    //musicaFondo.looping = true;     // Para que se repita infinitamente
    //PlayMusicStream(musicaFondo);   // Le doy Play solo acá (una sola vez)

    // Cargo los sonidos
    //sonido1 = LoadSound("assets/generarCaja.wav");
    //sonido2 = LoadSound("assets/caidaCaja.wav");


    // Creo el suelo inicial (Cuerpo Estático)
    objetos.emplace_back(std::make_unique<Proyectil>(mundo.get(), b2Vec2{ 500, 580 }, 0.0f, 1000.0f, 40.0f, b2_staticBody, DARKGRAY));

    // Cargo catapulta
    catapulta.Iniciar();

}

void Juego::Actualizar() {

    // UpdateMusicStream(musicaFondo); // OBLIGATORIO para que suene la música

    // Avanzo la simulación física
    mundo->Step(1.0f / 60.0f, 8, 3);

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
    //UnloadSound(sonidoGenerarCaja);
    //UnloadSound(sonidoCaidaCaja);
    //UnloadMusicStream(musicaFondo);

}





