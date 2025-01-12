#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// CSV ����ǂݍ��� �t�B�[���h�}�b�v�ƏՓ˔���ƕ␳�������Ȃ�
// �@
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


class Block {
public:
	Block(const tnl::Vector3& pos) : pos_(pos) {}

	static constexpr float CHIP_SIZE = 64;

	tnl::Vector3 pos_ = { 0, 0, 0 };
};

const int PLAYER_SIZE = 60;
float gravity = 0;
tnl::Vector3 player_pos = { 300, 300, 0 };

std::vector<std::vector<int>> map_csv;

std::list<Block*> blocks;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	map_csv = tnl::LoadCsv<int>("resource/csv/example_map_chip.csv");

	float sx = DXE_WINDOW_WIDTH_QUARTER_F;
	float sy = 100;

	for (int i = 0; i < map_csv.size(); ++i) {
		for (int k = 0; k < map_csv[i].size(); ++k) {
			if (0 == map_csv[i][k]) continue;
			tnl::Vector3 pos;
			pos.x = { sx + k * Block::CHIP_SIZE };
			pos.y = { sy + i * Block::CHIP_SIZE };
			blocks.emplace_back(new Block(pos));
		}
	}


}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	tnl::Vector3 prev_pos = player_pos;

	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		player_pos.x -= 10;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		player_pos.x += 10;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		gravity = -20.0f;
	}

	gravity += 0.98;
	player_pos.y += gravity;

	// �v���C���[�ɋ߂����Ƀ\�[�g
	blocks.sort([](Block* l, Block* r) {
		float ld = (player_pos - l->pos_).length();
		float rd = (player_pos - r->pos_).length();
		return ld < rd;
		});

	// �u���b�N�ƏՓ˔��� & �␳
	for (auto blk : blocks) {

		// �Փ˔���
		if (tnl::IsIntersectRect(player_pos, PLAYER_SIZE, PLAYER_SIZE, blk->pos_, Block::CHIP_SIZE, Block::CHIP_SIZE)) {

			// ��`���m�̍��W�␳
			// arg1.2. ��` A, B �̈ړ��O�̍��W
			// arg3.4. ��` A, B �̃T�C�Y
			// arg5.6. ��` A, B �̈ړ���̍��W ( ���̊֐��ɂ���ĕ␳��̍��W�ɍX�V )
			// arg7.8. ��, �c �����̕␳�^�C�v
			// ....... [ PWRFL_A : A �� ���� ] [ PWRFL_B : B �� ���� ] [ BOTH : A �� B �͉������� ]
			// arg9... �␳��� A �� B �̊Ԃɐ݂����� ( �f�t�H���g 1.0f )
			// ret.... ��` A �� B �ɑ΂��Ăǂ̕����֕␳���ꂽ��
			tnl::eCorrResRect n = tnl::CorrectPositionRect(
				prev_pos
				, blk->pos_
				, { PLAYER_SIZE, PLAYER_SIZE }
				, { (int)Block::CHIP_SIZE, (int)Block::CHIP_SIZE }
				, player_pos
				, blk->pos_
				, tnl::eCorrTypeRect::PWRFL_B
				, tnl::eCorrTypeRect::PWRFL_B, 1.0f);

			// �㉺�ɕ␳���ꂽ�ꍇ�͏d�̓��Z�b�g
			if (n == tnl::eCorrResRect::UP || n == tnl::eCorrResRect::DOWN) {
				gravity = 0;
			}
		}

	}

	//-------------------------------------------------------------------
	//
	// �`��
	//

	for (auto blk : blocks) {
		dxe::DrawBox({ blk->pos_.x, blk->pos_.y }, Block::CHIP_SIZE, Block::CHIP_SIZE, false);
	}

	dxe::DrawBox({ player_pos.x, player_pos.y }, PLAYER_SIZE, PLAYER_SIZE, false, dxe::Colors::Red);

	DrawString(0, 0, "W : �W�����v", -1);
	DrawString(0, 20, "AD : ���E�ړ�", -1);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif
