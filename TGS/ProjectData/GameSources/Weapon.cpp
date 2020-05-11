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

		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);
		SetAlphaActive(true);

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


	void Weapon::BmfDateRead(wstring model) {
		Mat4x4 m_spanMat;
		m_spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつけるa
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(model);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(model);
		ptrDraw->SetMeshToTransformMatrix(m_spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);

		SetAlphaActive(true);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//ptrColl->SetDrawActive(true);
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->SetMakedSize(Vec3(1.5f, 1.0f, 1.5f));
	}

	void Weapon::Gun() {
		int Rand = rand() % 8 + 1;

		m_pos.x = rand() % 60 + -30;
		m_pos.y = 0.0f;
		m_pos.z = rand() % 60 + -30;

		switch (Rand)
		{
		case 0:
			m_modelName = L"AziAssaultRifle_ver1.bmf";
			break; 
		case 1:
			m_modelName = L"AziAssaultRifle_ver1.bmf";
			break;
		case 2:
			m_modelName = L"RenkonRevolver_ver2.bmf";
			break;
		case 3:
			m_modelName = L"PotatoShotgun_ver1.bmf";
			break;
		case 4:
			m_modelName = L"ShrimpSMG_ver2.bmf";
			break;
		case 5:
			m_modelName = L"ChickenRocketlauncher_ver1.bmf";
			break;
		case 6:
			m_modelName = L"DoughnutSniperRifle_ver1.bmf";
			break;
		case 7:
			m_modelName = L"NasuLaser_ver1.bmf";
			break;
		case 8:
			m_modelName = L"Potato_ver1.bmf";
			break;
		default:
			break;
		}

		m_type = Rand;

	}

	void Weapon::OnCreate() {
		auto ptr = GetComponent<Transform>();

		Gun();
		BmfDateRead(m_modelName);

		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(1.0f));

		////影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//PtrDraw->SetTextureResource(text);
		//SetAlphaActive(true);

		auto gravity = AddComponent<Gravity>();

		SetBulletType(m_type);

		AddTag(L"Weapon");
		AddTag(L"FallGun");

	}

	void Weapon::OnUpdate() {

	}

	void Weapon::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto grav = GetComponent<Gravity>();
		auto ptrColl = GetComponent<CollisionObb>();
		if (Other->FindTag(L"Object")) {
			ptrColl->SetFixed(false);
			grav->SetGravityVerocityZero();
			grav->SetGravityZero();
			ptrColl->SetAfterCollision(AfterCollision::None);
		}

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

		//影をつける
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

		//影をつける
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

		//影をつける
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



	void SetGun::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(Vec3(0.0f, -8.5f, 0.0f));
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(3.0f, 3.0f, 3.0f));

		Mat4x4 m_spanMat;
		wstring m_modelName;
		if (m_gun) {
			m_modelName = L"CornGatling.bmf";
			m_spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f));
			AddTag(L"GatlingGun");
		}
		else {
			m_modelName = L"TomatoCannon.bmf";
			m_spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -1.1f, 0.0f));
			AddTag(L"Cannon");
		}

		//影をつけるa
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_modelName);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(m_modelName);
		ptrDraw->SetMeshToTransformMatrix(m_spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);

		SetAlphaActive(true);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->SetMakedSize(Vec3(1.5f, 2.0f, 1.5f));

		AddTag(L"Weapon");
		AddTag(L"SetGun");

		GetStage()->AddGameObject<GunSeat>(
			m_pos,
			m_quat,
			m_gun
			);

	}

	void SetGun::OnUpdate() {

	}

	void GunSeat::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetQuaternion(m_quat);

		Mat4x4 m_spanMat;
		wstring m_modelName;

		if (m_gun) {
			ptr->SetScale(Vec3(3.0f, 3.0f, 3.0f));
			m_modelName = L"CornProp.bmf";
			m_spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f));
			AddTag(L"GatlingGun");
		}
		else {
			ptr->SetScale(Vec3(3.0f, 1.0f, 3.0f));
			m_modelName = L"TomatoBattery.bmf";
			m_spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -1.3f, 0.0f));
			AddTag(L"Cannon");
		}

		//影をつけるa
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_modelName);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(m_modelName);
		ptrDraw->SetMeshToTransformMatrix(m_spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);

		SetAlphaActive(true);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->SetMakedSize(Vec3(1.5f, 2.0f, 1.5f));

		AddTag(L"Weapon");
		AddTag(L"SetGun");
	}

}