/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Character::BmfDateRead(wstring model) {
		Mat4x4 m_spanMat;
		m_spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.5f, 0.0f));

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(Vec3(1.0f, 1.7f, 1.0f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(model);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto PtrDraw = AddComponent<BcPNTBoneModelDraw>();
		PtrDraw->SetFogEnabled(false);
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(model);
		PtrDraw->SetMeshToTransformMatrix(m_spanMat);

		PtrDraw->AddAnimation(L"Stop", 0, 30, true, 30.0f);
		PtrDraw->AddAnimation(L"Walk", 35, 30, true, 30.0f);
		PtrDraw->ChangeCurrentAnimation(L"Stop");

		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetDrawActive(true);


		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		SetAlphaActive(true);

		////Rigidbodyをつける
		//auto PtrRedid = AddComponent<Rigidbody>();

	}

	void Character::CharaState() {

		float speed;
		float grav;
		float jump;

		switch (m_myData.type)
		{
		case CharacterType::POTATO:
			m_WeaponO.weapon = BulletS::Shot;
			m_WeaponT.weapon = BulletS::None;
			m_modelName = L"Animation_Potato_test5.bmf";
			speed = 5.0f;
			grav = 50.0f;
			jump = 10.0f;
			break;
		case CharacterType::SHRIMP:
			m_WeaponO.weapon = BulletS::Rocket;
			m_WeaponT.weapon = BulletS::None;
			m_modelName = L"0525_Animation_Shrimp_test4.bmf";
			speed = 10.0f;
			grav = 25.0f;
			jump = 15.0f;
			break;
		case CharacterType::CHICKEN:
			m_WeaponO.weapon = BulletS::Rocket;
			m_WeaponT.weapon = BulletS::None;
			speed = 15.0f;
			grav = 30.0f;
			jump = 14.0f;
			m_modelName = L"Chicken_Animation_test9.bmf";
			break;
		case CharacterType::DOUGHNUT:
			m_WeaponO.weapon = BulletS::Sniper;
			m_WeaponT.weapon = BulletS::None;
			m_modelName = L"Animation_Doughnut_test3.bmf";
			speed = 8.0f;
			grav = 25.0f;
			jump = 10.0f;
			break;
		default:
			m_WeaponO.weapon = BulletS::SMG;
			m_WeaponT.weapon = BulletS::None;
			m_modelName = L"0525_Animation_Shrimp_test4.bmf";
			speed = 10.0f;
			grav = 10.0f;
			jump = 10.0f;
			break;
		}

		m_moveSpeed = speed;
		m_defaultSpeed = speed;
		m_gravityScale = grav;
		m_jumpPower = jump;

		m_weaponState = GetTypeStage<GameStage>()->m_weaponState;

		BulletState(m_WeaponO.weapon, true);
		BulletState(m_WeaponT.weapon, false);
	}

	void Character::PlayerUI() {
		GetStage()->AddGameObject<UI_PlayerAmmo>(
			4,
			Vec3(725.0f, -120.0f, 0.0f),
			Vec3(120.0f, 50.0f, 1.0f),
			true
			);
		GetStage()->AddGameObject<UI_PlayerAmmo>(
			4,
			Vec3(875.0f, -120.0f, 0.0f),
			Vec3(120.0f, 50.0f, 1.0f),
			false
			);

		GetStage()->AddGameObject<UI_PlayerGatling>(
			Vec2(256.0f, 128.0f),
			Vec3(-800.0f, -450.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			10,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"CornIcon.png"
			);

		GetStage()->AddGameObject<UI_PlayerGatlingAmmo>(
			Vec3(-750.0f, -465.0f, 0.0f),
			Vec3(100.0f, 50.0f, 1.0f)
			);

		GetStage()->AddGameObject<UI_PlayerGun>(
			Vec2(300.0f, 450.0f),
			Vec3(800.0f, -300.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			11,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"WeaponSmoke.png",
			1
			);
		GetStage()->AddGameObject<UI_PlayerGun>(
			Vec2(300.0f, 450.0f),
			Vec3(800.0f, -300.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			15,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"WeaponFire.png",
			1
			);
		GetStage()->AddGameObject<UI_PlayerGrenade>(
			Vec2(191.0f, 450.0f),
			Vec3(794.5f, -300.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			11,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"WeaponGLiquid.png",
			false,
			m_toriGtime
			);
		GetStage()->AddGameObject<UI_PlayerGrenade>(
			Vec2(191.0f, 450.0f),
			Vec3(805.5f, -300.0f, 0.0f),
			Vec3(-1.0f, 1.0f, 1.0f),
			11,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"WeaponGSmoke.png",
			true,
			m_smokeGtime
			);
		GetStage()->AddGameObject<UI_Player>(
			Vec2(300.0f, 450.0f),
			Vec3(800.0f, -300.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			11,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"WeaponNabe.png"
			);
		GetStage()->AddGameObject<UI_PlayerWeapon>(
			Vec3(730.0f, -202.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			12,
			1
			);
		GetStage()->AddGameObject<UI_PlayerWeapon>(
			Vec3(870.0f, -202.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			12,
			0
			);
		GetStage()->AddGameObject<UI_Player>(
			Vec2(300.0f, 450.0f),
			Vec3(800.0f, -300.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			10,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"WeaponBack2.png"
			);
		GetStage()->AddGameObject<UI_PlayerDamage>(
			3,
			L"Share_Number.png",
			Vec3(800.0f, -430.0f, 0.0f),
			Vec3(250.0f, 100.0f, 1.0f)
			);
		GetStage()->AddGameObject<UI_Static_Image>(
			Vec2(64.0f, 128.0f),
			Vec3(800.0f, -120.0f, 0.0f),
			Vec3(0.5f),
			11,
			Col4(0.2f, 0.2f, 0.2f, 1.0f),
			L"Slash.png"
			);
	}

	void Character::Draw() {
		auto string = AddComponent<StringSprite>();
		string->SetText(L"");
		string->SetTextRect(Rect2D<float>(20.0f, 20.0f, 1920.0f, 1080.0f));

		CharaState();

		BmfDateRead(m_modelName);

		Respawn();

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(1.0f));
		ptrTrans->SetRotation(Vec3(0.0f));


		SetID(ID);

		AddTag(L"Character");
		auto gravity = AddComponent<Gravity>();
		gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

	}

	void Character::PlayerCamera() {
		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<Character>());
			ptrCamera->SetTargetToAt(Vec3(0.0f, 2.0f, 0));
		}

	}

	void Character::PlayerMove() {
		Vec3 angle(0, 0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			fThumbLY = -1.0f;
		}
		if (KeyState.m_bPushKeyTbl['D']) {
			//右
			fThumbLX = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			fThumbLX = -1.0f;
		}

		auto ptrTransform = GetComponent<Transform>();
		if (fThumbLX != 0 || fThumbLY != 0) {
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			angle.y = 0.0f;
		}

		float time = App::GetApp()->GetElapsedTime();
		auto grav = GetComponent<Gravity>();
		Vec3 speed = ptrTransform->GetPosition();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();


		if (angle.length() > 0.0f) {
			speed += angle * time * m_defaultSpeed;
			ptrTransform->SetPosition(speed);
			Animation(Anim::walk);
		}
		else {
			Animation(Anim::stop);
		}

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPushKeyTbl[VK_SPACE]) & m_jump) {
			PlaySE(L"jump_se.wav", 0.05f);
			grav->StartJump(Vec3(0.0f, m_jumpPower, 0.0f));
			m_jump = false;
		}

		PlayingWalkSE();
	}

	void Character::PlayingWalkSE() {
		Vec3 angle(0, 0, 0);
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}

		m_Second += App::GetApp()->GetElapsedTime();

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W'] || KeyState.m_bPushKeyTbl['S'] ||
			KeyState.m_bPushKeyTbl['D'] || KeyState.m_bPushKeyTbl['A']) {
			if (m_Second > 0.4f) {
				PlaySE(L"Asioto08.wav", 0.1f);
				m_Second = 0.0f;
			}
		}

		if (fThumbLX != 0 || fThumbLY != 0) {
			if (m_Second > 0.4f) {
				PlaySE(L"Asioto08.wav", 0.1f);
				m_Second = 0.0f;
			}

		}
	}

	void Character::PlayerRotMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		Vec3 angle(0, 0, 0);

		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		float fThumbRY = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			fThumbRY = cntlVec[0].fThumbRY;
		}

		if (KeyState.m_bPushKeyTbl['W']) {
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			fThumbLY = -1.0f;
		}
		if (KeyState.m_bPushKeyTbl['D']) {
			fThumbLX = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			fThumbLX = -1.0f;
		}

		auto trans = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		auto front = trans->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		float frontAngle = atan2(front.z, front.x);
		Vec2 moveVec;
		float cntlAngle;
		float totalAngle;
		//if ((cntlVec[0].bLeftTrigger > 250.0f || KeyState.m_bPushKeyTbl[VK_RBUTTON])) {
		moveVec = Vec2(0.0f, 1.0f);
		cntlAngle = atan2(0.0f, 1.0f);
		//}
		//else {
		//	moveVec = Vec2(fThumbLX, fThumbLY);
		//	cntlAngle = atan2(-fThumbLX, fThumbLY);
		//}
		totalAngle = frontAngle + cntlAngle;
		angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
		angle.normalize();
		float moveSize = moveVec.length();
		angle *= moveSize;
		angle.y = 0.0f;

		if (angle.length() > 0.0f) {
			auto ptr = GetBehavior<UtilBehavior>();
			ptr->RotToHead(angle, 1.0f);
		}

		auto ptr = GetComponent<Transform>();
		auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());
		gameStage->TestFunc();
		auto test = gameStage->GetCamera()->GetAt();

		Quat thisQuat = ptr->GetQuaternion();
		auto camera = OnGetDrawCamera();
		auto came = camera->GetEye();
		came.y -= 2.0f;
		auto fro = ptr->GetPosition() - came;
		m_bulletRot.facing(fro);

	}

	void Character::GrenadeFire() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();

		if (!m_smokeG) {
			if (m_smokeGtime >= m_Gtime) {
				m_smokeG = true;
			}
			else {
				float time = App::GetApp()->GetElapsedTime();
				m_smokeGtime += time;
			}
		}
		if (!m_toriG) {
			if (m_toriGtime >= m_Gtime) {
				m_toriG = true;
			}
			else {
				float time = App::GetApp()->GetElapsedTime();
				m_toriGtime += time;
			}
		}

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || KeyState.m_bPressedKeyTbl['Q']) && m_toriG) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition(),
				m_bulletRot,
				50.0f, 10.0f, true, ID, m_myData
				);
			m_toriG = false;
			m_toriGtime = 0.0f;
		}
		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) || KeyState.m_bPressedKeyTbl['E']) && m_smokeG) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition(),
				m_bulletRot,
				50.0f, 10.0f, false, ID, m_myData
				);
			m_smokeG = false;
			m_smokeGtime = 0.0f;
		}
	}

	void Character::Respawn() {
		int Rand = rand() % 8;
		const float activeY = -25.0f;
		auto PtrTransform = GetComponent<Transform>();
		//ランダムに出すように
		switch (Rand) {
		case 0:
			PtrTransform->SetPosition(Vec3(0.0f, 5.0f, 0.0f));
			break;
		case 1:
			PtrTransform->SetPosition(Vec3(-30.0f, 5.0f, 30.0f));
			break;
		case 2:
			PtrTransform->SetPosition(Vec3(30.0f, 5.0f, 30.0f));
			break;
		case 3:
			PtrTransform->SetPosition(Vec3(30.0f, 5.0f, -30.0f));
			break;
		case 4:
			PtrTransform->SetPosition(Vec3(-30.0f, 5.0f, -30.0f));
			break;
		case 5:
			PtrTransform->SetPosition(Vec3(-30.0f, 5.0f, 0.0f));
			break;
		case 6:
			PtrTransform->SetPosition(Vec3(30.0f, 5.0f, 0.0f));
			break;
		case 7:
			PtrTransform->SetPosition(Vec3(0.0f, 5.0f, -30.0f));
			break;
		default:
			PtrTransform->SetPosition(Vec3(0.0f, 5.0f, 0.0f));
			break;
		}
	}


	void Character::AttackHit(Vec3 rot) {
		auto grav = GetComponent<Gravity>();

		Vec2 force = m_force * 5.0f;

		Vec3 vecForce = rot * force.x;
		vecForce.y = force.y;

		grav->SetGravityVerocity(vecForce * ((m_damage / 250.0f) + m_shotHit));

		//ここで一定の条件（吹っ飛び率、自身をふっとばしたのはプレイヤーか）などで自身を表示するPinPを表示する
		/*if(m_opponent.isPlayer) */ShowMyPinP();
	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
		}

		if (Other->FindTag(L"Torimoti")) {
			m_torimoti = true;
			m_toriHitInTime = 15.0f;
		}

		if (Other->FindTag(L"Smoke")) {
			m_smoke = true;

			auto smoke = dynamic_pointer_cast<SmokeGrenade>(Other);
			if (smoke) {
				m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
				m_opponent = smoke->GetFrome();
			}
		}

		if (Other->FindTag(L"Explosion")) {
			if (Other->FindTag(L"Smoke")) {
				GetStage()->AddGameObject<GatlingAmmo>(
					GetComponent<Transform>()->GetPosition()
					);
			}

		}

		if (Other->FindTag(L"Bullet") && Other->GetID() != ID) {
			BulletDamage(Other->GetBulletType(), Other->GetComponent<Transform>()->GetForword());
			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
				m_opponent = bullet->GetFrome();
			}

			if (m_torimoti) {
				GetStage()->AddGameObject<GatlingAmmo>(
					GetComponent<Transform>()->GetPosition()
					);
				GetStage()->AddGameObject<GatlingAmmo>(
					GetComponent<Transform>()->GetPosition()
					);
				GetStage()->AddGameObject<GatlingAmmo>(
					GetComponent<Transform>()->GetPosition()
					);
				GetStage()->AddGameObject<GatlingAmmo>(
					GetComponent<Transform>()->GetPosition()
					);
				GetStage()->AddGameObject<GatlingAmmo>(
					GetComponent<Transform>()->GetPosition()
					);
				m_torimoti = false;
				m_toriHitInTime = 0.0f;
			}
		}

		if (Other->FindTag(L"GatlingAmmo")) {
			m_gatlingAmmo += m_gatlingPickAmmo;
			if (m_gatlingAmmo > 999)
				m_gatlingAmmo = 999;
			GetStage()->RemoveGameObject<GameObject>(Other);
		}


		if (Other->FindTag(L"Oil")) {
			//TouchOil();
		}

	}

	void Character::OnCollisionExcute(shared_ptr<GameObject>& Other) {

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) || KeyState.m_bPressedKeyTbl['F'])) {
			if (Other->FindTag(L"SetGun")) {
				if (!m_setGun) {
					m_setGun = true;
					auto trans = Other->GetComponent<Transform>();
					m_setGunPos = trans->GetPosition();
					if (Other->FindTag(L"GatlingGun")) {
						GetStage()->AddGameObject<SetGun>(
							trans->GetPosition(),
							trans->GetQuaternion(),
							true);
						m_setGunType = true;
						m_gatlingShotAmmo = 0;
						m_gatlingCoolTime = 0.0f;
					}
					else if (Other->FindTag(L"Cannon") && m_cannonAmmo) {
						m_setGunType = false;
					}

				}
				else {
					m_setGun = false;
				}
			}
			else if (Other->FindTag(L"FallGun")) {
				PickGun(Other->GetBulletType());
				GetStage()->RemoveGameObject<GameObject>(Other);
			}
			else if (Other->FindTag(L"CannonAmmoBox")) {
				m_cannonAmmo = true;
			}

		}

		if (Other->FindTag(L"Object")) {
			m_jump = true;
		}

		if (Other->FindTag(L"Smoke")) {
			m_smoke = true;
			m_smokeIn = true;
		}
		else {
			m_smokeIn = false;
		}

	}

	void Character::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = false;
		}

		if (Other->FindTag(L"SetGun")) {
			m_setGun = false;
		}

	}

	//油に触れた時の処理
	void Character::TouchOil() {

		GetTypeStage<GameStage>()->PlaySE(L"Aburamizu01.wav", 0.5f);

		GetStage()->AddGameObject<OilEffect>(
			GetComponent<Transform>()->GetPosition()
			);

		if (m_touchOil) m_touchOil->Run(m_myData);
		AddDeath(1);

		//PinPで表示しているのが自身だったらPinPを非表示にする
		auto pinp = GetStage()->GetSharedGameObject<PinP>(L"BlownPinP");
		if (m_myData.unique == pinp->GetUse().unique) {
			pinp->DeleteUse();
			pinp->Out(PinPAction::LEFT);
		}

		SetUpdateActive(true);
		SetDrawActive(true);


		auto grav = GetComponent<Gravity>();
		grav->SetGravityVerocityZero();

		Respawn();
		CharaState();
		m_smoke = false;
		m_torimoti = false;
		m_myData.level = 1;
		m_damage = 0.0f;

	}

	//相手を油に落とした時の処理
	void Character::DroppedIntoOil(const CharacterStatus_s& status) {
		AddScore(status.level * 100 + (status.level > 1 ? 100 : 0));
		auto kill = CharacterKillDetails_s({ status.type, status.level });
		AddKillCharacter(kill);
		AddKill(1);

		if (m_myData.isPlayer) {
			GetStage()->AddGameObject<UI_Kill_Icon>(
				Vec3(0.0f, -350.0f, 0.0f),
				Vec3(0.8f, 0.8f, 1.0f),
				100,
				status.type,
				status.level
				);
		}
	}

	//PinPに自身を指定して表示する
	void Character::ShowMyPinP() {
		auto pinp = GetStage()->GetSharedGameObject<PinP>(L"BlownPinP");
		auto& trans = GetComponent<Transform>();
		auto& pos = trans->GetPosition();
		pinp->SetUse(m_myData);
		//pinp->SetEye(pos + Vec3(0.0f, 15.0f, 30.0f));
		auto hoge = trans->GetForword();
		pinp->SetEye(Vec3(hoge.x * 80, 50.0f, hoge.z * 80));
		pinp->SetAt(pos);
		pinp->In(PinPAction::LEFT);
	}

	void Character::PinPUpdate() {
		auto pinp = GetStage()->GetSharedGameObject<PinP>(L"BlownPinP");
		if (pinp->GetUse().unique != m_myData.unique) return;
		auto& trans = GetComponent<Transform>();
		auto& pos = trans->GetPosition();
		pinp->SetAt(pos);
	}

	vector<CharacterKillDetails_s> Character::GetKillCharacters() {
		return m_killCharacters;
	}

	void Character::AddKillCharacter(const CharacterKillDetails_s& data) {
		m_killCharacters.push_back(data);
	}

	CharacterStatus_s Character::GetMyData() {
		return m_myData;
	}

	void Character::SetMyData(const CharacterStatus_s& data) {
		m_myData = data;
	}

	void Character::AddScore(const int score) {
		m_myData.score += score;
	}

	void Character::SetLevel(const unsigned int level) {
		if (level <= 0 || level >= 4) return;
		m_myData.level = level;
	}

	void Character::AddLevel() {
		int level = 1;
		if (m_torimoti)
			level = 2;
		if (m_smoke)
			level = 2;
		if (m_smoke && m_torimoti)
			level = 3;

		m_myData.level = level;
		ShotState();
	}

	void Character::AddKill(const int kill) {
		m_myData.kill += kill;
	}

	void Character::AddDeath(const int death) {
		m_myData.death += death;
	}

	void Character::ShotState() {
		if (m_shotTime > 0) {
			float time = App::GetApp()->GetElapsedTime();
			m_shotTime -= time;
		}
		else {
			m_shotHit = 1;
		}
	}

	void Character::BulletState(int state, bool weapon, bool same) {
		WeaponState_s m_state;
		for (int i = 0; i < m_weaponState.size(); i++)
		{
			if (m_weaponState[i].weapon == (BulletS)state) {
				m_state = m_weaponState[i];
			}
		}

		if (weapon) {
			if (same)
			{
				m_WeaponO.maxAmmo += m_state.maxAmmo + m_state.ammo;
			}
			else {
				m_WeaponO.weapon = m_state.weapon;
				m_WeaponO.barrage = m_state.barrage;
				m_WeaponO.ammo = m_state.reAmmo;
				m_WeaponO.reAmmo = m_state.ammo;
				m_WeaponO.maxAmmo = m_state.maxAmmo;
				m_WeaponO.intTime = m_state.intTime;
				m_WeaponO.maxIntTime = m_state.maxIntTime;
				m_WeaponO.reTime = m_state.reTime;
				m_WeaponO.maxreTime = m_state.maxreTime;
			}
		}
		else {
			if (same)
			{
				m_WeaponT.maxAmmo += m_state.maxAmmo + m_state.ammo;
			}
			else {
				m_WeaponT.weapon = m_state.weapon;
				m_WeaponT.barrage = m_state.barrage;
				m_WeaponT.ammo = m_state.reAmmo;
				m_WeaponT.reAmmo = m_state.ammo;
				m_WeaponT.maxAmmo = m_state.maxAmmo;
				m_WeaponT.intTime = m_state.intTime;
				m_WeaponT.maxIntTime = m_state.maxIntTime;
				m_WeaponT.reTime = m_state.reTime;
				m_WeaponT.maxreTime = m_state.maxreTime;
			}
		}
	}

	void Character::BulletFire() {

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		bool fire = false;

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) || KeyState.m_bPressedKeyTbl[VK_RBUTTON])) {
			m_weapon = !m_weapon;
			m_reload = false;
			m_fire = true;
			m_WeaponO.reTime = 0.0f;
			m_WeaponT.reTime = 0.0f;
			m_WeaponO.intTime = 0.0f;
			m_WeaponT.intTime = 0.0f;
		}

		if (BulletS::None == m_WeaponT.weapon) {
			m_weapon = true;
		}

		if (m_weapon) {
			if (m_WeaponO.barrage) {
				if ((cntlVec[0].bRightTrigger > 250.0f || KeyState.m_bPushKeyTbl[VK_LBUTTON])) {
					fire = true;
					m_fire = true;
				}
			}
			else {
				if ((cntlVec[0].bRightTrigger > 250.0f || KeyState.m_bPressedKeyTbl[VK_LBUTTON])) {
					fire = true;
				}
				else if ((cntlVec[0].bRightTrigger < 200.0f || KeyState.m_bUpKeyTbl[VK_LBUTTON])) {
					m_fire = true;
				}
			}

			if (((((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) || KeyState.m_bPressedKeyTbl['R'])
				&& m_WeaponO.ammo < m_WeaponO.reAmmo)
				|| m_WeaponO.ammo <= 0) && !m_reload) {
				m_reload = true;
				m_fire = false;
				m_WeaponO.reTime = m_WeaponO.maxreTime;
			}

			if (m_reload && m_WeaponO.maxAmmo > 0) {
				if (m_WeaponO.reTime > 0) {
					float time = App::GetApp()->GetElapsedTime();
					m_WeaponO.reTime -= time;
					m_fire = false;
				}
				else {
					int rem;
					rem = m_WeaponO.reAmmo - m_WeaponO.ammo;
					m_WeaponO.maxAmmo -= rem;
					if (m_WeaponO.maxAmmo < 0) {
						rem += m_WeaponO.maxAmmo;
						m_WeaponO.maxAmmo = 0;
					}
					m_WeaponO.ammo += rem;

					m_reload = false;
					m_fire = true;
				}
			}

			WeaponOFire(fire, m_bulletRot);

		}
		else {
			if (m_WeaponT.barrage) {
				if ((cntlVec[0].bRightTrigger > 250.0f || KeyState.m_bPushKeyTbl[VK_LBUTTON])) {
					fire = true;
					m_fire = true;
				}
			}
			else {
				if ((cntlVec[0].bRightTrigger > 250.0f || KeyState.m_bPressedKeyTbl[VK_LBUTTON])) {
					fire = true;
				}
				else if ((cntlVec[0].bRightTrigger < 200.0f || KeyState.m_bUpKeyTbl[VK_LBUTTON])) {
					m_fire = true;
				}
			}

			if (((((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) || KeyState.m_bPressedKeyTbl['R'])
				&& m_WeaponT.ammo < m_WeaponT.reAmmo)
				|| m_WeaponT.ammo <= 0) && !m_reload) {
				m_reload = true;
				m_fire = false;
				m_WeaponT.reTime = m_WeaponT.maxreTime;
			}

			if (m_reload && m_WeaponT.maxAmmo > 0) {
				if (m_WeaponT.reTime > 0) {
					float time = App::GetApp()->GetElapsedTime();
					m_WeaponT.reTime -= time;
					m_fire = false;
				}
				else {
					int rem;
					rem = m_WeaponT.reAmmo - m_WeaponT.ammo;
					m_WeaponT.maxAmmo -= rem;
					if (m_WeaponT.maxAmmo < 0) {
						rem += m_WeaponT.maxAmmo;
						m_WeaponT.maxAmmo = 0;
					}
					m_WeaponT.ammo += rem;

					m_reload = false;
					m_fire = true;
				}
			}

			WeaponTFire(fire, m_bulletRot);

		}
		
	}

	void Character::WeaponOFire(bool fire, Quat rot) {
		auto ptr = GetComponent<Transform>();

		if (m_reload && m_WeaponO.maxAmmo > 0) {
			if (m_WeaponO.reTime > 0) {
				float time = App::GetApp()->GetElapsedTime();
				m_WeaponO.reTime -= time;
				m_fire = false;
			}
			else {
				int rem;
				rem = m_WeaponO.reAmmo - m_WeaponO.ammo;
				m_WeaponO.maxAmmo -= rem;
				if (m_WeaponO.maxAmmo < 0) {
					rem += m_WeaponO.maxAmmo;
					m_WeaponO.maxAmmo = 0;
				}
				m_WeaponO.ammo += rem;

				m_reload = false;
				m_fire = true;
			}
		}

		if (m_WeaponO.ammo > 0 && m_WeaponO.intTime <= 0) {
			if (fire && m_fire) {
				if (m_WeaponO.weapon == BulletS::Shot) {

					for (size_t i = 0; i < 20; i++)
					{
						auto x = Util::RandZeroToOne() * 5.0f;
						if (Util::RandZeroToOne() < 2.5f) x *= -1;
						auto y = Util::RandZeroToOne() * 5.0f;
						if (Util::RandZeroToOne() < 2.5f) y *= -1;

						Quat r = rot;
						r.x += x * (XM_PI / 180.0f);
						r.y += y * (XM_PI / 180.0f);

						auto bullet = GetStage()->AddGameObject<Bullet>(
							ptr->GetPosition(),
							r,
							m_WeaponO.weapon,
							m_myData.unique,
							ID,
							m_myData
							);

						bullet->AddEvent([this](const CharacterStatus_s status) {
							DroppedIntoOil(status);
							});
					}

				}
				else {
					auto bullet = GetStage()->AddGameObject<Bullet>(
						ptr->GetPosition(),
						rot,
						m_WeaponO.weapon,
						m_myData.unique,
						ID,
						m_myData
						);

					bullet->AddEvent([this](const CharacterStatus_s status) {
						DroppedIntoOil(status);
						});

				}
				m_WeaponO.ammo--;
				m_WeaponO.intTime = m_WeaponO.maxIntTime;

				m_fire = false;
			}
		}
		else if (m_WeaponO.intTime > 0) {
			float time = App::GetApp()->GetElapsedTime();
			m_WeaponO.intTime -= time;
		}
	}

	void Character::WeaponTFire(bool fire, Quat rot) {
		auto ptr = GetComponent<Transform>();

		if (m_reload && m_WeaponT.maxAmmo > 0) {
			if (m_WeaponT.reTime > 0) {
				float time = App::GetApp()->GetElapsedTime();
				m_WeaponT.reTime -= time;
				m_fire = false;
			}
			else {
				int rem;
				rem = m_WeaponT.reAmmo - m_WeaponT.ammo;
				m_WeaponT.maxAmmo -= rem;
				if (m_WeaponT.maxAmmo < 0) {
					rem += m_WeaponT.maxAmmo;
					m_WeaponT.maxAmmo = 0;
				}
				m_WeaponT.ammo += rem;

				m_reload = false;
				m_fire = true;
			}
		}

		if (m_WeaponT.ammo > 0 && m_WeaponT.intTime <= 0) {
			if (fire && m_fire) {
				if (m_WeaponT.weapon == BulletS::Shot) {

					for (size_t i = 0; i < 20; i++)
					{
						auto x = Util::RandZeroToOne() * 5.0f;
						if (Util::RandZeroToOne() < 2.5f) x *= -1;
						auto y = Util::RandZeroToOne() * 5.0f;
						if (Util::RandZeroToOne() < 2.5f) y *= -1;

						Quat r = rot;
						r.x += x * (XM_PI / 180.0f);
						r.y += y * (XM_PI / 180.0f);

						auto bullet = GetStage()->AddGameObject<Bullet>(
							ptr->GetPosition(),
							r,
							m_WeaponT.weapon,
							m_myData.unique,
							ID,
							m_myData
							);

						bullet->AddEvent([this](const CharacterStatus_s status) {
							DroppedIntoOil(status);
							});
					}

				}
				else {
					auto bullet = GetStage()->AddGameObject<Bullet>(
						ptr->GetPosition(),
						rot,
						m_WeaponT.weapon,
						m_myData.unique,
						ID,
						m_myData
						);

					bullet->AddEvent([this](const CharacterStatus_s status) {
						DroppedIntoOil(status);
						});

				}
				m_WeaponT.ammo--;
				m_WeaponT.intTime = m_WeaponT.maxIntTime;

				m_fire = false;
			}
		}
		else if (m_WeaponT.intTime > 0) {
			float time = App::GetApp()->GetElapsedTime();
			m_WeaponT.intTime -= time;
		}

	}

	void Character::SetWeaponFire() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();

		bool fire = false;

		if ((cntlVec[0].bRightTrigger > 250.0f || KeyState.m_bPushKeyTbl[VK_LBUTTON])) {
			fire = true;
		}
		else {
			if (m_gatlingShotAmmo > 0.0f) {
				m_gatlingCoolTime = App::GetApp()->GetElapsedTime();

				m_gatlingShotAmmo -= (m_gatlingBombAmmo * m_gatlingCoolTime) / m_gatlingCoolMaxTime;
			}
			else if (m_gatlingShotAmmo < 0.0f) {
				m_gatlingShotAmmo = 0.0f;
			}
		}

		if (m_setGunType)
		{
			if (m_gatlingAmmo > 0 && m_intTimeGat <= 0) {
				if (fire) {
					auto bullet = GetStage()->AddGameObject<Bullet>(
						m_setGunPos + Vec3(0.0f, 1.0f, 0.0f),
						m_bulletRot,
						BulletS::Gatling,
						m_myData.unique,
						ID,
						m_myData
						);

					bullet->AddEvent([this](const CharacterStatus_s status) {
						DroppedIntoOil(status);
					});

					m_gatlingAmmo--;
					m_gatlingShotAmmo++;
					m_intTimeGat = 0.01f;
				}
			}
			else if (m_intTimeGat > 0) {
				float time = App::GetApp()->GetElapsedTime();
				m_intTimeGat -= time;
			}
		}
		else {
			if (fire && m_cannonAmmo) {
				auto bullet = GetStage()->AddGameObject<Bullet>(
					m_setGunPos + Vec3(0.0f,1.0f,0.0f),
					m_bulletRot,
					BulletS::Cannon,
					m_myData.unique,
					ID,
					m_myData
					);

				bullet->AddEvent([this](const CharacterStatus_s status) {
					DroppedIntoOil(status);
				});

				m_cannonAmmo = false;
			}
		}

		if (m_gatlingShotAmmo >= m_gatlingBombAmmo) {
			m_setGun = false;
			m_gatlingAmmo = 0;
			auto bullet = GetStage()->AddGameObject<Bullet>(
				m_setGunPos,
				m_bulletRot,
				BulletS::GExplosion,
				m_myData.unique,
				ID,
				m_myData
				);

			bullet->AddEvent([this](const CharacterStatus_s status) {
				DroppedIntoOil(status);
			});
		}
		else if (m_gatlingAmmo <= 0) {
			m_setGun = false;
		}
	}

	void Character::BulletDamage(int state,Vec3 rot) {
		Vec2 force;
		float damage;

		switch (state)
		{
		case BulletS::Assault:
			m_shotHit = 1;
			force = Vec2(3.0f, 2.0f);
			damage = 5.0;
			break;
		case BulletS::Hand:
			m_shotHit = 1;
			force = Vec2(3.0f, 3.0f);
			damage = 15.0;
			break;
		case BulletS::Shot:
			m_shotHit++;
			m_shotTime = 0.5f;
			force = Vec2(0.3f, 0.3f);
			damage = 5.0;
			break;
		case BulletS::SMG:
			m_shotHit = 1;
			force = Vec2(2.0f, 3.0f);
			damage = 2.0;
			break;
		case BulletS::Rocket:
			m_shotHit = 1;
			force = Vec2(0.0f, 0.0f);
			damage = 0.0;
			break;
		case BulletS::Sniper:
			m_shotHit = 1;
			force = Vec2(5.0f, 2.0f);
			damage = 20.0;
			break;
		case BulletS::Laser:
			m_shotHit = 1;
			force = Vec2(0.5f, 0.0f);
			damage = 20.0;
			break;
		case BulletS::Wind:
			m_shotHit = 1;
			force = Vec2(2.0f, 1.0f);
			damage = 1.0;
			break;
		case BulletS::Gatling:
			m_shotHit = 1;
			force = Vec2(10.0f, 5.0f);
			damage = 2.0;
			break;
		case BulletS::Cannon:
			m_shotHit = 1;
			force = Vec2(15.0f, 10.0f);
			damage = 50.0;
			break;
		case BulletS::GExplosion:
			m_shotHit = 1;
			force = Vec2(-5.0f, 5.0f);
			damage = 40.0;
			break;
		case BulletS::CExplosion:
			m_shotHit = 1;
			force = Vec2(5.0f, 5.0f);
			damage = 30.0;
			break;
		case BulletS::SExplosion:
			m_shotHit = 1;
			force = Vec2(5.0f, 5.0f);
			damage = 20.0;
			break;
		case BulletS::RExplosion:
			m_shotHit = 1;
			force = Vec2(4.0f, 3.0f);
			damage = 15.0;
			break;
		default:
			break;
		}

		m_force = force;
		m_damage += damage;

		AttackHit(rot);

	}

	void Character::PickGun(int state) {
		bool same = false;
		if (BulletS::None == m_WeaponT.weapon) {
			BulletState(state, false);
		}
		else {
			if (m_weapon) {
				if (m_WeaponO.weapon == state)
					same = true;
			}
			else {
				if (m_WeaponT.weapon == state) {
					same = true;
				}
			}
			BulletState(state, m_weapon, same);
		}
	}

	void Character::PlayerMovement() {
		AddLevel();

		float time = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(time);

		PlayerRotMove();
		if (GetTypeStage<GameStage>()->m_start) {
			if (m_setGun) {
				SetWeaponFire();
			}
			else {
				if (!Torimoti()) {
					PlayerMove();
				}
				BulletFire();
				GrenadeFire();
			}
		}
	
		auto pos = GetComponent<Transform>()->GetPosition();

		if (pos.y <= -10.0f) {
			TouchOil();
		}

	}

	void Character::DrawString() {
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring strFps(L"FPS: ");
		strFps += Util::UintToWStr(fps);
		strFps += L"\n";

		float time = App::GetApp()->GetElapsedTime();

		t += time;
		strFps += Util::FloatToWStr(t);
		strFps += L"\n";

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		float fThumbRX = 0.0f;
		float fThumbRY = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbRX = cntlVec[0].fThumbRX;
			fThumbRY = -cntlVec[0].fThumbRY;
		}

		strFps += Util::FloatToWStr(fThumbRX);
		strFps += L", ";
		strFps += Util::FloatToWStr(fThumbRY);
		strFps += L"\n";

		Vec3 rot = GetComponent<Transform>()->GetRotation();

		strFps += Util::FloatToWStr(m_bulletRot.w);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_bulletRot.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_bulletRot.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_bulletRot.z);
		strFps += L"\n";

		strFps += Util::FloatToWStr(m_gatlingShotAmmo);
		strFps += L"\n";
		strFps += Util::FloatToWStr(m_gatlingAmmo);
		strFps += L"\n";

		auto string = GetComponent<StringSprite>();
		string->SetText(strFps);

	}


	void Player::OnCreate() {
		Draw();
		PlayerUI();
		PlayerCamera();
	}

	void Player::OnUpdate() {
		PlayerMovement();
		DrawString();
	}



	void Enemy::OnCreate() {
		Draw();
	}

	void Enemy::OnUpdate() {
		AddLevel();
		PinPUpdate();
	}


	void OilEffect::CreateFirstEffect() {
		auto upPos = m_pos;
		upPos.y = -8.5f;

		m_fEfkEffect = GetTypeStage<GameStage>()->GetEffect(L"OilSplash.efk");
		m_fEfkPlay = ObjectFactory::Create<EfkPlay>(m_fEfkEffect, upPos);
		m_fEfkPlay->Play(m_fEfkEffect, upPos);
	}

	void OilEffect::CreateLastEffect() {
		auto upPos = m_pos;
		upPos.y = -8.5f;

		m_lEfkEffect = GetTypeStage<GameStage>()->GetEffect(L"OilBubble.efk");
		m_lEfkPlay = ObjectFactory::Create<EfkPlay>(m_lEfkEffect, upPos);
		m_lEfkPlay->Play(m_lEfkEffect, upPos);
	}

	void OilEffect::OnCreate() {
		CreateFirstEffect();
		GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
	}

	void OilEffect::OnUpdate() {
		if (m_fEfkPlay->IsCreated() && !m_lEfkPlay) {
	      CreateLastEffect();
		};
	}
}
//end basecross
