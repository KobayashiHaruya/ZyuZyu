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
			Vec3(0.0f, 3.14f, 0.0f),
			Vec3(0.0f, -1.5f, 0.0f));

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

		auto ptrColl = AddComponent<CollisionCapsule>();
		//ptrColl->SetMakedSize(Vec3(1.25f, 1.75f, 1.25f));
		//ptrColl->SetMakedHeight(4.0f);
		//ptrColl->SetMakedRadius(1.0f);
		ptrColl->SetMakedDiameter(2.5f);
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetDrawActive(true);

	}

	void Character::CharaState() {

		float speed;
		float grav;
		float jump;

		switch (m_myData.type)
		{
		case CharacterType::POTATO:
			m_weaponO = BulletS::Shot;
			m_weaponT = BulletS::None;
			m_modelName = L"Potato_ver1.bmf";
			speed = 5.0f;
			grav = 50.0f;
			jump = 10.0f;
			break;
		case CharacterType::SHRIMP:
			m_weaponO = BulletS::SMG;
			m_weaponT = BulletS::Hand;
			m_modelName = L"Shrimp_ver2.bmf";
			speed = 10.0f;
			grav = 25.0f;
			jump = 15.0f;
			break;
		case CharacterType::CHICKEN:
			m_weaponO = BulletS::Rocket;
			m_weaponT = BulletS::None;
			speed = 15.0f;
			grav = 30.0f;
			jump = 14.0f;
			m_modelName = L"Chicken_ver1.bmf";
			break;
		case CharacterType::DOUGHNUT:
			m_weaponO = BulletS::Sniper;
			m_weaponT = BulletS::None;
			m_modelName = L"Doughnut_ver1.bmf";
			speed = 8.0f;
			grav = 25.0f;
			jump = 10.0f;
			break;
		default:
			m_weaponO = BulletS::SMG;
			m_weaponT = BulletS::None;
			m_modelName = L"Shrimp_ver2.bmf";
			speed = 1.0f;
			grav = 10.0f;
			jump = 10.0f;
			break;
		}

		m_moveSpeed = speed;
		m_defaultSpeed = speed;
		m_gravityScale = grav;
		m_jumpPower = jump;

	}

	void Character::Draw() {
		auto string = AddComponent<StringSprite>();
		string->SetText(L"");
		string->SetTextRect(Rect2D<float>(20.0f, 20.0f, 1920.0f, 1080.0f));

		CharaState();

		BmfDateRead(m_modelName);
		BulletState(m_weaponO, true);
		BulletState(m_weaponT, false);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(Vec3(1.0f));
		ptrTrans->SetRotation(m_rot);


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
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
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


		if (angle.length() > 0.0f) {
			speed += angle * time * m_defaultSpeed;
			ptrTransform->SetPosition(speed);
		}

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPushKeyTbl[VK_SPACE]) & m_jump) {
			grav->StartJump(Vec3(0.0f, m_jumpPower, 0.0f));
			m_jump = false;
		}


	}

	void Character::PlayerRotMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		Vec3 angle(0, 0, 0);

		auto ptrTransform = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		float frontAngle = atan2(front.z, front.x);
		Vec2 moveVec(0.0f, 1.0f);
		float moveSize = moveVec.length();
		float cntlAngle = atan2(0.0f, 1.0f);
		float totalAngle = frontAngle + cntlAngle;
		angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
		angle.normalize();
		angle *= moveSize;
		angle.y = 0.0f;

		float fThumbRX = 0.0f;
		float fThumbRY = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbRX = cntlVec[0].fThumbRX;
			fThumbRY = cntlVec[0].fThumbRY;
		}

		if (KeyState.m_bPushKeyTbl[VK_RIGHT]) {
			fThumbRX = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl[VK_LEFT]) {
			fThumbRX = -1.0f;
		}

		if (KeyState.m_bPushKeyTbl[VK_DOWN]) {
			fThumbRY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl[VK_UP]) {
			fThumbRY = -1.0f;
		}

		auto time = App::GetApp()->GetElapsedTime();
		m_rot.x += fThumbRY * 0.1f * time;
		m_rot.y += fThumbRX * m_rotSpeed * time;

		if (abs(m_rot.x) >= XM_2PI) {
			m_rot.x = 0.0f;
		}
		if (abs(m_rot.y) >= XM_2PI) {
			m_rot.y = 0.0f;
		}

		if (angle.length() > 0.0f) {
			auto ptr = GetBehavior<UtilBehavior>();
			ptr->RotToHead(angle, 1.0f);
		}

	}

	void Character::Weapons() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();

		BulletFire();
		
		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) || KeyState.m_bPressedKeyTbl['E'])) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition(),
				ptr->GetQuaternion(),
				50.0f, 10.0f, true, ID
				);
		}
		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || KeyState.m_bPressedKeyTbl['Q'])) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition(),
				ptr->GetQuaternion(),
				50.0f, 10.0f, false, ID
				);
		}

	}

	void Character::Respawn() {
		//srand((unsigned int)time(NULL));
		int Rand = rand() % 5;
		//m_des = true;
		const float activeY = -25.0f;
		auto PtrTransform = GetComponent<Transform>();
		//if (abs(PtrTransform->GetPosition().y) > activeY) {
			//if (m_des) {
				//ランダムに出すように
				switch (Rand) {
				case 0:
					PtrTransform->SetPosition(Vec3(0.0f, 3.0f, 0.0f));
					break;
				case 1:
					PtrTransform->SetPosition(Vec3(-50.0f, 3.0f, 50.0f));
					break;
				case 2:
					PtrTransform->SetPosition(Vec3(50.0f, 3.0f, 50.0f));
					break;
				case 3:
					PtrTransform->SetPosition(Vec3(50.0f, 3.0f, -50.0f));
					break;
				case 4:
					PtrTransform->SetPosition(Vec3(-50.0f, 3.0f, -50.0f));
					break;
				default:
					PtrTransform->SetPosition(Vec3(0.0f, 3.0f, 0.0f));
					break;
				}
				//GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			//	m_des = false;
			//}
		//}
	}


	void Character::AttackHit(Vec3 rot) {
		auto grav = GetComponent<Gravity>();

		Vec2 force = m_force * 2.0f;

		Vec3 vecForce = rot * force.x;
		vecForce.y = force.y;
		grav->StartJump(vecForce);

		//ここで一定の条件（吹っ飛び率、自身をふっとばしたのはプレイヤーか）などで自身を表示するPinPを表示する
		/*if(m_opponent.isPlayer) */ShowMyPinP();
	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
		}

		if (Other->FindTag(L"Torimoti")) {
			Torimoti(true);
		}

		if (Other->FindTag(L"Bullet")) {
			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
				m_opponent = bullet->GetFrome();
			}
			if (Other->GetID() != ID) {
				BulletDamage(Other->GetBulletType(), Other->GetComponent<Transform>()->GetForword());
			}
		}
		if (Other->FindTag(L"Weapon")) {

		}
		if (Other->FindTag(L"Oil")) {
			TouchOil();
			Respawn();
		}
	}

	void Character::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
		}

		if (Other->FindTag(L"Torimoti")) {
			Torimoti(true);
		}

		if (Other->FindTag(L"Explosion")) {
			auto rot = Other->GetComponent<Transform>()->GetRotation();
			AttackHit(rot);
		}

	}

	void Character::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = false;
		}
	}

	//油に触れた時の処理
	void Character::TouchOil() {
		if(m_touchOil) m_touchOil->Run(m_myData);
		AddDeath(1);

		//PinPで表示しているのが自身だったらPinPを非表示にする
		auto pinp = GetStage()->GetSharedGameObject<PinP>(L"BlownPinP");
		if (m_myData.unique == pinp->GetUse().unique) {
			pinp->DeleteUse();
			pinp->Out(PinPAction::LEFT);
		}

		SetUpdateActive(true);
		SetDrawActive(true);
	}

	//相手を油に落とした時の処理
	void Character::DroppedIntoOil(const CharacterStatus_s& status) {
		AddScore(status.level * 100 + (status.level > 1 ? 100 : 0));
		auto kill = CharacterKillDetails_s({ status.type, status.level });
		AddKillCharacter(kill);
		AddKill(1);
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

	void Character::AddKill(const int kill) {
		m_myData.kill += kill;
	}

	void Character::AddDeath(const int death) {
		m_myData.death += death;
	}


	void Character::BulletState(BulletS state,bool weapon) {
		int maxAmmo;
		int reloadAmmo;
		float interval;
		float reload;
		bool barrage;

		switch (state)
		{
		case BulletS::None:
			maxAmmo = 0;
			reloadAmmo = 0;
			interval = 0;
			reload = 0;
			barrage = false;
			break;
		case BulletS::Assault:
			maxAmmo = 0;
			reloadAmmo = 30;
			interval = 8.0f;
			reload = 60;
			barrage = true;
			break;
		case BulletS::Hand:
			maxAmmo = 50;
			reloadAmmo = 15;
			interval = 1.0f;
			reload = 60;
			barrage = false;
			break;
		case BulletS::Shot:
			maxAmmo = 14;
			reloadAmmo = 2;
			interval = 2.0f;
			reload = 60;
			barrage = false;
			break;
		case BulletS::SMG:
			maxAmmo = 100;
			reloadAmmo = 20;
			interval = 3.0f;
			reload = 60;
			barrage = true;
			break;
		case BulletS::Rocket:
			maxAmmo = 8;
			reloadAmmo = 1;
			interval = 0.0f;
			reload = 60;
			barrage = false;
			break;
		case BulletS::Sniper:
			maxAmmo = 18;
			reloadAmmo = 6;
			interval = 30.0f;
			reload = 60;
			barrage = false;
			break;
		case BulletS::Laser:
			maxAmmo = 0;
			reloadAmmo = 50;
			interval = 0.0f;
			reload = 60;
			barrage = false;
			break;
		case BulletS::Wind:
			maxAmmo = 0;
			reloadAmmo = 900;
			interval = 0.0f;
			reload = 60;
			barrage = true;
			break;
		default:
			break;
		}

		if (weapon) {
			m_ammoO = reloadAmmo;
			m_reAmmoO = reloadAmmo;
			m_maxAmmoO = maxAmmo;
			m_intTimeO = 0;
			m_maxIntTimeO = interval;
			m_reTimeO = 0;
			m_maxreTimeO = reload;
			m_barrageO = barrage;
		}
		else {
			m_ammoT = reloadAmmo;
			m_reAmmoT = reloadAmmo;
			m_maxAmmoT = maxAmmo;
			m_intTimeT = 0;
			m_maxIntTimeT = interval;
			m_reTimeT = 0;
			m_maxreTimeT = reload;
			m_barrageT = barrage;
		}

	}


	void Character::BulletFire() {

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();

		bool fire = false;

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) || KeyState.m_bPressedKeyTbl[VK_RBUTTON])) {
			m_weapon = !m_weapon;
			m_reload = false;
			m_fire = true;
			m_reTimeO = 0;
			m_reTimeT = 0;
			m_intTimeO = 0;
			m_intTimeT = 0;

			if (BulletS::None == m_weaponT) {
				m_weapon = true;
			}
		}


		if (m_weapon) {
			if (m_barrageO) {
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

			if (m_ammoO > 0 && m_intTimeO <= 0) {
				if (fire && m_fire) {
					if (m_weaponO == BulletS::Shot) {
							
						for (size_t i = 0; i < 20; i++)
						{
							m_rot.x += rand();

							auto bullet = GetStage()->AddGameObject<Bullet>(
								ptr->GetPosition(),
								ptr->GetQuaternion(),
								m_weaponO,
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
							ptr->GetQuaternion(),
							m_weaponO,
							m_myData.unique,
							ID,
							m_myData
							);

						bullet->AddEvent([this](const CharacterStatus_s status) {
							DroppedIntoOil(status);
						});

					}
					m_ammoO--;
					m_intTimeO = m_maxIntTimeO;

					m_fire = false;
				}
			}
			else if (m_intTimeO > 0) {
				m_intTimeO--;
			}

			if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) || KeyState.m_bPressedKeyTbl['R']) && (m_ammoO != m_reAmmoO) && !m_reload) {
				m_reload = true;
				m_fire = false;
				m_reTimeO = m_maxreTimeO;
			}

			if (m_reload && m_maxAmmoO > 0) {
				if (m_reTimeO <= 0) {
					int rem;
					rem = m_reAmmoO - m_ammoO;
					m_maxAmmoO -= rem;
					if (m_maxAmmoO < 0) {
						rem += m_maxAmmoO;
						m_maxAmmoO = 0;
					}
					m_ammoO += rem;

					m_reload = false;
					m_fire = true;
				}
				else {
					float time = App::GetApp()->GetElapsedTime();
					m_reTimeO -= time;
				}
			}

		}
		else {
			if (m_barrageT) {
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

			if (m_ammoT > 0 && m_intTimeT <= 0) {
				if (fire && m_fire) {
					if (m_weaponT == BulletS::Shot) {

						for (size_t i = 0; i < 20; i++)
						{
							m_rot.x += rand();

							auto bullet = GetStage()->AddGameObject<Bullet>(
								ptr->GetPosition(),
								ptr->GetQuaternion(),
								m_weaponT,
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
							ptr->GetQuaternion(),
							m_weaponT,
							m_myData.unique,
							ID,
							m_myData
							);

						bullet->AddEvent([this](const CharacterStatus_s status) {
							DroppedIntoOil(status);
						});
					}

					m_ammoT--;
					m_intTimeT = m_maxIntTimeT;

					m_fire = false;
				}
			}
			else if (m_intTimeT > 0) {
				m_intTimeT--;
			}
	
			if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) || KeyState.m_bPressedKeyTbl['R']) && (m_ammoT != m_reAmmoT) && !m_reload) {
				m_reload = true;
				m_fire = false;
				m_reTimeT = m_maxreTimeT;
			}

			if (m_reload && m_maxAmmoT > 0) {
				if (m_reTimeT <= 0) {
					int rem;
					rem = m_reAmmoT - m_ammoT;
					m_maxAmmoT -= rem;
					if (m_maxAmmoT < 0) {
						rem += m_maxAmmoT;
						m_maxAmmoT = 0;
					}
					m_ammoT += rem;

					m_reload = false;
					m_fire = true;
				}
				else {
					float time = App::GetApp()->GetElapsedTime();
					m_reTimeT -= time;
				}
			}

		}

	}

	void Character::BulletDamage(int state,Vec3 rot) {
		Vec2 force;
		float damage;

		switch (state)
		{
		case BulletS::Assault:
			force = Vec2(3.0f, 2.0f);
			damage = 5.0;
			break;
		case BulletS::Hand:
			force = Vec2(3.0f, 3.0f);
			damage = 15.0;
			break;
		case BulletS::Shot:
			force = Vec2(1.0f, 1.0f);
			damage = 5.0;
			break;
		case BulletS::SMG:
			force = Vec2(2.0f, 3.0f);
			damage = 2.0;
			break;
		case BulletS::Rocket:
			force = Vec2(4.0f, 3.0f);
			damage = 25.0;
			break;
		case BulletS::Sniper:
			force = Vec2(2.0f, 5.0f);
			damage = 30.0;
			break;
		case BulletS::Laser:
			force = Vec2(1.0f, 2.0f);
			damage = 10.0;
			break;
		case BulletS::Wind:
			force = Vec2(0.0f, 1.0f);
			damage = 1.0;
			break;
		default:
			break;
		}

		m_force = force;

		AttackHit(rot);

	}


	void Character::DrawString() {
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring strFps(L"FPS: ");
		strFps += Util::UintToWStr(fps);
		strFps += L"\n";

		auto ptr = GetComponent<Transform>();
		Vec3 forword = ptr->GetForword();
		strFps += Util::FloatToWStr(forword.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(forword.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(forword.z);
		strFps += L"\n";

		Vec3 rot = ptr->GetRotation();
		strFps += Util::FloatToWStr(rot.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(rot.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(rot.z);
		strFps += L"\n";

		Quat qua = ptr->GetQuaternion();
		strFps += Util::FloatToWStr(qua.w);
		strFps += L", ";
		strFps += Util::FloatToWStr(qua.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(qua.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(qua.z);
		strFps += L"\n";

		strFps += Util::FloatToWStr(m_rot.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_rot.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_rot.z);
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


		strFps += Util::FloatToWStr(m_ammoO);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_maxAmmoO);
		strFps += L"\n";
		strFps += Util::FloatToWStr(m_ammoT);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_maxAmmoT);
		strFps += L"\n";

		auto string = GetComponent<StringSprite>();
		string->SetText(strFps);

	}


	void TestPlayer::OnCreate() {
		Draw();
		PlayerCamera();
	}

	void TestPlayer::OnUpdate() {
		PlayerMove();
		PlayerRotMove();
		Weapons();
		DrawString();
	}



	void TestEnemy::OnCreate() {
		Draw();
	}

	void TestEnemy::OnUpdate() {
		PinPUpdate();
	}


}
//end basecross
