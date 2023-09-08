/* -----------------------------------------------------------------------------------------
|																						   |
|								キャラクターのDEFINE宣言								   |
|																						   |
+ --------------------------------------------------------------------------------------- */
// キャラサイズ
#define PC_WIDTH 80.0f
#define PC_HEIGHT 180.0f


#define EFFECT_SLASH_WIDTH_MAX 15
#define EFFECT_SLASH_WIDTH_MIN 1
#define EFFECT_SLASH_WIDTH_FRAME 3
#define EFFECT_SLASH_WIDTH_SIZE 200
#define EFFECT_SLASH_HEIGHT_SIZE 200

#define EFFECT_SLASH_RADIAN 315

#define CHARA_ENUM_DEFAULT_SIZE		500.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
#define CHARA_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数

#define CHARA_HIT_HEIGHT			700.0f		// 当たり判定カプセルの高さ

// キャラクターのデータファイルが格納されているフォルダ
#define CHARADATA_DIR					"..\\Data\\Data\\Character\\"
/* -----------------------------------------------------------------------------------------
|																						   |
|								     CHARAの構造体宣言									   |
|																						   |
+ --------------------------------------------------------------------------------------- */
// キャラクターの当たり判定の情報
typedef struct _SCharaHitInfo
{
	// 当たり判定の幅
	float                 Width;

	// 当たり判定の高さ
	float                 Height;

	// 当たり判定の中心座標
	VECTOR                CenterPosition;
} SCharaHitInfo;

// キャラ情報構造体
typedef struct _CharaInfo{
	int				model ;				// キャラのモデルを格納
	int				mode ;				// キャラの状態
	int				attachidx ;			// キャラの現在のアニメーションを格納（アタッチ）
	float			anim_totaltime ;	// アニメのトータルアニメ
	float			playtime ;			// アニメ再生時間
	int				rootflm ;			// アニメのルート
	VECTOR			pos ;				// キャラの座標 x,y,z
	VECTOR			move ;				// キャラの移動量 x,y,z
	float			direction ;			// キャラの向き
	SCharaHitInfo	charahitinfo ;		// キャラヒットチェック用情報

} SCharaInfo ;

typedef struct _WeaponInfo {
	int				model;
	VECTOR			pos;
	SCharaHitInfo	weaponhitinfo;
} SWeaponInfo ;


