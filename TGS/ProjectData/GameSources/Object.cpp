#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Object::BmfDateRead(wstring model, Vec3 mpos, Vec3 mrot, Vec3 mscale) {
		Mat4x4 m_spanMat;
		mrot.y = mrot.y * 3.14f / 180.0f;
		m_spanMat.affineTransformation(
			mscale,
			Vec3(0.0f, 0.0f, 0.0f),
			mrot,
			mpos
		);

		//‰e‚ð‚Â‚¯‚éa
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(model);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(model);
		ptrDraw->SetMeshToTransformMatrix(m_spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);

		SetAlphaActive(true);

	}

	void Object::Draw() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		
		AddTag(L"Object");

	}

	void Object::OnCreate() {
		Draw();
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(Vec3(1.2f, 0.08f, 1.2f));
		//ptrColl->SetDrawActive(true);
		BmfDateRead(L"Stage_floor.bmf", Vec3(0.0f, -0.725f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	}
	
	void Object::OnUpdate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
	}

	void Oil::OnCreate() {
		Draw();
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetMakedSize(Vec3(4.0f, 0.825f, 4.0f));
		//ptrColl->SetDrawActive(true);
		BmfDateRead(L"Stage_oil.bmf", Vec3(0.0f, -0.7f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
		AddTag(L"Oil");
	}

	void Nabe::OnCreate() {
		Draw();
		BmfDateRead(L"Stage_nabe.bmf", Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	}

}