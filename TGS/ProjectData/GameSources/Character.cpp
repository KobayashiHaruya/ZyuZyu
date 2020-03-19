/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Character::Draw() {
		auto ptr = GetComponent<Transform>();

		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);


		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CAPSULE");

		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Character");



		PsBoxParam param(ptr->GetWorldMatrix(), 10.0f, true, PsMotionType::MotionTypeActive);
		auto psPtr = AddComponent<RigidbodyBox>(param);
		psPtr->SetAutoTransform(true);


		psPtr->SetAutoGravity(-m_gravityScale);

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
		if (fThumbLX != 0 || fThumbLY != 0) {
			auto ptrTransform = GetComponent<Transform>();
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

		auto vec = angle;
		auto ptrPs = GetComponent<RigidbodyBox>();
				
		Vec3 speed = Vec3(0.0f, 0.0f, 0.0f);

		if (vec.x != 0) {
			speed.x = vec.x * m_moveSpeed;
		}

		if (vec.z != 0) {
			speed.z = vec.z * m_moveSpeed;
		}

		speed = speed + ptrPs->GetPosition();
		ptrPs->SetPosition(speed);
		ptrPs->SetAngularVelocity(Vec3(0.0f, 0.0f, 0.0f));


		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl[VK_SPACE]) & m_jump) {
			auto vel = ptrPs->GetLinearVelocity();
			ptrPs->SetLinearVelocity(Vec3(vel.x, m_jumpPower, vel.z));
			m_jump = false;
		}


	}

	void Character::BulletFire() {
		GetStage()->AddGameObject<Bullet>(
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1.0f, 1.0f
			);
	}

	void Character::AttackHit(Vec3 rot) {
		auto ptrPs = GetComponent<RigidbodyBox>();

		

  //      float rad = rot.y * Mathf.Deg2Rad;

  //      float x = Mathf.Sin(rad);
  //      float z = Mathf.Cos(rad);

  //      Vec3 vecForce = (Vec3(x, 1.0f, z)) * m_force;

		//Vec3 force = vecForce * m_force;
		//ptrPs->SetLinearVelocity(m_force);

	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
			auto ptrPs = GetComponent<RigidbodyBox>();
		}
		if (Other->FindTag(L"Bullet")) {
			auto rot = Other->GetComponent<Transform>()->GetRotation();
			AttackHit(rot);
		}
	}

	void Character::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = false;
			auto ptrPs = GetComponent<RigidbodyBox>();
		}
	}


	void TestPlayer::OnCreate() {
		Draw();
		PlayerCamera();
	}

	void TestPlayer::OnUpdate() {
		PlayerMove();
	}

}
//end basecross
