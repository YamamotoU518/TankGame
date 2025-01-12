#pragma once
#pragma warning(disable:4819)

//---------------------------------------------------------------------------------------------------------------------------------
// 
// dxlib extension [ dxe ] ver. 2024f
// 
//---------------------------------------------------------------------------------------------------------------------------------

#include "../library/tnl_util.h"
#include "../library/tnl_csv.h"
#include "../library/tnl_input.h"
#include "../library/tnl_intersect.h"
#include "../library/tnl_math.h"
#include "../library/tnl_matrix.h"
#include "../library/tnl_quaternion.h"
#include "../library/tnl_sequence.h"
#include "../library/tnl_shared_factory.h"
#include "../library/tnl_vector2i.h"
#include "../library/tnl_vector2f.h"
#include "../library/tnl_vector3.h"
#include "../library/tnl_seek_unit.h"
#include "../library/tnl_rect.h"
#include "../library/tnl_interactor.h"
#include "../library/stb_image.h"
#include "../library/json11.hpp"
#include "DxLib.h"
#include "../dxe_build_setting.h"
#include "dxe_data.h"
#include "dxe_camera.h"
#include "dxe_prototype.h"
#include "dxe_texture.h"
#include "dxe_graphics_layer.h"
#include "dxe_font_text.h"
#include "dxe_input.h"
#include "mesh/dxe_mesh.h"
#include "mesh/dxe_inst_mesh.h"
#include "gui/dxe_gui_value_slider.h"
#include "gui/dxe_gui_menu_selector.h"
#include "gui/dxe_gui_drag_box.h"
#include "gui/dxe_gui_input_box.h"
#include "gui/dxe_gui_check_box.h"
#include "effects/dxe_shadow_map.h"
#include "effects/dxe_particle.h"
#include "effects/dxe_water_plane.h"
#include "../../ResourceConstantHedder.h"

namespace dxe {

	// �A�v���P�[�V�����̏I��
	DXE_PROTOTYPE_EXIT_APPLICATION;

	// �E�C���h�E���[�h�̐ݒ�( false �Ńt���X�N���[�� )
	DXE_PROTOTYPE_SET_WINDOW_MODE;

	// 1�t���[���̌o�ߕb�����擾
	DXE_PROTOTYPE_GET_DELTA_TIME;

	// �}�E�X�|�C���^�̕\���ݒ�
	DXE_PROTOTYPE_SET_VISIBLE_MOUSE_POINTER;

	// �����`��
	// arg1... �`����W
	// arg2... 16�i���J���[
	// arg3... ������S�̂̂ǂ�����_�Ƃ��Ĉ�����
	// arg4... �`�敶���� ( printf�Ɠ��l �����w��q�� )
	// arg5... �ψ���
	DXE_PROTOTYPE_DRAW_STRING_F32;

	// �t�H���g�n���h���w�蕶���`��
	// arg1... �`����W
	// arg2... 16�i���J���[
	// arg3... �t�H���g�n���h��
	// arg4... ������S�̂̂ǂ�����_�Ƃ��Ĉ�����
	// arg5... �`�敶���� ( printf�Ɠ��l �����w��q�� )
	// arg6... �ψ���
	DXE_PROTOTYPE_DRAW_STRING_TO_HANDLE;

	// ���C���`��
	// arg1... �n�_
	// arg2... �����x�N�g��
	// arg3... ����
	// arg4... 16�i���J���[
	DXE_PROTOTYPE_DRAW_LINE;

	// ��`�`��
	// arg1... ��`���S���W
	// arg2... ��
	// arg3... ����
	// arg4... �h��Ԃ���
	// arg5... 16�i���J���[
	DXE_PROTOTYPE_DRAW_BOX;

	// ��]��`�`��
	// arg1... ��`���S���W
	// arg2... ��
	// arg3... ����
	// arg4... ���W�A��
	// arg5... 16�i���J���[
	DXE_PROTOTYPE_DRAW_ROTA_BOX;

	// FPS �C���W�P�[�^�`��
	// arg1... �`����W
	DXE_PROTOTYPE_DRAW_FPS_INDICATOR;

	// ���Z�p�`��`��
	// arg1... ���Z�p�̒��S���W
	// arg2... ���Z�p�̕�
	// arg3... 16�i���J���[
	DXE_PROTOTYPE_DRAW_HEXAGON;


	// �f�o�b�O�p�̃O���b�h�n��
	// arg1... �J����
	// arg2... �O���b�h�}�X�̃T�C�Y
	// arg3... �O���b�h����ׂ�� ( �����Ŏw�� )
	// arg4... 16�i���J���[
	// tips... ���̊֐����g�p����O�ɃJ�����𐶐����� update �֐������s���Ă�������
	DXE_PROTOTYPE_DRAW_GRID_GROUND;


	// ���Z�p�`��~���l�߂��n�ʂ�`��
	// arg1... �J����
	// arg2... ���Z�p�`�̕�
	// arg3... �c���ɉ����ׂ邩
	// arg4... XYZ ����`�悷�邩
	// arg5... �F
	// tips... ���̊֐����g�p����O�ɃJ�����𐶐����� update �֐������s���Ă�������
	// tips... �y�������ł͂Ȃ��̂Ńf�o�b�O�p�r�ɂ��Ă�������
	DXE_PROTOTYPE_DRAW_HEXAGON_GROUND;

	// �f�t�H���g���C�g�p�����[�^�����\�[�X����ݒ�
	// arg1... DrawDefaultLightGuiController �ŏo�͂����o�C�i���t�@�C���p�X
	DXE_PROTOTYPE_SET_DEFAULT_LIGHT_PARAM;

	// �f�t�H���g���C�g�p�����[�^���R���g���[������GUI��`��
	DXE_PROTOTYPE_DRAW_DEFAULT_LIGHT_GUI_CONTROLLER;

	// �N���C�A���g�̈�Ƀh���b�O���ꂽ�t�@�C���p�X���擾����
	// ret... �t�@�C���p�X
	DXE_PROTOTYPE_GET_DRAG_FILE_PATH_TRIGGER;

	// �w�肵���t�@�C�����̃p�X�����\�[�X�萔�e�[�u���ɓo�^����Ă��邩
	// arg1... ��������t�@�C����
	DXE_PROTOTYPE_IS_ENABLE_FILE_PATH ;

	// �w�肵���t�H���g���̃p�X�����\�[�X�萔�e�[�u���ɓo�^����Ă��邩
	// arg1... ��������t�H���g��
	DXE_PROTOTYPE_IS_ENABLE_FONT_PATH ;

	// �t�@�C��������p�X���擾����
	DXE_PROTOTYPE_GET_PATH_FROM_FILE_NAME;

	// �t�H���g������p�X���擾����
	DXE_PROTOTYPE_GET_FONT_PATH_FROM_NAME;




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DXE_PROTOTYPE_GET_RECT_ORIGIN_LOCATION;
	DXE_PROTOTYPE_DRAW_AXIS;
	DXE_PROTOTYPE_DRAW_AABB;
	DXE_PROTOTYPE_DRAW_OBB;
	DXE_PROTOTYPE_DRAW_BD_SPHERE;
	DXE_PROTOTYPE_DRAW_3D_LINE;

	DXE_PROTOTYPE_GET_LOOK_AT_CAMERA_FACTOR;
	DXE_PROTOTYPE_GET_FREE_LOOK_CAMERA_FACTOR;
	DXE_PROTOTYPE_GET_TRANSFORM_CAMERA_FACTOR;

	DXE_PROTOTYPE_SET_DRAG_FILE_PATH;
	DXE_PROTOTYPE_SET_DELTA_TIME;
	DXE_PROTOTYPE_SET_UNLIMIT_DELTA_TIME;

	DXE_PROTOTYPE_GET_VISIBLE_MOUSE_POINTER;
	DXE_PROTOTYPE_GET_WINDOW_MODE;
	DXE_PROTOTYPE_IS_EXIT_APPLICATION;
	DXE_PROTOTYPE_DIRECTX_INITIALIZE;
	DXE_PROTOTYPE_RENDER_BEGIN;
	DXE_PROTOTYPE_RENDER_END;
	DXE_PROTOTYPE_RELEASE;

	DXE_PROTOTYPE_GET_DEPTH_STENCEL_STATE;
	DXE_PROTOTYPE_GET_BLEND_STATE;
	DXE_PROTOTYPE_GET_SAMPLER_STATE;
	DXE_PROTOTYPE_GET_RASTERRIZE_STATE;

}

/*

class GameCamera : public dxe::Camera {
public :

	GameCamera(){};
	GameCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h){}

	enum class eCtrlMode {
		LOOK_AT, FREE_LOOK, TRANSFORM
	};
	inline void setControllMode( eCtrlMode mode ) noexcept { ctrl_mode_ = mode; }
	inline eCtrlMode getControllMode()const noexcept { return ctrl_mode_; }

	void update();


	void lookAtToOther();
	void freeLookToOther();
	void transformToOhter();


	eCtrlMode ctrl_mode_ = eCtrlMode::FREE_LOOK;

	// mode freelook param
	float to_target_distance_ = 300 ;
	float axis_x_angle_ = tnl::ToRadian(45);
	float axis_y_angle_ = 0;

	// mode transform param
	tnl::Quaternion rot_;

};


void GameCamera::lookAtToOther() {
	rot_ = tnl::Quaternion::LookAt(pos_, target_, up_);

	tnl::Vector3 invlook = pos_ - target_;
	to_target_distance_ = invlook.length();
	tnl::Vector3 vx = tnl::Vector3::Normalize(invlook.xz() );
	tnl::Vector3 vy = tnl::Vector3::Normalize(invlook);
	axis_y_angle_ = (invlook.x < 0)? vx.angle({ 0, 0, -1 }) : -vx.angle({ 0, 0, -1 });
	axis_x_angle_ = (invlook.y < 0)? -vy.angle(vx) : vy.angle(vx) ;
}

void GameCamera::freeLookToOther() {
	tnl::Quaternion  q = tnl::Quaternion::RotationAxis( {0, 1, 0}, axis_y_angle_);
	tnl::Vector3 vz = tnl::Vector3::TransformCoord({ 0, 0, 1 }, q);
	q *= tnl::Quaternion::RotationAxis(tnl::Vector3::Cross({0, 1, 0}, vz), axis_x_angle_);
	pos_ = target_ + tnl::Vector3::TransformCoord({ 0, 0, -to_target_distance_ }, q);

	rot_ = tnl::Quaternion::LookAt(pos_, target_, up_);
}

void GameCamera::transformToOhter() {

	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, to_target_distance_ }, rot_);

	tnl::Vector3 invlook = pos_ - target_;
	to_target_distance_ = invlook.length();
	tnl::Vector3 vx = tnl::Vector3::Normalize(invlook.xz());
	tnl::Vector3 vy = tnl::Vector3::Normalize(invlook);
	axis_y_angle_ = (invlook.x < 0) ? vx.angle({ 0, 0, -1 }) : -vx.angle({ 0, 0, -1 });
	axis_x_angle_ = (invlook.y < 0) ? -vy.angle(vx) : vy.angle(vx);

}


void GameCamera::update() {
	switch ( ctrl_mode_ ) {
	case eCtrlMode::LOOK_AT :
		lookAtToOther();
		break;
	case eCtrlMode::FREE_LOOK :
		freeLookToOther();
		break;
	case eCtrlMode::TRANSFORM:
		transformToOhter();
		break;
	}
	dxe::Camera::update();
}
*/


