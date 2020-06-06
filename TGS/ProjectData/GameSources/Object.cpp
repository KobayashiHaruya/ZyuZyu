#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Object::BmfDateRead(wstring model, Vec3 mpos) {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		Mat4x4 m_spanMat;
		m_spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			m_modelRot,
			mpos
		);

		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(model);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetMeshResource(model);
		ptrDraw->SetMeshToTransformMatrix(m_spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);

		SetAlphaActive(true);

		AddTag(L"Object");


	}

	void Object::ObjectModel() {

		bool phy = false;

		switch (m_food)
		{
		case ObjectType::Oil:
			m_modelName = L"Oil_50(100).bmf";
			m_modelPos = Vec3(0.0f, -238.35f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(0.0f);
			phy = false;
			break;
		case ObjectType::Kakiage:
			m_modelName = L"Kakiage_50(100).bmf";
			m_modelPos = Vec3(0.0f, -238.35f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(18.0f, 2.0f, 18.0f);
			phy = true;
			AddTag(L"Ground");
			break;
		case ObjectType::Nabe:
			m_modelName = L"Nabe_50(100).bmf";
			m_modelPos = Vec3(0.0f, -238.35f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(0.0f);
			phy = false;
			break;
		case ObjectType::Asupara:
			m_modelName = L"Asuparagasu_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(0.65f, 0.65f, 2.5f);
			phy = true;
			break;
		case ObjectType::Azi:
			m_modelName = L"Azifurai_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(2.0f, 1.0f, 2.5f);
			phy = true;
			break;
		case ObjectType::Harumaki:
			m_modelName = L"Harumaki_ver3.bmf";
			m_modelPos = Vec3(0.0f, 0.0, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(2.7f, 1.0f, 1.4f);
			phy = true;
			break;
		case ObjectType::Kabotya:
			m_modelName = L"Kabotya_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(1.5f, 0.5f, 1.0f);
			phy = true;
			break;
		case ObjectType::Katu:
			m_modelName = L"Katu_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(1.7f, 0.9f, 2.3f);
			phy = true;
			break;
		case ObjectType::Korokke:
			m_modelName = L"Korokke_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(1.25f, 0.8f, 1.6f);
			phy = true;
			break;
		case ObjectType::Nasu:
			m_modelName = L"Nasu_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, XM_PI);
			m_colSize = Vec3(1.0f, 0.65f, 1.4f);
			phy = true;
			break;
		case ObjectType::Imo:
			m_modelName = L"Satumaimo_ver3.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(1.5f, 0.4f, 1.5f);
			phy = true;
			break;
		case ObjectType::Siitake:
			m_modelName = L"Siitake_ver2.bmf";
			m_modelPos = Vec3(0.0f, 0.0f, 0.0f);
			m_modelRot = Vec3(0.0f, 0.0f, 0.0f);
			m_colSize = Vec3(1.0f, 0.5f, 1.0f);
			phy = true;
			break;
		default:
			break;
		}

		BmfDateRead(m_modelName, m_modelPos);

		if (phy) {
			Collision();
		}
	}

	void Object::Collision() {
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->AddExcludeCollisionTag(L"Smoke");
		ptrColl->AddExcludeCollisionTag(L"Torimoti");
		ptrColl->AddExcludeCollisionTag(L"Explosion");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Object");

		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(m_colSize);
		ptrColl->SetFixed(true);
	}

	void Object::OnCreate() {
		ObjectModel();
	}
	

	void Result_Icon::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(1.0f, 1.0f, 0.5f));

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		vertices[0].textureCoordinate = Vec2(0, 0);

		vertices[1].textureCoordinate = Vec2(1, 0);

		vertices[2].textureCoordinate = Vec2(0, 1.0f);

		vertices[3].textureCoordinate = Vec2(1, 1.0f);

		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}

		m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto draw = AddComponent<PCTStaticDraw>();
		draw->SetMeshResource(m_SquareMeshResource);
		switch (m_type)
		{
		case POTATO:
			draw->SetTextureResource(L"Result_Potato.png");
			break;
		case SHRIMP:
			draw->SetTextureResource(L"Result_Shrimp.png");
			break;
		case CHICKEN:
			draw->SetTextureResource(L"Result_Chicken.png");
			break;
		case DOUGHNUT:
			draw->SetTextureResource(L"Result_Doughnut.png");
			break;
		}
		SetDrawLayer(-2);
		SetAlphaActive(true);

		auto gravity = AddComponent<Gravity>();

		auto ptrColl = AddComponent<CollisionObb>();

	}

	void Wall::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetPosition(m_Position);
		PtrTransform->SetQuaternion(m_Qt);
		PtrTransform->SetScale(m_Scale);

		auto ptrColl = AddComponent<CollisionObb>();

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);
		SetAlphaActive(true);
		SetDrawActive(false);

		//物理計算ボックス
		PsBoxParam param(PtrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);

	}


}