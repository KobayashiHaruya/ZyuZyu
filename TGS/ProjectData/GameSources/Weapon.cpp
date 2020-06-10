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
			speed = 65.0f;
			grav = 4.0f;
			time = 5.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Assault:
			speed = 65.0f;
			grav = 4.0f;
			time = 5.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Hand:
			speed = 75.0f;
			grav = 4.0f;
			time = 5.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Shot:
			speed = 60.0f;
			grav = 5.0f;
			time = 5.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::SMG:
			speed = 75.0f;
			grav = 1.0f;
			time = 5.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Rocket:
			speed = 55.0f;
			grav = 0.5f;
			time = 5.0f;
			scale = Vec3(1.5f);
			AddTag(L"Bullet");
			break;
		case BulletS::Sniper:
			speed = 140.0f;
			grav = 2.0f;
			time = 2.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Laser:
			speed = 120.0f;
			grav = 0.0f;
			time = 2.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Wind:
			speed = 80.0f;
			grav = 5.0f;
			time = 0.2f;
			scale = Vec3(2.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Gatling:
			speed = 100.0f;
			grav = 5.0f;
			time = 1.0f;
			scale = Vec3(1.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::Cannon:
			speed = 20.0f;
			grav = 1.0f;
			time = 10.0f;
			scale = Vec3(3.0f);
			AddTag(L"Bullet");
			break;
		case BulletS::GExplosion:
			speed = 0.0f;
			grav = 0.0f;
			time = 0.2f;
			scale = Vec3(10.0f);
			AddTag(L"Explosion");
			AddTag(L"Bullet");
			break;
		case BulletS::CExplosion:
			speed = 0.0f;
			grav = 0.0f;
			time = 0.2f;
			scale = Vec3(15.0f);
			AddTag(L"Explosion");
			AddTag(L"Bullet");
			break;
		case BulletS::SExplosion:
			speed = 0.0f;
			grav = 0.0f;
			time = 0.2f;
			scale = Vec3(13.0f);
			AddTag(L"Explosion");
			AddTag(L"Bullet");
			AddTag(L"Smoke");
			break;
		case BulletS::RExplosion:
			speed = 0.0f;
			grav = 0.0f;
			time = 0.5f;
			scale = Vec3(5.0f);
			AddTag(L"Explosion");
			AddTag(L"Bullet");
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

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->AddExcludeCollisionTag(L"Bullet");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Explosion");

		auto gravity = AddComponent<Gravity>();
		gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

		EffectState(m_type);
		if (m_frome.isPlayer) {
			SE(m_type);
		}

		SetID(ID);
		SetBulletType(m_type);
	}

	void Bullet::EffectState(BulletS state) {
		switch (state)
		{
		case BulletS::None:
			Effect(L"Assault_ver2.efk");
			break;
		case BulletS::Assault:
			Effect(L"Assault_ver2.efk");
			break;
		case BulletS::Hand:
			Effect(L"Revolver_ver2.efk");
			break;
		case BulletS::Shot:
			Effect(L"Shotgun_ver2.efk");
			break;
		case BulletS::SMG:
			Effect(L"SMG_ver2.efk");
			break;
		case BulletS::Rocket:
			Effect(L"RocketBoost.efk");
			break;
		case BulletS::Sniper:
			Effect(L"Sniper2_ver2.efk");
			break;
		case BulletS::Laser:
			Effect(L"Laser3_ver2.efk");
			break;
		case BulletS::Wind:
			Effect(L"Wind_ver2.efk");
			break;
		case BulletS::Gatling:
			Effect(L"Gatling_ver2.efk");
			break;
		case BulletS::Cannon:
			break;
		case BulletS::GExplosion:
			Effect(L"Explosion_Gatling.efk");
			break;
		case BulletS::CExplosion:
			Effect(L"NExplosion_Tomato.efk");
			Effect(L"Explosion_Tomato2.efk");
			break;
		case BulletS::SExplosion:
			Effect(L"Explosion_Grenade.efk");
			break;
		case BulletS::RExplosion:
			Effect(L"Explosion_Egg.efk");
			break;
		default:
			break;
		}
	}

	void Bullet::Effect(wstring name) {
		auto ptr = GetComponent<Transform>();

		m_efkEffect = GetTypeStage<GameStage>()->GetEffect(name);
		m_efkPlay = ObjectFactory::Create<EfkPlay>(m_efkEffect, ptr->GetPosition());
		m_efkPlay->Play(m_efkEffect, ptr->GetPosition());

		//Vec3 rot = ptr->GetForword();
		//m_efkPlay->SetRotation(Vec3(ptr->GetForword()));
	}
	
	void Bullet::SE(BulletS state) {
		wstring SEName;
		float volume;

		switch (state)
		{
		case BulletS::None:
			SEName = L"ハンドガン01.wav";
			volume = 0.1f;
			break;
		case BulletS::Assault:
			SEName = L"ハンドガン01.wav";
			volume = 0.1f;
			break;
		case BulletS::Hand:
			SEName = L"+Zyu_05.wav";
			volume = 0.1f;
			break;
		case BulletS::Shot:
			SEName = L"short_se.wav";
			volume = 0.01f;
			break;
		case BulletS::SMG:
			SEName = L"+Ga03.wav";
			volume = 0.1f;
			break;
		case BulletS::Rocket:
			SEName = L"Roketto01.wav";
			volume = 0.1f;
			break;
		case BulletS::Sniper:
			SEName = L"爆発_色々03.wav";
			volume = 0.1f;
			break;
		case BulletS::Laser:
			SEName = L"レーザー05.wav";
			volume = 0.1f;
			break;
		case BulletS::Wind:
			SEName = L"+Kaze05.wav";
			volume = 0.1f;
			break;
		case BulletS::Gatling:
			SEName = L"+Ga03.wav";
			volume = 0.05f;
			break;
		case BulletS::Cannon:
			SEName = L"cannonbomb_se.wav";
			volume = 0.1f;
			break;
		case BulletS::GExplosion:
			SEName = L"cannonbomb_se.wav";
			volume = 0.1f;
			break;
		case BulletS::CExplosion:
			SEName = L"cannonbomb_se.wav";
			volume = 0.1f;
			break;
		case BulletS::SExplosion:
			SEName = L"explosion_smork_se.wav";
			volume = 0.1f;
			break;
		case BulletS::RExplosion:
			SEName = L"+Bakuhatu01.wav";
			volume = 0.1f;
			break;
		default:
			break;
		}

		GetTypeStage<GameStage>()->PlaySE(SEName, volume);

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
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}

	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (FindTag(L"Explosion") || m_type == BulletS::Laser) {

		}
		else if ((Other->FindTag(L"Object") && !Other->FindTag(L"Bullet"))
			|| (Other->FindTag(L"Grenade") && !Other->FindTag(L"Smoke")) ||
			Other->GetID() != ID) {
			Destroy();

			m_efkPlay->StopEffect();
			if (m_type == BulletS::Rocket) {
				auto ptr = GetComponent<Transform>();

				auto eBullet = GetStage()->AddGameObject<Bullet>(
					ptr->GetPosition(),
					ptr->GetQuaternion(),
					BulletS::RExplosion,
					m_frome.unique,
					ID,
					m_frome
					);

				AddEvent([this](const CharacterStatus_s status) {
					Destroy();
				});

				eBullet->AddEvent([this](const CharacterStatus_s status) {
					Run(status);
				});
			}

		}
	}

	void Bullet::Destroy() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		//m_efkPlay->StopEffect();
	}

	void Bullet::OnCreate() {
		Draw();
		Move();
	}

	void Bullet::OnUpdate() {
		auto pos = GetComponent<Transform>();
		m_efkPlay->SetLocation(pos->GetPosition());
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
		m_pos.y = 10.0f;
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
			m_modelName = L"MaitakeWind_ver1.bmf";
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

		auto gravity = AddComponent<Gravity>();

		SetBulletType(m_type);

		AddTag(L"Weapon");
		AddTag(L"FallGun");

	}

	void Weapon::OnUpdate() {
		if (0.0f >= m_time) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
		else {
			float time = App::GetApp()->GetElapsedTime();
			m_time -= time;
		}
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
		ptr->SetScale(Vec3(0.6f));

		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CAPSULE");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->AddExcludeCollisionTag(L"Smoke");
		ptrColl->AddExcludeCollisionTag(L"Torimoti");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");

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
					ID,
					m_frome
					);
			}
			else {
				GetStage()->AddGameObject<TorimotiGrenade>(
					ptr->GetPosition(),
					m_rot,
					ID,
					m_frome
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
		ptr->SetScale(Vec3(13.0f));

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->AddExcludeCollisionTag(L"Grenade");
		ptrColl->AddExcludeCollisionTag(L"Smoke");
		ptrColl->AddExcludeCollisionTag(L"Torimoti");
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Object");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");
		
		AddTag(L"Grenade");
		AddTag(L"Smoke");

		m_efkEffect = GetTypeStage<GameStage>()->GetEffect(L"SmokeGrenade.efk");
		m_efkPlay = ObjectFactory::Create<EfkPlay>(m_efkEffect, ptr->GetPosition());
		m_efkPlay->Play(m_efkEffect, ptr->GetPosition());
		Vec3 rot = ptr->GetForword();
		m_efkPlay->SetRotation(rot);

		m_time = 8.0;

	}

	void SmokeGrenade::OnUpdate() {
		Timer();
	}

	void SmokeGrenade::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			m_efkPlay->StopEffect();

			auto trans = GetComponent<Transform>();

			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				m_frome = bullet->GetFrome();
				AddEvent([bullet](const CharacterStatus_s status) {
					bullet->Run(status);
					});
			}

			//このBulletハ爆発のeffectを再生するために使用していると思われる
			//ということはここに煙に当たったバレットの情報をまるっと入れてあげればキル情報を更新d家いるのでは？
			auto eBullet = GetStage()->AddGameObject<Bullet>(
				trans->GetPosition(),
				trans->GetQuaternion(),
				BulletS::SExplosion,
				Other->GetID(),
				Other->GetID(),
				m_frome
				);

			if (bullet) {
				eBullet->AddEvent([bullet](const CharacterStatus_s status) {
					bullet->Run(status);
					});
			}

			AddEvent([eBullet](const CharacterStatus_s status) {
				eBullet->Run(status);
				});
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
		ptr->SetScale(Vec3(10.0f, 0.3f, 10.0f));

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

		ptrColl->AddExcludeCollisionTag(L"Grenade");
		ptrColl->AddExcludeCollisionTag(L"Smoke");
		ptrColl->AddExcludeCollisionTag(L"Torimoti");
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Object");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");

		AddTag(L"Grenade");
		AddTag(L"Torimoti");

		m_time = 15.0;

	}

	void TorimotiGrenade::OnUpdate() {
		Timer();
	}


	void GatlingAmmo::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(1.0));

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//左上頂点
		vertices[0].textureCoordinate = Vec2(0, 0);
		//右上頂点
		vertices[1].textureCoordinate = Vec2(1, 0);
		//左下頂点
		vertices[2].textureCoordinate = Vec2(0, 1.0f);
		//右下頂点
		vertices[3].textureCoordinate = Vec2(1, 1.0f);

		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}

		m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto draw = AddComponent<PCTStaticDraw>();
		draw->SetMeshResource(m_SquareMeshResource);
		draw->SetTextureResource(L"Corn.png");
		SetAlphaActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->AddExcludeCollisionTag(L"Grenade");
		ptrColl->AddExcludeCollisionTag(L"Bullet");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Explosion");

		auto gravity = AddComponent<Gravity>();

		float X = rand() % 5;
		float Z = rand() % 5;
		gravity->StartJump(Vec3(X, 2.0f, Z));

	}

	void GatlingAmmo::OnUpdate() {		
		auto PtrTransform = GetComponent<Transform>();
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

		Quat Qt;
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		PtrTransform->SetQuaternion(Qt);

		if (0.0f >= m_time) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
		else {
			float time = App::GetApp()->GetElapsedTime();
			m_time -= time;
		}
	}

	void GatlingAmmo::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto grav = GetComponent<Gravity>();
		auto ptrColl = GetComponent<CollisionObb>();
		if (Other->FindTag(L"Object")) {
			AddTag(L"GatlingAmmo");
			ptrColl->SetFixed(false);
			grav->SetGravityVerocityZero();
			grav->SetGravityZero();
			ptrColl->SetAfterCollision(AfterCollision::None);
		}

	}


	void CannonAmmoBox::BmfDateRead(wstring model) {
		Mat4x4 m_spanMat;
		m_spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f));

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
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);
		AddTag(L"CannonAmmoBox");

		ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->AddExcludeCollisionTag(L"Grenade");
		ptrColl->AddExcludeCollisionTag(L"Bullet");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Explosion");
	}

	void CannonAmmoBox::OnCreate() {
		auto ptr = GetComponent<Transform>();

		BmfDateRead(m_modelName);

		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f));
		ptr->SetScale(Vec3(1.0f));

	}


	void SetGun::OnCreate() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetQuaternion(m_qua);
		ptr->SetScale(Vec3(3.0f));

		Mat4x4 m_spanMat;
		wstring m_modelName;
		if (m_gun) {
			m_modelName = L"CornGatling.bmf";
			m_spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f));

		}
		else {
			m_modelName = L"TomatoCannon.bmf";
			m_spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -1.1f, 0.0f));

			GetStage()->AddGameObject<GunSeat>(
				m_pos,
				m_qua,
				m_gun
				);
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
		ptrDraw->SetDiffuse(Col4(1.0f, 0.6f, 0.0f, 1.0f));

		SetAlphaActive(true);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Weapon");
		//AddTag(L"SetGun");


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
			ptr->SetScale(Vec3(3.0f, 0.6f, 3.0f));
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
		ptrColl->AddExcludeCollisionTag(L"Grenade");
		ptrColl->AddExcludeCollisionTag(L"Bullet");
		ptrColl->AddExcludeCollisionTag(L"GatlingAmmo");
		ptrColl->AddExcludeCollisionTag(L"SetGun");
		ptrColl->AddExcludeCollisionTag(L"Explosion");

		ptrColl->SetMakedSize(Vec3(0.5f, 1.0f, 0.5f));

		AddTag(L"Weapon");
		AddTag(L"SetGun");
	}

}