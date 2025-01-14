#pragma warning(disable:4819)
#include "../../../library/tnl_math.h"
#include "../dxe_mesh.h"

namespace dxe {

	//----------------------------------------------------------------------------------------
	Shared<Mesh> Mesh::CreateSphere(const float radius, const int div_w, const int div_h, const bool is_left_cycle) noexcept
	{
		Shared<Mesh> mesh = Shared<Mesh>(new Mesh());
		mesh->desc_ = std::make_shared<MeshDescSphere>(radius, div_w, div_h, is_left_cycle);
		mesh->shape_type_ = eShapeType::SPHERE;

		tnl::Vector3 far_vtx = { 0, 0, 0 };

		// 横並びの頂点数 = ( 横分割数 * 2 ) - ( 横分割数 - 1 )
		// 縦並びの頂点数 = ( 縦分割数 * 2 ) - ( 縦分割数 - 1 )
		// 総頂点数 = 横並びの頂点数 * 縦並びの頂点数
		int vtx_num = ((div_w * 2) - (div_w - 1)) * ((div_h * 2) - (div_h - 1));
		mesh->vtxs_.resize(vtx_num);

		// 頂点座標の計算
		for (int i = 0; i < (div_h + 1); ++i) {
			float v = i / ((float)div_h);
			float y = cosf(tnl::PI * v) * radius;
			float r = sinf(tnl::PI * v) * radius;

			// 頭頂部の頂点が重複するのを防ぐため ( 法線が計算できなくなるので )
			r = (r < FLT_EPSILON) ? 0.00001f : r;

			for (int k = 0; k < (div_w + 1); ++k) {
				float u = k / ((float)div_w);

				tnl::Vector3 pv;
				pv.x = cosf(2 * tnl::PI * u) * r;
				pv.y = y;
				pv.z = sinf(2 * tnl::PI * u) * r;

				mesh->vtxs_[(i * (div_w + 1)) + k].pos.x = pv.x;
				mesh->vtxs_[(i * (div_w + 1)) + k].pos.y = pv.y;
				mesh->vtxs_[(i * (div_w + 1)) + k].pos.z = pv.z;

				far_vtx.x = (fabs(pv.x) > fabs(far_vtx.x)) ? pv.x : far_vtx.x;
				far_vtx.y = (fabs(pv.y) > fabs(far_vtx.y)) ? pv.y : far_vtx.y;
				far_vtx.z = (fabs(pv.z) > fabs(far_vtx.z)) ? pv.z : far_vtx.z;

				pv.normalize();

				if (is_left_cycle) {
					mesh->vtxs_[(i * (div_w + 1)) + k].norm = { -pv.x, -pv.y, -pv.z };
				}
				else {
					mesh->vtxs_[(i * (div_w + 1)) + k].norm = { pv.x, pv.y, pv.z };
				}


				mesh->vtxs_[(i * (div_w + 1)) + k].u = u;
				mesh->vtxs_[(i * (div_w + 1)) + k].v = v;

				mesh->vtxs_[(i * (div_w + 1)) + k].dif = GetColorU8(255, 255, 255, 255);
				mesh->vtxs_[(i * (div_w + 1)) + k].spc = GetColorU8(255, 255, 255, 255);
			}
		}

		mesh->createPlaneIndex(div_w, div_h, !is_left_cycle);
		mesh->createVBO();

		mesh->bd_sphere_radius_ = far_vtx.length();
		mesh->bd_box_size_ = far_vtx * 2.0f;

		return mesh;

	}


	Shared<Mesh> Mesh::CreateSphereMV(const float radius, const int div_w, const int div_h, const bool is_left_cycle) noexcept {
		Shared<Mesh> mesh = CreateSphere(radius, div_w, div_h, is_left_cycle);
		mesh = CreateConvertMV(mesh);
		return mesh;
	}


}
