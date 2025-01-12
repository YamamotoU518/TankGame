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

	// �e�p�[�c�̃I�t�Z�b�g���
	tnl::Vector3 pts_ofs_pos_[static_cast<int>(eParts::Max)];
	tnl::Quaternion pts_ofs_rot_[static_cast<int>(eParts::Max)];

	// �p�[�c���ʂɉ�]�����邽�߂̕ێ����
	tnl::Quaternion barrel_wrd_rot_; // barrel�̃��[���h��ԏ�̉�](90���|�������)
	float ballrel_rot_y_ = 0;
	float ballrel_rot_x_ = 0;	// �C�g�̓��[�J���� x ����]��������

	// �p�[�c���b�V��
	Shared<dxe::Mesh> pts_meshs_[static_cast<int>(eParts::Max)];

	// �p�[�c�̃T�C�Y���萔
	const tnl::Vector3 BODY_SIZE = { 100, 50, 200 };
	const float GUN_BARREL_RADIUS = 10;
	const float GUN_BARREL_LENGTH = 200;

	const float speed_ = 2; // �^���N�̈ړ����x

	tnl::Vector3 muzzle_pos_; // bullet�����˂����ʒu
};