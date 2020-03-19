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


		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		PsBoxParam param(ptr->GetWorldMatrix(), 100.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetAutoTransform(false);


		AddTag(L"Object");

	}

	void Object::OnCreate() {
		Draw();
	}

}