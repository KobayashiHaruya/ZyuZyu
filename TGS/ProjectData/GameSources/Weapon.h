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
		Wind
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

	public:

		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const BulletS& type,
			const unsigned int fromUnique,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_type(type),
			m_fromUnique(fromUnique),
			ID(id)
		{}
		~Bullet() {}

		void Draw();
		void Move();
		void Timer();
		void Destroy();
		void BulletState(BulletS state);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		unsigned int GetFromUnique() {
			return m_fromUnique;
		}
	};


	class Grenade :public GameObject {
		Vec3 m_pos;
		Quat m_rot;
		float m_moveSpeed;
		float m_gravityScale;
		int ID;

		bool m_grenade;

	public:
		Grenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const float& speed,
			const float& gravity,
			const bool& grenade,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_grenade(grenade),
			ID(id)
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

	public:
		SmokeGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const Vec3& scale,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			ID(id)
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

	public:
		TorimotiGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const Vec3& scale,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			ID(id)
		{}
		~TorimotiGrenade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Timer();

	};


}