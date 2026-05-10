#include "Proyectil.h"

Proyectil::Proyectil(b2World* mundo, b2Vec2 pos, float ang, float rad, b2BodyType tipo, Color col)
    : ObjetoFisico(mundo, pos, ang, tipo, col) {

    radio = rad;

    // Defino la forma circular
    b2CircleShape formaCircular;
    formaCircular.m_radius = radio;
     
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

    // Le paso a Raylib la info de Box2D para representar el objeto
    DrawCircleV({ pos.x, pos.y },radio,ORANGE);

}
