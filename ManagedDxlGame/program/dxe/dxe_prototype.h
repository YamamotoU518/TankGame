#pragma once

#define DXE_PROTOTYPE_GET_RECT_ORIGIN_LOCATION				void GetRectOriginLocatePosition(float &x, float &y, int size_x, int size_y, eRectOrigin e_location);
#define DXE_PROTOTYPE_DRAW_STRING_F32						void DrawString(const tnl::Vector2f& pos, int color, eRectOrigin e_location, const char* str, ...) ;
#define DXE_PROTOTYPE_DRAW_STRING_TO_HANDLE					void DrawStringToHandle(const tnl::Vector2f& pos, int color, int font_hdl, eRectOrigin e_location, const char* str, ...) ;
#define DXE_PROTOTYPE_DRAW_LINE								void DrawLine(const tnl::Vector2f& pos, const tnl::Vector2f& v, const float length, const int color = -1);
#define DXE_PROTOTYPE_DRAW_BOX								void DrawBox(const tnl::Vector2f& pos, const float width, const float height, const bool fill = true, const int color = -1);
#define DXE_PROTOTYPE_DRAW_ROTA_BOX							void DrawRotaBox(const tnl::Vector2f& pos, float w, float h, float rad, int color = -1);
#define DXE_PROTOTYPE_DRAW_FPS_INDICATOR					void DrawFpsIndicator(const tnl::Vector2i& pos);
#define DXE_PROTOTYPE_DRAW_HEXAGON							void DrawHexagon(const tnl::Vector2f& pos, float width, int color = -1);
#define DXE_PROTOTYPE_DRAW_GRID_GROUND						void DrawGridGround(const Shared<dxe::Camera> camera, const float square_size, int row_num, int color = 0x99999999);
#define DXE_PROTOTYPE_DRAW_HEXAGON_GROUND					void DrawHexagonGround(const Shared<dxe::Camera> camera, const float hex_width, int row_num, bool is_draw_center_line = true, int color = 0x99999999);
#define DXE_PROTOTYPE_SET_DEFAULT_LIGHT_PARAM				void SetDefaultLightParameter(const std::string& file_path);
#define DXE_PROTOTYPE_DRAW_DEFAULT_LIGHT_GUI_CONTROLLER		void DrawDefaultLightGuiController();

#define DXE_PROTOTYPE_DRAW_AXIS								void DrawAxis(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const tnl::Quaternion& rot, const float length);
#define DXE_PROTOTYPE_DRAW_AABB								void DrawAABB(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const tnl::Vector3& size, const int color = 0x0000ffff);
#define DXE_PROTOTYPE_DRAW_OBB								void DrawOBB(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const tnl::Quaternion& rot, const tnl::Vector3& size, const int color = 0x00ff00ff);
#define DXE_PROTOTYPE_DRAW_BD_SPHERE						void DrawBdSphere(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const float radius);
#define DXE_PROTOTYPE_DRAW_3D_LINE							void DrawLine3DEx(const Shared<dxe::Camera> camera, const tnl::Vector3& st, const tnl::Vector3& en, const int color = -1);

#define DXE_PROTOTYPE_GET_DELTA_TIME						float GetDeltaTime();
#define DXE_PROTOTYPE_GET_DRAG_FILE_PATH_TRIGGER			std::string GetDragFilePathReadTrigger();

#define DXE_PROTOTYPE_IS_ENABLE_FILE_PATH					bool IsEnableFilePath(const char* file_name) ;
#define DXE_PROTOTYPE_IS_ENABLE_FONT_PATH					bool IsEnableFontPath(const char* font_name) ;

#define DXE_PROTOTYPE_GET_PATH_FROM_FILE_NAME				const char* GetPathFromFileName(const char* file_name) ;
#define DXE_PROTOTYPE_GET_FONT_PATH_FROM_NAME				const char* GetPathFromFontName(const char* font_name) ;

#define DXE_PROTOTYPE_GET_LOOK_AT_CAMERA_FACTOR				void GetLookAtCameraFactor(const float axis_x_angle, const float axis_y_angle, const float distance, tnl::Vector3& out_target_to_position);
#define DXE_PROTOTYPE_GET_FREE_LOOK_CAMERA_FACTOR			void GetFreeLookCameraFactor(const tnl::Vector3& position, const tnl::Vector3& target, float& out_axis_x_angle, float& out_axis_y_angle, float& out_distance);
#define DXE_PROTOTYPE_GET_TRANSFORM_CAMERA_FACTOR			void GetTransformCameraFactor(const tnl::Vector3& position, const tnl::Vector3& target, const tnl::Vector3& up, tnl::Quaternion& out_rot);

#define DXE_PROTOTYPE_SET_DRAG_FILE_PATH					void SetDragFilePath(const std::string& drag_file_path);
#define DXE_PROTOTYPE_SET_DELTA_TIME						void SetDeltaTime(float delta_time);
#define DXE_PROTOTYPE_SET_UNLIMIT_DELTA_TIME				void SetUnlimitDeltaTime(float delta_time);

#define DXE_PROTOTYPE_SET_WINDOW_MODE						void SetWindowMode(bool is_window);
#define DXE_PROTOTYPE_GET_WINDOW_MODE						bool GetWindowMode();

#define DXE_PROTOTYPE_EXIT_APPLICATION						void ExitApplication();
#define DXE_PROTOTYPE_IS_EXIT_APPLICATION					bool IsExitApplication();

#define DXE_PROTOTYPE_SET_VISIBLE_MOUSE_POINTER				void SetVisibleMousePointer(bool visible);
#define DXE_PROTOTYPE_GET_VISIBLE_MOUSE_POINTER				bool GetVisibleMousePointer();

#define DXE_PROTOTYPE_DIRECTX_INITIALIZE					void DirectXInitialize();
#define DXE_PROTOTYPE_RENDER_BEGIN							void DirectXRenderBegin();
#define DXE_PROTOTYPE_RENDER_END							void DirectXRenderEnd();
#define DXE_PROTOTYPE_RELEASE								void DirectXRelease();

#define DXE_PROTOTYPE_GET_DEPTH_STENCEL_STATE				ID3D11DepthStencilState* GetDepthStencilState(const eDepthStenclil mode);
#define DXE_PROTOTYPE_GET_BLEND_STATE						ID3D11BlendState* GetBlendState(const eBlendState state);
#define DXE_PROTOTYPE_GET_SAMPLER_STATE						ID3D11SamplerState* GetSamplerState(const eSamplerState state);
#define DXE_PROTOTYPE_GET_RASTERRIZE_STATE					ID3D11RasterizerState* GetRasterizerState(const eRasterizerState state);

