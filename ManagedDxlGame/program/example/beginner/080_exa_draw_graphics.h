#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// [ 入門 ] 画像描画サンプル ( ゲーム業界では 2D画像描画 を スプライト描画 と呼んだりします )
//
// ※ リソースファイルの画像ファイルをロードして描画するサンプルです
//
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


// ロードした画像を識別するハンドル変数
int graphics_handle = 0;


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
	SetFontSize(30);

	// 画像ファイルのロード
	// 指定するファイル名はプロジェクトのルートフォルダからのパスになります
	// ! ロードは重い処理でメモリも消費します　必要な時に１度だけ実行しましょう ( 毎フレーム実行されないよう工夫しましょう )
	graphics_handle = LoadGraph("resource/graphics/example/paper.png");
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	// tips... 描画処理を含め、プログラムは基本的に 『 左から右に 』、『 上から下に 』向かって処理されます
	//         つまり、描画処理も先に実行された画像が奥に描画されます
	//         背景などの奥に描画したい画像はキャラクタ等よりも先に描画しましょう


	// 画像の描画処理
	// 第１引数... x 座標
	// 第２引数... y 座標
	// 第３引数... 拡大率
	// 第４引数... 回転角度 ( ラジアン指定 )
	// 第５引数... 画像に埋め込まれた透明度を有効にするか
	DrawRotaGraph(400, 400, 1.0, 0, graphics_handle, true);

	// 同じハンドルを使って２つ目を描画する ( 90 度回転させてみる )
	DrawRotaGraph(800, 400, 1.0, tnl::ToRadian(90), graphics_handle, true);



	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}


//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
}


#endif