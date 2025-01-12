#pragma once
#include "../dxe/dxe.h"
#include "gameobject.h"

class GameObject;

/// <summary>
/// 3DCollider �̊��N���X
/// </summary>
class Collider : public std::enable_shared_from_this<Collider>{
public:
	enum COLLIDER_TYPE {
		INVALID_TYPE,
		BOXCOLLIDER_3D,
		SPHERECOLLIDER
	};

	enum COLLIDER_TAG {
		INVALID_TAG,
		PLAYER,
		ENEMY,
		PLAYER_BULLET,
		ENEMY_BULLET,
		WALL
	};

private:
	COLLIDER_TYPE type_;
	COLLIDER_TAG tag_;

protected:
	tnl::Vector3 size_;
	float radius_;
	std::weak_ptr<GameObject> object_; // �����̃I�u�W�F�N�g��pointer����
	std::function<bool(std::shared_ptr<Collider>)> hitCallback_;
	std::shared_ptr<Collider> GetPtr() { return shared_from_this(); } // ������(Collider��)pointer
	Collider() : type_(COLLIDER_TYPE::INVALID_TYPE), tag_(COLLIDER_TAG::INVALID_TAG) {}
public:
	Collider(COLLIDER_TYPE type, std::weak_ptr<GameObject> object, tnl::Vector3 size = tnl::Vector3{0, 0, 0}); // ������Collider_Type�ƃI�u�W�F�N�g��pointer
	Collider(COLLIDER_TYPE type, std::weak_ptr<GameObject> object, float radius = 0); // ������Collider_Type�ƃI�u�W�F�N�g��pointer
	virtual ~Collider(){}
	COLLIDER_TYPE GetType() { return type_; }
	COLLIDER_TAG GetTag() { return tag_; }
	std::weak_ptr<GameObject> GetGameObject() { return object_; }
	tnl::Vector3 GetSize() { if (size_.x) return size_; } // �T�C�Y�������return
	float GetRadius() { if (radius_) return radius_; } // radius�������return

	virtual bool IsHit(std::shared_ptr<Collider> target) = 0;
	void UpdateTag(COLLIDER_TAG tag);
	void SetCallback(std::function<bool(std::shared_ptr<Collider>)> callback);
};

class BoxCollider : public Collider {
	BoxCollider() {}
	BoxCollider(BoxCollider&&) = delete;
public:
	BoxCollider(std::weak_ptr<GameObject> object, float x, float y, float z)
		:Collider(COLLIDER_TYPE::BOXCOLLIDER_3D, object, tnl::Vector3{x, y, z}) {}
	bool IsHit(std::shared_ptr<Collider> target); // target�ƂԂ�������
};

class SphereCollider : public Collider {
	SphereCollider() {}
	SphereCollider(SphereCollider&&) = delete;
public:
	SphereCollider(std::weak_ptr<GameObject> object, float radius)
		:Collider(COLLIDER_TYPE::SPHERECOLLIDER, object, radius) {}
	bool IsHit(std::shared_ptr<Collider> target); // target�ƂԂ�������
};