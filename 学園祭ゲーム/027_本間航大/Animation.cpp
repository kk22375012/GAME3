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
	MV1DetachAnim(Player[0].model, Player[0].attachidx);
	switch (Animation) {
		// 立ち状態の処理
		case STAND:
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_nutral);
			Player[0].mode = STAND;
			break;

		//走り状態の処理
		case RUN:
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_run);
			Player[0].mode = RUN;
			break;

		// ジャンプ開始時の処理
		case JUMPIN :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_jumpin);
			Player[0].mode = JUMPIN;
			break;

		// ジャンプ中の処理
		case JUMPLOOP :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_jumploop);
			Player[0].mode = JUMPLOOP;
			break;

		// ジャンプ終了時の処理
		case JUMPOUT :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_jumpout);
			Player[0].mode = JUMPOUT;
			break;

		// 攻撃時の処理
		case ATTACK :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_attack);
			Player[0].mode = ATTACK;
			break;
	}
	Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);
}

// ------------------------------------------------------------------------ //
//						エネミーのアニメーション							//
// ------------------------------------------------------------------------ //
void AnimationEnemy(int Animation) {
	MV1DetachAnim(Player[1].model, Player[1].attachidx);
	switch (Animation) {
		// 立ち状態の処理
		case E_STAND:
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_ntural);
			Player[1].mode = E_STAND;
			break;

		// ダメージを負う開始時の処理
		case E_BLOWIN :
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_blowin);
			Player[1].mode = E_BLOWIN;
			break;


		// ダメージ中の処理
		case E_BLOWLOOP :
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_blowloop);
			Player[1].mode = E_BLOWLOOP;
			break;

		// ダメージ終了時の処理
		case E_BLOWOUT :
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_blowout);
			Player[1].mode = E_BLOWOUT;
			break;
	}
	Player[1].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);

}



