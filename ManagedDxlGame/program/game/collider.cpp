#include "collider.h"

Collider::Collider(COLLIDER_TYPE type, std::weak_ptr<GameObject> object, tnl::Vector3 size) {
	type_ = type;
	object_ = object;
	tag_ = INVALID_TAG;
	size_ = size;
} // BoxCollider�̂Ƃ�

Collider::Collider(COLLIDER_TYPE type, std::weak_ptr<GameObject> object, float radius) {
	type_ = type;
	object_ = object;
	tag_ = INVALID_TAG;
	radius_ = radius;
} // SphereCollider�̂Ƃ�

void Collider::UpdateTag(COLLIDER_TAG tag) {
	tag_ = tag;
}

void Collider::SetCallback(std::function<bool(std::shared_ptr<Collider>)> callback) {
	hitCallback_ = callback;
}

bool BoxCollider::IsHit(std::shared_ptr<Collider> target) {
	switch (target->GetType())
	{
	case COLLIDER_TYPE::BOXCOLLIDER_3D :
	{
		auto obj = target->GetGameObject();
		auto tgt = obj.lock(); // ����̃I�u�W�F�N�g
		auto self = object_.lock(); // �����̃I�u�W�F�N�g
		auto tgt_size = target->GetSize();

		return tnl::IsIntersectAABB(self->position_, size_, tgt->position_, tgt_size);
	} // {}�ň͂�Ȃ��ƃG���[���ł�
	break;
	case COLLIDER_TYPE::SPHERECOLLIDER :
		break;
	}
	return false;
}

bool SphereCollider::IsHit(std::shared_ptr<Collider> target) {
	switch (target->GetType())
	{
	case COLLIDER_TYPE::BOXCOLLIDER_3D :
		break;
	case COLLIDER_TYPE::SPHERECOLLIDER :
		break;
	}
	return false;
}