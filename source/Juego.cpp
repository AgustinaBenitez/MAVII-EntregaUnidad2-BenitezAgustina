#include "Juego.h"
#include "Suelo.h"
#include "Obstaculo.h"

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

    // A partir del suelo me armo los límites de la pantalla

    // Pared Izquierda: x=10 (un poquito adentro), y=300 (mitad de alto), ancho=20, alto=600
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 10.0f, 300.0f }, 0.0f, 20.0f, 600.0f, b2_staticBody, DARKGRAY));

    // Pared Derecha: x=990, y=300, ancho=20, alto=600
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 990.0f, 300.0f }, 0.0f, 20.0f, 600.0f, b2_staticBody, DARKGRAY));

    // Techo: x=500 (mitad de ancho), y=10 (arriba), ancho=1000, alto=20
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 500.0f, 10.0f }, 0.0f, 1000.0f, 20.0f, b2_staticBody, DARKGRAY));

    // Cargo catapulta
    catapulta.Iniciar();

    // Creo proyectil (el guisante). Lo guardo en una variable temporal para tener el puntero
    auto guisante = std::make_unique<Proyectil>(mundo.get(), b2Vec2{ 131, 473 }, 0.0f, 15.0f, b2_dynamicBody, WHITE);
    proyectilActual = guisante.get(); // Guardo la dirección de memoria
    objetos.emplace_back(std::move(guisante)); // Lo muevo al vector

    ///////// Creo obstáculos

    for (int i = 0; i < 15; i++) {

        // Genero dimensiones (tamaños) aleatorias
        float randomW = (float)GetRandomValue(50, 80);
        float randomH = (float)GetRandomValue(40, 70);

        // Posición X aleatoria
        float randomX = (float)GetRandomValue(200, 900);
        
        // Cálculo de Y para que esté apoyado (Centro = Superficie - Mitad de su altura)
        float superficieSuelo = 560.0f; // El "piso" real de mi mundo
        float posY = superficieSuelo - (randomH / 2.0f);

        // Colores aleatorios --- Esto me ayudé de Gemini porque me estaba embrollando creando vector de colores
        Color colorAzar = { (unsigned char)GetRandomValue(50, 255),
                            (unsigned char)GetRandomValue(50, 255),
                            (unsigned char)GetRandomValue(50, 255), 255 };

        // Los meto al vector de objetos (uso b2_dynamicBody para que reaccionen al mundo físico)
        objetos.emplace_back(std::make_unique<Obstaculo>(mundo.get(), b2Vec2{ randomX, posY }, randomW, randomH, colorAzar, BLACK));

    }
}

void Juego::Actualizar() {

    UpdateMusicStream(musicaFondo); // OBLIGATORIO para que suene la música

    // Avanzo la simulación física
    mundo->Step(1.0f / 60.0f, 8, 3);

    // Creo proyectil al presionar ESPACIO
    if (IsKeyPressed(KEY_SPACE) && proyectilActual != nullptr) {

        PlaySound(sonidoDisparo);

        // Aplico el impulso (X positivo a la derecha, Y negativo hacia arriba)
        // El valor depende de la masa (densidad)
        b2Vec2 impulsoInicial(10000.0f, -5000.0f);
        
        // Ejecuto la acción en el objeto
        proyectilActual->AplicarImpulsoInicial(impulsoInicial);

        // Anulo la referencia para que sea un disparo único y no se pueda disparar dos veces
        proyectilActual = nullptr;

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





