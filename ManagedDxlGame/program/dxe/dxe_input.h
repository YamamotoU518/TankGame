#pragma once
#include <stack>
#include "../library/tnl_vector2f.h"
#include "../library/tnl_using.h"
#include "../library/tnl_util.h"

namespace dxe {

	class Input {
	public :

		//---------------------------------------------------------------------------------------------------------------------------------
		enum class eJoypad {
			UNUSED, PAD1, PAD2, PAD3, PAD4, MAX
		};
		enum class fDualReaction { TNL_ENUM_BIT_FLAG(NONE), TNL_ENUM_BIT_FLAG(FIRST), TNL_ENUM_BIT_FLAG(SECOND) };
		enum class eDualFirstReaction { NONE, KEEP, PRESSED };
		enum class eDualSecondReaction { KEEP, PRESSED };

		//---------------------------------------------------------------------------------------------------------------------------------
		enum class eButton {

			//---------------------------------------------------------------------------------------------------------------
			//
			// keybord
			//
			KB_BACK				// BackSpace�L�[	D_DIK_BACK
			, KB_TAB			// Tab�L�[			D_DIK_TAB
			, KB_RETURN			// Enter�L�[		D_DIK_RETURN
			, KB_LSHIFT			// ��Shift�L�[		D_DIK_LSHIFT
			, KB_RSHIFT			// �EShift�L�[		D_DIK_RSHIFT
			, KB_LCONTROL		// ��Ctrl�L�[		D_DIK_LCONTROL
			, KB_RCONTROL		// �ECtrl�L�[		D_DIK_RCONTROL
			, KB_ESCAPE			// Esc�L�[			D_DIK_ESCAPE
			, KB_SPACE			// �X�y�[�X�L�[		D_DIK_SPACE
			, KB_PGUP			// PageUp�L�[		D_DIK_PGUP
			, KB_PGDN			// PageDown�L�[		D_DIK_PGDN
			, KB_END			// End�L�[			D_DIK_END
			, KB_HOME			// Home�L�[			D_DIK_HOME
			, KB_LEFT			// ���L�[			D_DIK_LEFT
			, KB_UP				// ��L�[			D_DIK_UP
			, KB_RIGHT			// �E�L�[			D_DIK_RIGHT
			, KB_DOWN			// ���L�[			D_DIK_DOWN
			, KB_INSERT			// Insert�L�[		D_DIK_INSERT
			, KB_DELETE			// Delete�L�[		D_DIK_DELETE
			, KB_MINUS			// �|�L�[			D_DIK_MINUS
			, KB_YEN			// ���L�[			D_DIK_YEN
			, KB_PREVTRACK		// �O�L�[			D_DIK_PREVTRACK
			, KB_PERIOD			// �D�L�[			D_DIK_PERIOD
			, KB_SLASH			// �^�L�[			D_DIK_SLASH
			, KB_LALT			// ��Alt�L�[		D_DIK_LALT
			, KB_RALT			// �EAlt�L�[		D_DIK_RALT
			, KB_SCROLL			// ScrollLock�L�[	D_DIK_SCROLL
			, KB_SEMICOLON		// �G�L�[			D_DIK_SEMICOLON
			, KB_COLON			// �F�L�[			D_DIK_COLON
			, KB_LBRACKET		// �m�L�[			D_DIK_LBRACKET
			, KB_RBRACKET		// �n�L�[			D_DIK_RBRACKET
			, KB_AT				// ���L�[			D_DIK_AT
			, KB_BACKSLASH		// �_�L�[			D_DIK_BACKSLASH
			, KB_COMMA			// �C�L�[			D_DIK_COMMA
			, KB_KANJI			// �����L�[			D_DIK_KANJI
			, KB_CONVERT		// �ϊ��L�[			D_DIK_CONVERT
			, KB_NOCONVERT		// ���ϊ��L�[		D_DIK_NOCONVERT
			, KB_KANA			// �J�i�L�[			D_DIK_KANA
			, KB_APPS			// �A�v���P�[�V�������j���[�L�[		D_DIK_APPS
			, KB_CAPSLOCK		// CaspLock�L�[		D_DIK_CAPSLOCK
			, KB_SYSRQ			// PrintScreen�L�[	D_DIK_SYSRQ
			, KB_PAUSE			// PauseBreak�L�[	D_DIK_PAUSE
			, KB_LWIN			// ��Win�L�[		D_DIK_LWIN
			, KB_RWIN			// �EWin�L�[		D_DIK_RWIN
			, KB_NUMLOCK		// �e���L�[NumLock�L�[		D_DIK_NUMLOCK
			, KB_NUMPAD0		// �e���L�[�O				D_DIK_NUMPAD0
			, KB_NUMPAD1		// �e���L�[�P				D_DIK_NUMPAD1
			, KB_NUMPAD2		// �e���L�[�Q				D_DIK_NUMPAD2
			, KB_NUMPAD3		// �e���L�[�R				D_DIK_NUMPAD3
			, KB_NUMPAD4		// �e���L�[�S				D_DIK_NUMPAD4
			, KB_NUMPAD5		// �e���L�[�T				D_DIK_NUMPAD5
			, KB_NUMPAD6		// �e���L�[�U				D_DIK_NUMPAD6
			, KB_NUMPAD7		// �e���L�[�V				D_DIK_NUMPAD7
			, KB_NUMPAD8		// �e���L�[�W				D_DIK_NUMPAD8
			, KB_NUMPAD9		// �e���L�[�X				D_DIK_NUMPAD9
			, KB_MULTIPLY		// �e���L�[���L�[			D_DIK_MULTIPLY
			, KB_ADD			// �e���L�[�{�L�[			D_DIK_ADD
			, KB_SUBTRACT		// �e���L�[�|�L�[			D_DIK_SUBTRACT
			, KB_DECIMAL		// �e���L�[�D�L�[			D_DIK_DECIMAL
			, KB_DIVIDE			// �e���L�[�^�L�[			D_DIK_DIVIDE
			, KB_NUMPADENTER	// �e���L�[�̃G���^�[�L�[	D_DIK_NUMPADENTER
			, KB_F1				// �e�P�L�[			D_DIK_F1
			, KB_F2				// �e�Q�L�[			D_DIK_F2
			, KB_F3				// �e�R�L�[			D_DIK_F3
			, KB_F4				// �e�S�L�[			D_DIK_F4
			, KB_F5				// �e�T�L�[			D_DIK_F5
			, KB_F6				// �e�U�L�[			D_DIK_F6
			, KB_F7				// �e�V�L�[			D_DIK_F7
			, KB_F8				// �e�W�L�[			D_DIK_F8
			, KB_F9				// �e�X�L�[			D_DIK_F9
			, KB_F10			// �e�P�O�L�[		D_DIK_F10
			, KB_F11			// �e�P�P�L�[		D_DIK_F11
			, KB_F12			// �e�P�Q�L�[		D_DIK_F12
			, KB_A				// �`�L�[			D_DIK_A
			, KB_B				// �a�L�[			D_DIK_B
			, KB_C				// �b�L�[			D_DIK_C
			, KB_D				// �c�L�[			D_DIK_D
			, KB_E				// �d�L�[			D_DIK_E
			, KB_F				// �e�L�[			D_DIK_F
			, KB_G				// �f�L�[			D_DIK_G
			, KB_H				// �g�L�[			D_DIK_H
			, KB_I				// �h�L�[			D_DIK_I
			, KB_J				// �i�L�[			D_DIK_J
			, KB_K				// �j�L�[			D_DIK_K
			, KB_L				// �k�L�[			D_DIK_L
			, KB_M				// �l�L�[			D_DIK_M
			, KB_N				// �m�L�[			D_DIK_N
			, KB_O				// �n�L�[			D_DIK_O
			, KB_P				// �o�L�[			D_DIK_P
			, KB_Q				// �p�L�[			D_DIK_Q
			, KB_R				// �q�L�[			D_DIK_R
			, KB_S				// �r�L�[			D_DIK_S
			, KB_T				// �s�L�[			D_DIK_T
			, KB_U				// �t�L�[			D_DIK_U
			, KB_V				// �u�L�[			D_DIK_V
			, KB_W				// �v�L�[			D_DIK_W
			, KB_X				// �w�L�[			D_DIK_X
			, KB_Y				// �x�L�[			D_DIK_Y
			, KB_Z				// �y�L�[			D_DIK_Z
			, KB_0 				// �O�L�[			D_DIK_0
			, KB_1				// �P�L�[			D_DIK_1
			, KB_2				// �Q�L�[			D_DIK_2
			, KB_3				// �R�L�[			D_DIK_3
			, KB_4				// �S�L�[			D_DIK_4
			, KB_5				// �T�L�[			D_DIK_5
			, KB_6				// �U�L�[			D_DIK_6
			, KB_7				// �V�L�[			D_DIK_7
			, KB_8				// �W�L�[			D_DIK_8
			, KB_9				// �X�L�[			D_DIK_9
			, KB_MAX

			//---------------------------------------------------------------------------------------------------------------
			//
			// mouse
			//
			, MOUSE_MIN = KB_MAX
			, MOUSE_LEFT = MOUSE_MIN	// �}�E�X���{�^��
			, MOUSE_RIGHT				// �}�E�X�E�{�^��
			, MOUSE_MIDDLE				// �}�E�X�����{�^��
			, MOUSE_MAX
			, MOUSE_NUM = MOUSE_MAX - MOUSE_MIN


			, UNIQUE_DEVICE_BUTTON_MAX = MOUSE_MAX

			//---------------------------------------------------------------------------------------------------------------
			//
			// joypad
			//
			, PAD_MIN = MOUSE_MAX
			, PAD_A	= PAD_MIN		// �`�{�^��
			, PAD_B					// �a�{�^��
			, PAD_X					// �w�{�^��
			, PAD_Y					// �x�{�^��
			, PAD_L					// �k�{�^��
			, PAD_R					// �q�{�^��
			, PAD_SELECT			// SELECT �{�^��
			, PAD_START				// START�{�^��
			, PAD_L_STICK			// L�X�e�B�b�N�{�^��
			, PAD_R_STICK			// R�X�e�B�b�N�{�^��
			, PAD_UP				// �\���L�[�@��
			, PAD_RIGHT				// �\���L�[�@��
			, PAD_DOWN				// �\���L�[�@��
			, PAD_LEFT				// �\���L�[�@��
			, PAD_L_STICK_UP		// L�X�e�B�b�N�@���@
			, PAD_L_STICK_RIGHT		// L�X�e�B�b�N�@���@
			, PAD_L_STICK_DOWN		// L�X�e�B�b�N�@���@
			, PAD_L_STICK_LEFT		// L�X�e�B�b�N�@���@
			, PAD_R_STICK_UP		// R�X�e�B�b�N�@���@
			, PAD_R_STICK_RIGHT		// R�X�e�B�b�N�@���@
			, PAD_R_STICK_DOWN		// R�X�e�B�b�N�@���@
			, PAD_R_STICK_LEFT		// R�X�e�B�b�N�@���@
			, PAD_L_TRIGGER			// L�g���K�[�L�[
			, PAD_R_TRIGGER			// R�g���K�[�L�[
			, PAD_MAX
			, PAD_BTN_NUM = PAD_MAX - PAD_MIN
			//---------------------------------------------------------------------------------------------------------------------------------

			, E_BUTTON_MAX = PAD_MAX
		};

		//---------------------------------------------------------------------------------------------------------------------------------
		enum class eVariable {
			MOUSE_VEL_X			// �}�E�X X ���W�ω���
			, MOUSE_VEL_Y		// �}�E�X Y ���W�ω���
			, MOUSE_VEL_W		// �}�E�X�z�C�[���ω���
			, PAD_L_STICK_X		// ���X�e�B�b�N X �� �X�|��
			, PAD_L_STICK_Y		// ���X�e�B�b�N Y �� �X�|��
			, PAD_R_STICK_X		// �E�X�e�B�b�N X �� �X�|��
			, PAD_R_STICK_Y		// �E�X�e�B�b�N Y �� �X�|��
			, PAD_L_TRIGGER		// ���g���K�[������
			, PAD_R_TRIGGER		// �E�g���K�[������
		};


		// ����
		// arg1... �L���X�e�[�W
		// arg2... �g�p����W���C�p�b�h
		static Shared<Input> Create(int32_t enable_stage = 0, eJoypad use_joypad_id = eJoypad::UNUSED) noexcept ;

		// ���͌��m�̗L���X�e�[�W�ݒ�
		// �ݒ肷��X�e�[�W
		static void ChangeEnableStage(int32_t target_satge) noexcept ;

		// �L���X�e�[�W��O��ݒ�֖߂�
		static void UndoEnableStage() noexcept ;

		// ���݂̗L���X�e�[�W���擾
		static int32_t GetEnableStage() noexcept { return running_stage_; }


		// �g�p����L�[�{�[�h�̃L�[��ǉ�
		// arg1... eButton ( �ό� )
		template<typename... tKeys>
		void addDetectKeybord(tKeys... iParams) noexcept {
			const eButton array[] = { static_cast<eButton>(iParams)... };
			for (eButton elem : array) {
				if (elem >= eButton::KB_MAX) continue;
				check_buttons_.emplace_back( elem );
			}
		}

		// �������ςȂ����͌��m
		// arg1... eButton ( �ό� )
		// ret.... [ ���͗L�� : true ] [ ���͖��� : false ]
		template<typename... tBtns>
		bool keep(tBtns... iParams) const noexcept {
			if (!checkEnable()) return false ;
			const eButton array[] = { static_cast<eButton>(iParams)... };
			for (eButton elem : array) {
				if (static_cast<int32_t>(elem) < static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)) {
					if (btn_keep[static_cast<int32_t>(elem)]) return true;
				}
				else {
					if (pad_keep[static_cast<int32_t>(elem) - static_cast<int32_t>(eButton::PAD_MIN)]) return true;
				}
			}
			return false;
		}

		// �����ꂽ�u��
		// arg1... eButton ( �ό� )
		// ret.... [ ���͗L�� : true ] [ ���͖��� : false ]
		template<typename... tBtns>
		bool pressed(tBtns... iParams) const noexcept {
			if (!checkEnable()) return false;
			const eButton array[] = { static_cast<eButton>(iParams)... };
			for (eButton elem : array) {
				if (static_cast<int32_t>(elem) < static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)) {
					if (0 != btn_trg_down[static_cast<int>(elem)]) return true;
				}
				else {
					if (0 != pad_trg_down[static_cast<int32_t>(elem) - static_cast<int32_t>(eButton::PAD_MIN)]) return true;
				}
			}
			return false;
		}

		// �����ꂽ�u��
		// arg1... eButton ( �ό� )
		// ret.... [ ���͗L�� : true ] [ ���͖��� : false ]
		template<typename... tBtns>
		bool released(tBtns... iParams) const noexcept {
			if (!checkEnable()) return false;
			const eButton array[] = { static_cast<eButton>(iParams)... };
			for (eButton elem : array) {
				if (static_cast<int32_t>(elem) < static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)) {
					if (0 != btn_trg_release[static_cast<int>(elem)]) return true;
				}
				else {
					if (0 != pad_trg_release[static_cast<int32_t>(elem) - static_cast<int32_t>(eButton::PAD_MIN)]) return true;
				}
			}
			return false;
		}


		// �������ςȂ��ł̘A�Ŕ���
		// arg1... eButton
		// arg2... ���߂ɉ�����Ă����x�ڂ̔�������b��ɍs����
		// arg3... �O�x�ڈȍ~�����b�Ԋu�ōs����
		// ret.... [ ���͗L�� : true ] [ ���͖��� : false ]
		bool barrage(eButton button, float first_time_space, float since_time_space) noexcept ;


		// ��x��������
		// arg1... eButton
		// arg2... ���莞�ԊԊu ( �b )
		// arg3... ��x�ڂ̓��͂ɑ΂��锽�� eDualFirstReaction [ �����Ȃ� : NONE ] [ �L�[�v���� : KEEP ] [ �u�Ԃ̂� : PRESSED ]
		// arg4... ��x�ڂ̓��͂ɑ΂��锽�� eDualSecondReaction [ �L�[�v���� : KEEP ] [ �u�Ԃ̂� : PRESSED ]
		// ret.... arg3,4 �Ŏw�肵���p�����[�^�ɂ���� ���͔��肪 fDualReaction �̃r�b�g�t���O���A�� ������͂���x�ڂ̓��͂��𔻒�ł��܂�
		fDualReaction dual(eButton button, float time_limit, eDualFirstReaction first_reaction = eDualFirstReaction::PRESSED, eDualSecondReaction second_reaction = eDualSecondReaction::PRESSED) noexcept;


		// �p�����[�^�œ�������͒l
		// arg1... eVariable
		// ret.... ���͂��������l ( 0 �͊�{�I�ɓ��͂Ȃ� )
		// tips1.. ���E�̃g���K�[�Ɋւ��� DirectInput �͍��E�g���K�[����̕ϐ���
		//         �Ǘ����Ă���֌W�� [ + �̈悪���g���K�[ ] [ - �̈悪�E�g���K�[ ]
		//         �ƂȂ��Ă��܂��A���̂��ߗ����𓯎���������� +- �����E����Ă��܂��̂Œ���
		//         �v����ɍ��E�g���K�[�͗����𓯎��g�p���Ȃ��d�l�ŃQ�[��������������ǂ�
		// tips2.. �E�X�e�B�b�N�Ɋւ��� �p�b�h�̎�ނɂ���Ă͔������Ȃ��\��������܂�
		// tips3.. �e�l�� -1.0f �` +1.0f �܂ł͈̔͂Ŏ擾�ł��܂�
		float getValue(eVariable type) const noexcept ;


		// �W���C�p�b�h�̓��͏��o��
		void drawDebugJoypadInfo(const tnl::Vector2f& position);


		// �X�e�B�b�N�X�|�ɂ��P��������臒l
		TNL_PROPERTY(float, StickThreshold, stick_threshold_);

		// �g���K�[�����ʂɂ��P��������臒l
		TNL_PROPERTY(float, TriggerThreshold, trigger_threshold_);



		//---------------------------------------------------------------------------------------------------------------------------
		//
		// �ȉ����[�U�[�g�p�֎~
		//
		static void Initialize() noexcept ;
		static void Update() noexcept ;
		static void Destroy() noexcept ;
	private :
		static constexpr float STICK_THRESHOLD_MAX = 32767.0f;
		static constexpr float TRIGGER_THRESHOLD_MAX = 255.0f;

		float btn_barrage_keep_time_count[static_cast<int32_t>(eButton::E_BUTTON_MAX)] = { 0 };
		float btn_barrage_keep_time_limit[static_cast<int32_t>(eButton::E_BUTTON_MAX)] = { 0 };
		float btn_dual_time_limit[static_cast<int32_t>(eButton::E_BUTTON_MAX)] = { 0 };

		char pad_keep[static_cast<int32_t>(eButton::PAD_BTN_NUM)] = { 0 };
		char pad_xor_down[static_cast<int32_t>(eButton::PAD_BTN_NUM)] = { 0 };
		char pad_trg_down[static_cast<int32_t>(eButton::PAD_BTN_NUM)] = { 0 };
		char pad_xor_release[static_cast<int32_t>(eButton::PAD_BTN_NUM)] = { 0 };
		char pad_trg_release[static_cast<int32_t>(eButton::PAD_BTN_NUM)] = { 0 };

		std::vector<eButton> check_buttons_;
		std::vector<eVariable> check_values_;
		int32_t enable_stage_ = 0;
		float stick_threshold_ = 0.3f;
		float trigger_threshold_ = 0.3f;
		eJoypad use_joypad_id_ = eJoypad::UNUSED;
		bool is_active_ = true;
		void update() noexcept ;
		bool checkEnable() const noexcept { return (is_active_ && (running_stage_ == enable_stage_)); }

		static char btn_keep[static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)] ;
		static char btn_xor_down[static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)] ;
		static char btn_trg_down[static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)] ;
		static char btn_xor_release[static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)] ;
		static char btn_trg_release[static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)] ;
		static char trg_mask_table_[static_cast<int32_t>(eButton::UNIQUE_DEVICE_BUTTON_MAX)];

		static std::vector<int> dxlib_button_table_;
		static std::stack<int32_t> before_stages_;
		static std::list<Weak<Input>> maneged_inputs_;
		static tnl::Vector2f before_mouse_point_;
		static tnl::Vector2f forword_mouse_point_;
		static int32_t running_stage_;
	};
	TNL_ENUM_CLASS_BIT_MASK_OPERATOR(Input::fDualReaction);
}

