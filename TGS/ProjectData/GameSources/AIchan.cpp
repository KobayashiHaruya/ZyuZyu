/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Weapon.h"
#include "AIchan.h"

namespace basecross {

	//------------------------------------------------------------------------------------------------
	//アイちゃん本体 : Class
	//------------------------------------------------------------------------------------------------

	void AIchan::OnCreate() {
		Draw();

		m_stateMachine.reset(new StateMachine<AIchan>(GetThis<AIchan>()));
		m_stateMachine->ChangeState(SeekPatrolState::Instance());

		if (m_aiParam.isDebug) CreateDebugObject();
	}

	void AIchan::OnUpdate() {
		if (GetTypeStage<GameStage>()->m_start && !Torimoti()) {
			m_stateMachine->Update();

			AddLevel();
			if (m_aiParam.isDebug) UpdateDebugObject();
		}
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		auto pos = GetComponent<Transform>()->GetPosition();

		if (pos.y <= -10.0f) {
			TouchOil();
		}
	}

	void AIchan::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		Character::OnCollisionEnter(Other);

		//オブジェクトがBulletタグのついたオブジェクトだったら
		if (Other->FindTag(L"Bullet")) {
			auto bullet = dynamic_pointer_cast<Bullet>(Other);
			if (bullet) {
				auto character = GetCharacterByID(bullet->GetFromUnique());
				if (character) {
					SetTarget(character->GetComponent<Transform>());
					SetTargetType(AIChan::AITargetType::IS_FAR);
					m_stateMachine->ChangeState(SeekDiscoveryState::Instance());
				}
			}
		}
	}

	void AIchan::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		Character::OnCollisionExcute(Other);

		if (Other->FindTag(L"FallGun")) {
			PickGun(Other->GetBulletType());
			GetStage()->RemoveGameObject<GameObject>(Other);
		}

		//ステートマシンが巡回かつあたっている対象が床だったら
		auto currentState = m_stateMachine->GetCurrentState();
		if (Other->FindTag(L"Obstacle") && currentState == SeekPatrolState::Instance()) {
			if (m_jumpMissCount >= m_jumpMiss) {
				ChangeNextPoint();
				m_jumpMissCount = 0;
			}
			else {
				ObstacleJump();
			}
		}
		else {
			m_jumpMissCount = 0;
		}
	}

	void AIchan::DroppedIntoOil(const CharacterStatus_s& status) {
		Character::DroppedIntoOil(status);
		SetTarget(NULL);
		m_stateMachine->ChangeState(SeekPatrolState::Instance());
	}

	void AIchan::Move(const Vec3& toPos) {
		float time = App::GetApp()->GetElapsedTime();
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();
		auto move = toPos - pos;
		auto rot = move;
		move = move.normalize() * time * m_aiParam.pointPatrolMoveSpeed;
		move.y = 0;
		pos += move;
		trans->SetPosition(pos);
		auto ptr = GetBehavior<UtilBehavior>();
		ptr->RotToHead(rot, time * m_aiParam.pointPatrolRotSpeed);

		Animation(Anim::walk);
	}
	void AIchan::Jump(const Vec3& jumpVelocity) {
		auto gravity = GetComponent<Gravity>();
		gravity->StartJump(jumpVelocity);
	}
	bool AIchan::ThisToTargetAllowable(const float allowable, const Vec3& target, const bool isPlane) {
		Vec3& thisPos = GetComponent<Transform>()->GetPosition();
		Vec3 targetPos = target;
		if (isPlane) {
			thisPos.y = 0.0f;
			targetPos.y = 0.0f;
		}
		float distance = (targetPos - thisPos).length();
		return (distance < allowable) ? true : false;
	}
	float AIchan::GetThisToTargetDistance(const Vec3& target, const bool isPlane) {
		Vec3& thisPos = GetComponent<Transform>()->GetPosition();
		Vec3 targetPos = target;
		if (isPlane) {
			thisPos.y = 0.0f;
			targetPos.y = 0.0f;
		}
		return (targetPos - thisPos).length();
	}
	unsigned int AIchan::RandomNumber(const unsigned int& min, const unsigned int& max) {
		mt19937_64 mt{ random_device{}() };
		uniform_int_distribution<unsigned int> dist(min, max);
		return dist(mt);
	}
	void AIchan::UpdateEscapeMode() {
		if (GetDamage() >= m_aiParam.escapeDamage) {
			switch (m_aiParam.escapeMode)
			{
			case 0:
				m_escapeMode = RandomNumber(0, 1);
				break;
			case 1:
				m_escapeMode = true;
				break;
			case 2:
				m_escapeMode = false;
				break;
			default:
				break;
			}
		}
	}
	vector<shared_ptr<Character>> AIchan::GetCharacters() {
		vector<shared_ptr<Character>> characters;
		auto group = GetStage()->GetSharedObjectGroup(L"CharacterGroup");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto obj = v.lock();
			if (obj) {
				auto character = dynamic_pointer_cast<Character>(obj);
				if (character && character->GetMyData().unique != GetMyData().unique) {
					characters.push_back(character);
				}
			}
		}
		return characters;
	}
	vector<shared_ptr<Transform>> AIchan::GetCharacterTransforms() {
		vector<shared_ptr<Transform>> transforms;
		auto characters = GetCharacters();
		for (auto& character : characters) {
			transforms.push_back(character->GetComponent<Transform>());
		}
		return transforms;
	}
	shared_ptr<Transform> AIchan::GetClosestCharacterTransform() {
		auto transforms = GetCharacterTransforms();
		if (transforms.size() <= 0) return NULL;
		float closestDistance = GetThisToTargetDistance(transforms[0]->GetPosition());
		shared_ptr<Transform> closestTransform(transforms[0]);
		for (auto& transform : transforms) {
			auto distance = GetThisToTargetDistance(transform->GetPosition());
			if (closestDistance > distance) {
				closestDistance = distance;
				closestTransform = transform;
			}
		}
		return closestTransform;
	}
	shared_ptr<Character> AIchan::GetCharacterByID(const int id) {
		auto characters = GetCharacters();
		for (auto& character : characters) {
			if (character->GetMyData().unique == id) return character;
		}
		return NULL;
	}
	vector<shared_ptr<GameObject>> AIchan::GetObstacles() {
		vector<shared_ptr<GameObject>> obstacles;
		auto group = GetStage()->GetSharedObjectGroup(L"ObstacleGroup");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto obj = v.lock();
			obstacles.push_back(obj);
		}
		return obstacles;
	}
	vector<shared_ptr<Transform>> AIchan::GetObstacleTransforms() {
		vector<shared_ptr<Transform>> transforms;
		auto obstacles = GetObstacles();
		for (auto& obstacle : obstacles) {
			transforms.push_back(obstacle->GetComponent<Transform>());
		}
		return transforms;
	}
	shared_ptr<Transform> AIchan::GetClosestObstacleTransform() {
		auto transforms = GetObstacleTransforms();
		if (transforms.size() <= 0) return NULL;

		float closestDistance = GetThisToTargetDistance(transforms[0]->GetPosition(), true) - (transforms[0]->GetScale().getX() / 2.0f);
		shared_ptr<Transform> closestTransform(transforms[0]);
		for (auto& transform : transforms) {
			auto distance = GetThisToTargetDistance(transform->GetPosition(), true) - (transform->GetScale().getX() / 2.0f);
			if (closestDistance > distance) {
				closestDistance = distance;
				closestTransform = transform;
			}
		}
		/*
		float closestDistance = GetThisToTargetDistance(transforms[0]->GetPosition(), true) + (transforms[0]->GetScale().getX() / 2.0f);
		shared_ptr<Transform> closestTransform(transforms[0]);
		for (auto& transform : transforms) {
			auto distance = GetThisToTargetDistance(transform->GetPosition(), true) + (transform->GetScale().getX() / 2.0f);
			if (closestDistance > distance) {
				closestDistance = distance;
				closestTransform = transform;
			}
		}*/
		return closestTransform;
	}
	void AIchan::ObstacleJump() {
		auto obstacleTrans = GetClosestObstacleTransform();
		auto scale = obstacleTrans->GetScale();
		auto pos = obstacleTrans->GetPosition();
		if ((GetThisToTargetDistance(pos, true) - (scale.getX() / 2.0f)) <= 3.0f) {
			Jump(Vec3(0.0f, GetJumpPower(), 0.0f));
			m_jumpMissCount++;
		}
	}

	Vec3 AIchan::GetNextPoint() {
		if (m_aiParam.points.size() - 1 > m_pointIndex) {
			m_pointIndex++;
			return m_aiParam.points[m_pointIndex];
		}
		m_pointIndex = 0;
		return m_aiParam.points[m_pointIndex];
	}
	void AIchan::ChangeNextPoint() {
		m_point = GetNextPoint();
	}
	bool AIchan::PointChangePermission() {
		float time = App::GetApp()->GetElapsedTime();
		m_pointPatrolWaitTimeCount += time;
		if (m_pointPatrolWaitTime <= m_pointPatrolWaitTimeCount) {
			m_pointPatrolWaitTimeCount = 0.0f;
			return true;
		}
		return false;
	}
	bool AIchan::pointJumpPermission() {
		float time = App::GetApp()->GetElapsedTime();
		m_pointPatrolJumpWaitTimeCount += time;
		if (m_pointPatrolJumpWaitTime <= m_pointPatrolJumpWaitTimeCount) {
			m_pointPatrolJumpWaitTimeCount = 0.0f;
			return true;
		}
		return false;
	}

	bool AIchan::BulletChangePermission() {
		float time = App::GetApp()->GetElapsedTime();
		m_bulletChangeTimeCount += time;
		if (m_bulletChangeTime <= m_bulletChangeTimeCount) {
			m_bulletChangeTimeCount = 0.0f;
			return true;
		}
		return false;
	}
	void AIchan::RandomBulletSelect() {
		m_oldBulletNum = m_newBulletNum;

		SetFire(true, true);
		SetFire(false, false);

		SetWeaponOState(7, 0);
		SetWeaponTState(7, 0);
		SetWeaponOState(5, 0);
		SetWeaponTState(5, 0);

		//m_newBulletNum = RandomNumber(1, m_bulletMaxPossession);

		//リロードが発生したらもう一つの武器に切り替えるようにする
		auto one = GetWeaponOState();
		auto two = GetWeaponTState();
		if (one.ammo || !two.ammo) {
			m_newBulletNum = 1;
		}
		else {
			m_newBulletNum = m_bulletMaxPossession;
		}
	}
	bool AIchan::BulletShotPermission() {
		float time = App::GetApp()->GetElapsedTime();
		m_bulletShotWaitTimeCount += time;
		if (m_bulletShotWaitTime <= m_bulletShotWaitTimeCount) {
			m_bulletShotWaitTimeCount = 0.0f;
			return true;
		}
		return false;
	}
	void AIchan::RandomBulletShot() {
		bool fire = true;
		SetFire(true, true);

		auto thisQuat = GetComponent<Transform>()->GetQuaternion();

		if (m_target) {
			auto front = m_target->GetPosition() - GetComponent<Transform>()->GetPosition();
			thisQuat.facing(front);
		}

		if (m_newBulletNum == 1) {
			WeaponOFire(fire, thisQuat);
		}
		else if (m_newBulletNum == 2) {
			WeaponTFire(fire, thisQuat);
		}
	}

	void AIchan::CreateDebugObject() {
		auto stage = GetStage();
		for (auto& point : m_aiParam.points) {
			m_debugObjects.push_back(stage->AddGameObject<PointObject>(point, Vec3(1.0f)));
		}
	}
	void AIchan::UpdateDebugObject() {
		auto red = Col4(1.0f, 0.0f, 0.0f, 1.0f);
		auto blue = Col4(0.0f, 0.0f, 1.0f, 1.0f);
		auto newPointObject = m_debugObjects[m_pointIndex];
		newPointObject->SetColor(red);

		auto oldPointObject = m_debugObjects[m_pointIndex >= 0 ? (m_pointIndex == 0 ? m_debugObjects.size() - 1 : m_pointIndex - 1) : 0];
		oldPointObject->SetColor(blue);
	}


	//------------------------------------------------------------------------------------------------
	//アイちゃんポイント巡回ステート : Class
	//------------------------------------------------------------------------------------------------

	shared_ptr<SeekPatrolState> SeekPatrolState::Instance() {
		static shared_ptr<SeekPatrolState> instance(new SeekPatrolState);
		return instance;
	}

	void SeekPatrolState::Enter(const shared_ptr<AIchan>& Obj) {
		auto param = Obj->GetAiParam();
		Obj->SetPointPatrolWaitTime(Obj->RandomNumber(0, param.pointPatrolMaxWaitTime));
		Obj->SetPointPatrolJumpWaitTime(Obj->RandomNumber(0, param.pointPatrolJumpMaxWaitTime));
	}

	void SeekPatrolState::Execute(const shared_ptr<AIchan>& Obj) {
		auto param = Obj->GetAiParam();

		//決められたポイントを順番に巡回する
		if (Obj->ThisToTargetAllowable(param.pointAllowable, Obj->GetPoint(), true)) {
			if (Obj->PointChangePermission()) {
				Obj->SetPointPatrolWaitTime(Obj->RandomNumber(0, param.pointPatrolMaxWaitTime));
				Obj->ChangeNextPoint();
			}
		}
		else
		{
			Obj->Move(Obj->GetPoint());
		}

		if (Obj->pointJumpPermission()) {
			//Obj->Jump(Vec3(0.0f, param.pointPatrolJumpPower, 0.0f));
			//Obj->SetPointPatrolJumpWaitTime(Obj->RandomNumber(0, param.pointPatrolJumpMaxWaitTime));
		}


		//キャラクタが一定の距離近づいてきたらSeekDiscoveryStateに移行する
		auto closest = Obj->GetClosestCharacterTransform();
		if (closest) {
			auto distance = Obj->GetThisToTargetDistance(closest->GetPosition());
			if (distance < param.SearchRadius) {
				Obj->SetTarget(closest);
				Obj->SetTargetType(AIChan::AITargetType::IS_NEAR);
				Obj->GetStateMachine()->ChangeState(SeekDiscoveryState::Instance());
			}
		}

		//Obj->ObstacleJump();
	}

	void SeekPatrolState::Exit(const shared_ptr<AIchan>& Obj) {

	}


	//------------------------------------------------------------------------------------------------
	//アイちゃん敵追尾ステート : Class
	//------------------------------------------------------------------------------------------------

	shared_ptr<SeekDiscoveryState> SeekDiscoveryState::Instance() {
		static shared_ptr<SeekDiscoveryState> instance(new SeekDiscoveryState);
		return instance;
	}

	void SeekDiscoveryState::Enter(const shared_ptr<AIchan>& Obj) {
		auto param = Obj->GetAiParam();
		//もし自身の吹っ飛び率が高い場合に戦うか逃げるかの判断
		if (Obj->GetDamage() >= param.escapeDamage) {
			Obj->UpdateEscapeMode();
			if (!Obj->GetEscapeMode()) {
				//Obj->SetTarget(NULL);
				//Obj->GetStateMachine()->ChangeState(SeekEscapeState::Instance());
			}
		}

		Obj->SetBulletChangeTime(Obj->RandomNumber(0, param.bulletChangeMaxTime));
		Obj->SetBulletShotWaitTime(Obj->RandomNumber(0, param.bulletShotMaxWaitTime));
	}

	void SeekDiscoveryState::Execute(const shared_ptr<AIchan>& Obj) {
		auto target = Obj->GetTarget();
		if (target) {
			Obj->Move(target->GetPosition());

			//もしターゲットのタイプが近くにいた場合
			if (Obj->GetTargetType() == AIChan::AITargetType::IS_NEAR) {
				auto param = Obj->GetAiParam();
				auto distance = Obj->GetThisToTargetDistance(target->GetPosition());
				if (distance >= param.LoseRadius) {
					Obj->SetTarget(NULL);
					Obj->GetStateMachine()->ChangeState(SeekPatrolState::Instance());
				}
			}
		}

		auto cP = Obj->BulletChangePermission();
		if (cP) {
			Obj->RandomBulletSelect();
		}
		auto sP = Obj->BulletShotPermission();
		if (sP) {
		}
		Obj->RandomBulletShot();

		//Obj->ObstacleJump();
	}

	void SeekDiscoveryState::Exit(const shared_ptr<AIchan>& Obj) {

	}


	//------------------------------------------------------------------------------------------------
	//アイちゃん逃げるステート : Class
	//------------------------------------------------------------------------------------------------

	shared_ptr<SeekEscapeState> SeekEscapeState::Instance() {
		static shared_ptr<SeekEscapeState> instance(new SeekEscapeState);
		return instance;
	}

	void SeekEscapeState::Enter(const shared_ptr<AIchan>& Obj) {
		
	}

	void SeekEscapeState::Execute(const shared_ptr<AIchan>& Obj) {
		
	}

	void SeekEscapeState::Exit(const shared_ptr<AIchan>& Obj) {

	}


	//------------------------------------------------------------------------------------------------
	//ポイントデバッグ用 : Class
	//------------------------------------------------------------------------------------------------

	void PointObject::OnCreate() {
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetEmissive(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void PointObject::SetColor(const Col4& color) {
		auto ptrDraw = GetComponent<PNTStaticDraw>();
		ptrDraw->SetEmissive(color);
	}


	//------------------------------------------------------------------------------------------------
	//テスト障害物 : Class
	//------------------------------------------------------------------------------------------------

	void TestObstacle::OnCreate() {
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetScale(m_scale);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetEmissive(Col4(0.0f, 1.0f, 0.0f, 1.0f));
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
	}
}
//end basecross
