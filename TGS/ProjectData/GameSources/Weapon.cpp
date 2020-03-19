#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Weapon::Draw() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);


		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_Sphere");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_Sphere");
		//PtrDraw->SetDiffuse(m_color);

		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetAfterCollision(AfterCollision::None);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Weapon");

	}

	void Weapon::OnCreate() {
		Draw();
	}



	void BulletBase::Draw() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);


		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");


		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);


		AddTag(L"Bullet");

		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptr->GetWorldMatrix(), 10.0f, false, PsMotionType::MotionTypeActive);
		auto psPtr = AddComponent<RigidbodySphere>(param);
		psPtr->SetAutoTransform(true);

		psPtr->SetAutoGravity(0.0f);
	}

	void BulletBase::Move() {
		auto psPtr = GetComponent<RigidbodySphere>();
		auto rot = GetComponent<Transform>()->GetRotation();


		float rad = rot.y /** Mathf.Deg2Rad*/;

		float x = sinf(rad);
		float z = cosf(rad);

		

		Vec3 force = m_moveSpeed * Vec3(x, 1.0f, z);

		psPtr->SetLinearVelocity(force);
		psPtr->ApplyForce(Vec3(0.0f, -m_gravityScale, 0.0f));
	}

	void BulletBase::Destroy() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
	}


	void Bullet::OnCreate() {
		Draw();
		Move();

	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (!Other->FindTag(L"Bullet")) {
			Destroy();
		}
	}


}