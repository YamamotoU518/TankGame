#include "skybox.h"
#include "../dxe/dxe.h"

SkyBox::SkyBox() {
	skybox = dxe::Mesh::CreateCubeMV(5000, 20, 20);
	skybox->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/skybox/Magical.png"));
	skybox->loadMaterial(FILE_PATH_BIN_SKYBOX_MATERIAL);
}

void SkyBox::start() {

}

void SkyBox::update(float delta_time) {
	skybox->mulRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f)));
}

void SkyBox::draw(const Shared<dxe::Camera>& camera) {
	skybox->render(camera);
}