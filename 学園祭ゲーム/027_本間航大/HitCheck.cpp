#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//					���f���ƐڐG�����|���S���̌��o�|���S��					//
// ------------------------------------------------------------------------ //
void HitPolygonSearch() {
	HitDim = MV1CollCheck_Sphere(stagedata, -1, Player.pos, CHARA_ENUM_DEFAULT_SIZE + VSize(Player.move));
	WallNum = 0;
	FloorNum = 0;
	// ���o���ꂽ�|���S���̐������J��Ԃ�
	for (int i = 0; i < HitDim.HitNum; i++) {
		// �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.000001f) {
			printf("�ǈ���\n");
			// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�L�����N�^�[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
			if (HitDim.Dim[i].Position[0].y > Player.pos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > Player.pos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > Player.pos.y + 1.0f) {
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (WallNum < CHARA_MAX_HITCOLL) {
					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					Wall[WallNum] = &HitDim.Dim[i];

					// �ǃ|���S���̐������Z����
					WallNum++;
				}
			}
		}
		else {
			// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
			if (FloorNum < CHARA_MAX_HITCOLL) {
				// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
				Floor[FloorNum] = &HitDim.Dim[i];

				// ���|���S���̐������Z����
				FloorNum++;
			}
		}
	}
}

// ------------------------------------------------------------------------ //
//						�v���C���[�̏��ւ̃q�b�g�`�F�b�N					//
// ------------------------------------------------------------------------ //
int FloorSearch() {
	float MaxY_poly;
	// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
	HitFlag = 0;
	// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
	MaxY = 0.0f;
	MaxY_poly = 0.0f;

	// ���|���S���̐������J��Ԃ�
	for (int i = 0; i < FloorNum; i++) {
		// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[0].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[0].mode == JUMPIN || Player[0].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
		LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// �������Ă��Ȃ������牽�����Ȃ�
		if (LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
		if (HitFlag == 1 && MaxY > LineRes.Position.y) {
			continue;
		}

		// �|���S���ɓ��������t���O�𗧂Ă�
		HitFlag = 1;

		// �ڐG�����x���W��ۑ�����
		MaxY = LineRes.Position.y;
		MaxY_poly = Poly->Position[1].y;
	}


	return HitFlag;
}

// ------------------------------------------------------------------------ //
//						�G�l�~�[�̏��ւ̃q�b�g�`�F�b�N						//
// ------------------------------------------------------------------------ //
void E1_FloorSearch() {
	float E1_MaxY_poly;
	// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
	E1_HitFlag = 0;
	// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
	E1_MaxY = 0.0f;
	E1_MaxY_poly = 0.0f;

	// ���|���S���̐������J��Ԃ�
	for (int i = 0; i < FloorNum; i++) {
		// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[1].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[1].mode == JUMPIN || Player[1].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
		E1_LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// �������Ă��Ȃ������牽�����Ȃ�
		if (E1_LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
		if (E1_HitFlag == 1 && E1_MaxY > E1_LineRes.Position.y) {
			continue;
		}

		// �|���S���ɓ��������t���O�𗧂Ă�
		E1_HitFlag = 1;

		// �ڐG�����x���W��ۑ�����
		E1_MaxY = E1_LineRes.Position.y;
		E1_MaxY_poly = Poly->Position[1].y;
	}
}

int CollisionBlock() {
	VECTOR cal_pos1 = VAdd(Player[1].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
	VECTOR cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, -25.0f, 0.0f));

	LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
		VGet(Player[0].pos.x - 100.0f, Player[0].pos.y, Player[0].pos.z - 100.0f),
		VGet(Player[0].pos.x + 100.0f, Player[0].pos.y, Player[0].pos.z + 100.0f));

//		VGet(-200.0f,   0.0f, -200.0f),
//		VGet( 200.0f, 200.0f,  200.0f));

//		VGet(m_block[0].GetBlockPosition().x - 100.0f, m_block[0].GetBlockPosition().y, m_block[0].GetBlockPosition().z - 100.0f),
//	VGet(m_block[0].GetBlockTopPosition().x + 100.0f, m_block[0].GetBlockTopPosition().y, m_block[0].GetBlockTopPosition().z + 100.0f));

	// �������Ă��Ȃ������牽�����Ȃ�
	if (LineBlock.HitFlag == TRUE) {
		printf("aaaaaaa");
		// �|���S���ɓ��������t���O�𗧂Ă�
		HitFlag = 1;

		// �ڐG�����x���W��ۑ�����
		MaxY = LineBlock.Position.y;
	}


	return HitFlag;
}


