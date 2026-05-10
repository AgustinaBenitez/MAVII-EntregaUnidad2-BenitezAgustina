#pragma once
#include "ObjetoFisico.h"

class Proyectil : public ObjetoFisico {

private:

    float radio;

public:

    Proyectil(b2World* mundo, b2Vec2 pos, float ang, float rad, b2BodyType tipo, Color col);
    void Dibujar() override; // "Override" recomendado por Gemini siempre que esté heredando

};