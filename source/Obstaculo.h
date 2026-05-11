#pragma once
#include "ObjetoFisico.h"

class Obstaculo : public ObjetoFisico {

private:

    float ancho, alto;
    Color color2; // Segundo color para hacer un degradé

public:

    Obstaculo(b2World* mundo, b2Vec2 pos, float w, float h, Color c1, Color c2);
    void Dibujar() override;

};