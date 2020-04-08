/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Character::Draw() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(Vec3(1.0f));
		ptrTrans->SetRotation(m_rot);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CAPSULE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetOwnShadowActive(true);

		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

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
			GetStage()->AddGameObject<Bullet>(
				ptr->GetPosition() + Vec3(0.0f, 0.0f, 2.0f),
				m_rot,
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f
				);
		}
	}

	void Character::AttackHit(Vec3 rot) {
		auto grav = GetComponent<Gravity>();

		float rad = (rot.y * 180.0f) / 3.14f;

		float x = cos(rad);
		float z = sin(rad);

		Vec3 vecForce = (Vec3(x, 2.0f, z)) * m_force;

		grav->StartJump(vecForce);

	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
			auto rot = Other->GetComponent<Transform>()->GetRotation();
			AttackHit(rot);
		}
	}

	void Character::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
		}

	}

	void Character::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = false;
		}
	}


	void TestPlayer::OnCreate() {
		Draw();
		PlayerCamera();
	}

	void TestPlayer::OnUpdate() {
		PlayerMove();
		PlayerRotMove();
		BulletFire();
	}

}
//end basecross
