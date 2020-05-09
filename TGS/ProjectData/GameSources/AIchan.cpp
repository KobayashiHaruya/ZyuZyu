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
		m_stateMachine->Update();

		if (m_aiParam.isDebug) UpdateDebugObject();
	}

	void AIchan::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		Character::OnCollisionEnter(Other);
		if (Other->FindTag(L"Character")) {
			//m_stateMachine->ChangeState(SeekDiscoveryState::Instance());
		}
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
	}

	Vec3 AIchan::GetNextPoint() {
		if (m_aiParam.points.size() - 1 > m_pointIndex) {
			m_pointIndex++;
			return m_aiParam.points[m_pointIndex];
		}
		m_pointIndex = 0;
		return m_aiParam.points[m_pointIndex];
	}

	void AIchan::SetNextPoint() {
		if (ThisToTargetAllowable(m_point) && WaitCount()) {
			m_point = GetNextPoint();
		}
		else
		{
			m_point = m_aiParam.points[m_pointIndex];
		}
		Move(m_point);
	}

	bool AIchan::ThisToTargetAllowable(const Vec3& target) {
		Vec3& thisPos = GetComponent<Transform>()->GetPosition();
		Vec3 targetPos = target;
		thisPos.y = 0.0f;
		targetPos.y = 0.0f;
		float distance = (targetPos - thisPos).length();
		return (distance < m_aiParam.pointAllowable) ? true : false;
	}

	float AIchan::GetThisToTargetDistance(const Vec3& targetPos) {
		Vec3& thisPos = GetComponent<Transform>()->GetPosition();
		return (targetPos - thisPos).length();
	}

	bool AIchan::WaitCount() {
		if (m_aiParam.pointPatrolWaitTime != 0.0f) {
			m_pointWaitTimeCount += App::GetApp()->GetElapsedTime();

			if (m_aiParam.pointPatrolWaitTime <= m_pointWaitTimeCount) {
				m_pointWaitTimeCount = 0.0f;
				return true;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	vector<shared_ptr<Transform>> AIchan::GetCharacterTransforms() {
		vector<shared_ptr<Transform>> transforms;
		auto group = GetStage()->GetSharedObjectGroup(L"CharacterGroup");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto obj = v.lock();
			if (obj) {
				auto character = dynamic_pointer_cast<Character>(obj);
				if (character && character->GetMyData().unique != GetMyData().unique) {
					transforms.push_back(character->GetComponent<Transform>());
				}
			}
			
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

	unsigned int AIchan::RandomNumber(const unsigned int& min, const unsigned int& max) {
		mt19937_64 mt{ random_device{}() };
		uniform_int_distribution<unsigned int> dist(min, max);
		return dist(mt);
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
		m_newBulletNum = RandomNumber(1, m_bulletMaxPossession);
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
		auto trans = GetComponent<Transform>();
		auto my = GetMyData();
		auto id = GetId();
		if (m_newBulletNum == 1) {
			auto w = GetWeaponO();
			if (w == BulletS::Shot) {
				for (size_t i = 0; i < 1; i++)
				{
					auto bullet = GetStage()->AddGameObject<Bullet>(
						trans->GetPosition(),
						trans->GetQuaternion(),
						(BulletS)w,
						my.unique,
						id,
						my
						);

					bullet->AddEvent([this](const CharacterStatus_s status) {
						DroppedIntoOil(status);
					});
				}
			}
			else
			{
				auto bullet = GetStage()->AddGameObject<Bullet>(
					trans->GetPosition(),
					trans->GetQuaternion(),
					(BulletS)w,
					my.unique,
					id,
					my
					);

				bullet->AddEvent([this](const CharacterStatus_s status) {
					DroppedIntoOil(status);
				});
			}
		}
		else if (m_newBulletNum == 2) {
			
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

	}

	void SeekPatrolState::Execute(const shared_ptr<AIchan>& Obj) {
		Obj->SetNextPoint();
		auto aiParam = Obj->GetAiParam();
		auto closest = Obj->GetClosestCharacterTransform();
		if (closest) {
			auto distance = Obj->GetThisToTargetDistance(closest->GetPosition());
			if (distance < aiParam.SearchRadius) {
				Obj->SetTarget(closest);
				Obj->GetStateMachine()->ChangeState(SeekDiscoveryState::Instance());
			}
		}
	}

	void SeekPatrolState::Exit(const shared_ptr<AIchan>& Obj) {

	}


	//------------------------------------------------------------------------------------------------
	//アイちゃんポイント敵発見ステート : Class
	//------------------------------------------------------------------------------------------------

	shared_ptr<SeekDiscoveryState> SeekDiscoveryState::Instance() {
		static shared_ptr<SeekDiscoveryState> instance(new SeekDiscoveryState);
		return instance;
	}

	void SeekDiscoveryState::Enter(const shared_ptr<AIchan>& Obj) {
		auto param = Obj->GetAiParam();
		Obj->SetBulletChangeTime(Obj->RandomNumber(0, param.bulletChangeMaxTime));
		Obj->SetBulletShotWaitTime(Obj->RandomNumber(0, param.bulletShotMaxWaitTime));
	}

	void SeekDiscoveryState::Execute(const shared_ptr<AIchan>& Obj) {
		auto target = Obj->GetTarget();
		if (target) {
			Obj->Move(target->GetPosition());
			auto aiParam = Obj->GetAiParam();
			auto distance = Obj->GetThisToTargetDistance(target->GetPosition());
			if (distance >= aiParam.LoseRadius) {
				Obj->SetTarget(NULL);
				Obj->GetStateMachine()->ChangeState(SeekPatrolState::Instance());
			}
		}

		auto cP = Obj->BulletChangePermission();
		if (cP) {
			Obj->RandomBulletSelect();
		}
		auto sP = Obj->BulletShotPermission();
		if (sP) {
			Obj->RandomBulletShot();
		}
	}

	void SeekDiscoveryState::Exit(const shared_ptr<AIchan>& Obj) {

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

}
//end basecross
