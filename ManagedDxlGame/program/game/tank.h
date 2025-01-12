#pragma once
#include "gameobject.h"
#include "gamemanager.h"


class Tank : public GameObject {
public:
	enum class eParts {
		Body,
		GunBarrel,
		Max
	};

	Tank();

	void start() override;
	void update(float delta_time) override;
	void draw(const Shared<dxe::Camera>& camera) override;
	bool HitCallback(std::shared_ptr<Collider> target);

	// 各パーツのオフセット情報
	tnl::Vector3 pts_ofs_pos_[static_cast<int>(eParts::Max)];
	tnl::Quaternion pts_ofs_rot_[static_cast<int>(eParts::Max)];

	// パーツを個別に回転させるための保持情報
	tnl::Quaternion barrel_wrd_rot_; // barrelのワールド空間上の回転(90°倒した後の)
	float ballrel_rot_y_ = 0;
	float ballrel_rot_x_ = 0;	// 砲身はローカルな x 軸回転をさせる

	// パーツメッシュ
	Shared<dxe::Mesh> pts_meshs_[static_cast<int>(eParts::Max)];

	// パーツのサイズ情報定数
	const tnl::Vector3 BODY_SIZE = { 100, 50, 200 };
	const float GUN_BARREL_RADIUS = 10;
	const float GUN_BARREL_LENGTH = 200;

	const float speed_ = 2; // タンクの移動速度

	tnl::Vector3 muzzle_pos_; // bulletが発射される位置
};