#pragma once
#include "raylib.h"

class Catapulta {

private:

	// Textura para la catapulta
	Texture2D texturaCatapulta;

	////// Propiedades

	Vector2 posicionCatapulta;
	float escalaCatapulta;

public:

	Catapulta();
	~Catapulta();

	void Iniciar();
	void Dibujar();


};

