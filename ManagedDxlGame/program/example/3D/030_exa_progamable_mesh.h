#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// �v���O���}�u�����b�V�������@�@�T���v��
//
//
//---------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"

//-------------------------------------------------------------------------------------------------------
//
// ���W�Ǝp���Ő��䂷��J����
//
class TransformCamera : public dxe::Camera {
public:

	TransformCamera() {};
	TransformCamera(float screen_w, float screen_h) : dxe::Camera(screen_w, screen_h) {}

	void update();


	inline tnl::Vector3 up() {
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
		return up_;
	}
	inline tnl::Vector3 down() { return -up(); }

	inline tnl::Vector3 forward() override {
		target_ = position_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
		return tnl::Vector3::Normalize(target_ - position_);
	}
	inline tnl::Vector3 back() override { return -forward(); }
	inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
	inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	tnl::Quaternion rot_;

};

void TransformCamera::update() {

	//
	// �p���p�����[�^����^�[�Q�b�g���W�ƃA�b�p�[�x�N�g�����v�Z
	//

	target_ = position_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
	up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
	dxe::Camera::update();
}



Shared<TransformCamera> camera = nullptr;


std::vector<Shared<dxe::Mesh>> mesh_tbl;
Shared<dxe::Mesh> mesh;
//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 1500.0f);
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 1.0f));
	SetBackgroundColor(32, 32, 32);


	camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);
	camera->setPosition({ 370, 350, -540 });
	camera->rot_ = tnl::Quaternion(0.189f, -0.248f, 0.049f, 0.948f);

	auto texture = dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg");

	tnl::Vector3 st = { -400, 0, 300 };

	// ��
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_SPHERE, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// ����
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_DOME, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �l�p�`
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_PLANE, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �f�B�X�N
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_DISK, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �l�p�`( ���蔲�� )
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_HOLLOW_OUT_DISK_PLANE, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x = -400;
	st.z -= 200;

	// �~��
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_CYLINDER, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �~��
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_CONE, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �R�[���V�����_�[
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_CONE_CYLINDER, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �M
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_BARREL, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// ���M
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_HALF_BARREL, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x = -400;
	st.z -= 200;

	// ������
	mesh = dxe::Mesh::CreateFromFileMV(FILE_PATH_MV1_CUBE, 100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �g�[���X
	mesh = dxe::Mesh::CreateTorusMV(50, 30);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// ���O�p�`
	mesh = dxe::Mesh::CreateTriangleEquilateralMV(100);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �񓙕ӎO�p�`
	mesh = dxe::Mesh::CreateTriangleIsoscelesMV({ 100, 150, 0 });
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// ���p�O�p�`
	mesh = dxe::Mesh::CreateTriangleRightMV({ 100, 100, 0 });
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x = -400;
	st.z -= 200;

	// �{�b�N�X
	mesh = dxe::Mesh::CreateBoxMV
	({ 100, 70, 60 }
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_LEFT)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_RIGHT)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_UP)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_DOWN)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_BACK)
		, dxe::Texture::CreateFromFile(FILE_PATH_BMP_BOX_FORWORD)
	);
	mesh->setPosition(st);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

	// �f�B�X�N�����O
	mesh = dxe::Mesh::CreateDiskRingMV(50, 20);
	mesh->setPosition(st);
	mesh->setTexture(texture);
	mesh_tbl.emplace_back(mesh);
	st.x += 200;

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {


	//----------------------------------------------------------------------------------------------------
	//
	// �J��������
	//
	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				camera->left(),
				camera->right(),
				tnl::Vector3::up,
				tnl::Vector3::down
			};
			camera->addPosition(v[index] * 3.0f);

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	if (tnl::Input::IsMouseDown(tnl::Input::eMouse::RIGHT)) {
		tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
		camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
		camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.2f));
	}
	camera->addPosition(camera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f);



	camera->update();


	DrawGridGround(camera, 50, 20);

	for (auto mesh : mesh_tbl) {
		mesh->render(camera);
	}



	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(DXE_WINDOW_WIDTH - 270, 15, DXE_WINDOW_WIDTH, 130, 0, true);
	DrawString(DXE_WINDOW_WIDTH - 260, 20, "�E�N���b�N : ����", -1);
	DrawString(DXE_WINDOW_WIDTH - 260, 40, "�z�C�[�� : �O��", -1);
	DrawString(DXE_WINDOW_WIDTH - 260, 60, "A D : ���E�ړ�", -1);
	DrawString(DXE_WINDOW_WIDTH - 260, 80, "W S : �㉺�ړ�", -1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif