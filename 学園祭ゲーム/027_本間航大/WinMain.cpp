
#include "Common.h"		// --- 全ファイルでの共通ヘッダー


int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int stagedata_c ;
	float camera_direction = 0.0f;
	float LightPositionX = Player[0].pos.x;
	float LightPositionY = Player[0].pos.y;
	float LightPositionZ = Player[0].pos.z;

	char str[100];
	// 全体的なゲームの管理
	int gamemode = eSceneBlank ;

	//ステージのポジション
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// カメラポジション cpos:カメラ位置　ctgt:カメラ注視点
	cpos = VGet(0.0f,1000.0f,-2000.0f) ;
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
	EnemyInit();

	// ステージ情報の読み込み
	stagedata = MV1LoadModel("..\\Data\\Stage\\Stage00.mv1") ;
	skydata = MV1LoadModel("..\\Data\\Stage\\Stage00_sky.mv1");
	MV1SetUseZBuffer(skydata, false);
	// ブロックモデルの読み込み

	blockdate[TATAMI_BLOCK] = MV1LoadModel("..\\Data\\Stage\\たたみ.mv1");

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




	// ポイントライト
	Position = VGet(LightPositionX, LightPositionY, LightPositionZ);
	float Range = 10.0f;			// ライトの有効範囲
	float Attenuation0 = 0.1f;
	//float Atten2 = 0.1f;		
//	ChangeLightTypePoint(Position, 10.0f , 0.1f, 0.1f, 0.1f);

	// ライトの方向を設定
	SetLightDirection(VGet(0.0f, 1.5f, 0.0f));
	ShadowMapHandle = MakeShadowMap(1024, 1024);

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, -0.5f ) ) ;

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -6000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	stagedata_c = MV1LoadModel("..\\Data\\Stage\\Stage00_c.mv1") ;
	if(stagedata == -1) return -1 ;

=======
	// シャドウマップハンドルの作成


	// ライトの方向を設定
	SetLightDirection( VGet( 0.5f, -0.5f, 0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, 0.5f ) ) ;

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -5000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	stagedata_c = MV1LoadModel("..\\Data\\Stage\\Stage00_c.mv1") ;
	if(stagedata == -1) return -1 ;
>>>>>>> a7347d45580869c4bc2835f012c9a3eed6d10584
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
				gamemode = eScenePlay;
				break;

			case eSceneTitle:

				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
				}
				break;

			case eSceneChoice:
				cpos = VGet(0.0f, 1000.0f, -1500.0f);
				ctgt = VGet(0.0f, 500.0f, 0.0f);
				cadd = VGet(0.0f, 0.0f, 0.0f);

				Player[0].pos = VGet(200.0f, 200.0f, 0.0f);
				Player[1].pos = VGet(600.0f, 300.0f, 200.0f);

				// モデルの移動(配置)
				MV1SetRotationXYZ(Player[0].model, VGet(0.0f, 1.57f * Player[0].direction, 0.0f));
				MV1SetPosition(Player[0].model, Player[0].pos);
				MV1SetRotationXYZ(Player[1].model, VGet(0.0f, 1.57f * Player[1].direction, 0.0f));
				MV1SetPosition(Player[1].model, Player[1].pos);

				Draw();
				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					Player[0].pos = VGet(200.0f, 200.0f, -1000.0f);
					gamemode = eScenePlay;
				}
				break;

			case eScenePlay :
				// アニメーション進行
				if(Player[0].mode != JUMPOUT){
					Player[0].playtime += 0.5f ;
				}
				else{
					Player[0].playtime += 1.0f ;		
				}

				Player[1].playtime += 0.5f;
				if (Player[1].mode == E_BLOWIN) {
					Player[1].playtime += 2.0f;
				}

				//　エネミーのモーション終了時の処理
				if (Player[1].playtime > Player[1].anim_totaltime) {
					switch (Player[1].mode) {
						case E_STAND :
							Player[1].playtime = 0.0f;
							break;

						case E_BLOWIN :
							AnimationEnemy(E_BLOWLOOP);
							Player[1].playtime = 0.0f;
							Player[1].move.x = 0.0f;
							Player[1].move.y = 0.0f;
							Player[1].move.z = 0.0f;
							break;

						case E_BLOWLOOP :
							AnimationEnemy(E_BLOWOUT);
							Player[1].playtime = 0.0f;
							Player[1].anim_totaltime = MV1GetAnimTotalTime(Player[1].model, Player[1].attachidx);
							MV1SetAttachAnimTime(Player[1].model, Player[1].attachidx, Player[1].playtime);
							break;

						case E_BLOWOUT :
							AnimationEnemy(E_STAND);
							Player[1].playtime = 0.0f;
							break;
					}
				}

				//　プレイヤーのモーション終了時の処理
				if (Player[0].mode != FALL){
					if (Player[0].playtime > Player[0].anim_totaltime){
						if (Player[0].mode == JUMPIN) {
							AnimationPlayer(JUMPLOOP);
							Player[0].move.y = 15.0f;
							Player[0].pos.y += (Player[0].move.y * 4);	// ジャンプ直後の地面めり込みを避けるため
						}

						if (Player[0].mode == JUMPOUT)	AnimationPlayer(STAND);

						if (Player[0].mode == ATTACK) AnimationPlayer(STAND);

						Player[0].playtime = 0.0f ;
					}
				}

				// プレイヤーの攻撃モーション中の移動量変化の処理
				if (Player[0].mode == ATTACK) {
					if (Player[0].playtime > 8.0f) {
						Player[0].move.x = 0;
						Player[0].move.y = 0;
						Player[0].move.z = 0;
					}
				}

				// アニメーションの反映
				MV1SetAttachAnimTime(Player[0].model, Player[0].attachidx, Player[0].playtime);
				MV1SetAttachAnimTime(Player[1].model, Player[1].attachidx, Player[1].playtime);
				// キー操作
				if(Player[0].mode == STAND || Player[0].mode == RUN){
					PlayerMove();

					// アニメのループ管理(ジャンプループと落ちるものはループしない)
					if ( Player[0].mode != JUMPLOOP && Player[0].mode != FALL ) {
						if (Player[0].playtime > Player[0].anim_totaltime) {
							if ( Player[0].mode == JUMPIN ) {
								AnimationPlayer(JUMPLOOP);
								Player[0].move.y = 15.0f;
								Player[0].pos.y += (Player[0].move.y * 4);	// ジャンプ直後の地面めり込みを避けるため
							}
						}
					}
				}

				// 走っているか立っているかの区別
				if(key == 0){
					if(Player[0].mode == RUN) {
						AnimationPlayer(STAND);
						Player[0].move.x = 0.0f;
						Player[0].move.y = 0.0f;
						Player[0].move.z = 0.0f;
					}
				}
				else{
					if(Player[0].mode == STAND){
						AnimationPlayer(RUN);
					}
				}
				ClearDrawScreen() ;
				// ここに色々処理を追加する
				DrawBox(0,0,900,600,GetColor(255,255,255),true) ; //最後の引数をfalseにすると塗りつぶし無し

				// キャラとヒットチェック
				if(HitCheck_Capsule_Capsule(VAdd(Player[0].pos,Player[0].move),VAdd(Player[0].pos,Player[0].move),Player[0].charahitinfo.Width / 2,
											VAdd(Player[1].pos,Player[1].move),VAdd(Player[1].pos,Player[1].move),Player[1].charahitinfo.Width / 2) == TRUE){
					// 移動量を無しに
					Player[0].move.x = 0.0f ;
					Player[0].move.y = 0.0f ;
					Player[0].move.z = 0.0f ;
				}

				// 攻撃時のエネミーのヒットチェック
				if (Player[0].mode == ATTACK) {
					if (Player[1].mode == E_STAND) {
						if (HitCheck_Capsule_Capsule(VAdd(VGet(Player[0].pos.x - 80.0f, Player[0].pos.y, Player[0].pos.z - 80.0f), Player[0].move),
														VAdd(VGet(Player[0].pos.x + 80.0f, Player[0].pos.y, Player[0].pos.z + 80.0f), Player[0].move), Player[0].charahitinfo.Width / 2,
															VAdd(Player[1].pos, Player[1].move), VAdd(Player[1].pos, Player[1].move), Player[1].charahitinfo.Width / 2) == TRUE) {
							AnimationEnemy(E_BLOWIN);
							Player[1].playtime = 0.0f;
							// エネミーのノックバック
							if (Player[0].direction == DOWN) {
								Player[1].move.z -= ENEMY_KNOCKBACK;
								Player[1].direction = UP;
							}
							if (Player[0].direction == 0.5f) {
								Player[1].move.x -= ENEMY_KNOCKBACK / 2;
								Player[1].move.z -= ENEMY_KNOCKBACK / 2;
								Player[1].direction = 2.5f;
							}
							if (Player[0].direction == LEFT) {
								Player[1].move.x -= ENEMY_KNOCKBACK;
								Player[1].direction = RIGHT;
							}
							if (Player[0].direction == 1.5f) {
								Player[1].move.x -= ENEMY_KNOCKBACK / 2;
								Player[1].move.z += ENEMY_KNOCKBACK / 2;
								Player[1].direction = 3.5f;
							}
							if (Player[0].direction == UP) {
								Player[1].move.z += ENEMY_KNOCKBACK;
								Player[1].direction = DOWN;
							}
							if (Player[0].direction == 2.5f) {
								Player[1].move.x += ENEMY_KNOCKBACK / 2;
								Player[1].move.z += ENEMY_KNOCKBACK / 2;
								Player[1].direction = 0.5f;
							}
							if (Player[0].direction == RIGHT) {
								Player[1].move.x += ENEMY_KNOCKBACK;
								Player[1].direction = LEFT;
							}
							if (Player[0].direction == 3.5f) {
								Player[1].move.x += ENEMY_KNOCKBACK / 2;
								Player[1].move.z += ENEMY_KNOCKBACK / 2;
								Player[1].direction = 1.5f;
							}
						}
					}
				}

				MV1SetupCollInfo(StageMap[9][1], -1);

<<<<<<< HEAD
				// モデルと接触したポリゴンの検出
				HitPolygonSearch();

				HitDim = MV1CollCheck_Sphere( stagedata, -1, Player[0].pos, CHARA_ENUM_DEFAULT_SIZE + VSize( Player[0].move ) ) ;
=======
				HitDim = MV1CollCheck_Sphere(StageMap[9][1], -1, Player[0].pos, CHARA_ENUM_DEFAULT_SIZE + VSize( Player[0].move ) ) ;
>>>>>>> 41ef0f0ec99aa17962e74ba5344cf793327da0a5
				WallNum = 0 ;
				FloorNum = 0 ;
				// 検出されたポリゴンの数だけ繰り返し
				for(int i = 0 ; i < HitDim.HitNum ; i ++ ){
					// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
					if( HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.000001f ){
						printf("壁扱い\n") ;
						// 壁ポリゴンと判断された場合でも、キャラクターのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
						if( HitDim.Dim[i].Position[0].y > Player[0].pos.y + 1.0f ||
							HitDim.Dim[i].Position[1].y > Player[0].pos.y + 1.0f ||
							HitDim.Dim[i].Position[2].y > Player[0].pos.y + 1.0f ){
							// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
							if( WallNum < CHARA_MAX_HITCOLL ){
								// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
								Wall[WallNum] = &HitDim.Dim[i] ;

								// 壁ポリゴンの数を加算する
								WallNum ++ ;
							}
						}
					}
					else{
						// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
						if( FloorNum < CHARA_MAX_HITCOLL ){
							// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
							Floor[FloorNum] = &HitDim.Dim[i] ;

							// 床ポリゴンの数を加算する
							FloorNum ++ ;
						}
					}
				}

				
				// 床ポリゴンとの当たり判定
				if( FloorNum != 0 ){
					HitFlag = FloorSearch();
				}
				// 床ポリゴンに当たったかどうかで処理を分岐
				if( HitFlag == 1 ){
					// 接触したポリゴンで一番高いＹ座標をキャラクターのＹ座標にする
					Player[0].pos.y = MaxY ;
					Player[0].move.y = 0.0f ;

					if(Player[0].mode == FALL){
						AnimationPlayer(JUMPOUT);
						Player[0].playtime = 0.0f ;
						Player[0].move.x = 0.0f ;
						Player[0].move.y = 0.0f ;
						Player[0].move.z = 0.0f ;
					}
				}
				else{
					// 宙に浮いた状態
					if(Player[0].mode != FALL){ // ジャンプ状態じゃない
						MV1DetachAnim(Player[0].model,Player[0].attachidx) ;
						Player[0].mode = FALL ;
						Player[0].attachidx = MV1AttachAnim(Player[0].model,0, plyanim_jumploop) ;
						Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model,Player[0].attachidx) ;
						Player[0].playtime = 7.0f ;
						MV1SetAttachAnimTime(Player[0].model,Player[0].attachidx,Player[0].playtime) ;
					}
				}
				// ジャンプ中だったら重力追加させる
				if (Player[0].mode == FALL) {
					Player[0].move.y -= 0.5f;
				}

				E1_FloorSearch();
				// 床ポリゴンに当たったかどうかで処理を分岐
				if (E1_HitFlag == 1) {
					// 接触したポリゴンで一番高いＹ座標をキャラクターのＹ座標にする
					Player[1].pos.y = E1_MaxY;
					Player[1].move.y = 0.0f;
				}

				// 検出したキャラクターの周囲のポリゴン情報を開放する
				MV1CollResultPolyDimTerminate( HitDim ) ;

				// 移動処理
				Player[0].pos.x += Player[0].move.x ;
				Player[0].pos.y += Player[0].move.y ;
				Player[0].pos.z += Player[0].move.z ;

				Player[1].pos.x += Player[1].move.x;
				Player[1].pos.y += Player[1].move.y;
				Player[1].pos.z += Player[1].move.z;

				// カメラの視点操作
				CameraMove();

				// 背景(空)の操作
				skypos.x = cpos.x;
				skypos.y = cpos.y;
				skypos.z = cpos.z;

				// エネミーの向きの限定
				if (Player[1].direction < 0.0f) Player[1].direction += 4.0f;
				if (Player[1].direction > 4.0f) Player[1].direction -= 4.0f;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// モデルの回転
				MV1SetRotationXYZ(Player[0].model,VGet(0.0f,1.57f * Player[0].direction,0.0f)) ;
				// モデルの移動(配置)
				MV1SetPosition(Player[0].model,Player[0].pos);

				// モデルの回転
				MV1SetRotationXYZ(Player[1].model, VGet(0.0f, 1.57f * Player[1].direction, 0.0f));
				// モデルの移動(配置)
				MV1SetPosition(Player[1].model,Player[1].pos);

				// 武器を使うモデルにアタッチする(アタッチさせるモデルの回転や移動の後に行う)
				WeaponMatrix = MV1GetFrameLocalWorldMatrix(Player[0].model, WeponAttachFrameNum);	// アタッチさせるモデルとそのフレームを貰いそのローカル座標をワールド座標に変換するマトリックスを返す関数
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
	MV1DeleteModel(Player[0].model);
	MV1DeleteModel(Player[1].model);

	DxLib_End();
	return 0 ;
}

