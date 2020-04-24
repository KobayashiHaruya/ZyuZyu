/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Character::BmfDateRead(wstring model, Vec3 mpos, Vec3 mrot, Vec3 mscale) {
		Mat4x4 m_spanMat;
		mrot.y = mrot.y * 3.14f / 180.0f;
		m_spanMat.affineTransformation(
			mscale,
			Vec3(0.0f, 0.0f, 0.0f),
			mrot,
			mpos
		);

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

	}

	void Character::Draw() {
		//auto ptrTrans = GetComponent<Transform>();
		//ptrTrans->SetPosition(m_pos);
		//ptrTrans->SetScale(Vec3(1.0f));
		//ptrTrans->SetRotation(m_rot);

		////影をつける
		//auto ptrShadow = AddComponent<Shadowmap>();
		//ptrShadow->SetMeshResource(L"DEFAULT_CAPSULE");

		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		//ptrDraw->SetOwnShadowActive(true);

		//ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		//ptrDraw->SetTextureResource(L"trace.png");
		//SetAlphaActive(true);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(Vec3(1.0f));
		ptrTrans->SetRotation(m_rot);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(Vec3(1.0f, 1.5f, 1.0f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetDrawActive(true);

		AddTag(L"Character");
		auto gravity = AddComponent<Gravity>();
		//gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));

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
		Vec3 speed = ptrTransform->GetPosition();
		if (angle.length() > 0.0f) {
			speed += angle * time * m_moveSpeed;
			ptrTransform->SetPosition(speed);
		}

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl[VK_SPACE]) & m_jump) {
			auto grav = GetComponent<Gravity>();
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

		float fThumbRY = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbRY = cntlVec[0].fThumbRY;
		}

		if (KeyState.m_bPushKeyTbl[VK_RIGHT]) {
			fThumbRY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl[VK_LEFT]) {
			fThumbRY = -1.0f;
		}

		auto time = App::GetApp()->GetElapsedTime();
		m_rot.y += fThumbRY * m_rotSpeed * time;

		if (angle.length() > 0.0f) {
			auto ptr = GetBehavior<UtilBehavior>();
			ptr->RotToHead(angle, 1.0f);
		}

	}

	void Character::BulletFire() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl[VK_LBUTTON])) {
			auto bullet = GetStage()->AddGameObject<Bullet>(
				ptr->GetPosition() + Vec3(0.0f, 0.0f, 2.0f),
				m_rot,
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f,
				m_myData.unique,
				ID,
				m_myData
				);

			bullet->AddEvent([&](const CharacterStatus_s status) {
				DroppedIntoOil(status);
			});
		}

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl['E'])) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition() + Vec3(0.0f, 0.0f, 2.0f),
				m_rot,
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f, true, ID
				);
		}
		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl['Q'])) {
			GetStage()->AddGameObject<Grenade>(
				ptr->GetPosition() + Vec3(0.0f, 0.0f, 2.0f),
				m_rot,
				Vec3(1.0f, 1.0f, 1.0f),
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

		float rad = (rot.y * 180.0f) / 3.14f;

		float x = cos(rad);
		float z = sin(rad);

		Vec3 vecForce = (Vec3(x, 1.0f, z)) * m_force.x;
		vecForce.y = m_force.y;
		grav->StartJump(vecForce * 1.2f);

		//ここで一定の条件（吹っ飛び率、自身をふっとばしたのはプレイヤーか）などで自身を表示するPinPを表示する
		/*if(m_opponent.isPlayer) */ShowMyPinP();
	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
			//auto grav = GetComponent<Gravity>();
			//grav->SetGravityVerocityZero();
		}


		if (Other->FindTag(L"Bullet")) {
			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
				m_opponent = bullet->GetFrome();
			}
			auto rot = Other->GetComponent<Transform>()->GetRotation();
			AttackHit(rot);

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
			auto grav = GetComponent<Gravity>();
			grav->SetGravityVerocityZero();
		}

		if (Other->FindTag(L"Torimoti")) {

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




	void TestPlayer::OnCreate() {
		Draw();
		PlayerCamera();
		BmfDateRead(L"Potato_ver1.bmf", Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 180.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	}

	void TestPlayer::OnUpdate() {
		PlayerMove();
		PlayerRotMove();
		BulletFire();
	}



	void TestEnemy::OnCreate() {
		Draw();
		BmfDateRead(L"Potato_ver1.bmf", Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 180.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	}

	void TestEnemy::OnUpdate() {
		PinPUpdate();
	}


}
//end basecross
