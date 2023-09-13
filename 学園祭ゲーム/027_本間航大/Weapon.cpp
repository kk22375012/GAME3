#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//							武器の初期セット								//
// ------------------------------------------------------------------------ //
void WeaponInit() {
	PlayerSabel.model = MV1LoadModel("..\\Data\\Player\\Sabel.mv1");
	PlayerSabel.pos = VGet( 0.0f, 0.0f, 0.0f );
	PlayerSabel.weaponhitinfo.CenterPosition = VGet( 0.0f, -9.0f, -1.5f );
	PlayerSabel.weaponhitinfo.Width = 3.5f;
	PlayerSabel.weaponhitinfo.Height = -88.0f;

	WeponAttachFrameNum = MV1SearchFrame(Player[0].model, "wp");	// 武器をアタッチするモデルのアタッチするフレームを探す
}




