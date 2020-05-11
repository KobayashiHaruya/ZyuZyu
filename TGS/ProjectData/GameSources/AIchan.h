/*!
@file AIchan.h
@brief AI
*/

#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Character.h"
#include "Scene.h"

#include <random>

namespace basecross{

	//------------------------------------------------------------------------------------------------
	//�|�C���g�f�o�b�O�p : Class
	//------------------------------------------------------------------------------------------------

	class PointObject : public GameObject {
		Vec3 m_pos;
		Vec3 m_scale;

	public:
		PointObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& scale
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_scale(scale)
		{}
		~PointObject() {}

		virtual void OnCreate() override;

		void SetColor(const Col4& color);
	};

	//------------------------------------------------------------------------------------------------
	//�A�C�����p : struct
	//------------------------------------------------------------------------------------------------

	typedef struct AIParam {
		vector<Vec3> points;             //����|�C���g
		float pointAllowable;            //����|�C���g�ɂǂꂭ�炢�߂Â����玟�̏���|�C���g�ɐ؂�ւ��邩�̒l�B�l���������قǃ|�C���g�ɋ߂Â��Ȃ��Ƃ����Ȃ�
		float pointPatrolMoveSpeed;      //���񎞂̈ړ����x
		float pointPatrolRotSpeed;       //���񎞂̉�]���x
		int pointPatrolMaxWaitTime;      //���񎞂Ɏ��̃|�C���g�ɐ؂�ւ���܂ł̍ő�ҋ@���ԁi�b�j
		float pointPatrolJumpPower;      //���񎞂̃W�����v��
		int pointPatrolJumpMaxWaitTime;  //���񎞂Ƀ����_���ŃW�����v����ő�ҋ@���ԁi�b�j
		float SearchRadius;              //���G�͈́i���a�j
		float LoseRadius;                //�G�����͈͈̔ȏ㗣���ƌ������i���a�j
		int bulletChangeMaxTime;         //������ǂꂭ�炢�̎��ԂŐ؂�ւ��鏈�������邩�̍ő厞�ԁi�b�j
		int bulletShotMaxWaitTime;       //�����Ă��玟�̌��܂ł̍ő�ҋ@���ԁi�b�j
		int escapeMode;                  //������ї��������Ƃ��̓����i0: �����邩�키���������_���Ō��߂�, 1: �K���키, 2: �K��������j
		float escapeDamage;              //���̒l�ɂȂ�Ɛ�����ї����瓦���邩�키����escapeMode�ɂ���Ĕ��f����
		bool isDebug;                    //�L���ɂ���Ə���|�C���g����������
	} AIParam_s;


	//------------------------------------------------------------------------------------------------
	//�A�C�����{�� : Class
	//------------------------------------------------------------------------------------------------

	class AIchan : public Character {
		AIParam_s m_aiParam;  //�p�����[�^
		unique_ptr<StateMachine<AIchan>> m_stateMachine;  //�X�e�[�g�}�V��


		////////����Ɋւ��郁���o�ϐ� - ��������////////
		Vec3 m_point;
		int m_pointIndex;
		float m_pointPatrolWaitTime;
		float m_pointPatrolWaitTimeCount;
		float m_pointPatrolJumpWaitTime;
		float m_pointPatrolJumpWaitTimeCount;
		////////����Ɋւ��郁���o�ϐ� - �����܂�////////


		////////�L�����N�^��ǂ�������Ɋւ��郁���o�ϐ� - ��������////////
		shared_ptr<Transform> m_target;
		////////�L�����N�^��ǂ�������Ɋւ��郁���o�ϐ� - �����܂�////////


		////////����Ɋւ��郁���o�ϐ� - ��������////////
		int m_bulletNum;
		int m_bulletMaxPossession;
		int m_newBulletNum;
		int m_oldBulletNum;
		float m_bulletChangeTime;
		float m_bulletChangeTimeCount;
		float m_bulletShotWaitTime;
		float m_bulletShotWaitTimeCount;
		////////����Ɋւ��郁���o�ϐ� - �����܂�////////


		////////�f�o�b�O�Ɋւ��郁���o�ϐ��Ɗ֐� - ��������////////
		vector<shared_ptr<PointObject>> m_debugObjects;
		void CreateDebugObject();
		void UpdateDebugObject();
		////////�f�o�b�O�Ɋւ��郁���o�ϐ��Ɗ֐� - �����܂�////////

	public:
		AIchan(const shared_ptr<Stage>& StagePtr,
			const CharacterType type,
			const bool isPlayer,
			const int unique,
			const int& id,
			const AIParam_s& aiParam
		) :
			Character(StagePtr,
				type,
				isPlayer,
				unique,
				id
			),
			m_aiParam(aiParam),
			m_point(NULL),
			m_pointIndex(NULL),
			m_debugObjects(NULL),
			m_pointPatrolWaitTime(NULL),
			m_pointPatrolWaitTimeCount(NULL),
			m_pointPatrolJumpWaitTime(NULL),
			m_pointPatrolJumpWaitTimeCount(NULL),
			m_target(NULL),
			m_bulletNum(9),
			m_bulletMaxPossession(2),
			m_newBulletNum(NULL),
			m_oldBulletNum(NULL),
			m_bulletChangeTimeCount(NULL)
		{}
		~AIchan() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;

		void Move(const Vec3& toPos);
		void Jump(const Vec3& jumpVelocity);
		bool ThisToTargetAllowable(const float allowable, const Vec3& target, const bool isPlane = false);
		float GetThisToTargetDistance(const Vec3& target, const bool isPlane = false);
		vector<shared_ptr<Character>> GetCharacters();
		vector<shared_ptr<Transform>> GetCharacterTransforms();
		shared_ptr<Transform> GetClosestCharacterTransform();
		shared_ptr<Character> GetCharacterByID(const int id);
		unsigned int RandomNumber(const unsigned int& min, const unsigned int& max);

		Vec3 GetNextPoint();
		void ChangeNextPoint();
		bool PointChangePermission();
		bool pointJumpPermission();

		bool BulletChangePermission();
		void RandomBulletSelect();
		bool BulletShotPermission();
		void RandomBulletShot();

		AIParam_s GetAiParam() {
			return m_aiParam;
		}

		unique_ptr<StateMachine<AIchan>>& GetStateMachine() {
			return m_stateMachine;
		}

		Vec3 GetPoint() {
			return m_point;
		}
		void SetPoint(const Vec3& point) {
			m_point = point;
		}

		shared_ptr<Transform> GetTarget() {
			return m_target;
		}
		void SetTarget(const shared_ptr<Transform>& trans) {
			m_target = trans;
		}

		float GetPointPatrolWaitTime() {
			return m_pointPatrolWaitTime;
		}
		void SetPointPatrolWaitTime(const float pointPatrolWaitTime) {
			m_pointPatrolWaitTime = pointPatrolWaitTime;
		}

		float GetPointPatrolJumpWaitTime() {
			return m_pointPatrolJumpWaitTime;
		}
		void SetPointPatrolJumpWaitTime(const float pointPatrolJumpWaitTime) {
			m_pointPatrolJumpWaitTime = pointPatrolJumpWaitTime;
		}

		float GetBulletChangeTime() {
			return m_bulletChangeTime;
		}
		void SetBulletChangeTime(const float bulletChangeTime) {
			m_bulletChangeTime = bulletChangeTime;
		}

		float GetBulletShotWaitTime() {
			return m_bulletShotWaitTime;
		}
		void SetBulletShotWaitTime(const float bulletShotWaitTime) {
			m_bulletShotWaitTime = bulletShotWaitTime;
		}
	};


	//------------------------------------------------------------------------------------------------
	//�A�C�����|�C���g����X�e�[�g : Class
	//------------------------------------------------------------------------------------------------

	class SeekPatrolState : public ObjState<AIchan> {
		SeekPatrolState() {}
	public:
		static shared_ptr<SeekPatrolState> Instance();
		virtual void Enter(const shared_ptr<AIchan>& Obj)override;
		virtual void Execute(const shared_ptr<AIchan>& Obj)override;
		virtual void Exit(const shared_ptr<AIchan>& Obj)override;
	};


	//------------------------------------------------------------------------------------------------
	//�A�C�����G�����X�e�[�g : Class
	//------------------------------------------------------------------------------------------------

	class SeekDiscoveryState : public ObjState<AIchan> {
		SeekDiscoveryState() {}
	public:
		static shared_ptr<SeekDiscoveryState> Instance();
		virtual void Enter(const shared_ptr<AIchan>& Obj)override;
		virtual void Execute(const shared_ptr<AIchan>& Obj)override;
		virtual void Exit(const shared_ptr<AIchan>& Obj)override;
	};


	//------------------------------------------------------------------------------------------------
	//�A�C����񓦂���X�e�[�g : Class
	//------------------------------------------------------------------------------------------------

	class SeekEscapeState : public ObjState<AIchan> {
		SeekEscapeState() {}
	public:
		static shared_ptr<SeekEscapeState> Instance();
		virtual void Enter(const shared_ptr<AIchan>& Obj)override;
		virtual void Execute(const shared_ptr<AIchan>& Obj)override;
		virtual void Exit(const shared_ptr<AIchan>& Obj)override;
	};
}
//end basecross
