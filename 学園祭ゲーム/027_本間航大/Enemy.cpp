#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//							エネミーの初期セット							//
// ------------------------------------------------------------------------ //
void EnemyInit() {
	// ---------------------------- // 
	//		キャラ情報セット		//
	// ---------------------------- // 
	Player[1].pos = VGet(1000.0f, 0.0f, -400.0f);
	Player[1].direction = UP;
	Player[1].mode = E_STAND;
	Player[1].charahitinfo.Height = PC_HEIGHT;
	Player[1].charahitinfo.Width = PC_WIDTH;
	Player[1].charahitinfo.CenterPosition = Player[1].pos;
	Player[1].move = VGet(0.0f, 0.0f, 0.0f);

	// --------------------------- // 
	//		キャラモデルセット	   //
	// --------------------------- //
	Player[1].model = MV1LoadModel("..\\Data\\Ninja\\忍者_sub.mv1");
	Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_ntural);
	Player[1].anim_totaltime = MV1GetAttachAnimTotalTime(Player[1].model, Player[1].attachidx);
	// アニメーションして動いてもその場で動いてるような状態
	Player[1].rootflm = MV1SearchFrame(Player[1].model, "root");
	MV1SetFrameUserLocalMatrix(Player[1].model, Player[1].rootflm, MGetIdent());
	Player[1].playtime = 0.0f;

}



