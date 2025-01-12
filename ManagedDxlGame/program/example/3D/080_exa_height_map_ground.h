#if 0

//------------------------------------------------------------------------------------------------
//
// Height Map ����n�`���쐬����T���v��
//
//------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"


Shared<dxe::Camera> camera = nullptr;
Shared<dxe::Mesh> ground = nullptr;


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);

	ground = dxe::Mesh::CreateFromHeightMapMV("resource/graphics/example/height_map.png", 10000, 10000, 100, 200, 200);
	ground->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example//height_map.png"));

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	ground->mulRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f)));

	//-------------------------------------------------------------------------------
	//
	// update
	//
	//-------------------------------------------------------------------------------
	camera->update();


	//-------------------------------------------------------------------------------
	//
	// draw
	//
	//-------------------------------------------------------------------------------

	ground->render(camera);
	ground->drawGuiMaterialControlloer();

	dxe::DrawGridGround(camera, 50, 20);
	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}


#endif