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
	//ポイントデバッグ用 : Class
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
	//アイちゃん用 : struct
	//------------------------------------------------------------------------------------------------

	typedef struct AIParam {
		vector<Vec3> points;             //巡回ポイント
		float pointAllowable;            //巡回ポイントにどれくらい近づいたら次の巡回ポイントに切り替えるかの値。値が小さいほどポイントに近づかないといけない
		float pointPatrolMoveSpeed;      //巡回時の移動速度
		float pointPatrolRotSpeed;       //巡回時の回転速度
		int pointPatrolMaxWaitTime;      //巡回時に次のポイントに切り替えるまでの最大待機時間（秒）
		float pointPatrolJumpPower;      //巡回時のジャンプ力
		int pointPatrolJumpMaxWaitTime;  //巡回時にランダムでジャンプする最大待機時間（秒）
		float SearchRadius;              //索敵範囲（半径）
		float LoseRadius;                //敵がこの範囲以上離れると見失う（半径）
		int bulletChangeMaxTime;         //武器をどれくらいの時間で切り替える処理をするかの最大時間（秒）
		int bulletShotMaxWaitTime;       //撃ってから次の撃つまでの最大待機時間（秒）
		int escapeMode;                  //吹っ飛び率が高いときの動き（0: 逃げるか戦うかをランダムで決める, 1: 必ず戦う, 2: 必ず逃げる）
		float escapeDamage;              //この値になると吹っ飛び率から逃げるか戦うかをescapeModeによって判断する
		bool isDebug;                    //有効にすると巡回ポイントを可視化する
	} AIParam_s;


	//------------------------------------------------------------------------------------------------
	//アイちゃん本体 : Class
	//------------------------------------------------------------------------------------------------

	class AIchan : public Character {
		AIParam_s m_aiParam;  //パラメータ
		unique_ptr<StateMachine<AIchan>> m_stateMachine;  //ステートマシン


		////////巡回に関するメンバ変数 - ここから////////
		Vec3 m_point;
		int m_pointIndex;
		float m_pointPatrolWaitTime;
		float m_pointPatrolWaitTimeCount;
		float m_pointPatrolJumpWaitTime;
		float m_pointPatrolJumpWaitTimeCount;
		////////巡回に関するメンバ変数 - ここまで////////


		////////キャラクタを追いかけるに関するメンバ変数 - ここから////////
		shared_ptr<Transform> m_target;
		////////キャラクタを追いかけるに関するメンバ変数 - ここまで////////


		////////武器に関するメンバ変数 - ここから////////
		int m_bulletNum;
		int m_bulletMaxPossession;
		int m_newBulletNum;
		int m_oldBulletNum;
		float m_bulletChangeTime;
		float m_bulletChangeTimeCount;
		float m_bulletShotWaitTime;
		float m_bulletShotWaitTimeCount;
		////////武器に関するメンバ変数 - ここまで////////


		////////デバッグに関するメンバ変数と関数 - ここから////////
		vector<shared_ptr<PointObject>> m_debugObjects;
		void CreateDebugObject();
		void UpdateDebugObject();
		////////デバッグに関するメンバ変数と関数 - ここまで////////

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
	//アイちゃんポイント巡回ステート : Class
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
	//アイちゃん敵発見ステート : Class
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
	//アイちゃん逃げるステート : Class
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
