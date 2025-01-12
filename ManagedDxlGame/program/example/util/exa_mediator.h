#if 0


//---------------------------------------------------------------------------------------------------------------
//
//
// �N���X�Ԃł̑a������ۂ��Ȃ���ʐM���s�� �C���^���N�V�����R�[�f�B�l�[�^�[ �T���v��
//
// �Q�̃C���X�^���X�ԂŃ��f�B�G�[�^�Ƃ��ăC���^���N�^�[�𗘗p�����ʐM�̏ꍇ
//
//---------------------------------------------------------------------------------------------------------------
#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


//---------------------------------------------------------------------------------------
//
// UIButton.h
//
//---------------------------------------------------------------------------------------

class UIButton : public std::enable_shared_from_this<UIButton> {
public:

	// �N���X�Ԃ̑a�����ʐM���T�|�[�g���� �C���^���N�^�[ �L�q�}�N��
	// ���̃}�N�����L�q���邱�Ƃ� tnlInteractor �Ŏn�܂�ʐM�֐��������L�q����܂�
	TNL_INTERACTOR_DECLARE(
		CALL_BALL_MOVE,					// �~�ւ́u�����v��ʒm���� ID
		CALL_BALL_STOP,					// �~�ւ́u�~�܂�v��ʒm���� ID
		CALL_BALL_RANDOM_COLOR_CHENGE	// �~�֐F�ւ��{�^���������ꂽ����ʒm���� ID
	);

	UIButton
	(const tnl::Vector3& position
		, const std::string& on_text
		, const std::string& off_text
		, const std::function<void(const Shared<UIButton>&)>& on_click_proc)

		: position_(position)
		, on_text_(on_text)
		, off_text_(off_text)
		, on_click_proc_(on_click_proc)
	{}

	bool getSelected() { return is_selected_; }
	void setSelected(bool flag) { is_selected_ = flag; }

	const tnl::Vector3& getPosition() { return position_; }
	void setPosition(const tnl::Vector3& position) { position_ = position; }

	void update();
	void draw();
private:
	bool is_forcus_ = false;
	bool is_click_ = false;
	bool is_selected_ = false;
	tnl::Vector3 size_ = { 100, 30, 0 };
	tnl::Vector3 position_;
	std::function<void(const Shared<UIButton>&)> on_click_proc_;
	std::string on_text_;
	std::string off_text_;
};

//---------------------------------------------------------------------------------------
//
// UIButton.cpp
//
//---------------------------------------------------------------------------------------

void UIButton::update() {
	is_forcus_ = false;
	is_click_ = false;
	tnl::Vector3 ms = tnl::Input::GetMousePosition();
	if (tnl::IsIntersectPointRect((int)ms.x, (int)ms.y, (int)position_.x, (int)position_.y, (int)size_.x, (int)size_.y)) {
		is_forcus_ = true;
		if (tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT)) is_click_ = true;

		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::OUT_LEFT)) {
			on_click_proc_(shared_from_this());
		}
	}

}

void UIButton::draw() {
	int color = -1;
	if (is_forcus_) color = GetColor(128, 128, 255);
	if (is_click_) color = GetColor(255, 128, 128);

	std::string btn_str = (!is_selected_) ? on_text_ : off_text_;

	dxe::DrawBox({ TNL_DEP_V2(position_) }, size_.x, size_.y, false, color);
	DrawFormatString((int)(position_.x - (size_.x / 4)), (int)position_.y - 10, -1, btn_str.c_str());
}



//---------------------------------------------------------------------------------------
//
// Circle.h
//
//---------------------------------------------------------------------------------------

class Circle : public std::enable_shared_from_this<Circle> {
public:
	Circle(const tnl::Vector3& position) : position_(position) {}

	void update();
	void draw();

	void setMoveFlag(bool flag) { is_move_ = flag; }
	const tnl::Vector3& getPosition() { return position_; }
	void randomColorChange() { color_ = GetColor(rand() % 255, rand() % 255, rand() % 255); }

private:
	bool is_move_ = false;
	float speed_ = 10;
	float radius_ = 100;
	int color_ = -1;
	tnl::Vector3 position_;
};

//---------------------------------------------------------------------------------------
//
// Circle.cpp
//
//---------------------------------------------------------------------------------------

void Circle::update() {
	if (!is_move_) return;
	position_.x += speed_;

	float l_lim_x = 200;
	float r_lim_x = 1000;
	if (position_.x < l_lim_x) {
		position_.x = l_lim_x;
		speed_ = -speed_;
	}
	if (position_.x > r_lim_x) {
		position_.x = r_lim_x;
		speed_ = -speed_;
	}
}

void Circle::draw() {
	DrawCircle((int)position_.x, (int)position_.y, (int)radius_, color_, false);
}




//---------------------------------------------------------------------------------------
//
// game main
//
//---------------------------------------------------------------------------------------


// ���ꂼ��̃C���X�^���X�͓Ɨ������O���[�o���ȕϐ��ł���
// ����̃N���X�̕�܊֌W�ɂ��Ȃ����
Shared<UIButton> button_move;
Shared<UIButton> button_color_change;
Shared<Circle> circle;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {

	// move stop �{�^���̍쐬
	button_move = std::make_shared<UIButton>(
		tnl::Vector3(DXE_WINDOW_WIDTH_HALF, DXE_WINDOW_HEIGHT_HALF, 0),
		"move",
		"stop",

		// �N���b�N���ꂽ���ɍs���鏈��
		[](const Shared<UIButton>& btn) {
			btn->setSelected(!btn->getSelected());
			if (btn->getSelected()) {

				// �~�ւ́u�����v�ʒm
				// ���̊֐��ɂ��߂�l�͖����̂Ńe���v���[�g�^�w��� void
				// arg1... TNL_INTERACTOR_DECLARE �ɐݒ肵�� �u�����v�ʒm ID
				// arg2... CALL_BALL_MOVE �ɑΉ�����ʒm�ɕt�������p�����[�^ ( ����� bool �^ �����̌^�ł��Ή� )
				// tips... arg2 �œn���^�ɂ��Ă� ���̌�� TNL_INTERACTOR_SEND_TRANSMITTER_REGISTER �Őݒ�
				btn->tnlInteractorArgsTransmitter<void>(UIButton::eTnlICId::CALL_BALL_MOVE, true);
			}
			else {

				// �~�ւ́u�~�܂�v�ʒm
				// ���̊֐��ɂ��߂�l�� const tnl::Vector3& �Ȃ̂Ńe���v���[�g�^�w��ɂ��̂悤�ɋL�q
				// arg1... TNL_INTERACTOR_DECLARE �ɐݒ肵�� �u�~�܂�v�ʒm ID
				// arg2... CALL_BALL_MOVE �ɑΉ�����ʒm�ɕt�������p�����[�^ ( ����� bool �^ �����̌^�ł��Ή� )
				// ret.... CALL_BALL_STOP �����s�������ʂ� �ԐM ( ����͉~�̍��W��ԐM���Ƃ��Ă��� )
				// tips... arg2 �œn���^�ɂ��Ă� ���̌�� TNL_INTERACTOR_SEND_TRANSMITTER_REGISTER �Őݒ�
				tnl::Vector3 recipt = btn->tnlInteractorArgsTransmitter<const tnl::Vector3&>(UIButton::eTnlICId::CALL_BALL_STOP, false);

				// �󂯎�����ԐM���( �~�̍��W )�Ń{�^���̍��W���X�V
				btn->setPosition(recipt);
			}
		});


	// color �{�^���̍쐬
	button_color_change = std::make_shared<UIButton>(
		tnl::Vector3(DXE_WINDOW_WIDTH - 100, 100, 0),
		"color",
		"color",

		// �N���b�N���ꂽ���ɍs���鏈��
		[](const Shared<UIButton>& btn) {

			// �~�ւ́u�F��ς���v�ʒm
			// ���̊֐��ɂ��߂�l�͖����̂Ńe���v���[�g�^�w��� void
			// arg1... TNL_INTERACTOR_DECLARE �ɐݒ肵�� �u�F��ς���v�ʒm ID
			// tips... ���̊֐��ł̉~�ւ̒ʒm�ŕt�����͖����̂� arg2 �͑��݂��Ȃ� ( ��L�Ƃ͊֐������Ⴄ���ɗ��� )
			btn->tnlInteractorTransmitter<>(UIButton::eTnlICId::CALL_BALL_RANDOM_COLOR_CHENGE);
		});



	// �~�̍쐬
	circle = std::make_shared<Circle>(tnl::Vector3(DXE_WINDOW_WIDTH_HALF, DXE_WINDOW_HEIGHT_HALF, 0));


	// move �{�^������ �~�ɑ΂��āu�����v�ʒm�������e��o�^
	// arg1... move �{�^�����ʒm���o���̂� �{�^���̃C���X�^���X
	// arg2... �ʒm����̕ԐM�͐ݒ肵�Ȃ��̂� void
	// arg3... �ʒm�����ʂ��� ID ��ݒ�
	// arg4... �ʒm��̃C���X�^���X�� std::weak_ptr �Ŏw��
	// arg5... �~�ւ̒ʒm�ɕt������ݒ肷�� ( �����ł� bool �^ )
	// arg6... �����_���� {} �̂݋L�q ( �ʒm���e�̏��� )
	TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(button_move, void, UIButton::eTnlICId::CALL_BALL_MOVE, Weak<Circle>(circle), bool, {
		// �{�^������ʒm���ꂽ�� �ʒm��Ƃ��Đݒ肳��Ă���C���X�^���X���擾
		Shared<Circle> cir = TNL_INTERACTOR_GET_WEAK_REFERENCE(Weak<Circle>).lock();

	// �{�^������n���ꂽ�t�������g�p���ĉ~�̏����X�V
	// �����ł� TNL_INTERACTOR_GET_RECEIPT_INFORMATION() �œ�����̂� arg5�Ŏw�肵���^ ( bool )
	cir->setMoveFlag(TNL_INTERACTOR_GET_RECEIPT_INFORMATION());
		});

	// stop �{�^������ �~�ɑ΂��āu�~�܂�v�ʒm�������e��o�^
	// arg1... stop �{�^�����ʒm���o���̂� �{�^���̃C���X�^���X
	// arg2... �ʒm����̕ԐM���󂯂邽�߂̌^��ݒ� �����ł� const tnl::Vector3& 
	// arg3... �ʒm�����ʂ��� ID ��ݒ�
	// arg4... �ʒm��̃C���X�^���X�� std::weak_ptr �Ŏw��
	// arg5... �~�ւ̒ʒm�ɕt������ݒ肷�� ( �����ł� bool �^ )
	// arg6... �����_���� {} �̂݋L�q ( �ʒm���e�̏��� )
	TNL_INTERACTOR_UNSAFE_ARGS_TRANSMITTER_REGISTER(button_move, const tnl::Vector3&, UIButton::eTnlICId::CALL_BALL_STOP, Weak<Circle>(circle), bool, {
		Shared<Circle> cir = TNL_INTERACTOR_GET_WEAK_REFERENCE(Weak<Circle>).lock();
		cir->setMoveFlag(TNL_INTERACTOR_GET_RECEIPT_INFORMATION());

		// �ԐM�Ƃ��� const tnl::Vector3& ��Ԃ� ( �~�̍��W )
		return cir->getPosition();
		});


	// color �{�^������ �~�ɑ΂��āu�F��ς���v�ʒm�������e��o�^
	// arg1... color �{�^�����ʒm���o���̂� �{�^���̃C���X�^���X
	// arg2... �ʒm����̕ԐM�͐ݒ肵�Ȃ��̂� void
	// arg3... �ʒm�����ʂ��� ID ��ݒ�
	// arg4... �ʒm��̃C���X�^���X�� std::weak_ptr �Ŏw��
	// arg5... �����_���� {} �̂݋L�q ( �ʒm���e�̏��� )
	// tips... ��L�Q�ƈ���ĉ~�ւ̕t������ݒ肵�Ȃ��}�N�� ( �}�N������ SEND �� VOID ���Ⴄ���ɗ��� )
	TNL_INTERACTOR_UNSAFE_TRANSMITTER_REGISTER(button_color_change, void, UIButton::eTnlICId::CALL_BALL_RANDOM_COLOR_CHENGE, Weak<Circle>(circle), {
		Shared<Circle> cir = TNL_INTERACTOR_GET_WEAK_REFERENCE(Weak<Circle>).lock();
		cir->randomColorChange();
		});

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {


	button_move->update();
	button_color_change->update();
	circle->update();


	button_move->draw();
	button_color_change->draw();
	circle->draw();

	DrawFormatString(0, 0, -1, "move �� color �̓}�E�X�N���b�N�Ŕ�������{�^���ł�");
	DrawFormatString(0, 20, -1, "stop ���N���b�N����Ɠ����Ă���~���~�܂�Amove �{�^�����~�̒��S�ɔz�u����܂�");

	DrawFormatString(0, 50, -1, "���̃T���v���̓{�^���Ɖ~�̊ԂŃ��f�B�G�[�^�p�^�[�����T�|�[�g���� TNL_INTERACTOR �̃T���v���ł�");
	DrawFormatString(0, 70, -1, "move ���N���b�N�����ƃ{�^���̏�Ԃ����� �~�ɑ΂��� �u����( true )�v�������� �u�~�܂�( false )�v�̒ʒm���s���܂�");
	DrawFormatString(0, 90, -1, "�u�~�܂�v�̒ʒm�������Ƃ��A�~�ɑ΂���ʒm�̕ԐM�Ƃ��ĉ~�̍��W���󂯎��A�{�^���̍��W���X�V���Ă��܂�");

	DrawFormatString(0, 120, -1, "color �{�^���͉~�ւ̒ʒm�ɂ����� move stop �̂悤�ɒʒm����t�����܂��� �܂��~����̕ԐM������܂���");


	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}




//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif
