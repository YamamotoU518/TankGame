#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// �e�N�X�`���ւ̕`��T���v��
//
//
//---------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"

Shared<dxe::Camera> camera = nullptr;
Shared<dxe::Mesh> mesh = nullptr;
Shared<dxe::Texture> texture = nullptr;

int test_gfx = 0;
int test_count = 0;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 1500.0f);
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 1.0f));
	SetBackgroundColor(32, 32, 32);



	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);


	// �`��̈�𐶐�
	test_gfx = MakeScreen(200, 200, TRUE);
	// DxLib �̃O���t�B�b�N�n���h������e�N�X�`���𐶐�
	texture = dxe::Texture::CreateFromDxLibGraphHdl(test_gfx);

	mesh = dxe::Mesh::CreatePlaneMV({ 200, 200, 0 }, 20, 20);
	mesh->setTexture(texture);


	mesh->mulRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-45)));
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {


	test_count++;

	// �`��Ώۂ��e�N�X�`���ɕύX
	SetDrawScreen(test_gfx);

	// �e�N�X�`���ɑ΂���`�揈��
	ClearDrawScreen();
	DrawBox(0, 0, 200, 200, GetColor(128, 32, 32), TRUE);
	DrawFormatString(0, 0, -1, "abcd = %d", test_count);

	// �`��Ώۂ��o�b�N�o�b�t�@�֖߂�
	SetDrawScreen(DX_SCREEN_BACK);



	camera->update();

	dxe::DrawGridGround(camera, 50, 20);

	mesh->render(camera);

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif