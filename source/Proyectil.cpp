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
    circuloFixture.density = 0.1f;
    circuloFixture.friction = 0.3f;
    circuloFixture.restitution = 2.0f;

    // Vinculo la forma al cuerpo
    cuerpo->CreateFixture(&circuloFixture);

    // Desactivo la gravedad inicial para que el proyectil se mantenga quieto, listo para ser disparado
    //Para que no se "caiga" de la catapulta antes de tiempo
    cuerpo->SetGravityScale(0.0f);

}

Proyectil::~Proyectil() {

    UnloadTexture(texturaGuisante);

}

void Proyectil::AplicarImpulsoInicial(b2Vec2 impulso) {

    // Le "devuelvo" la gravedad para que haga la parábola
    cuerpo->SetGravityScale(1.0f);

    // Aplico el impulso al centro para producir el cambio inmediato en la velocidad
    cuerpo->ApplyLinearImpulseToCenter(impulso, true);

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
