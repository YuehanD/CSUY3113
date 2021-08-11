#include "Level1.h"

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 12
unsigned int level1_data[] =
{
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 3,
 3, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 2, 0, 3,
 3, 2, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 3,
 3, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 3,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 3,
 3, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 3,
 3, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

#define LEVEL1_ENEMY_COUNT 2


void Level1::Initialize() {
	state.nextScene = -1;
	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
	// Move over all of the player and enemy code from initialization.

	// Initialize Player
	state.player = new Entity();
	//state.player->modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
	state.player->position = glm::vec3(5, -3.0f, 0);
	state.player->movement = glm::vec3(0);
	state.player->acceleration = glm::vec3(0, 0, 0);
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


	state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
	GLuint enemyTextureID = Util::LoadTexture("ctg.png");
	state.enemies[0].textureID = enemyTextureID;
	state.enemies[0].position = glm::vec3(1, -1.0f, 0);
	state.enemies[0].movement = glm::vec3(0);
	state.enemies[0].acceleration = glm::vec3(0);
	state.enemies[0].entityType = ENEMY;

	state.enemies[1].textureID = enemyTextureID;
	state.enemies[1].position = glm::vec3(1, -5.0f, 0);
	state.enemies[1].movement = glm::vec3(0);
	state.enemies[1].acceleration = glm::vec3(0);
	state.enemies[1].entityType = ENEMY;

	state.enemies[0].aiType = SURROUNDER;
	state.enemies[0].aiState = CLOCKWISE;

	state.enemies[1].aiType = SURROUNDER;
	state.enemies[1].aiState = CLOCKWISE;

	state.key = new Entity();
	GLuint keyTextureID = Util::LoadTexture("key.png");
	state.key->textureID = keyTextureID;
	state.key->position = glm::vec3(1, -10.0f, 0);
	state.key->entityType = KEY;

	state.door = new Entity();
	GLuint closeTextureID = Util::LoadTexture("close.png");
	state.door->textureID = closeTextureID;
	state.door->position = glm::vec3(12, -1, 0);
	state.door->entityType = DOOR;

}
void Level1::Update(float deltaTime) {
	state.player->Update(deltaTime, state.player, &state.enemies[0], LEVEL1_ENEMY_COUNT, state.map);
	state.enemies[0].Update(deltaTime, state.player, &state.enemies[0], 0, state.map);
	state.enemies[1].Update(deltaTime, state.player, &state.enemies[1], 0, state.map);
	state.key->Update(deltaTime, state.player, NULL, 0, state.map);
	state.door->Update(deltaTime, state.player, NULL, 0, state.map);

	/*if (state.player->position.x >= 12) {
		state.nextScene = 2;
	}*/

	if (state.player->door_open == true) {
		if (!state.door->door_open) {
			GLuint openTextureID = Util::LoadTexture("open.png");
			state.door->textureID = openTextureID;
			state.door->door_open = true;
		}
	}

	if (state.player->win == true) {
		state.nextScene = 2;
	}
}
void Level1::Render(ShaderProgram *program) {
	state.map->Render(program);
	state.player->Render(program);
	state.enemies[0].Render(program);
	state.enemies[1].Render(program);
	state.key->Render(program);
	state.door->Render(program);
}

