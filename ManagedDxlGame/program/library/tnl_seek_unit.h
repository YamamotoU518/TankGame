#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <mutex>
#include "tnl_using.h"
#include "tnl_shared_factory.h"

namespace tnl {

	/* �}���`�X���b�h�𗘗p����v���W�F�N�g�ł� tnl_build_setting.h �� TNL_BUILD_SWITCH_USE_MULTI_THREDING �� true �ɐݒ肵�Ă������� */
#if TNL_BUILD_SWITCH_USE_MULTI_THREDING
#define TNL_SEEK_UNIT_LOCK_GUARD_MUTEX() std::lock_guard<std::mutex> lock(mutex_);
#else
#define TNL_SEEK_UNIT_LOCK_GUARD_MUTEX()
#endif


	class SeekUnit final {
	private :
		SeekUnit() = default;
	public:
		~SeekUnit() {}

		enum class ePlayMode {
			SINGLE,		// �P���Đ�
			REPEAT,		// ���s�[�g�Đ�
			REFLECTION	// ���]�Đ�( ���s�[�g )
		};
		enum class ePlayDir {
			FORWARD,	// �ʏ�
			REVERSE		// �t�Đ�
		};
		enum class eCondition {
			STANDBY,	// �ҋ@��
			PLAYING,	// �Đ���
			ENDED		// �Đ�����
		};
		enum class eFrameType {
			PREV,		// �O�̃t���[��
			CURRENT,	// ���݂̃t���[��
			NEXT		// ���̃t���[��
		};

		//-----------------------------------------------------------------------------------------------------------------
		// arg1... �Œ�t���[�����[�g
		// arg2... �S�̂̍Đ�����
		// arg3... ���t���[����
		// arg4... ePlayMode
		// arg5... ePlayDir
		// tips... ���t���[������ 0 ��ݒ肷��ƃt���[���Ǘ��ł͂Ȃ����Ԃ̊����ŊǗ��������̂Ƒz�肵�܂�
		//         ���̂��ߑ��t���[������ 0 ��ݒ肵���ꍇ ���\�b�h���� Frame �ƕt���Ă�����͔̂񐄏��ł�
		static Shared<SeekUnit> Create( float fix_fps, uint32_t total_frame_num, float total_time, ePlayMode play_mode, ePlayDir play_dir ) ;


		//-----------------------------------------------------------------------------------------------------------------
		// �Đ�
		// tips... �ꎞ��~�Ɏ��s�����ꍇ�͒�~�����ꏊ����̍Đ��ɂȂ�܂�
		// tips... �P���Đ��ōŌ�܂ōĐ����ꂽ��Ɏ��s����Ǝn�߂���̍Đ��ɂȂ�܂�
		void play();

		//-----------------------------------------------------------------------------------------------------------------
		// �ꎞ��~
		void pause();

		//-----------------------------------------------------------------------------------------------------------------
		// ���X�^�[�g( �n�߂���Đ� )
		void restart();

		//-----------------------------------------------------------------------------------------------------------------
		// �V�[�N�ꏊ�� 0 �` 1.0 �̊����Ŏw�肵���ꏊ�֔�΂�
		void jumpSeekRate(float seek_rate);

		//-----------------------------------------------------------------------------------------------------------------
		// �V�[�N�ꏊ�� �t���[���ԍ� �Őݒ肵���ꏊ�֔�΂�
		void jumpSeekFrame(uint32_t frame);

		//-----------------------------------------------------------------------------------------------------------------
		// �A�b�v�f�[�g����( ���t���[�����s���Ă������� )
		void update(float delta_time);


		//-------------------------------------------------------------------------------------------------------
		//
		// setter
		//
		// 

		// �Đ��X�e�[�g�ݒ�
		void setPlayState(ePlayMode play_mode, ePlayDir play_dir);

		// �S�̂̃X�s�[�h�X�P�[����ݒ�
		void setTimeScale(float time_scale);

		// �t���[���̍Đ��J�n���ɂP�x�������s�����R�[���o�b�N��ݒ�
		// arg1... �t���[���ԍ�
		// arg2... �R�[���o�b�N
		void setFrameTriggerCallback(int32_t frame, const std::function<void(const std::any&)>& callback);

		// setFrameTriggerCallback �̃R�[���o�b�N�֐��ŎQ�Ƃ���I�u�W�F�N�g��ݒ肷��
		void setFrameTriggerCallbacReference(const std::any& reference);


		//-------------------------------------------------------------------------------------------------------
		//
		// getter
		//

		// ���݂̏�Ԃ��擾
		eCondition getCondition() { return condition_; }

		// ���t���[�������擾
		inline uint32_t getTotalFrameNum() { return total_frame_num_; }

		// ���ݍĐ����̃t���[���ԍ����擾
		uint32_t getSeekFrame(eFrameType e_frame = eFrameType::CURRENT);

		// ���݂̃V�[�N�|�W�V������ 0 �` 1.0 �̊����Ŏ擾
		float getSeekRate() { return seek_position_ / total_time_; }

		// �S�̂̍Đ����Ԃ�ݒ�
		void setTotalTime(float total_time);


	private:
		mutable std::mutex mutex_;
		float fix_fps_ = 60.0f;
		float time_scale_ = 1.0f;
		float total_time_ = 0;
		float seek_position_ = 0;
		int32_t direction_ = 1;
		uint32_t total_frame_num_ = 0;
		std::function<void(const std::any&)> call_of_trigger_ = nullptr;
		std::vector<std::function<void(const std::any&)>> frame_callback_storage_;
		ePlayMode play_mode_ = ePlayMode::SINGLE;
		ePlayDir play_dir_ = ePlayDir::FORWARD;
		eCondition condition_ = eCondition::STANDBY;
		std::any frame_callback_reference_;

		// �V�[�N����
		void seekProcess(float delta_time);

		// ���t���[�����̐ݒ�
		void setTotalFrameNum(uint32_t frame_num = 0);

		// ���݂̃t���[���̃t���[��������̍Đ����Ԃ̊���
		float getSeekRateInFrame();

		// ��~
		void stop();

	};


}

