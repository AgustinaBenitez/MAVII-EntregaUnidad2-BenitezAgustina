#include "Proyectil.h"

Proyectil::Proyectil(b2World* mundo, b2Vec2 pos, float ang, float w, float h, b2BodyType tipo, Color col)
    : ObjetoFisico(mundo, pos, ang, tipo, col) {

    ancho = w;
    alto = h;

    // Defino la forma circular
    b2CircleShape formaCircular;
    formaCircular.m_radius = 20.0f;
     
    // Defino las propiedades físicas mediante una fixture
    b2FixtureDef circuloFixture;
    circuloFixture.shape = &formaCircular;
    circuloFixture.density = 1.0f;
    circuloFixture.friction = 0.3f;
    circuloFixture.restitution = 0.6f;

    // Vinculo la forma al cuerpo
    cuerpo->CreateFixture(&circuloFixture);

}

void Proyectil::Dibujar() {

    // Obtengo el estado calculado por Box2D
    b2Vec2 pos = cuerpo->GetPosition();

    // Convierto para Raylib
    //float anguloGrados = cuerpo->GetAngle() * RAD2DEG;

    Vector2 origen = { ancho / 2.0f, alto / 2.0f };

    // Le paso a Raylib la info de Box2D para representar el objeto

    // circles.push_back({ circleBody, 20.0f, Fade(ORANGE, 0.95f) });

    DrawCircleV(origen,20.0f,ORANGE);
}
