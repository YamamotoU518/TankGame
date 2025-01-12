#if 0

//-----------------------------------------------------------------------------------------------------------
//
//
// ��`�Ɖ~�̏Փ˔���ƕ␳�T���v��
//
//
//-----------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


// �~�̍��W�Ɣ��a
tnl::Vector3 posA = { 100, 400, 0 };
float radiusA = 50;

// ��`�̍��W�ƃT�C�Y
tnl::Vector3 posB = { 600, 400, 0 };
tnl::Vector2i sizeB = { 200, 300 };


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	SetFontSize(30);
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	// �~�̈ړ��O�̍��W��ۑ�
	tnl::Vector3 before_circle = posA;

	// ���ꂼ��̈ړ�����
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) posA.x -= 6;
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) posA.x += 6;
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) posA.y -= 6;
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) posA.y += 6;

	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) posB.x -= 5;
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) posB.x += 5;
	if (tnl::Input::IsKeyDown(eKeys::KB_UP))	posB.y -= 5;
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) posB.y += 5;


	DrawFormatString(0, 0, -1, "WASD �� �~ ���ړ�");
	DrawFormatString(0, 30, -1, "�J�[�\���L�[ �� ��` ���ړ�");

	if (tnl::IsIntersectRectCircle(posB, sizeB, posA, radiusA)) {
		tnl::CorrectPositionRectCircle(posB, sizeB, before_circle, radiusA, posA);
	}

	DrawCircle(posA.x, posA.y, radiusA, -1, false);

	dxe::DrawBox({ posB.x, posB.y }, sizeB.x, sizeB.y, false, -1);

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif