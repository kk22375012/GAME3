
#include "Common.h"		// --- �S�t�@�C���ł̋��ʃw�b�_�[

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int stagedata_c ;
	float camera_direction = 0.0f;

	char str[100];
	// �S�̓I�ȃQ�[���̊Ǘ�
	int gamemode = eSceneBlank ;

	//�X�e�[�W�̃|�W�V����
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// �J�����|�W�V���� cpos:�J�����ʒu�@ctgt:�J���������_
	cpos = VGet(0.0f,1400.0f,0.0f) ;
	ctgt = VGet(0.0f,500.0f,-400.0f) ;
	cadd = VGet(0.0f, 0.0f, 0.0f);

	VECTOR Position ;


	ChangeWindowMode(TRUE) ;

	SetGraphMode(900,600,32) ;

	// DX���C�u�����̏�����				DX���C�u�����[�X�^�[�g
	if(DxLib_Init() == -1) return -1 ;

	AnimationInit();
	PlayerInit();
	WeaponInit();
	Enemy1Init();

	// �X�e�[�W���̓ǂݍ���
	stagedata = MV1LoadModel("..\\Data\\Stage\\Stage00.mv1") ;
	skydata = MV1LoadModel("..\\Data\\Stage\\Stage00_sky.mv1");
	MV1SetUseZBuffer(skydata, false);
	// �u���b�N���f���̓ǂݍ���
	blockdate[TATAMI_BLOCK] = MV1LoadModel("..\\Data\\Stage\\��.mv1");
	// �}�b�v�f�[�^�ɔ��f
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			switch (StageMap[y][x]) {
				case TATAMI_BLOCK :
					StageMap[y][x] = MV1DuplicateModel(blockdate[TATAMI_BLOCK]);
					break;
			}
		}
	}



	// �V���h�E�}�b�v�n���h���̍쐬


	// ���C�g�̕�����ݒ�
	SetLightDirection( VGet( 0.5f, -0.5f, -0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, -0.5f ) ) ;

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -6000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	stagedata_c = MV1LoadModel("..\\Data\\Stage\\Stage00_c.mv1") ;
	if(stagedata == -1) return -1 ;

	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo( stagedata, -1 ) ;

	SetDrawScreen(DX_SCREEN_BACK) ;

	int MeshNum ;

	// ���f���Ɋ܂܂�郁�b�V���̐����擾����
    MeshNum = MV1GetMeshNum( stagedata ) ;

    // ���b�V���̐��������[�v
    for(int i = 0 ; i < MeshNum ; i ++ ){
	// ���b�V���Ɋ܂܂�钸�_�̃��[�J�����W�̍ő���W�l��`��
		Position = MV1GetMeshMaxPosition( stagedata, i ) ;
//		DrawFormatString( 0, 112, GetColor( 255,255,255 ), "Max Position          x %f  y %f  z %f", Position.x, Position.y, Position.z ) ;

		// ���b�V���Ɋ܂܂�钸�_�̃��[�J�����W�̍ŏ����W�l��`��
		Position = MV1GetMeshMinPosition( stagedata, i ) ;
//		DrawFormatString( 0, 128, GetColor( 255,255,255 ), "Min Position          x %f  y %f  z %f", Position.x, Position.y, Position.z ) ;

	}
	/* ------------------------------------------------------------------------------------------------
												�Q�[�����[�v										
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

				// ���f���̈ړ�(�z�u)
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
				// �A�j���[�V�����i�s
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

				//�@�G�l�~�[�̃��[�V�����I�����̏���
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

				//�@�v���C���[�̃��[�V�����I�����̏���
				if (Player.mode != FALL){
					if (Player.playtime > Player.anim_totaltime){
						if (Player.mode == JUMPIN) {
							AnimationPlayer(JUMPLOOP);
							Player.move.y = 15.0f;
							Player.pos.y += (Player.move.y * 4);	// �W�����v����̒n�ʂ߂荞�݂�����邽��
						}

						if (Player.mode == JUMPOUT)	AnimationPlayer(STAND);

						if (Player.mode == ATTACK) AnimationPlayer(STAND);

						Player.playtime = 0.0f ;
					}
				}

				// �v���C���[�̍U�����[�V�������̈ړ��ʕω��̏���
				if (Player.mode == ATTACK) {
					if (Player.playtime > 8.0f) {
						Player.move.x = 0;
						Player.move.y = 0;
						Player.move.z = 0;
					}
				}

				// �A�j���[�V�����̔��f
				MV1SetAttachAnimTime(Player.model, Player.attachidx, Player.playtime);
				MV1SetAttachAnimTime(Enemy1.model, Enemy1.attachidx, Enemy1.playtime);
				// �L�[����
				if(Player.mode == STAND || Player.mode == RUN){
					PlayerMove();

					// �A�j���̃��[�v�Ǘ�(�W�����v���[�v�Ɨ�������̂̓��[�v���Ȃ�)
					if ( Player.mode != JUMPLOOP && Player.mode != FALL ) {
						if (Player.playtime > Player.anim_totaltime) {
							if ( Player.mode == JUMPIN ) {
								AnimationPlayer(JUMPLOOP);
								Player.move.y = 15.0f;
								Player.pos.y += (Player.move.y * 4);	// �W�����v����̒n�ʂ߂荞�݂�����邽��
							}
						}
					}
				}

				// �����Ă��邩�����Ă��邩�̋��
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
				// �����ɐF�X������ǉ�����
				DrawBox(0,0,900,600,GetColor(255,255,255),true) ; //�Ō�̈�����false�ɂ���Ɠh��Ԃ�����

				// �L�����ƃq�b�g�`�F�b�N
				if(HitCheck_Capsule_Capsule(VAdd(Player.pos,Player.move),VAdd(Player.pos,Player.move),Player.charahitinfo.Width / 2,
											VAdd(Enemy1.pos,Enemy1.move),VAdd(Enemy1.pos,Enemy1.move),Enemy1.charahitinfo.Width / 2) == TRUE){
					// �ړ��ʂ𖳂���
					Player.move.x = 0.0f ;
					Player.move.y = 0.0f ;
					Player.move.z = 0.0f ;
				}

				// �U�����̃G�l�~�[�̃q�b�g�`�F�b�N
				if (Player.mode == ATTACK) {
					if (Enemy1.mode == E_STAND) {
						if (HitCheck_Capsule_Capsule(VAdd(VGet(Player.pos.x - 80.0f, Player.pos.y, Player.pos.z - 80.0f), Player.move),
														VAdd(VGet(Player.pos.x + 80.0f, Player.pos.y, Player.pos.z + 80.0f), Player.move), Player.charahitinfo.Width / 2,
															VAdd(Enemy1.pos, Enemy1.move), VAdd(Enemy1.pos, Enemy1.move), Enemy1.charahitinfo.Width / 2) == TRUE) {
							AnimationEnemy1(E_BLOWIN);
							Enemy1.playtime = 0.0f;
							// �G�l�~�[�̃m�b�N�o�b�N
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

				// ���f���ƐڐG�����|���S���̌��o
				HitPolygonSearch();
				
				// ���|���S���Ƃ̓����蔻��
				if( FloorNum != 0 ){
					HitFlag = FloorSearch();
				}
				// ���|���S���ɓ����������ǂ����ŏ����𕪊�
				if( HitFlag == 1 ){
					// �ڐG�����|���S���ň�ԍ����x���W���L�����N�^�[�̂x���W�ɂ���
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
					// ���ɕ��������
					if(Player.mode != FALL){ // �W�����v��Ԃ���Ȃ�
						MV1DetachAnim(Player.model,Player.attachidx) ;
						Player.mode = FALL ;
						Player.attachidx = MV1AttachAnim(Player.model,0, plyanim_jumploop) ;
						Player.anim_totaltime = MV1GetAttachAnimTotalTime(Player.model,Player.attachidx) ;
						Player.playtime = 7.0f ;
						MV1SetAttachAnimTime(Player.model,Player.attachidx,Player.playtime) ;
					}
				}
				// �W�����v����������d�͒ǉ�������
				if (Player.mode == FALL) {
					Player.move.y -= 0.5f;
				}

				E1_FloorSearch();
				// ���|���S���ɓ����������ǂ����ŏ����𕪊�
				if (E1_HitFlag == 1) {
					// �ڐG�����|���S���ň�ԍ����x���W���L�����N�^�[�̂x���W�ɂ���
					Enemy1.pos.y = E1_MaxY;
					Enemy1.move.y = 0.0f;
				}

				// ���o�����L�����N�^�[�̎��͂̃|���S�������J������
				MV1CollResultPolyDimTerminate( HitDim ) ;

				// �ړ�����
				Player.pos.x += Player.move.x ;
				Player.pos.y += Player.move.y ;
				Player.pos.z += Player.move.z ;

				Enemy1.pos.x += Enemy1.move.x;
				Enemy1.pos.y += Enemy1.move.y;
				Enemy1.pos.z += Enemy1.move.z;

				// �J�����̎��_����
				CameraMove();

				// �w�i(��)�̑���
				skypos.x = cpos.x;
				skypos.y = cpos.y;
				skypos.z = cpos.z;

				// �G�l�~�[�̌����̌���
				if (Enemy1.direction < 0.0f) Enemy1.direction += 4.0f;
				if (Enemy1.direction > 4.0f) Enemy1.direction -= 4.0f;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// ���f���̉�]
				MV1SetRotationXYZ(Player.model,VGet(0.0f,1.57f * Player.direction,0.0f)) ;
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(Player.model,Player.pos);

				// ���f���̉�]
				MV1SetRotationXYZ(Enemy1.model, VGet(0.0f, 1.57f * Enemy1.direction, 0.0f));
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(Enemy1.model,Enemy1.pos);

				// ������g�����f���ɃA�^�b�`����(�A�^�b�`�����郂�f���̉�]��ړ��̌�ɍs��)
				WeaponMatrix = MV1GetFrameLocalWorldMatrix(Player.model, WeponAttachFrameNum);	// �A�^�b�`�����郂�f���Ƃ��̃t���[����Ⴂ���̃��[�J�����W�����[���h���W�ɕϊ�����}�g���b�N�X��Ԃ��֐�
				MV1SetMatrix(PlayerSabel.model, WeaponMatrix);									// �A�^�b�`���郂�f���ƃ}�g���b�N�X��Ⴂ���W�ɒ����֐�

				// �n��(�z�u)
				MV1SetPosition(stagedata, stagepos);
				MV1SetPosition(skydata, skypos);

				for (int y = 0; y < MAP_Y; y++) {
					for (int x = 0; x < MAP_X; x++) {
						MV1SetPosition(StageMap[y][x], VGet((x * 200.0f), ((MAP_Y - y) * 200.0f), 0.0f));
					}
				}

				// �`��
				Draw();

				ScreenFlip() ;
				break ;

			case eSceneClear :
				break ;
		}

	}


	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(ShadowMapHandle);
	// �X�e�[�W���f���̍폜
	MV1DeleteModel(stagedata);
	// �L�����N�^�[���f���̍폜
	MV1DeleteModel(Player.model);
	MV1DeleteModel(Enemy1.model);

	DxLib_End();
	return 0 ;
}

