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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, leftMatrix, rightMatrix, projectionMatrix;

// Start at 0, 0, 0
glm::vec3 left_position = glm::vec3(0.0f, 0.0f, 0.0f);
// Don¡¯t go anywhere (yet).
glm::vec3 left_movement = glm::vec3(0, 0.0f, 0);

// Start at 0, 0, 0
glm::vec3 right_position = glm::vec3(0.0f, 0.0f, 0.0f);
// Don¡¯t go anywhere (yet).
glm::vec3 right_movement = glm::vec3(0, 0, 0);

// Start at 0, 0, 0
glm::vec3 ball_position = glm::vec3(0.0f, 0.0f, 0.0f);
// Don¡¯t go anywhere (yet).
glm::vec3 ball_movement = glm::vec3(1.0f, 1.0f, 0);

float player_speed = 5.0f;

const int thickness = 3;




void Initialize() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 480);

	program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

	viewMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);

	projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

	program.SetProjectionMatrix(projectionMatrix);
	program.SetViewMatrix(viewMatrix);
	//program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	glUseProgram(program.programID);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glEnable(GL_BLEND);
	// Good setting for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void ProcessInput() {
	left_movement = glm::vec3(0);
	right_movement = glm::vec3(0);

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
		case SDL_WINDOWEVENT_CLOSE:
			gameIsRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				// Move the left up
				
				break;

			case SDLK_s:
				
				// Move the left down
				break;
			case SDLK_UP:
				// Move the right up
				break;
			case SDLK_DOWN:
				// Move the right down
				break;
			}
			break; // SDL_KEYDOWN
		}
	}

	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) {
		left_movement.y = 1.0f;
	}
	if (keys[SDL_SCANCODE_S]) {
		left_movement.y = -1.0f;
	}
	if (keys[SDL_SCANCODE_UP]) {
		right_movement.y = 1.0f;
	}
	if (keys[SDL_SCANCODE_DOWN]) {
		right_movement.y = -1.0f;
	}
}

float lastTicks = 0.0f;

void Update() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;
	// Add (direction * units per second * elapsed time)
	left_position += left_movement * player_speed * deltaTime;
	right_position += right_movement * player_speed * deltaTime;
	ball_position += ball_movement * player_speed * deltaTime;




	modelMatrix = glm::mat4(1.0f);
	leftMatrix = glm::mat4(1.0f);
	rightMatrix = glm::mat4(1.0f);

	leftMatrix = glm::translate(rightMatrix, glm::vec3(-4.5f, 0.0f, 0.0f));
	leftMatrix = glm::translate(leftMatrix, left_position);
	leftMatrix = glm::scale(leftMatrix, glm::vec3(0.4f, 2.5f, 1.0f));

	rightMatrix = glm::translate(rightMatrix, glm::vec3(4.5f, 0.0f, 0.0f));
	rightMatrix = glm::translate(rightMatrix, right_position);
	rightMatrix = glm::scale(rightMatrix, glm::vec3(0.4f, 2.5f, 1.0f));





	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, ball_position);

	if (ball_position.y >= 7.0f)
	{
		if (ball_movement.y > 0) {
			ball_movement.y *= -1;
		}
	}
	else if (ball_position.y <=	-7.0f)
	{
		if (ball_movement.y < 0) {
			ball_movement.y *= -1;
		}
	}

	if (ball_position.x >= 8.3f) {
		//ball_movement.x = 0;
		//ball_movement.y = 0;
		ball_movement.x *= -1;
	}
	else if (ball_position.x <= -9.6f) {
		//ball_movement.x = 0;
		//ball_movement.y = 0;
		if (ball_movement.x < 0) {
			ball_movement.x *= -1;
		}
	}



	if (((modelMatrix[3].x) >= (rightMatrix[3].x - 0.35f)) && (((modelMatrix[3].y + 0.25f) <= (rightMatrix[3].y + 1.0f)) && ((modelMatrix[3].y - 0.25f) >= (rightMatrix[3].y - 1.0f)))) {
		ball_movement.x *= -1;
	}

	if (((modelMatrix[3].x) <= (leftMatrix[3].x + 0.35f)) && (((modelMatrix[3].y + 0.25f) <= (leftMatrix[3].y + 1.0f)) && ((modelMatrix[3].y - 0.25f) >= (leftMatrix[3].y - 1.0f)))) {
		ball_movement.x *= -1; 
	}


	

}


void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);

	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program.texCoordAttribute);


	//single texture
	program.SetModelMatrix(modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//single texture
	program.SetModelMatrix(leftMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//single texture
	program.SetModelMatrix(rightMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 6);



	SDL_Rect Wall{
		0,
		0,
		1024,
		thickness
	};


	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);

	SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
	SDL_Quit();
}



int main(int argc, char* argv[]) {
	Initialize();

	while (gameIsRunning) {
		ProcessInput();
		Update();
		Render();
	}

	Shutdown();
	return 0;
}
