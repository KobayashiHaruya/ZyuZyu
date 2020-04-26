#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Bullet::BulletState(BulletS state) {
		float speed;
		float grav;
		float time;
		Vec3 scale;
		wstring tag;

		switch (state)
		{
		case BulletS::None:
			break;
		case BulletS::Assault:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Hand:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Shot:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::SMG:
			speed = 50.0f;
			grav = 1.0f;
			time = 3.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Rocket:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Sniper:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Laser:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Wind:
			speed = 50.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		default:
			break;
		}

		m_scale = scale;
		m_moveSpeed = speed;
		m_gravityScale = grav;
		m_time = time;

	}

	void Bullet::Draw() {
		BulletState(m_type);

		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetQuaternion(m_rot);
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


		SetID(ID);
		SetBulletType(m_type);

		AddTag(L"Bullet");

	}

	void Bullet::Move() {
		auto trans = GetComponent<Transform>();
		auto grav = GetComponent<Gravity>();

		Vec3 force = trans->GetForword() * m_moveSpeed;

		grav->StartJump(force);
	}

	void Bullet::Timer() {
		auto time = App::GetApp()->GetElapsedTime();

		m_time -= time;

		if (m_time <= 0.0f) {
			Destroy();
		}

	}

	void Bullet::Destroy() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->GetID() != ID && !Other->FindTag(L"Bullet")) {
			Destroy();
		}
	}

	void Bullet::OnCreate() {
		Draw();
		Move();
	}

	void Bullet::OnUpdate() {
		Timer();
	}



	void Grenade::Move() {
		auto trans = GetComponent<Transform>();
		auto grav = GetComponent<Gravity>();

		Vec3 force = trans->GetForword() * m_moveSpeed;

		grav->StartJump(force);
	}

	void Grenade::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetQuaternion(m_rot);
		ptr->SetScale(Vec3(0.5f));

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CAPSULE");

		PtrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetAfterCollision(AfterCollision::None);


		auto gravity = AddComponent<Gravity>();
		gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		SetID(ID);
		AddTag(L"Grenade");


		Move();
	}

	void Grenade::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->GetID() != ID && !Other->FindTag(L"Grenade")) {
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
		ptr->SetQuaternion(m_rot);
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

		AddTag(L"Grenade");
		AddTag(L"Smoke");

		m_time = 8.0;

	}

	void SmokeGrenade::OnUpdate() {
		Timer();
	}

	void SmokeGrenade::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
			SetID(Other->GetID());
			AddTag(L"Explosion");
			RemoveTag(L"Smoke");
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

		auto ptrColl = AddComponent<CollisionObb>();
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




}