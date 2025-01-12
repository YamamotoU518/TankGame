#if 0

//-----------------------------------------------------------------------------------------------------------
//
//
// �����m�̏Փ˔���ƕ␳�T���v��
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
Shared<dxe::Mesh> sphereA = nullptr;
Shared<dxe::Mesh> sphereB = nullptr;
const float RADIUS = 50;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);

	sphereA = dxe::Mesh::CreateSphereMV(RADIUS);
	sphereA->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg"));
	sphereA->setPosition({ 100, 0, 0 });

	sphereB = sphereA->createClone();
	sphereB->setPosition({ -100, 0, 0 });

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	//-------------------------------------------------------------------------------
	//
	// update
	//
	//-------------------------------------------------------------------------------
	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				tnl::Vector3::left,
				tnl::Vector3::right,
				tnl::Vector3::forward,
				tnl::Vector3::back
			};
			sphereA->addPosition(v[index] * 3.0f);
		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	// �Փ˔���ƕ␳����
	tnl::Vector3 posA = sphereA->getPosition();
	tnl::Vector3 posB = sphereB->getPosition();

	if (tnl::IsIntersectSphere(posA, RADIUS, posB, RADIUS)) {
		tnl::Vector3 center = (posA + posB) / 2.0f;
		tnl::Vector3 toA = tnl::Vector3::Normalize(posA - posB);
		tnl::Vector3 toB = tnl::Vector3::Normalize(posB - posA);
		sphereA->setPosition(center + (toA * RADIUS));
		sphereB->setPosition(center + (toB * RADIUS));
	}

	camera->update();


	//-------------------------------------------------------------------------------
	//
	// draw
	//
	//-------------------------------------------------------------------------------

	DrawGridGround(camera, 50, 20);

	sphereA->render(camera);
	sphereB->render(camera);

	DrawFormatString(0, 0, -1, "WASD �ňړ�");
	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif