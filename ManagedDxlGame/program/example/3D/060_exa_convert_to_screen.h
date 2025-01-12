#if 0

//-----------------------------------------------------------------------------------------------------------
//
//
// 3�������W���X�N���[�����W�֕ϊ�����T���v�� ( �L�����N�^��HP�Q�[�W�Ȃǂ� UI �ɗ��p���܂��傤 )
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

// �I�u�W�F�N�g����ړ��p
float time_count = 0;
Shared<tnl::PointsLerp> lerp_points = nullptr;

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


	std::vector<tnl::Vector3> points;
	points.emplace_back(tnl::Vector3(-300, 0, 300));
	points.emplace_back(tnl::Vector3(300, 0, 300));
	points.emplace_back(tnl::Vector3(300, 0, -300));
	points.emplace_back(tnl::Vector3(-300, 0, -300));
	points.emplace_back(tnl::Vector3(-300, 0, 300));
	lerp_points = std::make_shared<tnl::PointsLerp>(points);
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	//-------------------------------------------------------------------------------
	//
	// update
	//
	//-------------------------------------------------------------------------------
	time_count += delta_time * 0.1f;
	box->setPosition(lerp_points->getPosition(time_count));

	tnl::Vector3 screen_pos = tnl::Vector3::ConvertToScreen(
		{ box->getPosition().x, 100, box->getPosition().z }
		, DXE_WINDOW_WIDTH_F
		, DXE_WINDOW_HEIGHT_F
		, camera->getViewMatrix()
		, camera->getProjectionMatrix());

	camera->update();


	//-------------------------------------------------------------------------------
	//
	// draw
	//
	//-------------------------------------------------------------------------------

	DrawGridGround(camera, 50, 20);

	box->render(camera);

	DrawFormatString(screen_pos.x, screen_pos.y, -1, "test string");

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif
