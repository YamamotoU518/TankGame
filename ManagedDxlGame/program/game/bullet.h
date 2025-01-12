#pragma once
#include "gameobject.h"

class Bullet : public GameObject{
public:
	Bullet(tnl::Vector3 spawn_pos, tnl::Quaternion rotation, Collider::COLLIDER_TAG tag);
	void start() override;
	void update(float delta_time) override;
	void draw(const Shared<dxe::Camera>& camera) override;
	bool HitCallback(std::shared_ptr<Collider> target);

	Shared<dxe::Mesh> bullet;

private:
	float radius_ = 10;
	float speed_ = 5;
	float limit_ = 1;
	float timer_ = 0;
};
