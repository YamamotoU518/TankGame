#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// �e�L�X�g�I�u�W�F�N�g���p�T���v��
// 
//
//---------------------------------------------------------------------------------------------------------------
#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


int se_hdl = 0;
int current_message = 0;
Shared<dxe::FontText> text;

// �T���v���e�L�X�g ( �󕶌ɂ�� )
std::vector<std::string> test_message = {
	"�@��y�킪�͂��͔L�ł���B���O�͂܂������B\n�ǂ��Ő��ꂽ���Ƃ�ƌ�������Ƃ������ʁB\n���ł����Â����߂��߂������Ńj���[�j���[�����Ă����������͋L�����Ă���B",
	"��y�͂����Ŏn�߂Đl�ԂƂ������̂������B\n���������Ƃŕ����Ƃ���͏����Ƃ����l�Ԓ���\n����ֈ��ǂ������Ȏ푰�ł������������B\n���̏����Ƃ����͎̂��X��X��߂��܂��ĎςɂĐH���Ƃ����b�ł���B\n",
	"���������̓����͉��Ƃ����l���Ȃ���������ʒi�������Ƃ��v��Ȃ������B\n�����ނ̏��Ă̂Ђ�ɍڂ����ăX�[�Ǝ����グ��ꂽ��\n�������t���t�������������������΂���ł���B\n���̏�ŏ����������ď����̊�������̂�\n������l�ԂƂ������̂̌��n�݂͂��߂ł��낤�B",
	"���̎����Ȃ��̂��Ǝv�������������ł��c���Ă���B\n���т������đ�������ׂ��͂��̊炪��邵�Ă܂�Ŗ�ʂ₩�񂾁B\n���̌ゲ�L�ɂ������Ԉ�������������ȕЗւ�����ɂ�\n��x���o��ł��킵�������Ȃ��B",
	"�݂̂Ȃ炸��̐^�������܂�ɓˋN���Ă���B\n�������Ă��̌��̒����玞�X�Ղ��Ղ��Ɖ����ނ�𐁂��B\n�ǂ�����ނ��ۂ��Ď��Ɏ�����B\n���ꂪ�l�Ԃ̈��މ������΂��Ƃ������̂ł��鎖��\n�悤�₭���̍��m�����B"
};


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	SetFontSize(20);

	// �������� SE 
	se_hdl = LoadSoundMem(dxe::GetPathFromFileName(FILE_NAME_MP3_SE_SAMPLE_1));

	// �t�H���g�f�[�^�̒ǉ�
	tnl::AddFont(dxe::GetPathFromFontName(FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3));

	// �A�j���[�V�����e�L�X�g�̍쐬
	// arg1... �t�H���g�T�C�Y
	// arg2... �t�H���g�� ( �ȗ��� "�l�r �o����" )
	// arg3... �N�I���e�B�ݒ� ( DX_FONTTYPE_**** )
	// arg4... �t�H���g�̑��� ( �ȗ� �� �f�t�H���g�� -1 )
	// arg5... �����g�̑��� ( �ȗ��͘g���� )
	// ret.... dxe::FontText �� std::shared_ptr
	text = dxe::FontText::CreateAnimation(30, FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
	text->setString(test_message[0]);

	text->setPosition({ 70, 400 });
	text->setEdgeColor(dxe::Colors::Green);

	// �������肳��閈�ɍs�����[�U�[��`����
	text->setAnimUpdateCallback([&]() {
		// �������� SE �Đ�
		PlaySoundMem(se_hdl, DX_PLAYTYPE_BACK);
		});

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		// �ҋ@��ԂȂ�Đ�
		if (text->getAnimCondition() == tnl::SeekUnit::eCondition::STANDBY) {
			text->playAnimation();

			// �Đ����������Ă����玟�̃��b�Z�[�W
		}
		else if (text->getAnimCondition() == tnl::SeekUnit::eCondition::ENDED) {
			current_message++;
			current_message %= test_message.size();
			text->setString(test_message[current_message]);
			text->restartAnimation();

			// �A�j���[�V�������΂�
		}
		else {
			text->finishAnimation();
		}

	}


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		// �ꎞ��~
		text->pauseAnimation();
	}

	// �A�j���[�V�����X�V����
	text->updateAnimation();

	// �`��
	text->draw();


	dxe::DrawString({ DXE_WINDOW_WIDTH_HALF, DXE_WINDOW_HEIGHT_HALF }, -1, dxe::eRectOrigin::CENTER, "�G���^�[�L�[�ŕ����Đ�");

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}


//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
}


#endif