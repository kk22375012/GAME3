#include <DxLib.h>
#include "Common.h"
#include "../../../../../Program Files/DxLib/DxLib.h"

// ------------------------------------------------------------------------ //
//							プレイヤーの初期セット							//
// ------------------------------------------------------------------------ //
void PlayerInit() {
	// ---------------------------- // 
	//		キャラ情報セット		//
	// ---------------------------- //
<<<<<<< HEAD
	Player.pos = VGet(0.0f, 500.0f, 0.0f);		 // 草原
	Player.mode = STAND;
	Player.direction = DOWN;
	Player.charahitinfo.Height = PC_HEIGHT;
	Player.charahitinfo.Width = PC_WIDTH;
	Player.charahitinfo.CenterPosition = Player.pos;
	Player.move = VGet(0.0f, 0.0f, 0.0f);
=======
	if (CHOICESTAGE == 1) {
		Player[0].pos = VGet(0.0f, 500.0f, 0.0f);		 // 草原
	}
	else {
		Player[0].pos = VGet(500.0f, 800.0f, 2800.0f); // 洞窟
	}
	Player[0].mode = STAND;
	Player[0].direction = DOWN;
	Player[0].charahitinfo.Height = PC_HEIGHT;
	Player[0].charahitinfo.Width = PC_WIDTH;
	Player[0].charahitinfo.CenterPosition = Player[0].pos;
	Player[0].move = VGet(0.0f, 0.0f, 0.0f);
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584

	// ---------------------------- // 
	//		キャラモデルセット		//
	// ---------------------------^ // 
	Player[0].model = MV1LoadModel("..\\Data\\Ninja\\忍者.mv1");
	Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_nutral);
	Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);
	// アニメーションして動いてもその場で動いてるような状態
	Player[0].rootflm = MV1SearchFrame(Player[0].model, "root");
	MV1SetFrameUserLocalMatrix(Player[0].model, Player[0].rootflm, MGetIdent());
	Player[0].playtime = 0.0f;
}

// ------------------------------------------------------------------------ //
//							プレイヤーの移動関数							//
// ------------------------------------------------------------------------ //
void PlayerMove() {
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 下を押下 手前に移動
	if (key & PAD_INPUT_DOWN) {
<<<<<<< HEAD
		Player.move.x = 0.0f;
		Player.move.z = +12.0f;
		if (key & PAD_INPUT_7) {
			Player.move.z = 36.0f;
		}
		Player.direction = DOWN;
=======
		Player[0].move.x = 0.0f;
		Player[0].move.z = +12.0f;
		Player[0].direction = DOWN;
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584
	}

	// 上を押下 奥に移動
	if (key & PAD_INPUT_UP) {
<<<<<<< HEAD
		Player.move.x = 0.0f;
		Player.move.z = -12.0f;
		if (key & PAD_INPUT_7) {
			Player.move.z = -36.0f;
		}
		Player.direction = UP;
=======
		Player[0].move.x = 0.0f;
		Player[0].move.z = -12.0f;
		Player[0].direction = UP;
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584
	}

	// 左を押下 左に移動
	if (key & PAD_INPUT_LEFT) {
<<<<<<< HEAD
		Player.move.x = +12.0f;
		Player.move.z = 0.0f;
		if (key & PAD_INPUT_7) {
			Player.move.x = 36.0f;
		}
		Player.direction = LEFT;
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player.move.z = +12.0f;
			Player.direction = 0.5f;
=======
		Player[0].move.x = +12.0f;
		Player[0].move.z = 0.0f;
		Player[0].direction = LEFT;
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player[0].move.z = 12.0f;
			Player[0].direction = 0.5f;
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584
		}
		// 上を押下 奥に移動
		if (key & PAD_INPUT_UP) {
			Player[0].move.z = -12.0f;
			Player[0].direction = 1.5f;
		}
	}

	// 右方向への移動処理
	if (key & PAD_INPUT_RIGHT) {
<<<<<<< HEAD
		Player.move.x = -12.0f;
		Player.move.z = 0.0f;
		if (key & PAD_INPUT_7) {
			Player.move.x = -36.0f;
		}
		Player.direction = RIGHT;
=======
		Player[0].move.x = -12.0f;
		Player[0].move.z = 0.0f;
		Player[0].direction = RIGHT;
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player[0].move.z = +12.0f;
			Player[0].direction = 3.5f;
		}
		// 上を押下 奥に移動
		if (key & PAD_INPUT_UP) {
			Player[0].move.z = -12.0f;
			Player[0].direction = 2.5f;
		}
	}

	// 攻撃ボタン Dキー
/*	if (key & PAD_INPUT_6) {
		if (Player[0].mode == RUN) {
			if ((Player[0].direction >= 0) & (Player[0].direction < 1)) {
				Player[0].move.z += (Player[0].direction - 1) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (-Player[0].direction) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 1) & (Player[0].direction < 2)) {
				Player[0].move.z += (Player[0].direction - 1) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (Player[0].direction - 2) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 2) & (Player[0].direction < 3)) {
				Player[0].move.z += (3 - Player[0].direction) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (Player[0].direction - 2) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 3) & (Player[0].direction < 4)) {
				Player[0].move.z += (3 - Player[0].direction) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (4 - Player[0].direction) * Player[0]_ATTACK_SPEED;
			}
		}
		AnimationPlayer[0](ATTACK);
		Player[0].playtime = 0.0f;
		MV1SetAttachAnimTime(Player[0].model, Player[0].attachidx, Player[0].playtime);
	}
*/
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		Player.move.y = 1200.0f;
		printf("aaaaaaaa");
	}

	if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
		Player[0].move.x *= 2.0f;
		Player[0].move.z *= 2.0f;
	}

	if (Player[0].pos.x < -5300.0f) {
		if (Player[0].move.x < 0.0)
			Player[0].move.x = 0.0f;
	}
<<<<<<< HEAD
	if (Player.pos.x > 6640.0f) {
		if (Player.move.x > 0.0)
			Player.move.x = 0.0f;
=======
	if (Player[0].pos.x > 6150.0f) {
		if (Player[0].move.x > 0.0)
			Player[0].move.x = 0.0f;
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584
	}
	if (Player[0].pos.z > 4000.0f) {
		if (Player[0].move.z > 0)
			Player[0].move.z = 0.0f;
	}
	if (Player[0].pos.z < -6640.0f) {
		if (Player[0].move.z < 0)
			Player[0].move.z = 0.0f;
	}
}



