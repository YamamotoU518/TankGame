#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// [ ���� ] �Փ˔���T���v�� �}�E�X�J�[�\���Ƌ�`
//
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


// �{�b�N�X�̃T�C�Y
int size_w = 200;
int size_h = 200;

// �{�b�N�X�̒��S���W
tnl::Vector2f box_pos = { 600, 300 };


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	SetFontSize(30);
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();

	DrawFormatString(0, 0, -1, "�}�E�X�J�[�\���Ƌ�`�̏Փ˔���");


	if (tnl::IsIntersectPointRect(mouse_pos.x, mouse_pos.y, box_pos.x, box_pos.y, size_w, size_h)) {
		DrawFormatString(0, 30, -1, "hit");
	}

	dxe::DrawBox(box_pos, size_w, size_h, false);


	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}


//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
}


#endif