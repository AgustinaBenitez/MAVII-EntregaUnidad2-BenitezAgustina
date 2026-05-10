#include "Proyectil.h"

Proyectil::Proyectil(b2World* mundo, b2Vec2 pos, float ang, float rad, b2BodyType tipo, Color col)
    : ObjetoFisico(mundo, pos, ang, tipo, col) {

    radio = rad;

    // Cargo la textura del guisante
    texturaGuisante = LoadTexture("assets/PvZ - Repeater Pea.png");
    SetTextureFilter(texturaGuisante, TEXTURE_FILTER_BILINEAR);

    // Defino la forma circular
    b2CircleShape formaCircular;
    formaCircular.m_radius = radio;
     
    // Defino las propiedades físicas mediante una fixture
    b2FixtureDef circuloFixture;
    circuloFixture.shape = &formaCircular;
    circuloFixture.density = 0.05f;
    circuloFixture.friction = 0.3f;
    circuloFixture.restitution = 0.6f;

    // Vinculo la forma al cuerpo
    cuerpo->CreateFixture(&circuloFixture);

}

Proyectil::~Proyectil() {

    UnloadTexture(texturaGuisante);

}

void Proyectil::AplicarImpulso(b2Vec2 impulso) {

    cuerpo->ApplyLinearImpulseToCenter(impulso, true); // Para cambiar inmediatamente la velocidad

}

void Proyectil::Dibujar() {

    // Obtengo el estado calculado por Box2D
    b2Vec2 pos = cuerpo->GetPosition();
    float angulo = cuerpo->GetAngle() * RAD2DEG;

    // Defino el origen, el destino y el centro de rotación
    Rectangle source = { 0, 0, (float)texturaGuisante.width, (float)texturaGuisante.height };
    Rectangle dest = { pos.x, pos.y, radio * 2, radio * 2 };
    Vector2 centro = { radio, radio };

    // Le paso a Raylib la info de Box2D para representar el objeto
    DrawTexturePro(texturaGuisante, source, dest, centro, angulo, WHITE);

}
