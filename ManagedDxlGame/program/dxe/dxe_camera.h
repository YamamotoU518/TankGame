#pragma once
#include "../library/tnl_util.h"
#include "../library/tnl_math.h"
#include "../library/tnl_matrix.h"

namespace dxe {

	class Camera {
	public :

		enum class eDimension{ Type2D, Type3D };
		Camera(float screen_w, float screen_h, const eDimension dimension = eDimension::Type3D);
		virtual ~Camera() {}

		TNL_PROPERTY(eDimension, Dimension, dimension_);
		TNL_PROPERTY(float, Angle, angle_);
		TNL_PROPERTY(float, Aspect, aspect_);
		TNL_PROPERTY(float, Near, near_);
		TNL_PROPERTY(float, Far, far_);

		TNL_CALC_PROPERTY(tnl::Vector3, Position, position_);
		TNL_CALC_PROPERTY(tnl::Vector3, Target, target_);
		TNL_CALC_PROPERTY(tnl::Vector3, Upper, up_);

		TNL_PROPERTY(float, PositionX, position_.x);
		TNL_PROPERTY(float, PositionY, position_.y);
		TNL_PROPERTY(float, PositionZ, position_.z);
		TNL_PROPERTY(float, TargetX, target_.x);
		TNL_PROPERTY(float, TargetY, target_.y);
		TNL_PROPERTY(float, TargetZ, target_.z);
		TNL_PROPERTY(float, UpperX, up_.x);
		TNL_PROPERTY(float, UpperY, up_.y);
		TNL_PROPERTY(float, UpperZ, up_.z);

		// �X�N���[���̕�
		float getScreenWidth() { return screen_w_; }
		// �X�N���[���̍���
		float getScreenHeight() { return screen_h_; }

		// �r���[�s��̎擾
		const tnl::Matrix& getViewMatrix() const noexcept { return view_; }
		// �v���W�F�N�V�����s��̎擾
		const tnl::Matrix& getProjectionMatrix() const noexcept { return proj_; }

		// ���ʃx�N�g���̎擾
		virtual inline tnl::Vector3 forward() { return tnl::Vector3::Normalize(target_ - position_); }
		// �E�x�N�g���̎擾
		virtual inline tnl::Vector3 left() { return tnl::Vector3::Cross(forward(), { 0, 1, 0 }); }
		// �E�x�N�g���̎擾
		virtual inline tnl::Vector3 right() { return tnl::Vector3::Cross({ 0, 1, 0 }, forward()); }
		// ����x�N�g���̎擾
		virtual inline tnl::Vector3 back() { return tnl::Vector3::Normalize(position_ - target_); }


		//----------------------------------------------------------------------------------------------
		// work... �Q�[����ԍ��W���X�N���[�����W�֕ϊ�
		// arg1... �Q�[����ԍ��W
		// arg2... �J�������W�̉e�����ǂꂾ���󂯂邩
		// ret.... �X�N���[�����W
		// tips... 2D �J�����p
		tnl::Vector3 convertWorldToScreenPosition2D( const tnl::Vector3& world_position, float affect_weight = 1.0f );

		//----------------------------------------------------------------------------------------------
		// work... �X�N���[�����W���Q�[����ԍ��W�֕ϊ�
		// arg1... �X�N���[�����W
		// ret.... �Q�[����ԍ��W
		// tips... 2D �J�����p
		tnl::Vector3 convertScreenToWorldPosition2D( const tnl::Vector3& screen_position );


		//----------------------------------------------------------------------------------------------
		// work... �����䕽�ʂ̖@�����擾����
		// arg1... 6�̕��ʂ̂ǂꂩ
		// ret.... �����䕽�ʂ̖@��
		// tips... 3D �J�����p
		enum class eFlustum { Left, Right, Bottom, Top, Near, Far, Max };
		tnl::Vector3 getFlustumNormal(eFlustum flusum) ;

		// �X�V
		void update() ;

		// �f�o�b�O�p �J�����`��
		// arg1... �X�P�[��
		// arg2... �F
		// tips... 3D �p
		void render(float scale, uint32_t color = 0xffffff00) const ;

	protected :
		Camera() {}
		eDimension dimension_ = eDimension::Type3D;

		tnl::Matrix view_;
		tnl::Matrix proj_;

		// �J�����̂R�������W
		tnl::Vector3 position_;
		// �J�������R�����̂ǂ�����ʂ̒����ɂƂ炦�Ă��邩
		tnl::Vector3 target_;
		// �J�����́w��x���`����A�b�p�[�x�N�g��
		tnl::Vector3 up_ = tnl::Vector3(0, 1, 0);

		// �J�����̉�p ( �x )
		float angle_ = tnl::ToRadian(60.0f);
		// �J�����̃A�X�y�N�g�� ( �c���� )
		float aspect_ = 1.0f;
		// �J�����ɉf��͈͂̍ŋߋ���
		float near_ = 1.0f;
		// �J�����ɉf��͈͂̍ŉ�����
		float far_ = 50000.0f;

		float screen_w_ = 0;
		float screen_h_ = 0;

	};

}
