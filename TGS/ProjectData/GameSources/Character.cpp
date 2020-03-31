/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Character::Draw() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		bsm::Vec3 pointA(0, 0, 0);
		bsm::Vec3 pointB(0, 0, 0);
		pointA -= bsm::Vec3(0, m_scale.y * 0.5f, 0);
		pointB += bsm::Vec3(0, m_scale.y * 0.5f, 0);
		MeshUtill::CreateCapsule(m_scale.x,
			pointA, pointB, 18, vertices, indices, true);

		shared_ptr<MeshResource> m_CapsuleMesh;

		m_CapsuleMesh = MeshResource::CreateMeshResource(vertices, indices, false);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(Vec3(1.0f));
		//ptrTrans->SetQuaternion(q);
		ptrTrans->SetRotation(m_rot);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_CapsuleMesh);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(m_CapsuleMesh);
		ptrDraw->SetOwnShadowActive(true);

		//ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetTextureResource(L"trace.png");
		SetAlphaActive(true);

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(Vec3(1.0f, 1.5f, 1.0f));
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);

		AddTag(L"Character");
		auto gravity = AddComponent<Gravity>();
		gravity->SetGravity(Vec3(0.0f, -m_gravityScale, 0.0f));


		//Quat q;
		//q.rotationZ(-90.0f * (3.14f / 180.0f));

		////�����v�Z�J�v�Z��
		//PsCapsuleParam param;
		////���a�ɂ���
		//param.m_HalfLen = m_scale.y * 0.5f;
		//param.m_Radius = m_scale.x * 0.5f;
		//param.m_Mass = 1.0f;
		////�����e���\���̌v�Z
		//param.m_Inertia = BasePhysics::CalcInertiaCylinderX(
		//	param.m_HalfLen + param.m_Radius,
		//	param.m_Radius,
		//	param.m_Mass
		//);
		//param.m_MotionType = PsMotionType::MotionTypeActive;
		//param.m_Quat = q;
		//param.m_Pos = m_pos;
		//auto ptrPs = AddComponent<RigidbodyCapsule>(param);
		//ptrPs->SetDrawActive(true);

		//ptrPs->SetAutoTransform(true);

		//ptrPs->SetAutoGravity(-m_gravityScale);

	}

	void Character::PlayerCamera() {
		//�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(GetThis<Character>());
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
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
		}

		if (angle.x != 0) {
			m_pos.x = angle.x * m_moveSpeed;
		}

		if (angle.z != 0) {
			m_pos.z = angle.z * m_moveSpeed;
		}

		Vec3 speed = m_pos + ptrTransform->GetPosition();

		//ptrTransform->SetPosition(speed);

		//if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl[VK_SPACE]) & m_jump) {
		//	auto vel = ptrPs->GetLinearVelocity();
		//	ptrPs->SetLinearVelocity(Vec3(vel.x, m_jumpPower, vel.z));
		//	m_jump = false;
		//}


	}

	void Character::PlayerRotMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		float fThumbLY = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbRY;
		}

		if (KeyState.m_bPushKeyTbl[VK_RIGHT]) {
			//�E
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl[VK_LEFT]) {
			//��
			fThumbLY = -1.0f;
		}

		auto trans = GetComponent<Transform>();
		auto time = App::GetApp()->GetElapsedTime();
		m_rot.y += fThumbLY * m_rotSpeed * time;
		trans->SetRotation(m_rot);

	}

	void Character::BulletFire() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();
		
		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl['F'])) {
			GetStage()->AddGameObject<Bullet>(
				m_pos + Vec3(0.0f, 0.0f, 2.0f),
				m_rot,
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f
				);
		}
	}

	void Character::AttackHit(Vec3 rot) {
		//auto ptrPs = GetComponent<RigidbodyCapsule>();

		//float rad = rot.y * Mathf.Deg2Rad;

		//float x = Mathf.Sin(rad);
		//float z = Mathf.Cos(rad);

		//Vec3 vecForce = (Vec3(rot.x, 1.0f, rot.z)) * m_force;

		//ptrPs->SetLinearVelocity(rot);

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
