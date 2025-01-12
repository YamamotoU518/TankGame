#pragma once
#include "../library/tnl_util.h"
#include "../library/tnl_vector2f.h"
#include "../library/tnl_seek_unit.h"
#include "../dxe/dxe_data.h"
#include "../dxe_build_setting.h"

namespace dxe {

	/* �}���`�X���b�h�𗘗p����v���W�F�N�g�ł� tnl_build_setting.h �� TNL_BUILD_SWITCH_USE_MULTI_THREDING �� true �ɐݒ肵�Ă������� */
#if DXE_BUILD_SWITCH_USE_MULTI_THREDING
#define DXE_FONT_TEXT_LOCK_GUARD_MUTEX() std::lock_guard<std::mutex> lock(mutex_);
#else
#define DXE_FONT_TEXT_LOCK_GUARD_MUTEX()
#endif

	class FontText final {
	private:
		FontText() = default;
	public:
		~FontText();

		// �A�j���[�V���������e�L�X�g�̍쐬
		// arg1... �t�H���g�T�C�Y
		// arg2... �t�H���g�� ( �ȗ��� "�l�r �o����" )
		// arg3... �N�I���e�B�ݒ� ( DX_FONTTYPE_**** )
		// arg4... �t�H���g�̑��� ( �ȗ� �� �f�t�H���g�� -1 )
		// arg5... �����g�̑��� ( �ȗ��͘g���� )
		// ret.... dxe::FontText �� std::shared_ptr
		static Shared<FontText> Create
			( int32_t font_size
			, const std::string& font_name = "�l�r �o����"
			, int32_t quality = -1
			, int32_t thick = -1
			, int32_t egge_size = -1);

		// �A�j���[�V�����e�L�X�g�̍쐬
		// arg1... �t�H���g�T�C�Y
		// arg2... �t�H���g�� ( �ȗ��� "�l�r �o����" )
		// arg3... �N�I���e�B�ݒ� ( DX_FONTTYPE_**** )
		// arg4... �t�H���g�̑��� ( �ȗ� �� �f�t�H���g�� -1 )
		// arg5... �����g�̑��� ( �ȗ��͘g���� )
		// ret.... dxe::FontText �� std::shared_ptr
		static Shared<FontText> CreateAnimation
			( int32_t font_size
			, const std::string& font_name = "�l�r �o����"
			, int32_t quality = -1
			, int32_t thick = -1
			, int32_t egge_size = -1);


		TNL_CALC_PROPERTY(tnl::Vector2f, Position, position_);
		TNL_PROPERTY(eRectOrigin, Location, location_);
		TNL_PROPERTY(int32_t, Color, color_);
		TNL_PROPERTY(int32_t, EdgeColor, edge_color_);
		TNL_SET_SELF_PROPERTY(std::string, String, base_text_);
		TNL_SET_SELF_PROPERTY(std::string, Font, font_name_);
		TNL_SET_SELF_PROPERTY(tnl::Vector2f, Scale, scale_);
		TNL_SET_SELF_PROPERTY(int32_t, FontSize, font_size_);
		TNL_SET_SELF_PROPERTY(int32_t, Thick, thick_);
		TNL_SET_SELF_PROPERTY(int32_t, Quality, quality_);
		TNL_SET_SELF_PROPERTY(int32_t, EdgeSize, edge_size_);

		void draw();

		void updateAnimation();
		void playAnimation();
		void pauseAnimation();
		void restartAnimation();
		void finishAnimation();

		void addAnimTimeScale(float add_scale);
		void setAnimTimeScale(float time_scale);
		void setAnimWaitTime(float wait_time);
		tnl::SeekUnit::eCondition getAnimCondition();
		void setAnimUpdateCallback( const std::function<void()>& callback );

		Shared<FontText> createClone(const Shared<FontText>& origine);

	private:
		mutable std::mutex		mutex_;
		std::string				base_text_;
		std::string				anim_draw_text_;
		std::string				font_name_;
		tnl::Vector2f			position_;
		tnl::Vector2f			scale_ = { 1, 1 };
		eRectOrigin				location_ = eRectOrigin::LEFT_TOP;
		int32_t					font_size_ = 20;
		int32_t					color_ = -1;
		int32_t					thick_ = -1;
		int32_t					quality_ = -1; /* DX_DX_FONTTYPE_ */
		int32_t					edge_color_ = -1;
		int32_t					edge_size_ = -1;
		int32_t					handle_ = -1;
		float					anim_wait_time_ = 0.1f;
		float					anim_time_scale_ = 1.0f;
		Shared<tnl::SeekUnit>	anim_seek_;
		std::function<void()>	anim_update_callback_;
		bool					is_extend_ = false;

		void refresh();
	};

}


