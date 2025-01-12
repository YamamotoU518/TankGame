#include "wall.h"

Wall::Wall() {
	if (!origin_) origin_ = dxe::Mesh::CreateCubeMV(100);
	// CreateCubeMV はコストがかかるので、重くなる。なので一つオリジナルを作ってそれをcloneすることではやくすることができる
	origin_->setTexture(texture);
	auto csv = tnl::LoadCsv("CPPSecondField.csv");
}

void Wall::start() {
	float x = -1000;
	float z = 1000;

	for (int i = 0; i < csv.size(); ++i) {
		for (int k = 0; k < csv[i].size(); ++k) {
			if (0 == csv[i][k].getInt()) {
				x += 100;
				continue;
			}
			Shared<dxe::Mesh> clone = origin_->createClone();
			clone->setPosition({ x, 0, z });
			clone->setTexture(texture);

			field_meshs.emplace_back(clone);
			x += 100;
			//SetupCollider<BoxCollider>(Collider::COLLIDER_TAG::WALL, tnl::Vector3(100, 100, 100);
		}

		x = -1000;
		z -= 100;
	}
}

void Wall::update(float delta_time) {

}

void Wall::draw(const Shared<dxe::Camera>& camera) {
	for (auto cube : field_meshs) {
		cube->render(camera);
	}
}