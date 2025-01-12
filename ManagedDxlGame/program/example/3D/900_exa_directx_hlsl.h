#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// DirectX HLSL �V�F�[�_���� �O�p�`�`�� ( ���C�e�B���O���� �e�N�X�`���L�� )
//
//
//---------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxe/dxe.h"
#include "gm_main.h"

// ComPtr �� Microsoft ���̃X�}�[�g�|�C���^ 
// DirectX �����������f�[�^�̓v���O���}�� Release���\�b�h���R�[�����ĉ���������s����
// ComPtr �Ŏ�����������邩�ǂ��炩�ł�
// ComPtr ���g�p�����ق���������y�Ȃ̂Ŏg��������
// DxLib �� LONG_PTR ��`���ז��Ȃ̂ňꎞ�I�ɖ����ɂ��� ComPtr ���g����悤�ɂ���
#undef LONG_PTR
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>
#include <VertexTypes.h>
#include <CommonStates.h>
#include <WICTextureLoader.h>
template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

using namespace DirectX;

Shared<dxe::Camera> camera = nullptr;

Shared<dxe::Texture> texture = nullptr;

// ���_�o�b�t�@
ComPtr<ID3D11Buffer>				vertex_buffer = nullptr;
// �C���f�b�N�X�o�b�t�@
ComPtr<ID3D11Buffer>				index_buffer = nullptr;
// ���_�V�F�[�_�[
ComPtr<ID3D11VertexShader>          vertex_shader = nullptr;
// �s�N�Z���V�F�[�_�[
ComPtr<ID3D11PixelShader>           pixel_shader = nullptr;
// ���_���̓��C�A�E�g
ComPtr<ID3D11InputLayout>           input_layout = nullptr;
// �萔�o�b�t�@
ComPtr<ID3D11Buffer>                constant_buffer = nullptr;

// �e�N�X�`��
ComPtr<ID3D11Resource>				tex_res = nullptr;
ComPtr<ID3D11ShaderResourceView>	tex_srv = nullptr;


// �V�F�[�_�萔��`
typedef struct CBUFFER
{
	DirectX::XMMATRIX	mat_view_;  // �r���[ �s��
	DirectX::XMMATRIX	mat_proj_;  // �ˉe �s��
	DirectX::XMMATRIX	mat_world_;  // ���[���h �s��
} TEST_CBUFFER;

// ���_�f�[�^��`
typedef struct VERTEX
{
	DirectX::XMFLOAT3 position_;
	DirectX::XMFLOAT3 normal_;
	DirectX::XMFLOAT2 tex_coord_;
} TEST_VERTEX;

// �e�X�g�p���b�V���̒��_
const int MESH_VERTEX_NUM = 3;
TEST_VERTEX mesh_vertexs[MESH_VERTEX_NUM];

// ���_�����ԏ��Ԃ��`����C���f�b�N�X�z��
// �O�p�`�̖��� * 3 �ɂȂ�z����̊e�l�͒��_���W�z��̔z��ԍ��ɂȂ鎖�ɒ��ӂ��Ă�������
// �C���f�b�N�X�f�[�^���R��؂�ŎO�p�`�̃|���S�����\�����܂�
const int INDEX_NUM = 3;
UINT mesh_vtx_indexs[INDEX_NUM] = { 0, 2, 1 };


// ���f���f�[�^�Ƃ��Ẵg�����X�t�H�[�����
tnl::Vector3 position;
tnl::Vector3 scale = { 1, 1, 1 };
tnl::Quaternion rotation;


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {

	srand(time(0));
	SetBackgroundColor(32, 32, 32);

	// �J��������
	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);

	// ���_���W�ݒ�
	mesh_vertexs[0].position_ = { 0, 100, 0 };
	mesh_vertexs[1].position_ = { 50, 0, 0 };
	mesh_vertexs[2].position_ = { -50, 0, 0 };

	// �@���ݒ�
	mesh_vertexs[0].normal_ = { 0, 0, -1 };
	mesh_vertexs[1].normal_ = { 0, 0, -1 };
	mesh_vertexs[2].normal_ = { 0, 0, -1 };

	// UV ���W�ݒ�
	mesh_vertexs[0].tex_coord_ = { 0.5f, 0 };
	mesh_vertexs[1].tex_coord_ = { 1, 1 };
	mesh_vertexs[2].tex_coord_ = { 0, 1 };

	// DirectX �֐������ʂŕԂ��߂�l�^
	// �֐��̃G���[���m�Ŏg�p
	HRESULT hr = E_FAIL;

	// �V�F�[�_�̃R���p�C���֐����Ԃ��Ă���G���[���b�Z�[�W�󂯎��p
	ID3DBlob* p_err_message = nullptr;

	// VRAM ��Ɋm�ۂ��郁�����⃊�\�[�X�̗��p���@�Ȃǂ�ݒ肷��^
	D3D11_BUFFER_DESC buff_desc;
	D3D11_SUBRESOURCE_DATA sub_resouce_data;

	// DxLib ���� DirectX �f�o�C�X���擾
	// DirectX �f�o�C�X�� DirectX �{�̂Ŋe��K�v�ȃf�[�^�̐����Ȃǂ��s���܂�
	ID3D11Device* pd3dDevice = (ID3D11Device*)DxLib::GetUseDirect3D11Device();

	//-------------------------------------------------------------------------------------------------
	// 
	// ���_�o�b�t�@�̍쐬
	// 
	ID3D11Buffer* p_vertex_buffer = nullptr;
	ZeroMemory(&buff_desc, sizeof(buff_desc));
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = (UINT)(sizeof(TEST_VERTEX) * MESH_VERTEX_NUM);
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	ZeroMemory(&sub_resouce_data, sizeof(sub_resouce_data));
	sub_resouce_data.pSysMem = mesh_vertexs;
	hr = pd3dDevice->CreateBuffer(&buff_desc, &sub_resouce_data, &p_vertex_buffer);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : ���_�o�b�t�@�̐����Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}
	vertex_buffer.Attach(p_vertex_buffer); // ComPtr �Ɏ󂯎��


	//-------------------------------------------------------------------------------------------------
	// 
	// �C���f�b�N�X�o�b�t�@�̍쐬
	//
	ID3D11Buffer* p_index_buffer = nullptr;
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeof(UINT) * INDEX_NUM;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;
	sub_resouce_data.pSysMem = mesh_vtx_indexs;
	hr = pd3dDevice->CreateBuffer(&buff_desc, &sub_resouce_data, &p_index_buffer);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : �C���f�b�N�X�f�[�^�̍쐬�Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}
	index_buffer.Attach(p_index_buffer);


	//-------------------------------------------------------------------------------------------------
	// 
	// ���_�V�F�[�_�̍쐬
	//
	ID3DBlob* p_blob_vertex = nullptr;
	hr = D3DCompileFromFile(L"program/shader/simple_test.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS_Main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &p_blob_vertex, &p_err_message);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : ���_�V�F�[�_�̃R���p�C���Ɏ��s \n");
		OutputDebugStringA(static_cast<char*>(p_err_message->GetBufferPointer()));
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}

	ID3D11VertexShader* p_vertex_shader = nullptr;
	hr = pd3dDevice->CreateVertexShader(p_blob_vertex->GetBufferPointer(), p_blob_vertex->GetBufferSize(), NULL, &p_vertex_shader);
	vertex_shader.Attach(p_vertex_shader);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : ���_�V�F�[�_�̍쐬�Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}


	//-------------------------------------------------------------------------------------------------
	//
	// �s�N�Z���V�F�[�_�̍쐬
	//
	ID3DBlob* p_blob_pixel = nullptr;
	hr = D3DCompileFromFile(L"program/shader/simple_test.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS_Main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &p_blob_pixel, &p_err_message);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : �s�N�Z���V�F�[�_�̃R���p�C���Ɏ��s \n");
		OutputDebugStringA(static_cast<char*>(p_err_message->GetBufferPointer()));
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}

	ID3D11PixelShader* p_pixel_shader = nullptr;
	hr = pd3dDevice->CreatePixelShader(p_blob_pixel->GetBufferPointer(), p_blob_pixel->GetBufferSize(), NULL, &p_pixel_shader);
	pixel_shader.Attach(p_pixel_shader);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : �s�N�Z���V�F�[�_�̍쐬�Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}


	//-------------------------------------------------------------------------------------------------
	// 
	// ���_�C���v�b�g���C�A�E�g�쐬
	//
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},   // 
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},  // 
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},  // 
	};

	ID3D11InputLayout* il = nullptr;
	hr = pd3dDevice->CreateInputLayout(layout, ARRAYSIZE(layout),
		p_blob_vertex->GetBufferPointer(), p_blob_vertex->GetBufferSize(),
		&il);
	input_layout.Attach(il);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : ���_�C���v�b�g���C�A�E�g�̍쐬�Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}


	//-------------------------------------------------------------------------------------------------
	// 
	// �萔�o�b�t�@�̍쐬
	//
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth = sizeof(TEST_CBUFFER);
	ID3D11Buffer* cb = nullptr;
	hr = pd3dDevice->CreateBuffer(&bd, nullptr, &cb);
	constant_buffer.Attach(cb);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : �萔�o�b�t�@�̍쐬�Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}


	//-------------------------------------------------------------------------------------------------
	// 
	// �e�N�X�`������GPU�p�V�F�[�_���\�[�X���쐬
	//
	texture = dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg");

	ID3D11Resource* res = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;
	//wchar_t buff[256] = { 0 };
	//tnl::ToWChara(buff, texture_file_path);
	//hr = CreateWICTextureFromFile(pd3dDevice, buff, &res, &srv);
	hr = CreateWICTextureFromMemory(pd3dDevice, (uint8_t*)texture->getFileData(), (size_t)texture->getDataSize(), &res, &srv);
	tex_res.Attach(res);
	tex_srv.Attach(srv);
	if (S_OK != hr) {
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		tnl::DebugTrace("Error : �V�F�[�_���\�[�X�̍쐬�Ɏ��s \n");
		tnl::DebugTrace("-----------------------------------------------------------------\n");
		return;
	}


}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {


	rotation *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1));


	HRESULT hr = E_FAIL;

	// DxLib ���� DirectX �f�o�C�X�R���e�L�X�g���擾
	// �f�o�C�X�R���e�L�X�g���`�施�߂Ȃǂ��s���܂�
	ID3D11DeviceContext* pImmediateContext = (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext();


	// �J�����X�V
	camera->update();


	// DxLib �̊e��ݒ��ۑ�
	ID3D11VertexShader* bk_vs = nullptr;
	ID3D11PixelShader* bk_ps = nullptr;
	ID3D11ShaderResourceView* bk_srv = nullptr;
	pImmediateContext->VSGetShader(&bk_vs, NULL, 0);
	pImmediateContext->PSGetShader(&bk_ps, NULL, 0);
	pImmediateContext->PSGetShaderResources(0, 1, &bk_srv);


	//-------------------------------------------------------------------------------------------
	// 
	// �萔�o�b�t�@�� CPU ���Ōv�Z�����f�[�^��]��
	//
	{
		TEST_CBUFFER* cbuffer = nullptr;
		XMMATRIX matView, matProj, matWorld;
		D3D11_MAPPED_SUBRESOURCE mappedResource;

		matProj = XMLoadFloat4x4(&camera->getProjectionMatrix());
		matView = XMLoadFloat4x4(&camera->getViewMatrix());

		tnl::Matrix affine = tnl::Matrix::AffineTransformation(position, scale, rotation);
		matWorld = XMLoadFloat4x4(&affine);

		ID3D11Buffer* cb = constant_buffer.Get();
		hr = pImmediateContext->Map(cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		cbuffer = (TEST_CBUFFER*)(mappedResource.pData);

		cbuffer->mat_view_ = matView;
		cbuffer->mat_proj_ = matProj;
		cbuffer->mat_world_ = matWorld;

		pImmediateContext->Unmap(cb, 0);

		// �萔�o�b�t�@�𒸓_�V�F�[�_�ɃZ�b�g
		pImmediateContext->VSSetConstantBuffers(0, 1, &cb);

	}

	// �v���~�e�B�u �^�C�v����уf�[�^�̏����Ɋւ������ݒ�
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �[�x�X�e���V���o�b�t�@�̐ݒ�
	pImmediateContext->OMSetDepthStencilState(dxe::GetDepthStencilState(dxe::eDepthStenclil::DEPTH_W_ON_T_ON), 0);

	// ���X�^���C�U�X�e�[�g�ݒ�
	pImmediateContext->RSSetState(dxe::GetRasterizerState(dxe::eRasterizerState::CULL_NONE));

	// �u�����h�X�e�[�g�ݒ�
	pImmediateContext->OMSetBlendState(dxe::GetBlendState(dxe::eBlendState::NORMAL), 0, 0xffffffff);

	// �T���v���X�e�[�g��ݒ肷��
	ID3D11SamplerState* st = dxe::GetSamplerState(dxe::eSamplerState::ANISOTROPIC);
	pImmediateContext->PSSetSamplers(0, 1, &st);


	// ���̓A�Z���u���[ �X�e�[�W�ɒ��_�o�b�t�@�[�̔z����o�C���h����B
	UINT stride = sizeof(TEST_VERTEX);
	UINT offset = 0;
	ID3D11Buffer* vb = vertex_buffer.Get();
	pImmediateContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);


	//�C���f�b�N�X�o�b�t�@�̃Z�b�g
	pImmediateContext->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// ���_�f�[�^���C�A�E�g�ݒ�
	pImmediateContext->IASetInputLayout(input_layout.Get());

	// ���_�V�F�[�_�[���Z�b�g
	pImmediateContext->VSSetShader(vertex_shader.Get(), NULL, 0);

	// �s�N�Z���V�F�[�_�[���Z�b�g
	pImmediateContext->PSSetShader(pixel_shader.Get(), NULL, 0);

	// �e�N�X�`���[��ݒ肷��
	ID3D11ShaderResourceView* srv = tex_srv.Get();
	pImmediateContext->PSSetShaderResources(0, 1, &srv);

	// �`�施��
	pImmediateContext->DrawIndexed(INDEX_NUM, 0, 0);


	// �e��ݒ�� DxLib �ɖ߂�
	pImmediateContext->VSSetShader(bk_vs, NULL, 0);
	pImmediateContext->PSSetShader(bk_ps, NULL, 0);
	pImmediateContext->PSSetShaderResources(0, 1, &bk_srv);


	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}

#endif