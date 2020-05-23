/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
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

		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetMakedDiameter(2.5f);
		//ptrColl->AddExcludeCollisionTag(L"Weapon");
		ptrColl->SetAfterCollision(AfterCollision::Auto);
			
		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(model);
		ptrShadow->SetMeshToTransformMatrix(m_spanMat);

		auto ptrDraw = AddComponent <PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(model);
		ptrDraw->SetMeshToTransformMatrix(m_spanMat);
		//ptrDraw->AddAnimation(L"CharacterAnimation", 0, 210, true, 30.0f);
		//ptrDraw->ChangeCurrentAnimation(L"CharacterAnimation");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDrawActive(true);

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		SetAlphaActive(true);

		////Rigidbody������
		//auto PtrRedid = AddComponent<Rigidbody>();

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
			m_weaponT = BulletS::None;
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

		BulletState(m_weaponO, true);
		BulletState(m_weaponT, false);
	}

	void Character::PlayerUI() {
		GetStage()->AddGameObject<UI_PlayerAmmo>(
			3,
			L"Share_Number.png",
			Vec3(725.0f, -120.0f, 0.0f),
			Vec3(150.0f, 50.0f, 1.0f),
			true
			);
		GetStage()->AddGameObject<UI_PlayerAmmo>(
			3,
			L"Share_Number.png",
			Vec3(875.0f, -120.0f, 0.0f),
			Vec3(150.0f, 50.0f, 1.0f),
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
		//�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(GetThis<Character>());
			ptrCamera->SetTargetToAt(Vec3(0.0f, 0.25f, 0));
		}

	}

	void Character::PlayerMove() {
		Vec3 angle(0, 0, 0);
		//�R���g���[���̎擾
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
			//�O
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			fThumbLY = -1.0f;
		}
		if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			fThumbLX = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			fThumbLX = -1.0f;
		}

		auto ptrTransform = GetComponent<Transform>();
		if (fThumbLX != 0 || fThumbLY != 0) {
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
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

		if (angle.length() > 0.0f) {
			auto ptr = GetBehavior<UtilBehavior>();
			ptr->RotToHead(angle, 1.0f);
		}

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
				ptr->GetQuaternion(),
				50.0f, 10.0f, true, ID, m_myData
				);
			m_toriG = false;
			m_toriGtime = 0.0f;
		}
		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) || KeyState.m_bPressedKeyTbl['E']) && m_smokeG) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition(),
				ptr->GetQuaternion(),
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
		//�����_���ɏo���悤��
		switch (Rand) {
		case 0:
			PtrTransform->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
			break;
		case 1:
			PtrTransform->SetPosition(Vec3(-30.0f, 0.0f, 30.0f));
			break;
		case 2:
			PtrTransform->SetPosition(Vec3(30.0f, 0.0f, 30.0f));
			break;
		case 3:
			PtrTransform->SetPosition(Vec3(30.0f, 0.0f, -30.0f));
			break;
		case 4:
			PtrTransform->SetPosition(Vec3(-30.0f, 0.0f, -30.0f));
			break;
		case 5:
			PtrTransform->SetPosition(Vec3(-30.0f, 0.0f, 0.0f));
			break;
		case 6:
			PtrTransform->SetPosition(Vec3(30.0f, 0.0f, 0.0f));
			break;
		case 7:
			PtrTransform->SetPosition(Vec3(0.0f, 0.0f, -30.0f));
			break;
		default:
			PtrTransform->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
			break;
		}
	}


	void Character::AttackHit(Vec3 rot) {
		auto grav = GetComponent<Gravity>();

		Vec2 force = m_force * 5.0f;

		Vec3 vecForce = rot * force.x;
		vecForce.y = force.y;
		grav->StartJump(vecForce * ((m_damage / 200.0f) + 1));

		//�����ň��̏����i������ї��A���g���ӂ��Ƃ΂����̂̓v���C���[���j�ȂǂŎ��g��\������PinP��\������
		/*if(m_opponent.isPlayer) */ShowMyPinP();
	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
		}

		if (Other->FindTag(L"Torimoti")) {
			m_torimoti = true;
		}

		if (Other->FindTag(L"Smoke")) {
			m_smoke = true;
		}

		if (Other->FindTag(L"Explosion")) {
			BulletDamage(Other->GetBulletType(), Other->GetComponent<Transform>()->GetForword());
			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
				m_opponent = bullet->GetFrome();
			}

			if (Other->FindTag(L"Smoke")) {
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
			}

		}
		else if(Other->FindTag(L"Bullet") && Other->GetID() != ID){
			BulletDamage(Other->GetBulletType(), Other->GetComponent<Transform>()->GetForword());
			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
				m_opponent = bullet->GetFrome();
			}

			if (m_toriIn) {
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
			}
		}

		if (Other->FindTag(L"GatlingAmmo")) {
			m_gatlingAmmo += m_gatlingPickAmmo;
			if (m_gatlingAmmo > 999)
				m_gatlingAmmo = 999;
			GetStage()->RemoveGameObject<GameObject>(Other);
		}


		if (Other->FindTag(L"Oil")) {
			TouchOil();
			Respawn();
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

		if (Other->FindTag(L"Torimoti")) {
			m_torimoti = true;
			Torimoti(true);
			m_toriIn = true;
		}
		else {
			Torimoti(false);
			m_toriIn = false;
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

		if (Other->FindTag(L"Torimoti")) {
			Torimoti(false);
		}

		if (Other->FindTag(L"SetGun")) {
			m_setGun = false;
		}

	}

	//���ɐG�ꂽ���̏���
	void Character::TouchOil() {
		if (m_touchOil) m_touchOil->Run(m_myData);
		AddDeath(1);

		//PinP�ŕ\�����Ă���̂����g��������PinP���\���ɂ���
		auto pinp = GetStage()->GetSharedGameObject<PinP>(L"BlownPinP");
		if (m_myData.unique == pinp->GetUse().unique) {
			pinp->DeleteUse();
			pinp->Out(PinPAction::LEFT);
		}

		SetUpdateActive(true);
		SetDrawActive(true);

		CharaState();
		m_smoke = false;
		m_torimoti = false;
		m_myData.level = 1;
		m_damage = 0.0f;
	}

	//�������ɗ��Ƃ������̏���
	void Character::DroppedIntoOil(const CharacterStatus_s& status) {
		AddScore(status.level * 100 + (status.level > 1 ? 100 : 0));
		auto kill = CharacterKillDetails_s({ status.type, status.level });
		AddKillCharacter(kill);
		AddKill(1);

		GetStage()->AddGameObject<UI_Kill_Icon>(
			Vec3(0.0f, -350.0f, 0.0f),
			Vec3(0.8f, 0.8f, 1.0f),
			100,
			status.type,
			status.level
			);
	}

	//PinP�Ɏ��g���w�肵�ĕ\������
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

	vector<CharacterKillList_s> Character::GetKillList() {
		return m_killList;
	}


	void Character::AddKillCharacter(const CharacterKillDetails_s& data) {
		m_killCharacters.push_back(data);

		CharacterKillList(state);

		switch (data.type)
		{
		case CharacterType::SHRIMP:
			state.killState = 0;
			break;
		case CharacterType::CHICKEN:
			state.killState = 3;
			break;
		case CharacterType::POTATO:
			state.killState = 6;
			break;
		case CharacterType::DOUGHNUT:
			state.killState = 9;
			break;
		default:
			break;
		}

		state.killState += data.level;

		m_killList.push_back(state);
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
	}

	void Character::AddKill(const int kill) {
		m_myData.kill += kill;
	}

	void Character::AddDeath(const int death) {
		m_myData.death += death;
	}


	void Character::BulletState(int state, bool weapon, bool same) {
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
			interval = 0.5f;
			reload = 0.5f;
			barrage = true;
			break;
		case BulletS::Hand:
			maxAmmo = 50;
			reloadAmmo = 15;
			interval = 0.2f;
			reload = 0.5f;
			barrage = false;
			break;
		case BulletS::Shot:
			maxAmmo = 14;
			reloadAmmo = 2;
			interval = 1.0f;
			reload = 0.5f;
			barrage = false;
			break;
		case BulletS::SMG:
			maxAmmo = 100;
			reloadAmmo = 20;
			interval = 0.1f;
			reload = 0.5f;
			barrage = true;
			break;
		case BulletS::Rocket:
			maxAmmo = 8;
			reloadAmmo = 1;
			interval = 0.0f;
			reload = 0.5f;
			barrage = false;
			break;
		case BulletS::Sniper:
			maxAmmo = 18;
			reloadAmmo = 6;
			interval = 1.0f;
			reload = 0.5f;
			barrage = false;
			break;
		case BulletS::Laser:
			maxAmmo = 0;
			reloadAmmo = 50;
			interval = 0.3f;
			reload = 0.5f;
			barrage = false;
			break;
		case BulletS::Wind:
			maxAmmo = 0;
			reloadAmmo = 2000;
			interval = 1.0f / 60.0f;
			reload = 0.5f;
			barrage = true;
			break;
		default:
			break;
		}

		if (weapon) {
			if (same)
			{
				m_maxAmmoO += maxAmmo + reloadAmmo;
				m_barrageO = barrage;
			}
			else {
				m_ammoO = reloadAmmo;
				m_reAmmoO = reloadAmmo;
				m_maxAmmoO = maxAmmo;
				m_intTimeO = 0;
				m_maxIntTimeO = interval;
				m_reTimeO = 0;
				m_maxreTimeO = reload;
				m_barrageO = barrage;
				m_weaponO = BulletS(state);
			}
		}
		else {
			if (same)
			{
				m_maxAmmoT += maxAmmo + reloadAmmo;
				m_barrageT = barrage;
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
				m_weaponT = BulletS(state);
			}
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

		}

		if (BulletS::None == m_weaponT) {
			m_weapon = true;
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

			if (((((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) || KeyState.m_bPressedKeyTbl['R'])
				&& m_ammoO < m_reAmmoO)
				|| m_ammoO <= 0) && !m_reload) {
				m_reload = true;
				m_fire = false;
				m_reTimeO = m_maxreTimeO;
			}
			
			if (m_reload && m_maxAmmoO > 0) {
				if (m_reTimeO > 0) {
					float time = App::GetApp()->GetElapsedTime();
					m_reTimeO -= time;
					m_fire = false;
				}
				else {
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
			}

			if (m_ammoO > 0 && m_intTimeO <= 0) {
				if (fire && m_fire) {
					if (m_weaponO == BulletS::Shot) {

						for (size_t i = 0; i < 20; i++)
						{
							//Quat X;
							//X.x = (i * 3.14f) / 180.0f;
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
				float time = App::GetApp()->GetElapsedTime();
				m_intTimeO -= time;
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

			if (((((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) || KeyState.m_bPressedKeyTbl['R'])
				&& m_ammoT < m_reAmmoT)
				|| m_ammoT <= 0) && !m_reload) {
				m_reload = true;
				m_fire = false;
				m_reTimeT = m_maxreTimeT;
			}

			if (m_reload && m_maxAmmoT > 0) {
				if (m_reTimeT > 0) {
					float time = App::GetApp()->GetElapsedTime();
					m_reTimeT -= time;
					m_fire = false;
				}
				else {
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
			}

			if (m_ammoT > 0 && m_intTimeT <= 0) {
				if (fire && m_fire) {
					if (m_weaponT == BulletS::Shot) {

						for (size_t i = 0; i < 20; i++)
						{
							//Quat X;
							//X.x = (i * 3.14f) / 180.0f;
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
				float time = App::GetApp()->GetElapsedTime();
				m_intTimeT -= time;
			}

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
						ptr->GetQuaternion(),
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
					ptr->GetQuaternion(),
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
				ptr->GetQuaternion(),
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
			force = Vec2(10.0f, 0.2f);
			damage = 1.0;
			break;
		case BulletS::Gatling:
			force = Vec2(10.0f, 5.0f);
			damage = 1.0;
			break;
		case BulletS::Cannon:
			force = Vec2(15.0f, 10.0f);
			damage = 1.0;
			break;
		case BulletS::GExplosion:
			force = Vec2(-5.0f, 5.0f);
			damage = 20.0;
			break;
		case BulletS::CExplosion:
			force = Vec2(5.0f, 5.0f);
			damage = 20.0;
			break;
		case BulletS::SExplosion:
			force = Vec2(5.0f, 5.0f);
			damage = 20.0;
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
		if (BulletS::None == m_weaponT) {
			BulletState(state, false);
		}
		else {
			if (m_weapon) {
				if (m_weaponO == state)
					same = true;
			}
			else {
				if (m_weaponT == state) {
					same = true;
				}
			}
			BulletState(state, m_weapon, same);
		}
	}

	void Character::PlayerMovement() {
		AddLevel();

		PlayerRotMove();
		if (m_setGun) {
			SetWeaponFire();
		}
		else {
			PlayerMove();
			BulletFire();
			GrenadeFire();
		}

		//auto ptrDraw = GetComponent<PNTStaticModelDraw>();
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//ptrDraw->UpdateAnimation(elapsedTime);
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

		Quat quat = GetComponent<Transform>()->GetQuaternion();
		Vec3 rot = GetComponent<Transform>()->GetRotation();

		strFps += Util::FloatToWStr(quat.w);
		strFps += L", ";
		strFps += Util::FloatToWStr(quat.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(quat.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(quat.z);
		strFps += L"\n";

		strFps += Util::FloatToWStr(rot.x);
		strFps += L", ";
		strFps += Util::FloatToWStr(rot.y);
		strFps += L", ";
		strFps += Util::FloatToWStr(rot.z);
		strFps += L"\n";

		strFps += Util::FloatToWStr(m_ammoO);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_maxAmmoO);
		strFps += L"\n";
		strFps += Util::FloatToWStr(m_ammoT);
		strFps += L", ";
		strFps += Util::FloatToWStr(m_maxAmmoT);
		strFps += L"\n";

		strFps += Util::FloatToWStr(m_gatlingShotAmmo);
		strFps += L"\n";
		strFps += Util::FloatToWStr(m_gatlingAmmo);
		strFps += L"\n";

		strFps += Util::FloatToWStr(GetTypeStage<GameStage>()->bomb);
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


}
//end basecross
