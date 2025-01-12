#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"
#include "gamemanager.h"

Shared<dxe::Camera> camera = nullptr;
Shared<Tank> tank;
Shared <dxe::Texture> texture;
std::list<Shared<dxe::Mesh>> field_meshs;
Shared<GameManager> gmr;
Shared<dxe::Mesh> ground;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	gmr = GameManager::GetInstance();

	srand(time(0));

	/*SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 5000.0f); */ // skyboxと共存できないかも
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);
	
	texture = dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg");

	tank = std::make_shared<Tank>();
	gmr->objects.emplace_back(tank);

	Shared<dxe::Mesh> origin = dxe::Mesh::CreateCubeMV(100);
	// CreateCubeMV はコストがかかるので、重くなる。なので一つオリジナルを作ってそれをcloneすることではやくすることができる
	origin->setTexture( texture );
	auto csv = tnl::LoadCsv("CPPSecondField.csv");

	float x = -1000;
	float z = 1000;

	for (int i = 0; i < csv.size(); ++i) {
		for (int k = 0; k < csv[i].size(); ++k) {
			if (0 == csv[i][k].getInt()) {
				x += 100;
				continue;
			}
			Shared<dxe::Mesh> clone = origin->createClone();
			clone->setPosition({ x, 0, z });
			clone->setTexture( texture );

			field_meshs.emplace_back(clone);
			x += 100;
		}

		x = -1000;
		z -= 100;
	}

	Shared<SkyBox> skybox = std::make_shared<SkyBox>();
	gmr->objects.emplace_back(skybox);

	ground = dxe::Mesh::CreatePlaneMV({ 2000, 2000, 0 }, 20, 20);
	ground->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/lawn.png"));
	ground->setRotation(tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90)));
	ground->setPosition({ 0, -50, 0 });

	for (auto obj : gmr->objects) {
		obj->start();
	}
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
	for (auto obj : gmr->objects) { obj->update(delta_time); }

	tnl::Vector3 back_ofs = tnl::Vector3::TransformCoord({ 0, 300, -500 }, tank->rotation_);
	camera->setPosition(tank->position_ + back_ofs);
	camera->setTarget(tank->position_);

	camera->update();

	// bullet の削除処理
	auto bullet_it = gmr->bullets.begin();
	while (bullet_it != gmr->bullets.end()) {
		if (!(*bullet_it)->is_alive_) {
			bullet_it = gmr->bullets.erase(bullet_it);
			continue;
		}
		bullet_it++;
	}

	// オブジェクトの削除処理
	auto obj_it = gmr->objects.begin();
	while (obj_it != gmr->objects.end()) {
		if (!(*obj_it)->is_alive_) {
			obj_it = gmr->objects.erase(obj_it);
			continue;
		}
		obj_it++;
	}

	for (auto cube : field_meshs) {
		cube->render(camera);
	}

	ground->render(camera);

	for (auto obj : gmr->objects) { obj->draw(camera); }

	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}