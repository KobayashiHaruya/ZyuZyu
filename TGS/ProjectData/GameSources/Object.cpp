#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Object::Draw() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);


		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetColorAndAlpha(Flt4(0.5f, 1.0f, 1.0f, 1.0f));

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetDrawActive(true);
		
		AddTag(L"Object");

	}

	void Object::OnCreate() {
		Draw();
	}

	void Object::OnUpdate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
	}

}