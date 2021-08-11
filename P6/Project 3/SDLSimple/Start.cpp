#pragma once
#include "Start.h"
#include "Util.h"


#define START_ENEMY_COUNT 1

#define START_WIDTH 1
#define START_HEIGHT 1
unsigned int start_data[] =
{
0
};


void Start::Initialize() {
	state.nextScene = -1;
	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(START_WIDTH, START_HEIGHT, start_data, mapTextureID, 1.0f, 4, 1);
	// Move over all of the player and enemy code from initialization.

	// Initialize Player
	state.player = new Entity();
	


}
void Start::Update(float deltaTime) {

}
void Start::Render(ShaderProgram *program) {
	
}

