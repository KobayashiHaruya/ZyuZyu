#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ObjectBase::BmfDateRead(wstring model, Vec3 mpos, Vec3 mrot, Vec3 mscale) {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		Mat4x4 m_spanMat;
		mrot.y = mrot.y * 3.14f / 180.0f;
		m_spanMat.affineTransformation(
			mscale,
			Vec3(0.0f, 0.0f, 0.0f),
			mrot,
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

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		ptrColl->AddExcludeCollisionTag(L"Smoke");
		ptrColl->AddExcludeCollisionTag(L"Torimoti");
		ptrColl->AddExcludeCollisionTag(L"Explosion");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Object");

		SetAlphaActive(true);

		AddTag(L"Object");
	}

	void ObjectBase::Draw() {

		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		//‰e‚ð‚Â‚¯‚éa
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetDrawActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		ptrColl->AddExcludeCollisionTag(L"Smoke");
		ptrColl->AddExcludeCollisionTag(L"Torimoti");
		ptrColl->AddExcludeCollisionTag(L"Explosion");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Object");

		SetAlphaActive(true);

		AddTag(L"Object");
	}

	void Object::OnCreate() {
		Draw();
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
	}

	void OilStage::OnCreate() {
		BmfDateRead(L"Kakiage_50(100).bmf", Vec3(0.0f, -94.15f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(Vec3(10.5f, 2.0f, 10.5f));
		SetAlphaActive(true);

		AddTag(L"Object");
	}
	
	void OilStage::OnUpdate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
	}

	void Oil::OnCreate() {
		if (m_model) {
			BmfDateRead(L"Oil_50(100).bmf", Vec3(0.0f, -85.75f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		}
		else {
			Draw();
		}
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		AddTag(L"Oil");
	}

	void Nabe::OnCreate() {
		BmfDateRead(L"Nabe_50(100).bmf", Vec3(0.0f, -95.75f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
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

		//‰e‚ð‚Â‚¯‚é
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);
		SetAlphaActive(true);
		SetDrawActive(false);

		//•¨—ŒvŽZƒ{ƒbƒNƒX
		PsBoxParam param(PtrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);

	}

}