#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//								�`��֐�									//
// ------------------------------------------------------------------------ //
void Draw() {
	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(ShadowMapHandle);

	// ���f���̕`�� - �e�̕`��
	MV1DrawModel(Player[0].model);
	MV1DrawModel(Player[1].model);

	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, ShadowMapHandle);

	// �n��(�z�u)���`��
	MV1DrawModel(skydata);
	MV1DrawModel(stagedata);

	for (int y = 0; y < MAP_Y; y++) {
		for (int x = 0; x < MAP_X; x++) {
			MV1DrawModel(StageMap[x][y]);
		}
	}


	DrawTriangle3D(PolyCharaHitField[0], PolyCharaHitField[1], PolyCharaHitField[2],
		GetColor(255, 0, 0), TRUE);

	// ���f���̕`��
	MV1DrawModel(Player[0].model);
	MV1DrawModel(Player[1].model);
	MV1DrawModel(PlayerSabel.model);
	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);

}



