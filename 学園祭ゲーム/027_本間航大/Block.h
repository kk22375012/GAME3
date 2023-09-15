/* -----------------------------------------------------------------------------------------
|																						   |
|										Block.h											   |
|																						   |
+ --------------------------------------------------------------------------------------- */


class Block {
	private:
		VECTOR b_posi;
		VECTOR b_top_posi;
		POINT b_Map;
		bool b_use_flg;
		 
	public:
		int b_model;

		// 位置情報
		VECTOR GetBlockPosition() {
			return b_posi;
		}
		void SetBlockPosition(VECTOR set_top_posi) {
			b_posi = set_top_posi;
		}
		VECTOR GetBlockTopPosition() {
			return b_top_posi;
		}
		void SetBlockTopPosition(VECTOR set_top_posi) {
			b_top_posi = set_top_posi;
		}
		void SetBlockTopPositionY(float set_top_posi_y) {
			b_top_posi.y = set_top_posi_y;
		}

		// マップ座標
		POINT GetMapPosition() {
			return b_Map;
		}
		int GetMapPositionX() {
			return b_Map.x;
		}
		int GetMapPositionY() {
			return b_Map.y;
		}
		void SetMapPosition(POINT set_b_map) {
			b_Map = set_b_map;
		}
		void SetMapPositionY(int set_b_map_x) {
			b_Map.x = set_b_map_x;
		}
		void SetMapPositionX(int set_b_map_y) {
			b_Map.y = set_b_map_y;
		}

		// 使用フラグ
		bool GetBlockFlag() {
			return b_use_flg;
		}
		void SetBlockFlag(bool set_b_use_flg) {
			b_use_flg = set_b_use_flg;
		}
};

