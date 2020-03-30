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
		ptr->SetRotation(Vec3(0.0f, m_rot.y, 0.0f));
		ptr->SetScale(m_scale);

		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		PtrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

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
		auto trans = GetComponent<Transform>();
		auto rot = trans->GetRotation();

		float rad = (rot.y * 3.1415) / 180.0f;

		float x = sin(rad);
		float z = cos(rad);

		Vec3 force = m_moveSpeed * Vec3(z, 0.0f, x);

		psPtr->SetLinearVelocity(force);
		//psPtr->ApplyForce(Vec3(0.0f, -m_gravityScale, 0.0f));
	}

	void BulletBase::Destroy() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
	}


	void Bullet::OnCreate() {
		Draw();
		Move();
	}

	void Bullet::OnUpdate() {
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (!Other->FindTag(L"Bullet")) {
			Destroy();
		}
	}


}