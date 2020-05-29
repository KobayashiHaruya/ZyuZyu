/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "Weapon.h"

namespace basecross{

	typedef struct CharacterWeapon {
		BulletS weapon;
		bool barrage;
		int ammo;
		int maxAmmo;
		int reAmmo;
		float intTime;
		float maxIntTime;
		float reTime;
		float maxreTime;
	} CharacterWeapon_s;


	class Character : public GameObject {
		enum Anim
		{
			stop,
			walk
		};

		Vec3 m_modelPos;
		Vec3 m_modelRot;
		Vec3 m_modelScale;

		wstring m_modelName;

		bool m_weapon = true;

		bool m_fire = true;
		bool m_reload = false;

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
		Anim m_eAnim = Anim::stop;
		bool m_anim = false;

		CharacterStatus_s m_myData;
		vector<CharacterKillDetails_s> m_killCharacters;  //自身がキルした相手のキャラクタータイプとレベルを持つ
		vector<int> m_killList;

		vector<WeaponState_s> m_weaponState;
		CharacterWeapon_s m_WeaponO;
		CharacterWeapon_s m_WeaponT;

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
			m_myData({ type, 1, 0, 0, 0, isPlayer, unique }),
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
		void WeaponOFire(bool fire);
		void WeaponTFire(bool fire);
		void SetWeaponFire();
		void BulletState(int state, bool weapon, bool same = false);
		void CharaState();
		void AttackHit(Vec3 rot);

		void DrawString();

		void Animation() {
			auto PtrDraw = GetComponent<BcPNTBoneModelDraw>();
			if (m_eAnim == Anim::walk && m_anim) {
				PtrDraw->ChangeCurrentAnimation(L"Walk");
				m_anim = false;
			}
			else if (m_eAnim == Anim::stop && !m_anim) {
				PtrDraw->ChangeCurrentAnimation(L"Stop");
				m_anim = true;
			}
		}
		void Torimoti(bool hit) {
			if (hit) {
				m_defaultSpeed = 0.0f;
			}
			else {
				m_defaultSpeed = m_moveSpeed;
			}
		}
		int GetAmmoO() {
			return m_WeaponO.ammo;
		}
		int GetAmmoT() {
			return m_WeaponT.ammo;
		}
		int GetDAmmoO() {
			return m_WeaponO.maxAmmo;
		}
		int GetDAmmoT() {
			return m_WeaponT.maxAmmo;
		}
		int GetGatlingAmmo() {
			return m_gatlingAmmo;
		}
		bool GetGun() {
			return m_weapon;
		}
		int GetWeaponO() {
			return (int)m_WeaponO.weapon;
		}
		int GetWeaponT() {
			return (int)m_WeaponT.weapon;
		}
		CharacterWeapon_s GetWeaponOState() {
			return m_WeaponO;
		}
		CharacterWeapon_s GetWeaponTState() {
			return m_WeaponT;
		}
		void SetWeaponOState(int type,float value) {

			switch (type)
			{
			case 0:
				m_WeaponO.weapon = (BulletS)(int)value;
				break;
			case 1:
				m_WeaponO.barrage = (bool)value;
				break;
			case 2:
				m_WeaponO.ammo = value;
				break;
			case 3:
				m_WeaponO.maxAmmo = value;
				break;
			case 4:
				m_WeaponO.reAmmo = value;
				break;
			case 5:
				m_WeaponO.intTime = value;
				break;
			case 6:
				m_WeaponO.maxIntTime = value;
				break;
			case 7:
				m_WeaponO.reTime = value;
				break;
			case 8:
				m_WeaponO.maxreTime = value;
				break;
			default:
				break;
			}


		}
		void SetWeaponTState(int type, float value) {

			switch (type)
			{
			case 0:
				m_WeaponT.weapon = (BulletS)(int)value;
				break;
			case 1:
				m_WeaponT.barrage = (bool)value;
				break;
			case 2:
				m_WeaponT.ammo = value;
				break;
			case 3:
				m_WeaponT.maxAmmo = value;
				break;
			case 4:
				m_WeaponT.reAmmo = value;
				break;
			case 5:
				m_WeaponT.intTime = value;
				break;
			case 6:
				m_WeaponT.maxIntTime = value;
				break;
			case 7:
				m_WeaponT.reTime = value;
				break;
			case 8:
				m_WeaponT.maxreTime = value;
				break;
			default:
				break;
			}

		}
		void SetFire(bool fire, bool type) {
			if (type) {
				m_fire = fire;
			}
			else {
				m_reload = fire;
			}
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
		float GetJumpPower() {
			return m_jumpPower;
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
		vector<int> GetKillList();
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
