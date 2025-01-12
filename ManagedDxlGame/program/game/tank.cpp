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

	// WSで前後移動
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		position_ += tnl::Vector3::TransformCoord({ 0, 0, speed_ }, rotation_);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		position_ -= tnl::Vector3::TransformCoord({ 0, 0, speed_ }, rotation_);
	}
	// ADで回転
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		rotation_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-1));
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		rotation_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));
	}

	// 左右キーでバレルの回転
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

	// 砲身をワールド Y 軸 で回転させる姿勢の作成
	tnl::Quaternion qtn_bal_rot_y = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, ballrel_rot_y_);

	// 砲身のワールド空間の基本姿勢
	tnl::Quaternion qtn_bal_world_base_rot = rotation_ * pts_ofs_rot_[idx_barrel] * qtn_bal_rot_y;

	// 砲身のローカル X 軸回転させる姿勢の作成
	// ( ワールド基本姿勢から横軸を計算し それを X 回転軸とする )
	tnl::Quaternion qtn_bal_rot_x = tnl::Quaternion::RotationAxis(
		tnl::Vector3::TransformCoord({ 1, 0, 0 }, qtn_bal_world_base_rot), ballrel_rot_x_
	);

	barrel->setRotation(qtn_bal_world_base_rot * qtn_bal_rot_x);
	// barrel->setRotation(rotation_ * pts_ofs_rot_[idx_barrel] * ballrel_rot_);

	body->setPosition(position_ + pts_ofs_pos_[idx_body]);

	// 回転した砲身の座標
	// タンク本体の座標からオフセット分ずらした位置に配置する
	// Y 座標は単純に本体座標に足す
	// XZ 座標は砲身の基本姿勢( 現状寝ている姿勢 )から ローカルな Z方向にずらす必要がある
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
	// barrelの先を指定
	muzzle_pos_ = position_ +
		tnl::Vector3(0, bal_ofs_y, 0) +
		tnl::Vector3::TransformCoord({ 0, 0, GUN_BARREL_LENGTH }, barrel_wrd_rot_);

	body->render(camera);
	barrel->render(camera);
}

bool Tank::HitCallback(std::shared_ptr<Collider> target) {
	auto tgtTag = target->GetTag();

	if (tgtTag == Collider::COLLIDER_TAG::PLAYER_BULLET) return false; // 自分が撃った弾なら無視

	if (tgtTag == Collider::COLLIDER_TAG::ENEMY_BULLET) {
		hp_--;
		return true;
	}

	// 壁と敵のタンクに当たったときの処理（動く前のpositionに戻す）

	return true;
}