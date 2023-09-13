
#include "Common.h"		// --- 全ファイルでの共通ヘッダー

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int stagedata_c ;
	float camera_direction = 0.0f;

	char str[100];
	// 全体的なゲームの管理
	int gamemode = eSceneBlank ;

	//ステージのポジション
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// カメラポジション cpos:カメラ位置　ctgt:カメラ注視点
	cpos = VGet(0.0f,1400.0f,0.0f) ;
	ctgt = VGet(0.0f,500.0f,-400.0f) ;
	cadd = VGet(0.0f, 0.0f, 0.0f);

	VECTOR Position ;


	ChangeWindowMode(TRUE) ;

	SetGraphMode(900,600,32) ;

	// DXライブラリの初期化				DXライブラリースタート
	if(DxLib_Init() == -1) return -1 ;

	AnimationInit();
	PlayerInit();
	WeaponInit();
	Enemy1Init();

	// ステージ情報の読み込み
	stagedata = MV1LoadModel("..\\Data\\Stage\\Stage00.mv1") ;
	skydata = MV1LoadModel("..\\Data\\Stage\\Stage00_sky.mv1");
	MV1SetUseZBuffer(skydata, false);
	// ブロックモデルの読み込み
	blockdate[TATAMI_BLOCK] = MV1LoadModel("..\\Data\\Stage\\畳.mv1");
	// マップデータに反映
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			switch (StageMap[y][x]) {
				case TATAMI_BLOCK :
					StageMap[y][x] = MV1DuplicateModel(blockdate[TATAMI_BLOCK]);
					break;
			}
		}
	}



	// シャドウマップハンドルの作成


	// ライトの方向を設定
	SetLightDirection( VGet( 0.5f, -0.5f, -0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, -0.5f ) ) ;

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -6000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	stagedata_c = MV1LoadModel("..\\Data\\Stage\\Stage00_c.mv1") ;
	if(stagedata == -1) return -1 ;

	// モデル全体のコリジョン情報のセットアップ
	MV1SetupCollInfo( stagedata, -1 ) ;

	SetDrawScreen(DX_SCREEN_BACK) ;

	int MeshNum ;

	// モデルに含まれるメッシュの数を取得する
    MeshNum = MV1GetMeshNum( stagedata ) ;

    // メッシュの数だけループ
    for(int i = 0 ; i < MeshNum ; i ++ ){
	// メッシュに含まれる頂点のローカル座標の最大座標値を描画
		Position = MV1GetMeshMaxPosition( stagedata, i ) ;
//		DrawFormatString( 0, 112, GetColor( 255,255,255 ), "Max Position          x %f  y %f  z %f", Position.x, Position.y, Position.z ) ;

		// メッシュに含まれる頂点のローカル座標の最小座標値を描画
		Position = MV1GetMeshMinPosition( stagedata, i ) ;
//		DrawFormatString( 0, 128, GetColor( 255,255,255 ), "Min Position          x %f  y %f  z %f", Position.x, Position.y, Position.z ) ;

	}
	/* ------------------------------------------------------------------------------------------------
												ゲームループ										
	 ----------------------------------------------------------------------------------------------- */
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		PolyCharaHitField[0] = VGet(0.0f,0.0f,0.0f) ;
		PolyCharaHitField[1] = VGet(0.0f,0.0f,0.0f) ;
		PolyCharaHitField[2] = VGet(0.0f,0.0f,0.0f) ;
		MV1SetUseZBuffer(skydata, false);

						
		switch(gamemode){
			case eSceneBlank :
				gamemode = eSceneTitle;
				break;

			case eSceneTitle:

				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
				}
				break;

			case eSceneChoice:
				cpos = VGet(0.0f, 1000.0f, -100.0f);
				ctgt = VGet(0.0f, 500.0f, 0.0f);
				cadd = VGet(0.0f, 0.0f, 0.0f);

				Player.pos = VGet(200.0f, 200.0f, 0.0f);
				Enemy1.pos = VGet(600.0f, 300.0f, 200.0f);

				// モデルの移動(配置)
				MV1SetRotationXYZ(Player.model, VGet(0.0f, 1.57f * Player.direction, 0.0f));
				MV1SetPosition(Player.model, Player.pos);
				MV1SetRotationXYZ(Enemy1.model, VGet(0.0f, 1.57f * Enemy1.direction, 0.0f));
				MV1SetPosition(Enemy1.model, Enemy1.pos);

				Draw();
				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					gamemode = eScenePlay;
				}
				break;

			case eScenePlay :
				// アニメーション進行
				if(Player.mode != JUMPOUT){
					Player.playtime += 0.5f ;
				}
				else{
					Player.playtime += 1.0f ;		
				}

				Enemy1.playtime += 0.5f;
				if (Enemy1.mode == E_BLOWIN) {
					Enemy1.playtime += 2.0f;
				}

				//　エネミーのモーション終了時の処理
				if (Enemy1.playtime > Enemy1.anim_totaltime) {
					switch (Enemy1.mode) {
						case E_STAND :
							Enemy1.playtime = 0.0f;
							break;

						case E_BLOWIN :
							AnimationEnemy1(E_BLOWLOOP);
							Enemy1.playtime = 0.0f;
							Enemy1.move.x = 0.0f;
							Enemy1.move.y = 0.0f;
							Enemy1.move.z = 0.0f;
							break;

						case E_BLOWLOOP :
							AnimationEnemy1(E_BLOWOUT);
							Enemy1.playtime = 0.0f;
							Enemy1.anim_totaltime = MV1GetAnimTotalTime(Enemy1.model, Enemy1.attachidx);
							MV1SetAttachAnimTime(Enemy1.model, Enemy1.attachidx, Enemy1.playtime);
							break;

						case E_BLOWOUT :
							AnimationEnemy1(E_STAND);
							Enemy1.playtime = 0.0f;
							break;
					}
				}

				//　プレイヤーのモーション終了時の処理
				if (Player.mode != FALL){
					if (Player.playtime > Player.anim_totaltime){
						if (Player.mode == JUMPIN) {
							AnimationPlayer(JUMPLOOP);
							Player.move.y = 15.0f;
							Player.pos.y += (Player.move.y * 4);	// ジャンプ直後の地面めり込みを避けるため
						}

						if (Player.mode == JUMPOUT)	AnimationPlayer(STAND);

						if (Player.mode == ATTACK) AnimationPlayer(STAND);

						Player.playtime = 0.0f ;
					}
				}

				// プレイヤーの攻撃モーション中の移動量変化の処理
				if (Player.mode == ATTACK) {
					if (Player.playtime > 8.0f) {
						Player.move.x = 0;
						Player.move.y = 0;
						Player.move.z = 0;
					}
				}

				// アニメーションの反映
				MV1SetAttachAnimTime(Player.model, Player.attachidx, Player.playtime);
				MV1SetAttachAnimTime(Enemy1.model, Enemy1.attachidx, Enemy1.playtime);
				// キー操作
				if(Player.mode == STAND || Player.mode == RUN){
					PlayerMove();

					// アニメのループ管理(ジャンプループと落ちるものはループしない)
					if ( Player.mode != JUMPLOOP && Player.mode != FALL ) {
						if (Player.playtime > Player.anim_totaltime) {
							if ( Player.mode == JUMPIN ) {
								AnimationPlayer(JUMPLOOP);
								Player.move.y = 15.0f;
								Player.pos.y += (Player.move.y * 4);	// ジャンプ直後の地面めり込みを避けるため
							}
						}
					}
				}

				// 走っているか立っているかの区別
				if(key == 0){
					if(Player.mode == RUN) {
						AnimationPlayer(STAND);
						Player.move.x = 0.0f;
						Player.move.y = 0.0f;
						Player.move.z = 0.0f;
					}
				}
				else{
					if(Player.mode == STAND){
						AnimationPlayer(RUN);
					}
				}
				ClearDrawScreen() ;
				// ここに色々処理を追加する
				DrawBox(0,0,900,600,GetColor(255,255,255),true) ; //最後の引数をfalseにすると塗りつぶし無し

				// キャラとヒットチェック
				if(HitCheck_Capsule_Capsule(VAdd(Player.pos,Player.move),VAdd(Player.pos,Player.move),Player.charahitinfo.Width / 2,
											VAdd(Enemy1.pos,Enemy1.move),VAdd(Enemy1.pos,Enemy1.move),Enemy1.charahitinfo.Width / 2) == TRUE){
					// 移動量を無しに
					Player.move.x = 0.0f ;
					Player.move.y = 0.0f ;
					Player.move.z = 0.0f ;
				}

				// 攻撃時のエネミーのヒットチェック
				if (Player.mode == ATTACK) {
					if (Enemy1.mode == E_STAND) {
						if (HitCheck_Capsule_Capsule(VAdd(VGet(Player.pos.x - 80.0f, Player.pos.y, Player.pos.z - 80.0f), Player.move),
														VAdd(VGet(Player.pos.x + 80.0f, Player.pos.y, Player.pos.z + 80.0f), Player.move), Player.charahitinfo.Width / 2,
															VAdd(Enemy1.pos, Enemy1.move), VAdd(Enemy1.pos, Enemy1.move), Enemy1.charahitinfo.Width / 2) == TRUE) {
							AnimationEnemy1(E_BLOWIN);
							Enemy1.playtime = 0.0f;
							// エネミーのノックバック
							if (Player.direction == DOWN) {
								Enemy1.move.z -= ENEMY_KNOCKBACK;
								Enemy1.direction = UP;
							}
							if (Player.direction == 0.5f) {
								Enemy1.move.x -= ENEMY_KNOCKBACK / 2;
								Enemy1.move.z -= ENEMY_KNOCKBACK / 2;
								Enemy1.direction = 2.5f;
							}
							if (Player.direction == LEFT) {
								Enemy1.move.x -= ENEMY_KNOCKBACK;
								Enemy1.direction = RIGHT;
							}
							if (Player.direction == 1.5f) {
								Enemy1.move.x -= ENEMY_KNOCKBACK / 2;
								Enemy1.move.z += ENEMY_KNOCKBACK / 2;
								Enemy1.direction = 3.5f;
							}
							if (Player.direction == UP) {
								Enemy1.move.z += ENEMY_KNOCKBACK;
								Enemy1.direction = DOWN;
							}
							if (Player.direction == 2.5f) {
								Enemy1.move.x += ENEMY_KNOCKBACK / 2;
								Enemy1.move.z += ENEMY_KNOCKBACK / 2;
								Enemy1.direction = 0.5f;
							}
							if (Player.direction == RIGHT) {
								Enemy1.move.x += ENEMY_KNOCKBACK;
								Enemy1.direction = LEFT;
							}
							if (Player.direction == 3.5f) {
								Enemy1.move.x += ENEMY_KNOCKBACK / 2;
								Enemy1.move.z += ENEMY_KNOCKBACK / 2;
								Enemy1.direction = 1.5f;
							}
						}
					}
				}

				// モデルと接触したポリゴンの検出
				HitPolygonSearch();
				
				// 床ポリゴンとの当たり判定
				if( FloorNum != 0 ){
					HitFlag = FloorSearch();
				}
				// 床ポリゴンに当たったかどうかで処理を分岐
				if( HitFlag == 1 ){
					// 接触したポリゴンで一番高いＹ座標をキャラクターのＹ座標にする
					Player.pos.y = MaxY ;
					Player.move.y = 0.0f ;

					if(Player.mode == FALL){
						AnimationPlayer(JUMPOUT);
						Player.playtime = 0.0f ;
						Player.move.x = 0.0f ;
						Player.move.y = 0.0f ;
						Player.move.z = 0.0f ;
					}
				}
				else{
					// 宙に浮いた状態
					if(Player.mode != FALL){ // ジャンプ状態じゃない
						MV1DetachAnim(Player.model,Player.attachidx) ;
						Player.mode = FALL ;
						Player.attachidx = MV1AttachAnim(Player.model,0, plyanim_jumploop) ;
						Player.anim_totaltime = MV1GetAttachAnimTotalTime(Player.model,Player.attachidx) ;
						Player.playtime = 7.0f ;
						MV1SetAttachAnimTime(Player.model,Player.attachidx,Player.playtime) ;
					}
				}
				// ジャンプ中だったら重力追加させる
				if (Player.mode == FALL) {
					Player.move.y -= 0.5f;
				}

				E1_FloorSearch();
				// 床ポリゴンに当たったかどうかで処理を分岐
				if (E1_HitFlag == 1) {
					// 接触したポリゴンで一番高いＹ座標をキャラクターのＹ座標にする
					Enemy1.pos.y = E1_MaxY;
					Enemy1.move.y = 0.0f;
				}

				// 検出したキャラクターの周囲のポリゴン情報を開放する
				MV1CollResultPolyDimTerminate( HitDim ) ;

				// 移動処理
				Player.pos.x += Player.move.x ;
				Player.pos.y += Player.move.y ;
				Player.pos.z += Player.move.z ;

				Enemy1.pos.x += Enemy1.move.x;
				Enemy1.pos.y += Enemy1.move.y;
				Enemy1.pos.z += Enemy1.move.z;

				// カメラの視点操作
				CameraMove();

				// 背景(空)の操作
				skypos.x = cpos.x;
				skypos.y = cpos.y;
				skypos.z = cpos.z;

				// エネミーの向きの限定
				if (Enemy1.direction < 0.0f) Enemy1.direction += 4.0f;
				if (Enemy1.direction > 4.0f) Enemy1.direction -= 4.0f;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// モデルの回転
				MV1SetRotationXYZ(Player.model,VGet(0.0f,1.57f * Player.direction,0.0f)) ;
				// モデルの移動(配置)
				MV1SetPosition(Player.model,Player.pos);

				// モデルの回転
				MV1SetRotationXYZ(Enemy1.model, VGet(0.0f, 1.57f * Enemy1.direction, 0.0f));
				// モデルの移動(配置)
				MV1SetPosition(Enemy1.model,Enemy1.pos);

				// 武器を使うモデルにアタッチする(アタッチさせるモデルの回転や移動の後に行う)
				WeaponMatrix = MV1GetFrameLocalWorldMatrix(Player.model, WeponAttachFrameNum);	// アタッチさせるモデルとそのフレームを貰いそのローカル座標をワールド座標に変換するマトリックスを返す関数
				MV1SetMatrix(PlayerSabel.model, WeaponMatrix);									// アタッチするモデルとマトリックスを貰い座標に直す関数

				// 地面(配置)
				MV1SetPosition(stagedata, stagepos);
				MV1SetPosition(skydata, skypos);

				for (int y = 0; y < MAP_Y; y++) {
					for (int x = 0; x < MAP_X; x++) {
						MV1SetPosition(StageMap[y][x], VGet((x * 200.0f), ((MAP_Y - y) * 200.0f), 0.0f));
					}
				}

				// 描画
				Draw();

				ScreenFlip() ;
				break ;

			case eSceneClear :
				break ;
		}

	}


	// シャドウマップの削除
	DeleteShadowMap(ShadowMapHandle);
	// ステージモデルの削除
	MV1DeleteModel(stagedata);
	// キャラクターモデルの削除
	MV1DeleteModel(Player.model);
	MV1DeleteModel(Enemy1.model);

	DxLib_End();
	return 0 ;
}

