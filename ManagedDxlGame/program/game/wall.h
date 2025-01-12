#pragma once
#include "../dxe/dxe.h"
#include "gamemanager.h"
#include "gameobject.h"

class Wall : public GameObject {
public:
	Wall();
	void start() override;
	void update(float delta_time) override;
	void draw(const Shared<dxe::Camera>& camera) override;
private:
	std::list<Shared<dxe::Mesh>> field_meshs;
	Shared<dxe::Mesh> origin_;
};
