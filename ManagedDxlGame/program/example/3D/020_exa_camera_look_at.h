#if 0

//---------------------------------------------------------------------------------------------------------------
//
// LookAt �J����
// 
//�@�� ��{�ƂȂ���݂̂������Ă���J�����ł�
//�@�@ 3D �I�u�W�F�N�g����ʂɕ`�悷��ɂ����蓊�e�ϊ����s���܂�
// �@�@���e�ϊ��̓V�F�[�_�ɂ���ď�������܂����A���_���W�ɑ΂���
// �@�@MVP( ���f���r���[���e�s�� ) ���|�����킳��܂�
// �@�@MVP�s��͎��̂R�̍s����|�����킹�邱�ƂŐ�������܂�
// �@�@�P�D���f���s��@3D �I�u�W�F�N�g�̍��W(�s��)�E��](�s��)�E�X�P�[��(�s��) ���|�����킹���s��
// �@�@�Q�D�r���[�s��@�J�����̍��W�⒍���_�Ȃǂ��琶�������
// �@�@�R�D�v���W�F�N�V�����s��@�J�����̎���p�E�A�X�y�N�g��Ȃǂ��琶�������
// 
//�@LookAt �J�����Ƃ͓��e�ϊ����s�����߂ɕK�v�ȍŏ����̏��ō\������
//�@���[�U�[�̓J�����̍��W�ƒ����_�i����я�����x�N�g���j�𑀍삵�Đ��䂷��J�����ł�
// 
//---------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"

Shared<dxe::Camera> camera = nullptr;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 1500.0f);
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);


	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	float move = 3.0f;

	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) camera->addPosition({ -move, 0, 0 });
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) camera->addPosition({ move, 0, 0 });
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) camera->addPosition({ 0, move, 0 });
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) camera->addPosition({ 0, -move, 0 });

	if (tnl::Input::IsKeyDown(eKeys::KB_A)) camera->addTarget({ -move, 0, 0 });
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) camera->addTarget({ move, 0, 0 });
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) camera->addTarget({ 0, move, 0 });
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) camera->addTarget({ 0, -move, 0 });


	// �J�������̍X�V
	// �`�揈�����s���O�ɖ��t���[�����s
	camera->update();

	DrawGridGround(camera, 50, 20);

	DrawString(0, 0, "�������� �ō��W�ړ�", -1);
	DrawString(0, 20, "WASD �Ń^�[�Q�b�g�ړ�", -1);

	DrawFormatString(0, 50, -1, "position = %s", camera->getPosition().toString("%.2f").c_str());
	DrawFormatString(0, 70, -1, "target = %s", camera->getTarget().toString("%.2f").c_str());


	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif