#include "Catapulta.h"
#include "Juego.h"

Catapulta::Catapulta() {

	// Inicializo textura en cero para evitar warnings
	texturaCatapulta = { 0 };

}

Catapulta::~Catapulta() {

	UnloadTexture(texturaCatapulta);

}

void Catapulta::Iniciar() {

	// Propiedades
	escalaCatapulta = 0.15f;
	posicionCatapulta = { 70, 365 };

	// Cargo textura
	texturaCatapulta = LoadTexture("assets/texturaCatapulta.png");
	SetTextureFilter(texturaCatapulta, TEXTURE_FILTER_BILINEAR);

}

void Catapulta::Dibujar() {

	DrawTextureEx(texturaCatapulta, posicionCatapulta, 0.0f, escalaCatapulta, WHITE);

}