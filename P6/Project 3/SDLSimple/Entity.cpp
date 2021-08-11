#include "Entity.h"


Entity::Entity()
{
    position = glm::vec3(0);
    
    modelMatrix = glm::mat4(1.0f);
}


bool Entity::CheckCollision(Entity *other) {
	if (other==NULL||isActive == false || other->isActive == false)return false;

	float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
	float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);

	if (xdist < 0 && ydist < 0) {
		lastcollision = other->entityType;
		return true;
	}

	return false;
}


void Entity::CheckCollisionsY(Map *map)
{
	// Probes for tiles
	glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
	glm::vec3 top_left = glm::vec3(position.x - (width / 2)+0.01f, position.y + (height / 2), position.z);
	glm::vec3 top_right = glm::vec3(position.x + (width / 2)-0.01f, position.y + (height / 2), position.z);

	glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2)+0.01f, position.y - (height / 2), position.z);
	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2)-0.01f, position.y - (height / 2), position.z);

	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
}

void Entity::CheckCollisionsX(Map *map)
{
	// Probes for tiles
	glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2)+0.01f, position.z);
	glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2)-0.01f, position.z);

	glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);
	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2)+0.02f, position.z);
	glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2)-0.02f, position.z);

	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}
	else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}
	else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}
	if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedRight = true;
	}
	else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.x > 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedRight = true;
	}
	else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.x> 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedBottom = true;
	}
}


bool Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
	bool return_value = false;

	for (int i = 0; i < objectCount; i++)
	{
		Entity *object = &objects[i];

		if (CheckCollision(object))
		{
			float ydist = fabs(position.y - object->position.y);
			float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
			if (velocity.y > 0) {
				position.y -= penetrationY;
				velocity.y = 0;
				return_value = true;
			}
			else if (velocity.y < 0) {
				position.y += penetrationY;
				velocity.y = 0;
				return_value = true;
			}
		}
	}
	return return_value;
}

bool Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
	bool return_value = false;
	for (int i = 0; i < objectCount; i++)
	{
		Entity *object = &objects[i];

		if (CheckCollision(object))
		{
			float xdist = fabs(position.x - object->position.x);
			float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
			if (velocity.x > 0) {
				position.x -= penetrationX;
				velocity.x = 0;
				return_value = true;
			}
			else if (velocity.x < 0) {
				position.x += penetrationX;
				velocity.x = 0;
				return_value = true;
			}
		}
	}
	return return_value;
}





void Entity::AISurrounder() {
	movement.x = enemy_x;
	movement.y = enemy_y;
	speed = 3.5;

}


void Entity::AI(Entity *player) {
	switch (aiType)
	{
		case SURROUNDER:
			AISurrounder();
		break;
	}
}


void Entity::Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map)
{


	collidedTop = false;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;


	if (!isActive) {
		return;
	}


	if (entityType == ENEMY) {

		AI(player);	

		velocity.x = movement.x * speed;
		velocity.y = movement.y * speed;
		velocity += acceleration * deltaTime;
    
		position.y += velocity.y * deltaTime; // Move on Y
		CheckCollisionsY(map);


		position.x += velocity.x * deltaTime; // Move on X
		CheckCollisionsX(map);

		if (collidedBottom || collidedRight || collidedLeft || collidedTop) {
			if (enemy_x < 0) {
				enemy_y = 0.5;
				enemy_x = 0;
			}else if (enemy_x > 0) {
				enemy_y = -0.5;
				enemy_x = 0;
			}
			else if (enemy_y > 0) {
				enemy_x = 0.5;
				enemy_y = 0;
			}
			else {
				enemy_x = -0.5;
				enemy_y = 0;
			}

		}



		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
		return;
	}
	else if (entityType == PLAYER) {
		if (animIndices != NULL) {
			if (glm::length(movement) != 0) {
				animTime += deltaTime;

				if (animTime >= 0.25f)
				{
					animTime = 0.0f;
					animIndex++;
					if (animIndex >= animFrames)
					{
						animIndex = 0;
					}
				}
			}
			else {
				animIndex = 0;
			}
		}

		if (jump) {
			jump = false;
			if (isJump != false) {
				return;
			}
			isJump = true;
			velocity.y = jumpPower;
		}
	}
	else if (entityType == KEY) {
		if (player->CheckCollisionsX(this, 1)) {
			player->door_open = true;
			isActive = false;
			return;
		}else if (player->CheckCollisionsY(this, 1)) {
			player->door_open = true;
			isActive = false;
			return;
		}
	}
	else if (entityType == DOOR) {
		if (player->CheckCollisionsX(this, 1)) {
			player->win = true;
		}
		if (player->CheckCollisionsY(this, 1)) {
			player->win = true;
		}
	}
    


	/*for (int i = 0; i < objectCount; i++) {
		if (CheckCollision(&objects[i])) {
			fail = true;
		}
	}*/

    
	velocity.x = movement.x * speed;
	velocity.y = movement.y * speed;
	velocity += acceleration * deltaTime;
    
	position.y += velocity.y * deltaTime; // Move on Y
	CheckCollisionsY(map);
	if (CheckCollisionsY(objects, objectCount)) {
		fail = true;
	}// Fix if needed

	position.x += velocity.x * deltaTime; // Move on X
	CheckCollisionsX(map);
	if (CheckCollisionsX(objects, objectCount)) {
		fail = true;
	}
	 // Fix if needed
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;
    
    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
	if (!isActive) {
		return;
	}


    program->SetModelMatrix(modelMatrix);
    
    if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}




