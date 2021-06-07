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
glm::mat4 viewMatrix, modelMatrix, apple1Matrix, apple2Matrix, apple3Matrix, projectionMatrix;

float player_y = 0.0f;
float player_up = 1.0f;
float player_rotate = 0;

GLuint playerTextureID;
GLuint player2TextureID;

GLuint LoadTexture(const char* filePath) {
	int w, h, n;
	unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

	if (image == NULL) {
		std::cout << "Unable to load image. Make sure the path is correct\n";
		assert(false);
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(image);
	return textureID;
}

void Initialize() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Textured!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
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


	playerTextureID = LoadTexture("ctg.png");
	player2TextureID = LoadTexture("apple.png");
}

void ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			gameIsRunning = false;
		}
	}
}

float lastTicks = 0.0f;

void Update() { 
	
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;


	if (player_y > 2.5f) {
		player_up = -1.0f;
	}
	else if (player_y < -2.5f) {
		player_up = 1.0f;
	}

	player_y += 1.5f * player_up * deltaTime;

	player_rotate += 90.0f * deltaTime;


	modelMatrix = glm::mat4(1.0f);
	apple1Matrix = glm::mat4(1.0f);
	apple2Matrix = glm::mat4(1.0f);
	apple3Matrix = glm::mat4(1.0f);

	
	apple1Matrix = glm::translate(apple1Matrix, glm::vec3(-2.0f, 2.0f, 0.0f));
	apple1Matrix = glm::rotate(apple1Matrix, glm::radians(player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	apple1Matrix = glm::scale(apple1Matrix, glm::vec3(0.7f, 0.7f, 1.0f));

	apple2Matrix = glm::translate(apple2Matrix, glm::vec3(-2.0f, 0.0f, 0.0f));
	apple2Matrix = glm::rotate(apple2Matrix, glm::radians(-player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	apple2Matrix = glm::scale(apple2Matrix, glm::vec3(0.7f, 0.7f, 1.0f));

	apple3Matrix = glm::translate(apple3Matrix, glm::vec3(-2.0f, -2.0f, 0.0f));
	apple3Matrix = glm::rotate(apple3Matrix, glm::radians(-player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	apple3Matrix = glm::scale(apple3Matrix, glm::vec3(0.7f, 0.7f, 1.0f));
	
	
	
	modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, player_y, 0.0f));


	


	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.001f, 0.0f));
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(1.001f, 1.001f, 1.001f));
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
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
	glBindTexture(GL_TEXTURE_2D, playerTextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//single texture
	program.SetModelMatrix(apple1Matrix);
	glBindTexture(GL_TEXTURE_2D, player2TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//single texture
	program.SetModelMatrix(apple2Matrix);
	glBindTexture(GL_TEXTURE_2D, player2TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//single texture
	program.SetModelMatrix(apple3Matrix);
	glBindTexture(GL_TEXTURE_2D, player2TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);


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
