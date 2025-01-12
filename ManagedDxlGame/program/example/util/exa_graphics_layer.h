#if 0

//-----------------------------------------------------------------------------------------------------------
//
//
// �O���t�B�b�N�X���C���[���p�T���v��
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
Shared<dxe::Mesh> mesh = nullptr;
Shared<dxe::Mesh> ground = nullptr;

Shared<dxe::GraphicsLayer> layer1 = nullptr;
Shared<dxe::GraphicsLayer> layer2 = nullptr;


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);
	camera->setPosition({ 0, 300, -700 });

	mesh = dxe::Mesh::CreateSphereMV(100, 20, 20);
	mesh->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg"));
	mesh->setPosition({ 0, 100, 0 });

	ground = dxe::Mesh::CreatePlaneMV({ 2000, 2000, 0 }, 20, 20);
	ground->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/lawn.png"));
	ground->setRotation(tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90)));


	layer1 = std::make_shared<dxe::GraphicsLayer>(tnl::Vector2i(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT));


	// ���C���[�Q�𐶐�
	layer2 = std::make_shared<dxe::GraphicsLayer>(tnl::Vector2i(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT));
	// ���C���[�Q�����C����ʂɕ`�悷�鎞�̃u�����h���[�h��ݒ�
	layer2->setBlendMode(DX_BLENDMODE_ADD);
	// ���C���[�Q�ɑ΂��Ďg�p�����ʌ��ʂ�ݒ� ( �u���[���ƃu���[ )
	layer2->setAdoption(dxe::GraphicsLayer::fAdoption::BLOOM | dxe::GraphicsLayer::fAdoption::BLUR);


	// ���C���[�̐ݒ���O���t�@�C�����烍�[�h���č쐬����ɂ͂�����
	//layer2 = std::make_shared<dxe::GraphicsLayer>("resource/dxe_parameters/graphics_layer/graphics_layer_status.bin");


}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	mesh->mulRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1)));

	camera->update();


	// ���C���[1 �ɕ`��
	layer1->write([&]() {

		ground->render(camera);
		mesh->render(camera);

		});

	// ���C���[2 �ɕ`��
	layer2->write([&]() {

		mesh->render(camera);

		});

	// ���C���[�P�E�Q�����C����ʂɕ`��
	layer1->draw();
	layer2->draw();

	// ���C���[�Q�̃X�e�[�^�X�� GUI�Œ���
	layer2->drawGuiController({ 0, 0 });

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
}

#endif
