#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//								描画関数									//
// ------------------------------------------------------------------------ //
void Draw() {
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(ShadowMapHandle);

	// モデルの描画 - 影の描画
	MV1DrawModel(Player[0].model);
	MV1DrawModel(Player[1].model);

	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, ShadowMapHandle);

	// 地面(配置)＆描画
	MV1DrawModel(skydata);
	MV1DrawModel(stagedata);

	blockcnt = 0;
	for (blockcnt = 0; blockcnt < 100; blockcnt++) {
		if (m_block[blockcnt].GetBlockFlag() == TRUE) {
			MV1DrawModel(m_block[blockcnt].b_model);
		}
	}

	DrawTriangle3D(PolyCharaHitField[0], PolyCharaHitField[1], PolyCharaHitField[2],
		GetColor(255, 0, 0), TRUE);

	// モデルの描画
	MV1DrawModel(Player[0].model);
	MV1DrawModel(Player[1].model);
	MV1DrawModel(PlayerSabel.model);
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

}



