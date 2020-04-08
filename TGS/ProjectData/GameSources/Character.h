/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

#include "Weapon.h"

namespace basecross{

	class Character : public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_moveSpeed;
		float m_rotSpeed = 1.0f;
		float m_gravityScale;
		float m_jumpPower;

		float m_force = 1.0f;
		bool m_jump = true;

		CharacterStatus_s m_myData;
		vector<CharacterKillDetails_s> m_killCharacters;  //自身がキルした相手のキャラクタータイプとレベルを持つ

		shared_ptr<ObstacleEvent<const CharacterStatus_s>> m_touchOil;

	public:

		Character(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const float& jump,
			const CharacterType type,
			const bool isPlayer,
			const unsigned int unique
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_jumpPower(jump),
			m_myData({ type, 1, NULL, NULL, NULL, isPlayer, unique }),
			m_killCharacters(vector<CharacterKillDetails_s>(NULL)),
			m_touchOil(NULL)
		{}
		~Character() {}

		void Draw();
		void PlayerCamera();
		void PlayerMove();
		void PlayerRotMove();
		void BulletFire();
		void AttackHit(Vec3 rot);

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void TouchOil();
		void DroppedIntoOil(const CharacterStatus_s& status);

		vector<CharacterKillDetails_s> GetKillCharacters();
		void AddKillCharacter(const CharacterKillDetails_s& data);
		CharacterStatus_s GetMyData();
		void SetMyData(const CharacterStatus_s& data);
		void AddScore(const int score);
		void SetLevel(const unsigned int level);
		void AddKill(const int kill);
		void AddDeath(const int death);
	
	};


	class TestPlayer : public Character {
	public:
		TestPlayer(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const float& jump,
			const CharacterType type,
			const bool isPlayer,
			const int unique
		) :
			Character(StagePtr,
			pos,
			rot,
			scale,
			speed,
			gravity,
			jump,
			type,
			isPlayer,
			unique
			)
		{}
		~TestPlayer() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


	class TestEnemy : public Character {
	public:
		TestEnemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const float& jump,
			const CharacterType type,
			const bool isPlayer,
			const int unique
		) :
			Character(StagePtr,
				pos,
				rot,
				scale,
				speed,
				gravity,
				jump,
				type,
				isPlayer,
				unique
			)
		{}
		~TestEnemy() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


}
//end basecross
