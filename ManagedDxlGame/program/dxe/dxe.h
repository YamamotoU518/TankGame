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

	// アプリケーションの終了
	DXE_PROTOTYPE_EXIT_APPLICATION;

	// ウインドウモードの設定( false でフルスクリーン )
	DXE_PROTOTYPE_SET_WINDOW_MODE;

	// 1フレームの経過秒数を取得
	DXE_PROTOTYPE_GET_DELTA_TIME;

	// マウスポインタの表示設定
	DXE_PROTOTYPE_SET_VISIBLE_MOUSE_POINTER;

	// 文字描画
	// arg1... 描画座標
	// arg2... 16進数カラー
	// arg3... 文字列全体のどこを基点として扱うか
	// arg4... 描画文字列 ( printfと同様 書式指定子可 )
	// arg5... 可変引数
	DXE_PROTOTYPE_DRAW_STRING_F32;

	// フォントハンドル指定文字描画
	// arg1... 描画座標
	// arg2... 16進数カラー
	// arg3... フォントハンドル
	// arg4... 文字列全体のどこを基点として扱うか
	// arg5... 描画文字列 ( printfと同様 書式指定子可 )
	// arg6... 可変引数
	DXE_PROTOTYPE_DRAW_STRING_TO_HANDLE;

	// ライン描画
	// arg1... 始点
	// arg2... 方向ベクトル
	// arg3... 長さ
	// arg4... 16進数カラー
	DXE_PROTOTYPE_DRAW_LINE;

	// 矩形描画
	// arg1... 矩形中心座標
	// arg2... 幅
	// arg3... 高さ
	// arg4... 塗りつぶすか
	// arg5... 16進数カラー
	DXE_PROTOTYPE_DRAW_BOX;

	// 回転矩形描画
	// arg1... 矩形中心座標
	// arg2... 幅
	// arg3... 高さ
	// arg4... ラジアン
	// arg5... 16進数カラー
	DXE_PROTOTYPE_DRAW_ROTA_BOX;

	// FPS インジケータ描画
	// arg1... 描画座標
	DXE_PROTOTYPE_DRAW_FPS_INDICATOR;

	// 正六角形を描画
	// arg1... 正六角の中心座標
	// arg2... 正六角の幅
	// arg3... 16進数カラー
	DXE_PROTOTYPE_DRAW_HEXAGON;


	// デバッグ用のグリッド地面
	// arg1... カメラ
	// arg2... グリッドマスのサイズ
	// arg3... グリッドを並べる個数 ( 偶数個で指定 )
	// arg4... 16進数カラー
	// tips... この関数を使用する前にカメラを生成して update 関数を実行してください
	DXE_PROTOTYPE_DRAW_GRID_GROUND;


	// 正六角形を敷き詰めた地面を描画
	// arg1... カメラ
	// arg2... 正六角形の幅
	// arg3... 縦横に何個並べるか
	// arg4... XYZ 軸を描画するか
	// arg5... 色
	// tips... この関数を使用する前にカメラを生成して update 関数を実行してください
	// tips... 軽い処理ではないのでデバッグ用途にしてください
	DXE_PROTOTYPE_DRAW_HEXAGON_GROUND;

	// デフォルトライトパラメータをリソースから設定
	// arg1... DrawDefaultLightGuiController で出力したバイナリファイルパス
	DXE_PROTOTYPE_SET_DEFAULT_LIGHT_PARAM;

	// デフォルトライトパラメータをコントロールするGUIを描画
	DXE_PROTOTYPE_DRAW_DEFAULT_LIGHT_GUI_CONTROLLER;

	// クライアント領域にドラッグされたファイルパスを取得する
	// ret... ファイルパス
	DXE_PROTOTYPE_GET_DRAG_FILE_PATH_TRIGGER;

	// 指定したファイル名のパスがリソース定数テーブルに登録されているか
	// arg1... 検索するファイル名
	DXE_PROTOTYPE_IS_ENABLE_FILE_PATH ;

	// 指定したフォント名のパスがリソース定数テーブルに登録されているか
	// arg1... 検索するフォント名
	DXE_PROTOTYPE_IS_ENABLE_FONT_PATH ;

	// ファイル名からパスを取得する
	DXE_PROTOTYPE_GET_PATH_FROM_FILE_NAME;

	// フォント名からパスを取得する
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


