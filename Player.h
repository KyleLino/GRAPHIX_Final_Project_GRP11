#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#pragma once
class Player
{
private:
	float playerDepth = 0.0f;
	float playerForwardLocation = 0.0f;
	float playerBackwardLocation = 0.0f;
	float playerLeftLocation = 0.0f;
	float PlayerRightLocation = 0.0f;
	float playerUpLocation = 0.0f;
	float playerDownLocation = 0.0f;

public:
	void setPlayerDepth(float externalPlayerDepth);
	float getPlayerDepth();
	void setPlayerForwardLocation(float externalPlayerForwardLocation);
	float getPlayerForwardLocation();
	void setPlayerBackwardLocation(float externalPlayerBackwardLocation);
	float getPlayerBackwardLocation();
	void setPlayerLeftLocation(float externalPlayerLeftLocation);
	float getPlayerLeftLocation();
	void setPlayerRightLocation(float externalPlayerRightLocation);
	float getPlayerRightLocation();
	void setPlayerUpLocation(float externalPlayerUpLocation);
	float getPlayerUpLocation();
	void setPlayerDownLocation(float externalPlayerDownLocation);
	float getPlayerDownLocation();
};
