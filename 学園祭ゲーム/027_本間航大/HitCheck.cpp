#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//					モデルと接触したポリゴンの検出ポリゴン					//
// ------------------------------------------------------------------------ //
void HitPolygonSearch() {
	HitDim = MV1CollCheck_Sphere(stagedata, -1, Player.pos, CHARA_ENUM_DEFAULT_SIZE + VSize(Player.move));
	WallNum = 0;
	FloorNum = 0;
	// 検出されたポリゴンの数だけ繰り返し
	for (int i = 0; i < HitDim.HitNum; i++) {
		// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.000001f) {
			printf("壁扱い\n");
			// 壁ポリゴンと判断された場合でも、キャラクターのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
			if (HitDim.Dim[i].Position[0].y > Player.pos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > Player.pos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > Player.pos.y + 1.0f) {
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (WallNum < CHARA_MAX_HITCOLL) {
					// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
					Wall[WallNum] = &HitDim.Dim[i];

					// 壁ポリゴンの数を加算する
					WallNum++;
				}
			}
		}
		else {
			// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
			if (FloorNum < CHARA_MAX_HITCOLL) {
				// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
				Floor[FloorNum] = &HitDim.Dim[i];

				// 床ポリゴンの数を加算する
				FloorNum++;
			}
		}
	}
}

// ------------------------------------------------------------------------ //
//						プレイヤーの床へのヒットチェック					//
// ------------------------------------------------------------------------ //
int FloorSearch() {
	float MaxY_poly;
	// 床ポリゴンに当たったかどうかのフラグを倒しておく
	HitFlag = 0;
	// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
	MaxY = 0.0f;
	MaxY_poly = 0.0f;

	// 床ポリゴンの数だけ繰り返し
	for (int i = 0; i < FloorNum; i++) {
		// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[0].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[0].mode == JUMPIN || Player[0].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
		LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// 当たっていなかったら何もしない
		if (LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
		if (HitFlag == 1 && MaxY > LineRes.Position.y) {
			continue;
		}

		// ポリゴンに当たったフラグを立てる
		HitFlag = 1;

		// 接触したＹ座標を保存する
		MaxY = LineRes.Position.y;
		MaxY_poly = Poly->Position[1].y;
	}


	return HitFlag;
}

// ------------------------------------------------------------------------ //
//						エネミーの床へのヒットチェック						//
// ------------------------------------------------------------------------ //
void E1_FloorSearch() {
	float E1_MaxY_poly;
	// 床ポリゴンに当たったかどうかのフラグを倒しておく
	E1_HitFlag = 0;
	// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
	E1_MaxY = 0.0f;
	E1_MaxY_poly = 0.0f;

	// 床ポリゴンの数だけ繰り返し
	for (int i = 0; i < FloorNum; i++) {
		// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[1].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[1].mode == JUMPIN || Player[1].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
		E1_LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// 当たっていなかったら何もしない
		if (E1_LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
		if (E1_HitFlag == 1 && E1_MaxY > E1_LineRes.Position.y) {
			continue;
		}

		// ポリゴンに当たったフラグを立てる
		E1_HitFlag = 1;

		// 接触したＹ座標を保存する
		E1_MaxY = E1_LineRes.Position.y;
		E1_MaxY_poly = Poly->Position[1].y;
	}
}

int CollisionBlock() {
	VECTOR cal_pos1 = VAdd(Player[1].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
	VECTOR cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, -25.0f, 0.0f));

	LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
		VGet(Player[0].pos.x - 100.0f, Player[0].pos.y, Player[0].pos.z - 100.0f),
		VGet(Player[0].pos.x + 100.0f, Player[0].pos.y, Player[0].pos.z + 100.0f));

//		VGet(-200.0f,   0.0f, -200.0f),
//		VGet( 200.0f, 200.0f,  200.0f));

//		VGet(m_block[0].GetBlockPosition().x - 100.0f, m_block[0].GetBlockPosition().y, m_block[0].GetBlockPosition().z - 100.0f),
//	VGet(m_block[0].GetBlockTopPosition().x + 100.0f, m_block[0].GetBlockTopPosition().y, m_block[0].GetBlockTopPosition().z + 100.0f));

	// 当たっていなかったら何もしない
	if (LineBlock.HitFlag == TRUE) {
		printf("aaaaaaa");
		// ポリゴンに当たったフラグを立てる
		HitFlag = 1;

		// 接触したＹ座標を保存する
		MaxY = LineBlock.Position.y;
	}


	return HitFlag;
}


