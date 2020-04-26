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
		Vec3 m_modelPos;
		Vec3 m_modelRot;
		Vec3 m_modelScale;

		wstring m_modelName;

		BulletS m_weaponO;
		BulletS m_weaponT;

		bool m_weapon = true;
		bool m_barrageO;
		bool m_barrageT;

		int m_ammoO;
		int m_maxAmmoO;
		int m_reAmmoO;
		float m_intTimeO;
		float m_maxIntTimeO;
		float m_reTimeO;
		float m_maxreTimeO;

		int m_ammoT;
		int m_maxAmmoT;
		int m_reAmmoT;
		float m_intTimeT;
		float m_maxIntTimeT;
		float m_reTimeT;
		float m_maxreTimeT;

		bool m_fire = true;
		bool m_reload = false;

		float m_moveSpeed;
		float m_defaultSpeed;
		float m_rotSpeed = 2.0f;
		float m_gravityScale;
		float m_jumpPower;
		int ID;

		Vec2 m_force;
		bool m_des = false;
		bool m_jump = true;

		CharacterStatus_s m_myData;
		vector<CharacterKillDetails_s> m_killCharacters;  //自身がキルした相手のキャラクタータイプとレベルを持つ

		shared_ptr<ObstacleEvent<const CharacterStatus_s>> m_touchOil;

	public:

		Character(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const CharacterType type,
			const bool isPlayer,
			const unsigned int unique,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_myData({ type, 1, NULL, NULL, NULL, isPlayer, unique }),
			m_killCharacters(vector<CharacterKillDetails_s>(NULL)),
			m_touchOil(NULL),
			ID(id)
		{}
		~Character() {}

		virtual void BmfDateRead(wstring model);
		void Draw();
		void PlayerCamera();
		void PlayerMove();
		void PlayerRotMove();
		void Respawn();
		void Weapons();
		void BulletDamage(int state, Vec3 rot);
		void BulletFire();
		void BulletState(BulletS state,bool weapon);
		void CharaState();

		void DrawString();

		void Torimoti(bool hit) {
			if (hit) {
				m_defaultSpeed = m_moveSpeed / 2.0f;
			}
			else {
				m_defaultSpeed = m_moveSpeed;
			}

		}

		void AttackHit(Vec3 rot);

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
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
			const CharacterType type,
			const bool isPlayer,
			const int unique,
			const int& id
		) :
			Character(StagePtr,
			pos,
			rot,
			scale,
			type,
			isPlayer,
			unique,
				id
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
			const CharacterType type,
			const bool isPlayer,
			const int unique,
			const int& id
		) :
			Character(StagePtr,
				pos,
				rot,
				scale,
				type,
				isPlayer,
				unique,
				id
			)
		{}
		~TestEnemy() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


}
//end basecross
