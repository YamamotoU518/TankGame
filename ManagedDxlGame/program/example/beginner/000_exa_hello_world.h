#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// [ ���� ] hello world
// 
// �� ��ʂ� hello world �̕������o�͂���邾���̃T���v���ł�
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	// ������`��
	// ������...x ���W
	// ������...y ���W
	// ��O����... �����̐F
	// ��l����... �o�͂��镶���� ( ������� �w " �x�_�u���N�H�[�e�[�V���� �ň͂��܂� )
	DrawFormatString(570, 300, -1, "hello world");



	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}


//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
}


#endif