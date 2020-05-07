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
			speed = 80.0f;
			grav = 5.0f;
			time = 0.2f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Gatling:
			speed = 80.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			break;
		case BulletS::Cannon:
			speed = 80.0f;
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

		//PtrDraw->SetTextureResource(L"trace.png");
		//SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionRect>();
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


	void Weapon::Gun() {
		int Rand = rand() % 8 + 1;

		m_pos.x = rand() % 60 + -30;
		m_pos.y = 0.0f;
		m_pos.z = rand() % 60 + -30;

		switch (Rand)
		{
		case 0:
			text = L"None.png";
			break;
		case 1:
			text = L"Assault.png";
			break;
		case 2:
			text = L"Hand.png";
			break;
		case 3:
			text = L"Shot.png";
			break;
		case 4:
			text = L"SMG.png";
			break;
		case 5:
			text = L"Rocket.png";
			break;
		case 6:
			text = L"Sniper.png";
			break;
		case 7:
			text = L"Laser.png";
			break;
		case 8:
			text = L"Wind.png";
			break;
		default:
			break;
		}

		m_type = Rand;

	}

	void Weapon::OnCreate() {
		auto ptr = GetComponent<Transform>();

		Gun();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(1.0f));

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetTextureResource(text);
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		auto gravity = AddComponent<Gravity>();

		SetBulletType(m_type);

		AddTag(L"Weapon");
		AddTag(L"FallGun");

	}

	void Weapon::OnUpdate() {

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

		//PtrDraw->SetTextureResource(L"trace.png");
		//SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetAfterCollision(AfterCollision::None);


		auto gravity = AddComponent<Gravity>();
		gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		SetID(ID);
		AddTag(L"Grenade");


		Move();
	}

	void Grenade::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if ((Other->GetID() != ID && !Other->FindTag(L"Grenade")) || Other->FindTag(L"Object")) {
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

		//PtrDraw->SetTextureResource(L"trace.png");
		//SetAlphaActive(true);

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

		//PtrDraw->SetTextureResource(L"trace.png");
		//SetAlphaActive(true);

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


	void GatlingGun::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(Vec3(0.0f, -8.5f, 0.0f));
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(1.5f, 3.0f, 1.5f));

		//‰e‚ð‚Â‚¯‚é
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"SetGun");
		AddTag(L"GatlingGun");

	}

	void GatlingGun::OnUpdate() {

	}


}