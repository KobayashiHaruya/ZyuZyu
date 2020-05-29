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


		SetAlphaActive(true);

		AddTag(L"Object");

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetFogEnabled(true);
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//PtrDraw->SetOwnShadowActive(true);
		//PtrDraw->SetTextureResource(L"SKY_TX");

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
		Draw();
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(Vec3(10.5f, 0.5f, 10.5f));
		BmfDateRead(L"Kakiage_50(100).bmf", Vec3(0.0f, -95.75f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetAlphaActive(true);

		AddTag(L"Object");
	}
	
	void OilStage::OnUpdate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
	}

	void Oil::OnCreate() {
		Draw();
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetMakedSize(Vec3(50.0f, 1.0f, 50.0f));
		BmfDateRead(L"Oil_50(100).bmf", Vec3(0.0f, -85.75f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		AddTag(L"Oil");
	}

	void Nabe::OnCreate() {
		BmfDateRead(L"Nabe_50(100).bmf", Vec3(0.0f, -95.75f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
	}

}