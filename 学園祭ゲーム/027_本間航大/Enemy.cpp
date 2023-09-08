#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//							エネミーの初期セット							//
// ------------------------------------------------------------------------ //
void Enemy1Init() {
	// ---------------------------- // 
	//		キャラ情報セット		//
	// ---------------------------- // 
	Enemy1.pos = VGet(1000.0f, 0.0f, -400.0f);
	Enemy1.direction = DOWN;
	Enemy1.mode = E_STAND;
	Enemy1.charahitinfo.Height = PC_HEIGHT;
	Enemy1.charahitinfo.Width = PC_WIDTH;
	Enemy1.charahitinfo.CenterPosition = Enemy1.pos;
	Enemy1.move = VGet(0.0f, 0.0f, 0.0f);

	// --------------------------- // 
	//		キャラモデルセット	   //
	// --------------------------- //
	Enemy1.model = MV1LoadModel("..\\Data\\Goblin\\鮫_sub2.mv1");
	Enemy1.attachidx = MV1AttachAnim(Enemy1.model, 0, gobanim_ntural);
	Enemy1.anim_totaltime = MV1GetAttachAnimTotalTime(Enemy1.model, Enemy1.attachidx);
	// アニメーションして動いてもその場で動いてるような状態
	Enemy1.rootflm = MV1SearchFrame(Enemy1.model, "root");
	MV1SetFrameUserLocalMatrix(Enemy1.model, Enemy1.rootflm, MGetIdent());
	Enemy1.playtime = 0.0f;

}



