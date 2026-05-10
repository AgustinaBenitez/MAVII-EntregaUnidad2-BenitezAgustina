#pragma once
#include "ObjetoFisico.h"

class Proyectil : public ObjetoFisico {

private:

    float ancho, alto;

public:

    Proyectil(b2World* mundo, b2Vec2 pos, float ang, float w, float h, b2BodyType tipo, Color col);
    void Dibujar() override; // "Override" recomendado por Gemini siempre que esté heredando

};