/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "Weapon.h"

namespace basecross{

	class Character : public GameObject {
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

		int m_gatlingAmmo = 150;
		int m_gatlingPickAmmo = 30;
		int m_gatlingBombAmmo = 150;
		float m_gatlingShotAmmo;
		float m_gatlingCoolMaxTime = 5.0f;
		float m_gatlingCoolTime = 0.0f;
		float m_intTimeGat = 0.01;
		bool m_setGun = false;
		bool m_cannonAmmo = false;
		bool m_setGunType;
		Vec3 m_setGunPos;

		bool m_torimoti = false;
		bool m_smoke = false;
		bool m_toriIn = false;
		bool m_smokeIn = false;

		float m_Gtime = 4.0f;
		float m_smokeGtime = 4.0f;
		float m_toriGtime = 4.0f;
		bool m_smokeG = true;
		bool m_toriG = true;

		bool m_fire = true;
		bool m_reload = false;

		float m_damage = 0.0f;

		float m_moveSpeed;
		float m_defaultSpeed;
		float m_rotSpeed = 2.0f;
		float m_gravityScale;
		float m_jumpPower;
		int ID;
		float t;
		Vec2 m_force;
		bool m_des = false;
		bool m_jump = false;

		CharacterStatus_s m_myData;
		vector<CharacterKillDetails_s> m_killCharacters;  //自身がキルした相手のキャラクタータイプとレベルを持つ
		vector<CharacterKillList_s> m_killList;

		shared_ptr<ObstacleEvent<const CharacterStatus_s>> m_touchOil;
		CharacterStatus_s m_opponent;  //自身を攻撃してきた相手のステータスを持つ

	public:

		Character(const shared_ptr<Stage>& StagePtr,
			const CharacterType type,
			const bool isPlayer,
			const unsigned int unique,
			const int& id
		) :
			GameObject(StagePtr),
			m_myData({ type, 1, NULL, NULL, NULL, isPlayer, unique }),
			m_killCharacters(vector<CharacterKillDetails_s>(NULL)),
			m_touchOil(NULL),
			ID(unique),
			m_opponent({})
		{}
		~Character() {}

		virtual void BmfDateRead(wstring model);
		void Draw();
		void PlayerCamera();
		void PlayerMove();
		void PlayerRotMove();
		void PlayerUI();
		void PlayerMovement();

		void PickGun(int state);

		void Respawn();
		void GrenadeFire();
		void BulletDamage(int state, Vec3 rot);
		void BulletFire();
		void SetWeaponFire();
		void BulletState(int state, bool weapon, bool same = false);
		void CharaState();
		void AttackHit(Vec3 rot);

		void DrawString();

		void Torimoti(bool hit) {
			if (hit) {
				m_defaultSpeed = 0.0f;
			}
			else {
				m_defaultSpeed = m_moveSpeed;
			}
		}
		int GetAmmoO() {
			return m_ammoO;
		}
		int GetAmmoT() {
			return m_ammoT;
		}
		int GetDAmmoO() {
			return m_maxAmmoO;
		}
		int GetDAmmoT() {
			return m_maxAmmoT;
		}
		int GetGatlingAmmo() {
			return m_gatlingAmmo;
		}
		bool GetGun() {
			return m_weapon;
		}
		int GetWeaponO() {
			return (int)m_weaponO;
		}
		int GetWeaponT() {
			return (int)m_weaponT;
		}
		float GetSGTime() {
			return m_smokeGtime;
		}
		float GetTGTime() {
			return m_toriGtime;
		}
		float GetDamage() {
			return m_damage;
		}

		int GetId() {
			return m_myData.unique;
		}

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void TouchOil();
		void DroppedIntoOil(const CharacterStatus_s& status);
		void ShowMyPinP();
		void PinPUpdate();

		vector<CharacterKillDetails_s> GetKillCharacters();
		vector<CharacterKillList_s> GetKillList();
		void AddKillCharacter(const CharacterKillDetails_s& data);
		CharacterStatus_s GetMyData();
		void SetMyData(const CharacterStatus_s& data);
		void AddScore(const int score);
		void SetLevel(const unsigned int level);
		void AddLevel();
		void AddKill(const int kill);
		void AddDeath(const int death);
	};

	class Player :public Character {
	public:
		Player(const shared_ptr<Stage>& StagePtr,
			const CharacterType type,
			const bool isPlayer,
			const int unique,
			const int& id
		) :
			Character(StagePtr,
			type,
			isPlayer,
			unique,
				id
			)
		{}
		~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


	class Enemy : public Character {
	public:
		Enemy(const shared_ptr<Stage>& StagePtr,
			const CharacterType type,
			const bool isPlayer,
			const int unique,
			const int& id
		) :
			Character(StagePtr,
				type,
				isPlayer,
				unique,
				id
			)
		{}
		~Enemy() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


}
//end basecross
