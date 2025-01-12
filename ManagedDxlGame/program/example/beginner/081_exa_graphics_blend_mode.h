#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// �u�����h���[�h�T���v��
// 
// �� �������E���Z�����E���Z����
// �@
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


int back_ground_hdl = 0;
int alpha_image_hdl = 0;
int add_image_hdl = 0;
int sub_image_hdl = 0;

tnl::Vector3 pos[3];

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	back_ground_hdl = LoadGraph("resource/graphics/example/Sifi_town3_6n.png");
	alpha_image_hdl = LoadGraph("resource/graphics/example/stone.png");
	add_image_hdl = LoadGraph("resource/graphics/example/point.jpg");
	sub_image_hdl = LoadGraph("resource/graphics/example/scissors.png");


	pos[0] = { DXE_WINDOW_WIDTH_QUARTER_F, DXE_WINDOW_HEIGHT_HALF_F, 0 };
	pos[1] = { DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F, 0 };
	pos[2] = { DXE_WINDOW_WIDTH_HALF_F + DXE_WINDOW_WIDTH_QUARTER_F, DXE_WINDOW_HEIGHT_HALF_F, 0 };

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	/* SetDrawBlendMode �͈�x�ݒ肷��ƁA�Đݒ肷��܂ł����Ƃ��̐ݒ�ŕ`�悳��܂� */

	// �s�����`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, back_ground_hdl, true);

	// �������`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	DrawRotaGraph(pos[0].x, pos[0].y, 1.0f, 0, alpha_image_hdl, true);

	// ���Z�������`��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRotaGraph(pos[1].x, pos[1].y, 1.0f, 0, add_image_hdl, true);

	// ���Z�������`��
	SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	DrawRotaGraph(pos[2].x, pos[2].y, 1.0f, 0, sub_image_hdl, true);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif
