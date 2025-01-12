#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// [ 入門 ] hello world
// 
// ※ 画面に hello world の文字が出力されるだけのサンプルです
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	// 文字列描画
	// 第一引数...x 座標
	// 第二引数...y 座標
	// 第三引数... 文字の色
	// 第四引数... 出力する文字列 ( 文字列は 『 " 』ダブルクォーテーション で囲います )
	DrawFormatString(570, 300, -1, "hello world");



	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}


//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
}


#endif