#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

enum EntityType{PLAYER, PLATFORM, ENEMY};

enum AIType{WALKER, JUMPER, ATTACKER};
enum AIState {NORMAL};

class Entity {
public:

	EntityType entityType;
	AIType aiType;
	AIState aiState;

	EntityType lastcollision;
	bool isActive=true;

	bool isJump = false;

	glm::vec3 position;
	glm::vec3 movement;
	glm::vec3 acceleration;
	glm::vec3 velocity;

	float width = 1;
	float height = 1;

	bool jump = false;
	float jumpPower = 0;

	float speed = 1;

	GLuint textureID;

	glm::mat4 modelMatrix;

	int *animRight = NULL;
	int *animLeft = NULL;
	int *animUp = NULL;
	int *animDown = NULL;

	int *animIndices = NULL;
	int animFrames = 0;
	int animIndex = 0;
	float animTime = 0;
	int animCols = 0;
	int animRows = 0;

	Entity();

	bool CheckCollision(Entity *other);
	void CheckCollisionsY(Entity *objects, int objectCount);
	void CheckCollisionsX(Entity *objects, int objectCount);
	void Update(float deltaTime, Entity *platforms, int platformCount);
	void Render(ShaderProgram *program);
	void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
};
