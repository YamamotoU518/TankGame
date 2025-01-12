#if 0

//-----------------------------------------------------------------------------------------------------------
//
//
// �}�E�X�J�[�\�����烌�C���΂��ĂR������Ԃɑ��݂���I�u�W�F�N�g�ƏՓ˔�����Ƃ�T���v��
//
//
//-----------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"


Shared<dxe::Camera> camera = nullptr;
Shared<dxe::Mesh> box = nullptr;


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);

	box = dxe::Mesh::CreateCubeMV(100);
	box->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg"));
	box->setPosition({ -100, 0, 0 });

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	//-------------------------------------------------------------------------------
	//
	// update
	//
	//-------------------------------------------------------------------------------

	tnl::Vector3 ms = tnl::Input::GetMousePosition();

	tnl::Vector3 ray_nml = tnl::Vector3::CreateScreenRay(ms.x, ms.y, DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F, camera->getViewMatrix(), camera->getProjectionMatrix());

	tnl::Vector3 pos = box->getPosition();

	if (tnl::IsIntersectRayAABB(
		camera->getPosition()
		, ray_nml
		, tnl::ToMaxAABB(pos, { 100, 100, 100 })
		, tnl::ToMinAABB(pos, { 100, 100, 100 })))
	{
		DrawFormatString(0, 30, -1, "hit");
	}

	camera->update();


	//-------------------------------------------------------------------------------
	//
	// draw
	//
	//-------------------------------------------------------------------------------

	DrawGridGround(camera, 50, 20);

	box->render(camera);

	DrawString(0, 0, "�}�E�X�J�[�\�����L���[�u�ɏd�˂Ă�������", -1);

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}


#endif