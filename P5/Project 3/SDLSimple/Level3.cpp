#include "Level3.h"

#define LEVEL3_ENEMY_COUNT 1

#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8
unsigned int level3_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};


void Level3::Initialize() {
	state.nextScene = -1;
	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
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


	state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
	GLuint enemyTextureID = Util::LoadTexture("ctg2.png");

	state.enemies[0].entityType = ENEMY;
	state.enemies[0].textureID = enemyTextureID;
	state.enemies[0].position = glm::vec3(3, -2.25f, 0);
	state.enemies[0].speed = 1;
	state.enemies[0].isActive = true;

	state.enemies[0].aiType = WALKER;

}
void Level3::Update(float deltaTime) {
	state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);

	if (state.player->position.x >= 12) {
		
	}

}
void Level3::Render(ShaderProgram *program) {
	state.map->Render(program);
	state.player->Render(program);
}

