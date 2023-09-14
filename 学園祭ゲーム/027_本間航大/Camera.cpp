#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//								カメラの移動関数							//
// ------------------------------------------------------------------------ //
void CameraMove() {
	if (key & PAD_INPUT_5) {
		cpos.z -= 12.0f;
	}

	// 上を押下 奥に移動
	if (key & PAD_INPUT_8) {
		cpos.z += 12.0f;
	}

	// 左を押下 左に移動
	if (key & PAD_INPUT_4) {
		cpos.x -= 12.0f;
	}

	// 右方向への移動処理
	if (key & PAD_INPUT_6) {
		cpos.x += 12.0f;
	}
	// Wキー
	if (key & PAD_INPUT_2) {
		cpos.y += 12.0f;
	}

	// Sキー
	if (key & PAD_INPUT_1) {
		cpos.y -= 12.0f;
	}

	// カメラの視点操作
	cpos.x;
	cpos.y;
	cpos.z;

	// カメラの注視点操作
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 200.0f;
	ctgt.z = cpos.z + 1000.0f;
}


