#pragma once
#include "ObjetoFisico.h"

class Proyectil : public ObjetoFisico {

private:

    float radio;
    Texture2D texturaGuisante;

public:

    Proyectil(b2World* mundo, b2Vec2 pos, float ang, float rad, b2BodyType tipo, Color col);
    ~Proyectil();

    void AplicarImpulso(b2Vec2 impulso);
    void Dibujar() override; // "Override" recomendado por Gemini siempre que esté heredando

};