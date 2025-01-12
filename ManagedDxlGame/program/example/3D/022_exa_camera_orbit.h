#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// Orbit�J�����T���v��
//
// �� Orbit �J�����́A����̒����_�𒆐S�ɃJ�������O���i�I�[�r�b�g�j��`���悤�ɉ�]����J�����ł��B
//    ��ʓI�ɂ́A�����_�ɑ΂��ăJ�����̋�����p�x��ύX���邱�ƂŁA3D�I�u�W�F�N�g��V�[����l�X�Ȋp�x���猩�邱�Ƃ��\�ł��B
// 
//    �v���C���[�̓J�����̉�]�����Y�[���C���E�A�E�g�ɂ���āA���_���ړ������邱�Ƃ��ł��A
//    ���3D���f���̃r���[�A�[��V�~�����[�V�����Q�[���Ȃǂŗ��p����܂��B
// 
//    Orbit�J�����̊�{�I�ȑ���Ƃ��āA�����_����ɐ�����]�i���[�j�Ɛ�����]�i�s�b�`�j������A
//    �v���C���[���w�肵���p�x�ɉ����ăJ�����͉�]���A��苗����ۂ��Ȃ��璍���_���������܂��B
// 
//    3D�I�u�W�F�N�g�̕`��ɂ� LookAt �J�������ێ�����r���[�s��ƃv���W�F�N�V�����s�񂪕K�v�ł���A
//    Orbit �J������ LookAt �J�������p�����č쐬����܂��B
// 
//    Orbit�J�����͈ȉ��̗v�f�Ő��䂳��܂��F
//    1. �����_�̍��W
//    2. �J�����̋����i�Y�[���j
//    3. ��]�p�x�i���[�ƃs�b�`�j
// 
//    �J�����̉�]��Y�[���C���E�A�E�g����ɂ��A�v���C���[�͎��_�̎��R�x�������ۂ��Ȃ���
//    3D�I�u�W�F�N�g��V�[�����ώ@���邱�Ƃ��ł��܂��B
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
// �����_�܂ł́u ���� �v�u Y���p�x �v�u X���p�x �v�Ő��䂷��J����
//
class OrbitCamera : public dxe::Camera {
public:
	OrbitCamera() {};
	OrbitCamera(float screen_w, float screen_h) : dxe::Camera(screen_w, screen_h) {}

	void update();

	float to_target_distance_ = 500;
	float axis_x_angle_ = tnl::ToRadian(45);
	float axis_y_angle_ = 0;
};


void OrbitCamera::update() {

	//
	// �t���[���b�N�̐���p�����[�^����J�������W���v�Z
	//

	// Y����]�����p�����쐬
	tnl::Quaternion  q = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, axis_y_angle_);

	// ���_����Ƃ��āA�P�ʃx�N�g����Y����]�������������ʂ� xz ���ʂɌv�Z
	tnl::Vector3 xz = tnl::Vector3::TransformCoord({ 0, 0, 1 }, q);

	// xz �Ɛ^��̃x�N�g���ŊO�ς��v�Z���A�p�� q �̃��[�J����X�����v�Z
	tnl::Vector3 local_axis_x = tnl::Vector3::Cross({ 0, 1, 0 }, xz);

	// Y���p���ɑ΂��A����Ƀ��[�J��X���ŉ�]��������
	// ���_����J�������W�����֌����p�����ł���
	q *= tnl::Quaternion::RotationAxis(local_axis_x, axis_x_angle_);

	// �p�������ւ̋������W���^�[�Q�b�g�̍��W�ɑ������ƂŃJ�������W�ƂȂ�
	position_ = target_ + tnl::Vector3::TransformCoord({ 0, 0, -to_target_distance_ }, q);

	// �x�[�X�J�����̃A�b�v�f�[�g
	// �r���[�s��E�v���W�F�N�V�����s��̍X�V
	dxe::Camera::update();
}




Shared<OrbitCamera> camera = nullptr;
Shared<dxe::Mesh> mesh = nullptr;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 1500.0f);
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<OrbitCamera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);

	mesh = dxe::Mesh::CreateSphereMV(100, 20, 20);
	mesh->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg"));

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				camera->left(),
				camera->right(),
				camera->forward().xz(),
				camera->back().xz()
			};
			mesh->addPosition(v[index] * 3.0f);
			camera->setTarget(mesh->getPosition());

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);


	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT))	camera->axis_y_angle_ += tnl::ToRadian(1);
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) camera->axis_y_angle_ -= tnl::ToRadian(1);
	if (tnl::Input::IsKeyDown(eKeys::KB_UP))	camera->axis_x_angle_ += tnl::ToRadian(1);
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN))	camera->axis_x_angle_ -= tnl::ToRadian(1);

	if (tnl::Input::IsKeyDown(eKeys::KB_Z))	camera->to_target_distance_ += 1;
	if (tnl::Input::IsKeyDown(eKeys::KB_X))	camera->to_target_distance_ -= 1;


	camera->update();

	DrawGridGround(camera, 50, 20);

	mesh->render(camera);

	DrawFormatString(0, 0, -1, "WASD �ňړ�");
	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif