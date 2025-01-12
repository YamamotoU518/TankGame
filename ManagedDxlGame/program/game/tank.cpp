#include "tank.h"
#include "bullet.h"

Tank::Tank() {
	pts_ofs_pos_[static_cast<int>(eParts::Body)] = tnl::Vector3{ 0, 0, 0 };
	pts_ofs_pos_[static_cast<int>(eParts::GunBarrel)] =
		tnl::Vector3{
			0,
			BODY_SIZE.y * 0.5f + GUN_BARREL_RADIUS,
			GUN_BARREL_LENGTH * 0.5f
	};

	pts_meshs_[static_cast<int>(eParts::Body)] = dxe::Mesh::CreateBoxMV
	(BODY_SIZE
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_LEFT)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_RIGHT)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_UP)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_DOWN)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_BACK)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_FORWORD)
	);
	pts_meshs_[static_cast<int>(eParts::GunBarrel)] = dxe::Mesh::CreateCylinderMV(
		GUN_BARREL_RADIUS,
		GUN_BARREL_LENGTH);

	pts_meshs_[static_cast<int>(eParts::GunBarrel)]->setTexture(
		dxe::Texture::CreateFromFile(FILE_PATH_JPG_TEST)
	);
}

void Tank::start() {
	SetupCollider<BoxCollider>(Collider::COLLIDER_TAG::PLAYER, BODY_SIZE);
}

void Tank::update(float delta_time) {

	// WS�őO��ړ�
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		position_ += tnl::Vector3::TransformCoord({ 0, 0, speed_ }, rotation_);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		position_ -= tnl::Vector3::TransformCoord({ 0, 0, speed_ }, rotation_);
	}
	// AD�ŉ�]
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		rotation_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-1));
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		rotation_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
	}

	// ���E�L�[�Ńo�����̉�]
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		// ballrel_rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-1));
		ballrel_rot_y_ -= tnl::ToRadian(1);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
		// ballrel_rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
		ballrel_rot_y_ += tnl::ToRadian(1);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		Shared<Bullet> bullet = std::make_shared<Bullet>(muzzle_pos_, barrel_wrd_rot_);
		auto gmr = GameManager::GetInstance();
		gmr->bullets.emplace_back(bullet);
		gmr->objects.emplace_back(bullet);
	}
}

void Tank::draw(const Shared<dxe::Camera>& camera)
{
	const int idx_body = static_cast<int>(eParts::Body);
	const int idx_barrel = static_cast<int>(eParts::GunBarrel);

	pts_ofs_rot_[idx_barrel] =
		tnl::Quaternion::RotationAxis(tnl::Vector3::TransformCoord({ 1, 0, 0 }, rotation_), tnl::ToRadian(90));

	auto body = pts_meshs_[idx_body];
	auto barrel = pts_meshs_[idx_barrel];

	body->setRotation(rotation_ * pts_ofs_rot_[idx_body]);

	// �C�g�����[���h Y �� �ŉ�]������p���̍쐬
	tnl::Quaternion qtn_bal_rot_y = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, ballrel_rot_y_);

	// �C�g�̃��[���h��Ԃ̊�{�p��
	tnl::Quaternion qtn_bal_world_base_rot = rotation_ * pts_ofs_rot_[idx_barrel] * qtn_bal_rot_y;

	// �C�g�̃��[�J�� X ����]������p���̍쐬
	// ( ���[���h��{�p�����牡�����v�Z�� ����� X ��]���Ƃ��� )
	tnl::Quaternion qtn_bal_rot_x = tnl::Quaternion::RotationAxis(
		tnl::Vector3::TransformCoord({ 1, 0, 0 }, qtn_bal_world_base_rot), ballrel_rot_x_
	);

	barrel->setRotation(qtn_bal_world_base_rot * qtn_bal_rot_x);
	// barrel->setRotation(rotation_ * pts_ofs_rot_[idx_barrel] * ballrel_rot_);

	body->setPosition(position_ + pts_ofs_pos_[idx_body]);

	// ��]�����C�g�̍��W
	// �^���N�{�̂̍��W����I�t�Z�b�g�����炵���ʒu�ɔz�u����
	// Y ���W�͒P���ɖ{�̍��W�ɑ���
	// XZ ���W�͖C�g�̊�{�p��( ����Q�Ă���p�� )���� ���[�J���� Z�����ɂ��炷�K�v������
	float bal_ofs_x = pts_ofs_pos_[idx_barrel].x;
	float bal_ofs_y = pts_ofs_pos_[idx_barrel].y;
	float bal_ofs_z = pts_ofs_pos_[idx_barrel].z;
	barrel->setPosition(
		position_ +
		tnl::Vector3(0, bal_ofs_y, 0) +
		tnl::Vector3::TransformCoord({ 0, 0, bal_ofs_z }, rotation_ * qtn_bal_rot_y * qtn_bal_rot_x)
	);
	/*barrel->setPosition(
		position_ + tnl::Vector3::TransformCoord(pts_ofs_pos_[idx_barrel], rotation_ * ballrel_rot_));*/

	barrel_wrd_rot_ = rotation_ * qtn_bal_rot_x * qtn_bal_rot_y;
	// barrel�̐���w��
	muzzle_pos_ = position_ +
		tnl::Vector3(0, bal_ofs_y, 0) +
		tnl::Vector3::TransformCoord({ 0, 0, GUN_BARREL_LENGTH }, barrel_wrd_rot_);

	body->render(camera);
	barrel->render(camera);
}

bool Tank::HitCallback(std::shared_ptr<Collider> target) {
	auto tgtTag = target->GetTag();

	if (tgtTag == Collider::COLLIDER_TAG::PLAYER_BULLET) return false; // �������������e�Ȃ疳��

	if (tgtTag == Collider::COLLIDER_TAG::ENEMY_BULLET) {
		hp_--;
		return true;
	}

	// �ǂƓG�̃^���N�ɓ��������Ƃ��̏����i�����O��position�ɖ߂��j

	return true;
}