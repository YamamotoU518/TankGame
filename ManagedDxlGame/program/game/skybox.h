#pragma once
#include "gameobject.h"
#include "gamemanager.h"

class SkyBox : public GameObject {
public :
	SkyBox();
	void start() override;
	void update(float delta_time) override;
	void draw(const Shared<dxe::Camera>& camera) override;

	Shared<dxe::Mesh> skybox;
};
