#include "bullet.h"

Bullet::Bullet(tnl::Vector3 spawn_pos, tnl::Quaternion rotation, Collider::COLLIDER_TAG tag) {
	position_ = spawn_pos;
	rotation_ = rotation;
	bullet = dxe::Mesh::CreateSphereMV(radius_, 20, 20, true);
	bullet->setTexture(dxe::Texture::CreateFromFile(FILE_PATH_BMP_BLUE1));
}

void Bullet::start() {

}

void Bullet::update(float delta_time) {
	position_ += tnl::Vector3::TransformCoord({ 0, 0, speed_ }, rotation_);
	timer_ += delta_time;
	if (timer_ >= limit_) {
		is_alive_ = false;
	}
}

void Bullet::draw(const Shared<dxe::Camera>& camera) {
	bullet->setPosition(position_);
	bullet->setRotation(rotation_);
	bullet->render(camera);
}

bool Bullet::HitCallback(std::shared_ptr<Collider> target) {
	hp_--;
	return true;
}