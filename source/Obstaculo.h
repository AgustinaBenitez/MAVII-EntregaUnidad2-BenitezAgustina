#pragma once
#include "ObjetoFisico.h"

class Obstaculo : public ObjetoFisico {

private:

    float ancho, alto;

public:

    Obstaculo(b2World* mundo, b2Vec2 pos, float w, float h, Color c);
    void Dibujar() override;

};