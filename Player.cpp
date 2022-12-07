#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "Player.h"

void Player::setPlayerDepth(float externalPlayerDepth)
{
	playerDepth = externalPlayerDepth;
}

float Player::getPlayerDepth()
{
	return playerDepth;
}

void Player::setPlayerForwardLocation(float externalPlayerForwardLocation)
{
	playerForwardLocation = externalPlayerForwardLocation;
}

float Player::getPlayerForwardLocation()
{
	return playerForwardLocation;
}

void Player::setPlayerBackwardLocation(float externalPlayerBackwardLocation)
{
	playerBackwardLocation = externalPlayerBackwardLocation;
}

float Player::getPlayerBackwardLocation()
{
	return playerBackwardLocation;
}

void Player::setPlayerLeftLocation(float externalPlayerLeftLocation)
{
	playerLeftLocation = externalPlayerLeftLocation;
}

float Player::getPlayerLeftLocation()
{
	return playerLeftLocation;
}

void Player::setPlayerRightLocation(float externalPlayerRightLocation)
{
	PlayerRightLocation = externalPlayerRightLocation;
}

float Player::getPlayerRightLocation()
{
	return PlayerRightLocation;
}

void Player::setPlayerUpLocation(float externalPlayerUpLocation)
{
	playerUpLocation = externalPlayerUpLocation;
}

float Player::getPlayerUpLocation()
{
	return playerUpLocation;
}

void Player::setPlayerDownLocation(float externalPlayerDownLocation)
{
	playerDownLocation = externalPlayerDownLocation;
}

float Player::getPlayerDownLocation()
{
	return playerDownLocation;
}
