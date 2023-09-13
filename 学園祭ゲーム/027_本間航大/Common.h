
/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.h
	NAME	: kz-matsu

+ ------ Explanation of file --------------------------------------------------------------------------
       
	全てのファイルで共通のヘッダーファイル

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

/* -----------------------------------------------------------------------------------------
|
|       DEFINE宣言
|
+ --------------------------------------------------------------------------------------- */
// 一つのイベント辺りに指定できるオブジェクトの最大数
#define STAGE_EVENT_OBJECT_MAX_NUM					(16)

// コリジョンモデルの最大マテリアル数
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

// キャラクターアニメーションのFPS
#define CHARA_ANIM_FPS					(30)

// キャラクターに付けられるサブ３Ｄモデルの最大数
#define CHARA_MAX_SUBMODEL				(4)

// キャラクターの文字列データで使用できる最大文字数
#define CHARA_MAX_STRINGLENGTH			(64)

// キャラクターの１アニメーションで扱える攻撃判定情報の数
#define CHARA_ATTACK_MAX_NUM			(4)

// キャラクターの攻撃判定用位置情報の最大数
#define CHARA_ATTACK_POS_MAX_NUM		(4)

// ステージ選択
#define CHOICESTAGE 1

// ブロック
#define BLOCK_TYPE			10
#define TATAMI_BLOCK		1
#define BREAK_BLOCK			2
#define FALL_BLOCK			3
#define INVINCIBLE_BLOCK	4
#define MOVE_BLOCK			5
#define NEEDLE_BLOCK		6

#define WEAPON_HEIGHT 110.0f
#define WEAPON_WIDTH 6.0f

// プレイヤーの移動攻撃時の加速
#define PLAYER_ATTACK_SPEED 16.0f

// エネミーの怯み移動
#define ENEMY_KNOCKBACK 15.0f

// カメラの回転量
#define CAMERA_ROTATE 200.0f

// マップ
#define MAP_Y 10
#define MAP_X 10
/* -----------------------------------------------------------------------------------------
|
|       共通ヘッダー
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>
#include "CharaBase.h"
#include "StageData.h"
#include "Animation.h"

#include "ConsoleWindow.h"	// --- コンソールウィンドウ


#include "math.h"
#include <ctime>        // time
#include <cstdlib>      // srand,rand
#include "../../../../../Program Files/DxLib/DxLib.h"
/* -----------------------------------------------------------------------------------------
|
|       型宣言
|
+ --------------------------------------------------------------------------------------- */

// --- シーンの名前
enum SceneName
{
	eSceneBlank = -1 ,
	eSceneTitle ,
	eSceneChoice , 
	eScenePlay ,
	eSceneClear ,
	eSceneOver ,
} ;

// --- キャラの方向
enum Direction
{
	DOWN,
	LEFT,
	UP,
	RIGHT,
} ;

// --- キャラの状態
enum CharaMode
{
	STAND,		// 立ち待機
	RUN,		// 走り状態
	JUMPIN,		// ジャンプ開始
	JUMPLOOP,	// 上昇中
	JUMPOUT,	// 着地
	FALL,		// 落下中
	ATTACK,		// 攻撃
} ;

enum EnemyMode 
{
	E_STAND,		// 立ち待機
	E_BLOWIN,		// ダメージ開始
	E_BLOWLOOP,	// ダメージ中
	E_BLOWOUT,	// ダメージ終了
};

/* -----------------------------------------------------------------------------------------
|
|       構造体宣言
|
+ --------------------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------------------
|
|       プロトタイプ宣言
|
+ --------------------------------------------------------------------------------------- */
// --- アニメーション
extern void AnimationInit();
extern void AnimationPlayer(int);
extern void AnimationEnemy1(int);

// --- プレイヤー
extern void PlayerInit();
extern void PlayerMove();

// --- 武器
extern void WeaponInit();

// --- エネミー
extern void Enemy1Init();

// --- モデルとの当たり判定
extern void HitPolygonSearch();
extern int FloorSearch();
extern void E1_FloorSearch();

// --- カメラの移動
void CameraMove();

// --- 描画
extern void Draw();

/* -----------------------------------------------------------------------------------------
|
|       外部参照宣言
|
+ --------------------------------------------------------------------------------------- */
// --- コンソールウィンドウ
extern ConsoleWindow g_cWin ;	

// --- アニメーション
extern int plyanim_nutral, plyanim_run, plyanim_jumpin, plyanim_jumploop, plyanim_jumpout;
extern int plyanim_attack;

extern int gobanim_ntural, gobanim_blowin, gobanim_blowloop, gobanim_blowout;

// --- プレイヤー
extern SCharaInfo Player;

// --- 武器
extern SWeaponInfo PlayerSabel;
extern int WeponAttachFrameNum;

// --- エネミー
extern SCharaInfo Enemy1;

// --- カメラ
extern VECTOR cpos;
extern VECTOR ctgt;
extern VECTOR cadd;

// --- キー入力
extern int key;

// シャドウマップハンドル
extern int ShadowMapHandle;

// ステージハンドル
extern int stagedata;
extern int skydata;
extern int blockdate[BLOCK_TYPE];


// ステージコリジョン情報
extern MV1_COLL_RESULT_POLY_DIM HitDim;					// キャラクターの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
extern int WallNum;										// 壁ポリゴンと判断されたポリゴンの数
extern int FloorNum;										// 床ポリゴンと判断されたポリゴンの数
extern MV1_COLL_RESULT_POLY* Wall[CHARA_MAX_HITCOLL];		// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
extern MV1_COLL_RESULT_POLY* Floor[CHARA_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列


extern int HitFlag;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
extern int E1_HitFlag;					// エネミー用ヒットフラグ
extern MV1_COLL_RESULT_POLY* Poly;		// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
extern HITRESULT_LINE LineRes;			// 線分とポリゴンとの当たり判定の結果を代入する構造体
extern HITRESULT_LINE E1_LineRes;

// キャラがヒットした床のポリゴン表示の座標
extern VECTOR PolyCharaHitField[3];
extern float MaxY;
extern float E1_MaxY;

extern int StageMap[MAP_Y][MAP_X];

// マトリックス
extern MATRIX WeaponMatrix;

