#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// 2D �J������K�p�����X�N���[������
// 
// �� 2D �Q�[���ł��J�����̊T�O��K�p���A�J�����𓮂������ƂŃI�u�W�F�N�g�S�Ă𓮂����܂�
// �@�J�������g�p���邱�ƂŃI�u�W�F�N�g�̍��W�̓X�N���[�����W�ł͂Ȃ��A�Q�[����ԍ��W�ƂȂ�܂�
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include "../dxe/dxe.h"
#include "gm_main.h"


const int FIELD_CHIP_NUM_W = 7;
const int FIELD_CHIP_NUM_H = 6;

int field[FIELD_CHIP_NUM_H][FIELD_CHIP_NUM_W] = {
	1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1,
};


//--------------------------------------------------------------------------------------------------
class Chip {
public:
	Chip(const tnl::Vector3& pos) : pos_(pos) {}
	static constexpr float WIDTH = 64;
	static constexpr float HEIGHT = 64;

	tnl::Vector3 pos_;
	void draw(const Shared<dxe::Camera>& camera);
};

void Chip::draw(const Shared<dxe::Camera>& camera) {
	// �Q�[����ԍ��W����X�N���[�����W�֕ϊ�
	tnl::Vector3 draw_pos = camera->convertWorldToScreenPosition2D(pos_);
	dxe::DrawBox({ draw_pos.x, draw_pos.y }, WIDTH, HEIGHT, false, 0);
}


//--------------------------------------------------------------------------------------------------
class Player {
public:
	static constexpr float RADIUS = 20;
	tnl::Vector3 pos_ = { 0, 0, 0 };
	void draw(const Shared<dxe::Camera>& camera);
};

void Player::draw(const Shared<dxe::Camera>& camera) {
	// �Q�[����ԍ��W����X�N���[�����W�֕ϊ�
	tnl::Vector3 draw_pos = camera->convertWorldToScreenPosition2D(pos_);
	DrawCircle(draw_pos.x, draw_pos.y, RADIUS, 0, false);
}

//--------------------------------------------------------------------------------------------------
class BackGround {
public:
	int gfx_hdl_ = 0;
	tnl::Vector3 pos_;
	void draw(const Shared<dxe::Camera>& camera);
};

void BackGround::draw(const Shared<dxe::Camera>& camera) {
	// �Q�[����ԍ��W����X�N���[�����W�֕ϊ�
	// �w�i�����J�����̉e������߂ăX�N���[�����x��x�����邽�� arg2 �� 0.1f ���w��
	tnl::Vector3 draw_pos = camera->convertWorldToScreenPosition2D(pos_, 0.1f);
	DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0f, 0, gfx_hdl_, true);
}


Player player;
BackGround back_ground;
Shared<dxe::Camera> camera;
std::list<Chip*> chips;


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	// 2D �p�J�������쐬
	// arg1... �`��̈�̕�
	// arg2... �`��̈�̍���
	// arg3... �J�����^�C�v( 2D or 3D )
	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F, dxe::Camera::eDimension::Type2D);

	back_ground.gfx_hdl_ = LoadGraph("resource/graphics/example/sky01.png");


	// �e�X�g�p�}�b�v�`�b�v�쐬
	float sx = Chip::WIDTH / 2;
	float sy = Chip::HEIGHT / 2;
	for (int i = 0; i < FIELD_CHIP_NUM_H; ++i) {
		for (int k = 0; k < FIELD_CHIP_NUM_W; ++k) {
			if (0 == field[i][k]) continue;
			chips.emplace_back(new Chip({ sx + k * Chip::WIDTH, sy + i * Chip::HEIGHT, 0 }));
		}
	}

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {


	if (tnl::Input::IsKeyDown(eKeys::KB_A))	player.pos_.x -= 5;
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) player.pos_.x += 5;
	if (tnl::Input::IsKeyDown(eKeys::KB_W))	player.pos_.y -= 5;
	if (tnl::Input::IsKeyDown(eKeys::KB_S))	player.pos_.y += 5;


	// �J�������v���C���[��ǂ�������悤�ɕ�Ԉړ�
	camera->addPosition((player.pos_ - camera->getPosition()) * 0.05f);

	// �J�������̍X�V( �`�揈���̑O�Ɏ��s���邱�� )
	camera->update();


	// �ȉ��`�揈��
	back_ground.draw(camera);
	player.draw(camera);
	for (auto chip : chips) { chip->draw(camera); }


	//
	// �}�E�X�J�[�\�����W���Q�[����ԍ��W�֕ϊ�
	//
	tnl::Vector3 scr_pos = tnl::Input::GetMousePosition();
	dxe::DrawBox({ scr_pos.x, scr_pos.y }, 10, 10, true, dxe::Colors::Red);

	tnl::Vector3 world_pos = camera->convertScreenToWorldPosition2D(scr_pos);
	DrawFormatString(0, 0, 0, "�}�E�X�J�[�\�����W���Q�[����ԍ��W�� %s", world_pos.toString("%.2f").c_str());


	DrawFormatString(0, 20, 0, "�v���C�����W( WASD �ňړ� ) %s", player.pos_.toString("%.2f").c_str());
	DrawFormatString(0, 40, 0, "�J�������W %s", camera->getPosition().toString("%.2f").c_str());

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}


#endif