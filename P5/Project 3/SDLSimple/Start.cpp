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
	//state.player->modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
	state.player->position = glm::vec3(5, 0.0f, 0);
	state.player->movement = glm::vec3(0);
	state.player->acceleration = glm::vec3(0, -10.81f, 0);
	state.player->speed = 2.2f;
	state.player->textureID = Util::LoadTexture("mdr.png");



	state.player->animRight = new int[4]{ 8, 9, 10, 11 };
	state.player->animLeft = new int[4]{ 4, 5, 6, 7 };
	state.player->animUp = new int[4]{ 12, 13, 14, 15 };
	state.player->animDown = new int[4]{ 0, 1, 2, 3 };

	state.player->animIndices = state.player->animRight;
	state.player->animFrames = 4;
	state.player->animIndex = 0;
	state.player->animTime = 0;
	state.player->animCols = 4;
	state.player->animRows = 4;

	state.player->height = 0.8f;
	state.player->width = 0.5f;
	state.player->entityType = PLAYER;


	state.player->jumpPower = 5.2f;
	state.player->entityType = PLAYER;


	state.enemies = new Entity[START_ENEMY_COUNT];
	GLuint enemyTextureID = Util::LoadTexture("ctg2.png");

	state.enemies[0].entityType = ENEMY;
	state.enemies[0].textureID = enemyTextureID;
	state.enemies[0].position = glm::vec3(3, -2.25f, 0);
	state.enemies[0].speed = 1;
	state.enemies[0].isActive = true;

	state.enemies[0].aiType = WALKER;

}
void Start::Update(float deltaTime) {

}
void Start::Render(ShaderProgram *program) {
	
}

