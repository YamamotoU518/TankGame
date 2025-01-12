#pragma once
#include "../dxe/dxe.h"
#include "bullet.h"
#include "tank.h"
#include "skybox.h"

class GameManager {
private:
	GameManager() {}
	static Shared<GameManager> instance_;

public:
	std::list<Shared<GameObject>> objects;
	std::list<Shared<Bullet>> bullets;

	static Shared<GameManager> GetInstance();
};