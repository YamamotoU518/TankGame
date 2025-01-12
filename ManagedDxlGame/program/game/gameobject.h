#pragma once
#include "../dxe/dxe.h"
#include "collider.h"

class Collider;
class GameObject : public std::enable_shared_from_this<GameObject>{
protected:
	std::shared_ptr<Collider> collider_;
	std::shared_ptr<GameObject> GetPtr() { return shared_from_this(); }
	virtual bool HitCallback(std::shared_ptr<Collider> target) {
		return true;
	}

public:
	GameObject() {}
	virtual ~GameObject() {}

	tnl::Vector3 position_;
	tnl::Quaternion rotation_;
	int hp_;

	bool is_alive_ = hp_ > 0;

	virtual void start() {}
	virtual void update(float delta_time) {}
	virtual void draw(const Shared<dxe::Camera>& camera) {}

	template<typename T>
	void SetupCollider(Collider::COLLIDER_TAG tag, tnl::Vector3 size) {
		collider_ = std::make_shared<T>(std::weak_ptr<GameObject>(GetPtr()), size);
		collider_->UpdateTag(tag);
		collider_->SetCallback(std::bind(&GameObject::HitCallback, &(*this), std::placeholders::_1));
	}
};

