#pragma once
#include "End.h"
#include "Util.h"


#define END_ENEMY_COUNT 1

#define END_WIDTH 1
#define END_HEIGHT 1
unsigned int end_data[] =
{
0
};


void End::Initialize() {
	state.nextScene = -1;
	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(END_WIDTH, END_HEIGHT, end_data, mapTextureID, 1.0f, 4, 1);
	// Move over all of the player and enemy code from initialization.

	// Initialize Player
	state.player = new Entity();



}
void End::Update(float deltaTime) {

}
void End::Render(ShaderProgram *program) {

}

