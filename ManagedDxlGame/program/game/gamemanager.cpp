#include "gamemanager.h"

Shared<GameManager> GameManager::instance_ = nullptr;

Shared<GameManager> GameManager::GetInstance() {
	if (!instance_) {
		instance_ = Shared<GameManager>(new GameManager());
	}
	return instance_;
}
