﻿// ManagedDxlGame.cpp : アプリケーションのエントリ ポイントを定義します。
//
#pragma warning(disable:4819)
#include <Windows.h >
#include <chrono>
#pragma comment(lib,"winmm.lib")

#include "ManagedDxlGame.h"
#include "DxLib.h"
#include "program/dxe_build_setting.h"
#include "program/library/tnl_input.h"
#include "program/game/gm_main.h"
#include "program/dxe/dxe.h"

#define MAX_LOADSTRING 100



// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名


static std::chrono::system_clock::time_point clock_start, clock_end;
static std::chrono::system_clock::time_point fps_clock_start, fps_clock_end;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // DirectX バージョン設定
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // Log.txt の出力
    SetOutApplicationLogValidFlag(FALSE);

    // ウインドウが非アクティブでもアプリケーションを動かすか
    SetAlwaysRunFlag(DXE_ALLWAYS_RUN_FLAG);

    // 画面モード変更時( とウインドウモード変更時 )にグラフィックスシステムの設定やグラフィックハンドルを
    // リセットするかどうかを設定する
    // Flag :  TRUE=リセットする( デフォルト )  FALSE=リセットしない
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // ウィンドウモードで起動
    dxe::SetWindowMode(true);

    // ウィンドウサイズ設定
    SetGraphMode(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 32);

    // ScreenFlip 実行時にＶＳＹＮＣ待ちをするかどうかを設定する
    SetWaitVSyncFlag(TRUE);

    // 深度バッファのビット幅
    SetZBufferBitDepth(32);
    SetCreateDrawValidGraphZBufferBitDepth(32);

    // ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
    {
        // エラーが起きたら直ちに終了
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    // マウスポインタの表示状態を設定する
    dxe::SetVisibleMousePointer(true);

    // ファイルドラッグの受付可否
    SetDragFileValidFlag(TRUE);

    // キー入力制御の初期化
    HWND hWnd = GetMainWindowHandle();
    HDC hdc = GetDC(hWnd);

    // メルセンヌツイスター初期化
    tnl::SetSeedMersenneTwister32(static_cast<int>(time(0) % INT_MAX));

    // tnl 入力制御初期化
    tnl::Input::Initialize(hInstance, hWnd, hdc, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

    // dxe 入力制御 初期化
    dxe::Input::Initialize();

    // dxe ウィンドウモード設定 ( DirectX 初期化設定 )
    dxe::SetWindowMode(DxLib::GetWindowModeFlag());

    // DXライブラリ拡張 DirectX 初期化
    dxe::DirectXInitialize();

    // 計測開始時間初期化
    clock_start = std::chrono::system_clock::now();

    // ゲームスタート処理
    gameStart();

    // メッセージループ
    while (1)
    {

        // フレーム間の経過時間
        // マイクロ秒で計測して秒に変換
        clock_end = std::chrono::system_clock::now();
        double micro_seconds = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(clock_end - clock_start).count());
        float delta_time = static_cast<float>(micro_seconds / 1000.0 / 1000.0);
        clock_start = clock_end;

        if (ProcessMessage() == -1) {
            break;
        }

        char filepath[256] = { 0 };
        if (0 == GetDragFilePath(filepath)) {
            dxe::SetDragFilePath(filepath);
        }
        DragFileInfoClear();

        fps_clock_start = std::chrono::system_clock::now();

        // 画面をクリア
        ClearDrawScreen();

        // キー状態の更新
        tnl::Input::Update();
        dxe::Input::Update();

        // ウインドウモード切替
        if (tnl::Input::IsKeyDown(eKeys::KB_LALT, eKeys::KB_RALT)) {
            if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
                dxe::SetWindowMode(!dxe::GetWindowMode());
            }
        }

        // ゲームメインルーチン
        dxe::SetDeltaTime(delta_time);
        gameMain(delta_time);

        if (dxe::IsExitApplication()) break;

        // バックバッファをフリップ
        ScreenFlip();

        // フレームレートコントロール
        fps_clock_end = std::chrono::system_clock::now();
        double fps_mic = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(fps_clock_end - fps_clock_start).count());
        float fps_mils = static_cast<float>(fps_mic / 1000.0);
        dxe::SetUnlimitDeltaTime(fps_mils);
        float fps_lim = 1000.0f / ( DXE_FIX_FPS + 0.5f ) ;

        if (fps_lim > fps_mils) {
            timeBeginPeriod(1);
            Sleep(DWORD(fps_lim - fps_mils));
            timeEndPeriod(1);
        }
    }

    const int t_wait = 100;
    // ゲーム側の終了処理
    Sleep(t_wait);
    gameEnd();
    dxe::Input::Destroy();
    dxe::Texture::DestroyAllTextures();
    Sleep(t_wait);

    // DXライブラリ拡張 DirectX 解放
    Sleep(t_wait);
    dxe::DirectXRelease();
    Sleep(t_wait);

    // ＤＸライブラリ使用の終了処理
    //  DXライブラリ拡張 DirectX 解放 とバッティングするのでコメントアウト
    //DxLib_End();

    ReleaseDC(hWnd, hdc);

    return 0;
}



