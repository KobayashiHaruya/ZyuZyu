#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Weapon::Draw() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);


		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_Sphere");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_Sphere");
		//PtrDraw->SetDiffuse(m_color);


		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetAfterCollision(AfterCollision::None);

		//ŠeƒpƒtƒH[ƒ}ƒ“ƒX‚ð“¾‚é
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

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		PtrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);


		auto gravity = AddComponent<Gravity>();
		gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		AddTag(L"Bullet");

		//WorldMatrix‚ð‚à‚Æ‚ÉRigidbodySphere‚Ìƒpƒ‰ƒ[ƒ^‚ðì¬
		PsSphereParam param(ptr->GetWorldMatrix(), 10.0f, false, PsMotionType::MotionTypeActive);
		auto psPtr = AddComponent<RigidbodySphere>(param);
		psPtr->SetAutoTransform(true);

		psPtr->SetAutoGravity(0.0f);
	}

	void BulletBase::Move() {
		auto psPtr = GetComponent<RigidbodySphere>();
		auto trans = GetComponent<Transform>();
		auto rot = trans->GetRotation();

		auto time = App::GetApp()->GetElapsedTime();

		Vec3 force = trans->GetForword() * m_moveSpeed;

		psPtr->SetLinearVelocity(force);
		//psPtr->ApplyForce(Vec3(0.0f, -m_gravityScale, 0.0f));
	}

	void BulletBase::Destroy() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
	}


	void Grenade::Move() {
		auto trans = GetComponent<Transform>();
		auto grav = GetComponent<Gravity>();
		auto rot = trans->GetRotation();

		auto time = App::GetApp()->GetElapsedTime();

		Vec3 force = trans->GetForword() * m_moveSpeed;

		grav->StartJump(force);
	}

	void Grenade::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		PtrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);


		auto gravity = AddComponent<Gravity>();
		//gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		AddTag(L"Grenade");


		Move();
	}

	void Grenade::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (!Other->FindTag(L"Grenade")) {
			auto ptr = GetComponent<Transform>();
			if (m_grenade) {
				GetStage()->AddGameObject<SmokeGrenade>(
					ptr->GetPosition(),
					m_rot,
					Vec3(15.0f, 15.0f, 15.0f),
					ID
					);
			}
			else {
				GetStage()->AddGameObject<TorimotiGrenade>(
					ptr->GetPosition(),
					m_rot,
					Vec3(10.0f, 0.5f, 10.0f),
					ID
					);
			}
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}


	void SmokeGrenade::Timer() {
		float time = App::GetApp()->GetElapsedTime();
		m_time -= time;
		if (0.0f >= m_time) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}

	}

	void SmokeGrenade::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		PtrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		//gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		AddTag(L"Grenade");
		AddTag(L"Smoke");

		m_time = 8.0;

	}

	void SmokeGrenade::OnUpdate() {
		Timer();
	}

	void SmokeGrenade::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
			AddTag(L"Explosion");
			m_time = 0.2f;
		}
	}


	void TorimotiGrenade::Timer() {
		float time = App::GetApp()->GetElapsedTime();
		m_time -= time;
		if (0.0f >= m_time) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}

	}

	void TorimotiGrenade::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f, m_rot.y, 0.0f));
		ptr->SetScale(m_scale);

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);

		//gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		AddTag(L"Grenade");
		AddTag(L"Torimoti");

		m_time = 15.0;

	}

	void TorimotiGrenade::OnUpdate() {
		Timer();
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