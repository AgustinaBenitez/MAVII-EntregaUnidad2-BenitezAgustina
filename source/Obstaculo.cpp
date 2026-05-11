#include "Obstaculo.h"

Obstaculo::Obstaculo(b2World* mundo, b2Vec2 pos, float w, float h, Color c)
    : ObjetoFisico(mundo, pos, 0.0f, b2_dynamicBody, c) {

    ancho = w;
    alto = h;

    b2PolygonShape forma;
    forma.SetAsBox(w / 2.0f, h / 2.0f);

    b2FixtureDef fixture;
    fixture.shape = &forma;
    fixture.density = 0.1f;     
    fixture.friction = 1.0f;
    fixture.restitution = 1.0f;

    cuerpo->CreateFixture(&fixture);

}

void Obstaculo::Dibujar() {

    b2Vec2 pos = cuerpo->GetPosition();
    float angulo = cuerpo->GetAngle() * RAD2DEG;

    Rectangle rec = { pos.x, pos.y, ancho, alto };
    Vector2 origen = { ancho / 2.0f, alto / 2.0f };

    // Dibujo los obstáculos
    DrawRectanglePro(rec, origen, angulo, color);
    
}