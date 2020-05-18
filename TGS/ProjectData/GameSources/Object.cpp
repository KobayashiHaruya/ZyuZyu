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

		////‰e‚ð‚Â‚¯‚é
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");


		//‰e‚ð‚Â‚¯‚éa
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetDrawActive(true);

		SetAlphaActive(true);

		//PtrDraw->SetTextureResource(L"trace.png");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		AddTag(L"Object");
	}

	void Object::OnCreate() {
		Draw();
	}

	void OilStage::OnCreate() {
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(Vec3(1.2f, 0.08f, 1.2f));
		//ptrColl->SetDrawActive(true);
		BmfDateRead(L"Stage_floor.bmf", Vec3(0.0f, -0.725f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	}
	
	void OilStage::OnUpdate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
	}

	void Oil::OnCreate() {
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(Vec3(100.0f, 0.825f, 100.0f));
		//ptrColl->SetDrawActive(true);
		BmfDateRead(L"Stage_oil.bmf", Vec3(0.0f, -0.7f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
		AddTag(L"Oil");
	}

	void Nabe::OnCreate() {
		BmfDateRead(L"Stage_nabe.bmf", Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	}

}