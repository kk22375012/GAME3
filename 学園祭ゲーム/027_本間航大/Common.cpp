
/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.cpp
	NAME	: kz-matsu

+ ------ Explanation of file --------------------------------------------------------------------------
       
	共通での処理、または汎用性がある関数や変数の実体宣言部

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

#include <windows.h>
#include <stdio.h>	// --- コンソール用

#include "Common.h"

/* -----------------------------------------------------------------------------------------
|
|       グローバル変数＆オブジェクトの実体宣言
|
+ --------------------------------------------------------------------------------------- */
// --- アニメーション
int plyanim_nutral, plyanim_run, plyanim_jumpin, plyanim_jumploop, plyanim_jumpout;
int plyanim_attack;

int gobanim_ntural, gobanim_blowin, gobanim_blowloop, gobanim_blowout;

// --- キー入力用変数
int key;

// シャドウマップハンドル
int ShadowMapHandle;

// ステージハンドル
int stagedata;
int skydata;
int blockdate[BLOCK_TYPE];

// ステージコリジョン情報
MV1_COLL_RESULT_POLY_DIM HitDim;					// キャラクターの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
int WallNum;										// 壁ポリゴンと判断されたポリゴンの数
int FloorNum;										// 床ポリゴンと判断されたポリゴンの数
MV1_COLL_RESULT_POLY* Wall[CHARA_MAX_HITCOLL];		// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
MV1_COLL_RESULT_POLY* Floor[CHARA_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

// 当たり判定
int HitFlag = FALSE;							// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
int E1_HitFlag = FALSE;								
MV1_COLL_RESULT_POLY* Poly;						// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
HITRESULT_LINE LineRes;							// 線分とポリゴンとの当たり判定の結果を代入する構造体
HITRESULT_LINE E1_LineRes;

// キャラがヒットした床のポリゴン表示の座標
VECTOR PolyCharaHitField[3];

// 床
float MaxY;
float E1_MaxY;
int StageMap[MAP_Y][MAP_X] = {
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
};

// マトリックス
MATRIX WeaponMatrix;

/* -----------------------------------------------------------------------------------------
|
|       グローバル関数の実装部
|
+ --------------------------------------------------------------------------------------- */

// --- コンソールウィンドウ
ConsoleWindow g_cWin;	

// --- アニメーション
void AnimationInit();
void AnimationPlayer(int);
void AnimationEnemy1(int);

// --- プレイヤー
SCharaInfo Player;
void PlayerInit();
void PlayerMove();

// --- 武器
SWeaponInfo PlayerSabel;
int WeponAttachFrameNum;
void WeaponInit();

// --- エネミー
SCharaInfo Enemy1;
void Enemy1Init();

// --- カメラ
VECTOR cpos;
VECTOR ctgt;
VECTOR cadd;

// --- モデルとの当たり判定
void HitPolygonSearch();
int FloorSearch();
void E1_FloorSearch();

// --- カメラの移動
void CameraMove();

// --- 描画
void Draw();



