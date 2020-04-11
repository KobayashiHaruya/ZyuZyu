/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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

		Quat q;
		q.rotationZ(-90.0f * (3.14f / 180.0f));

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(Vec3(1.0f));
		ptrTrans->SetQuaternion(q);

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

		AddTag(L"Character");


		//�����v�Z�J�v�Z��
		PsCapsuleParam param;
		//���a�ɂ���
		param.m_HalfLen = m_scale.y * 0.5f;
		param.m_Radius = m_scale.x * 0.5f;
		param.m_Mass = 1.0f;
		//�����e���\���̌v�Z
		param.m_Inertia = BasePhysics::CalcInertiaCylinderX(
			param.m_HalfLen + param.m_Radius,
			param.m_Radius,
			param.m_Mass
		);
		param.m_MotionType = PsMotionType::MotionTypeActive;
		param.m_Quat = q;
		param.m_Pos = m_pos;
		auto ptrPs = AddComponent<RigidbodyCapsule>(param);
		ptrPs->SetDrawActive(true);

		ptrPs->SetAutoTransform(true);

		ptrPs->SetAutoGravity(-m_gravityScale);

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
		auto ptrPs = GetComponent<RigidbodyCapsule>();

		Vec3 speed = Vec3(0.0f, 0.0f, 0.0f);

		if (vec.x != 0) {
			speed.x = vec.x * m_moveSpeed;
		}

		if (vec.z != 0) {
			speed.z = vec.z * m_moveSpeed;
		}

		speed = speed + ptrPs->GetPosition();
		ptrPs->SetPosition(speed);


		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl[VK_SPACE]) & m_jump) {
			auto vel = ptrPs->GetLinearVelocity();
			ptrPs->SetLinearVelocity(Vec3(vel.x, m_jumpPower, vel.z));
			m_jump = false;
		}


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
		auto ptrPs = GetComponent<RigidbodyCapsule>();

		Vec3 speed;
		ptrPs->SetAngularVelocity(speed);
		m_rot.y += fThumbLY * m_rotSpeed;
		trans->SetRotation(m_rot);

	}

	void Character::BulletFire() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		auto ptr = GetComponent<Transform>();

		if (((cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) || KeyState.m_bPressedKeyTbl['F'])) {

			auto bullet = GetStage()->AddGameObject<Bullet>(
				ptr->GetPosition() + Vec3(0.0f, 0.0f, 2.0f),
				ptr->GetRotation(),
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f,
				m_myData.unique
				);
			bullet->AddEvent([this](const CharacterStatus_s status) {
				DroppedIntoOil(status);
			});
		}
	}

	void Character::Respawn() {
		srand((unsigned int)time(NULL));
		int Rand = rand() % 5;
		const float activeY = 25.0f;
		auto PtrTransform = GetComponent<Transform>();

		if (abs(PtrTransform->GetPosition().y) > activeY) {
			m_des = true;
			if (m_des) {
				//�����_���ɏo���悤��
				switch (Rand) {
				case 0:
					GetStage()->AddGameObject<TestPlayer>(
						Vec3(0.0f, 3.0f, 0.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(1.0f, 1.0f, 1.0f),
						0.15f, 10.0f, 5.0f
						);
					break;
				case 1:
					GetStage()->AddGameObject<TestPlayer>(
						Vec3(-50.0f, 3.0f, 50.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(1.0f, 1.0f, 1.0f),
						0.15f, 10.0f, 5.0f
						);
					break;
				case 2:
					GetStage()->AddGameObject<TestPlayer>(
						Vec3(50.0f, 3.0f, 50.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(1.0f, 1.0f, 1.0f),
						0.15f, 10.0f, 5.0f
						);
					break;
				case 3:
					GetStage()->AddGameObject<TestPlayer>(
						Vec3(50.0f, 3.0f, -50.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(1.0f, 1.0f, 1.0f),
						0.15f, 10.0f, 5.0f
						);
					break;
				case 4:
					GetStage()->AddGameObject<TestPlayer>(
						Vec3(-50.0f, 3.0f, -50.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(1.0f, 1.0f, 1.0f),
						0.15f, 10.0f, 5.0f
						);
					break;
				default:
					GetStage()->AddGameObject<TestPlayer>(
						Vec3(0.0f, 3.0f, 0.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(1.0f, 1.0f, 1.0f),
						0.15f, 10.0f, 5.0f
						);
					break;
				}
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
				m_des = false;
			}
		}
	}


	void Character::AttackHit(Vec3 rot) {
		auto ptrPs = GetComponent<RigidbodyCapsule>();



  //      float rad = rot.y * Mathf.Deg2Rad;

  //      float x = Mathf.Sin(rad);
  //      float z = Mathf.Cos(rad);

        Vec3 vecForce = (Vec3(rot.x, 1.0f, rot.z)) * m_force;

		ptrPs->SetLinearVelocity(rot);

	}

	void Character::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = true;
			auto ptrPs = GetComponent<RigidbodyCapsule>();
		}
		if (Other->FindTag(L"Bullet")) {
			auto rot = Other->GetComponent<Transform>()->GetRotation();
			AttackHit(rot);
			m_touchOil = dynamic_pointer_cast<ObstacleEvent<const CharacterStatus_s>>(Other);
		}
		if (Other->FindTag(L"Weapon")) {

		}
		if (Other->FindTag(L"Oil")) {
			TouchOil();
		}
	}

	void Character::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Object")) {
			m_jump = false;
			auto ptrPs = GetComponent<RigidbodyCapsule>();
		}
	}

	//���ɐG�ꂽ���̏���
	void Character::TouchOil() {
		if(m_touchOil) m_touchOil->Run(m_myData);
		AddDeath(1);
		SetUpdateActive(false);
		SetDrawActive(false);
	}

	//�������ɗ��Ƃ������̏���
	void Character::DroppedIntoOil(const CharacterStatus_s& status) {
		AddScore(status.level * 100 + (status.level > 1 ? 100 : 0));
		auto kill = CharacterKillDetails_s({ status.type, status.level });
		AddKillCharacter(kill);
		AddKill(1);
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
	}

	void TestPlayer::OnUpdate() {
		PlayerMove();
		PlayerRotMove();
		BulletFire();
		Respawn();
	}



	void TestEnemy::OnCreate() {
		Draw();
	}

	void TestEnemy::OnUpdate() {

	}

}
//end basecross
