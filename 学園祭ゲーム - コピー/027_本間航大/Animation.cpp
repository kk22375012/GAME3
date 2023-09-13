#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						アニメーションの初期セット							//
// ------------------------------------------------------------------------ //
void AnimationInit() {
	// -------------------------------- // 
	//		アニメーションの読み込み	//
	// -------------------------------- //
	plyanim_nutral = MV1LoadModel("..\\Data\\Player\\Anim_Neutral.mv1");		// 立ちアニメ
	plyanim_run = MV1LoadModel("..\\Data\\Player\\Anim_Run.mv1");				// 走りアニメ	
	plyanim_jumpin = MV1LoadModel("..\\Data\\Player\\Anim_Jump_In.mv1");		// ジャンプ入り始めアニメ
	plyanim_jumploop = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Loop.mv1");	// ジャンプループアニメ
	plyanim_jumpout = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Out.mv1");		// ジャンプ着地アニメ
	plyanim_attack = MV1LoadModel("..\\Data\\Player\\Anim_Attack1.mv1");		// 攻撃アニメ

	gobanim_ntural = MV1LoadModel("..\\Data\\Goblin\\Anim_Neutral.mv1");		// ゴブリンの立ちアニメーション
	gobanim_blowin = MV1LoadModel("..\\Data\\Goblin\\Anim_Blow_In.mv1");		// ゴブリンのダメージ開始アニメ
	gobanim_blowloop = MV1LoadModel("..\\Data\\Goblin\\Anim_Blow_Loop.mv1");	// ゴブリンのダメージ中アニメ
	gobanim_blowloop = MV1LoadModel("..\\Data\\Goblin\\Anim_Blow_Out.mv1");		// ゴブリンのダメージ終了後アニメ

}

// ------------------------------------------------------------------------ //
//						プレイヤーのアニメーション							//
// ------------------------------------------------------------------------ //
void AnimationPlayer( int Animation ) {
	MV1DetachAnim(Player.model, Player.attachidx);
	switch (Animation) {
		// 立ち状態の処理
		case STAND:
			Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_nutral);
			Player.mode = STAND;
			break;

		//走り状態の処理
		case RUN:
			Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_run);
			Player.mode = RUN;
			break;

		// ジャンプ開始時の処理
		case JUMPIN :
			Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_jumpin);
			Player.mode = JUMPIN;
			break;

		// ジャンプ中の処理
		case JUMPLOOP :
			Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_jumploop);
			Player.mode = JUMPLOOP;
			break;

		// ジャンプ終了時の処理
		case JUMPOUT :
			Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_jumpout);
			Player.mode = JUMPOUT;
			break;

		// 攻撃時の処理
		case ATTACK :
			Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_attack);
			Player.mode = ATTACK;
			break;
	}
	Player.anim_totaltime = MV1GetAttachAnimTotalTime(Player.model, Player.attachidx);
}

// ------------------------------------------------------------------------ //
//						エネミーのアニメーション							//
// ------------------------------------------------------------------------ //
void AnimationEnemy1(int Animation) {
	MV1DetachAnim(Enemy1.model, Enemy1.attachidx);
	switch (Animation) {
		// 立ち状態の処理
		case E_STAND:
			Enemy1.attachidx = MV1AttachAnim(Enemy1.model, 0, gobanim_ntural);
			Enemy1.mode = E_STAND;
			break;

		// ダメージを負う開始時の処理
		case E_BLOWIN :
			Enemy1.attachidx = MV1AttachAnim(Enemy1.model, 0, gobanim_blowin);
			Enemy1.mode = E_BLOWIN;
			break;


		// ダメージ中の処理
		case E_BLOWLOOP :
			Enemy1.attachidx = MV1AttachAnim(Enemy1.model, 0, gobanim_blowloop);
			Enemy1.mode = E_BLOWLOOP;
			break;

		// ダメージ終了時の処理
		case E_BLOWOUT :
			Enemy1.attachidx = MV1AttachAnim(Enemy1.model, 0, gobanim_blowout);
			Enemy1.mode = E_BLOWOUT;
			break;
	}
	Enemy1.anim_totaltime = MV1GetAttachAnimTotalTime(Player.model, Player.attachidx);

}



