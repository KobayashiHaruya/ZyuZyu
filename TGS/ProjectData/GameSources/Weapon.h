#pragma once
#include "stdafx.h"

namespace basecross {

	template<typename... T>
	class ObstacleEvent {
		vector<function<void(T...)>> m_fromEvents;
	public:
		ObstacleEvent() :
			m_fromEvents(vector<function<void(T...)>>(0))
		{};
		~ObstacleEvent() {};
		void AddEvent(const function<void(T...)>& event) {
			m_fromEvents.push_back(event);
		}
		void Run(T... args) {
			for (auto& event : m_fromEvents) event(args...);
		}
	};


	enum BulletS {
		None,
		Assault,
		Hand,
		Shot,
		SMG,
		Rocket,
		Sniper,
		Laser,
		Wind,
		Gatling,
		Cannon,
		GExplosion,
		CExplosion,
		SExplosion
	};

	class Bullet :public GameObject, public ObstacleEvent<const CharacterStatus_s> {
		Vec3 m_pos;
		Quat m_rot;
		Vec3 m_scale;

		BulletS m_type;

		float m_moveSpeed;
		float m_gravityScale;
		float m_time;
		int ID;

		int m_fromUnique;

		CharacterStatus_s m_frome;

	public:

		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const BulletS& type,
			const unsigned int fromUnique,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_type(type),
			m_fromUnique(fromUnique),
			ID(id),
			m_frome(frome)
		{}
		~Bullet() {}

		void Draw();
		void Move();
		void Timer();
		void BulletState(BulletS state);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		unsigned int GetFromUnique() {
			return m_fromUnique;
		}

		CharacterStatus_s GetFrome() {
			return m_frome;
		}
	};


	class Weapon :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;

		int m_type;
		wstring text;
		wstring m_modelName;

	public:


		Weapon(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr) {}
		~Weapon() {}

		void Gun();
		void BmfDateRead(wstring model);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};


	class Grenade :public GameObject {
		Vec3 m_pos;
		Quat m_rot;
		float m_moveSpeed;
		float m_gravityScale;
		int ID;

		bool m_grenade;
			CharacterStatus_s m_frome;

	public:
		Grenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const float& speed,
			const float& gravity,
			const bool& grenade,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_grenade(grenade),
			ID(id),
			m_frome(frome)
		{}
		~Grenade() {}

		virtual void OnCreate() override;
		void Move();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};


	class SmokeGrenade :public GameObject {
		Vec3 m_pos;
		Quat m_rot;
		Vec3 m_scale;
		int ID;

		float m_time;
		CharacterStatus_s m_frome;

	public:
		SmokeGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const Vec3& scale,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			ID(id),
			m_frome(frome)
		{}
		~SmokeGrenade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Timer();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};


	class TorimotiGrenade :public GameObject {
		Vec3 m_pos;
		Quat m_rot;
		Vec3 m_scale;
		int ID;

		float m_time;
		CharacterStatus_s m_frome;

	public:
		TorimotiGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const Vec3& scale,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			ID(id),
			m_frome(frome)
		{}
		~TorimotiGrenade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Timer();

	};

	class GatlingAmmo :public GameObject {
		Vec3 m_pos;
		Quat m_qua;
		Vec3 m_scale = Vec3(1.0f);

		wstring m_modelName = L"CornGatling.bmf";

	public:
		GatlingAmmo(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos
		) :
			GameObject(StagePtr),
			m_pos(pos)
		{}
		~GatlingAmmo() {}

		virtual void BmfDateRead(wstring model);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class SetGun :public GameObject {
		Vec3 m_pos;
		Quat m_qua;
		Vec3 m_scale = Vec3(3.0f);

		bool m_gun;

	public:
		SetGun(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& quat,
			const bool& gun
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_qua(quat),
			m_gun(gun)
		{}
		~SetGun() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class GunSeat :public GameObject {
		Vec3 m_pos;
		Quat m_quat;
		Vec3 m_scale;

		bool m_gun;

	public:
		GunSeat(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& quat,
			const bool& gun
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_quat(quat),
			m_gun(gun)
		{}
		~GunSeat() {}

		virtual void OnCreate() override;

	};


}