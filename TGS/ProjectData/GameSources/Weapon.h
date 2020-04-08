#pragma once
#include "stdafx.h"

namespace basecross {

	template<typename... T>
	class ObstacleEvent {
		vector<function<void(T...)>> m_fromEvents;
	public:
		ObstacleEvent():
			m_fromEvents(vector<function<void(T...)>>(0))
		{};
		~ObstacleEvent() {};
		void AddEvent(const function<void(T...)>& event) {
			m_fromEvents.push_back(event);
		}
		void Run(T... args) {
			for(auto& event : m_fromEvents) event(args...);
		}
	};


	class Weapon :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;

	public:

		Weapon(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale)

		{}
		~Weapon() {}

		virtual void OnCreate() override;
		void Draw();

	};


	class BulletBase :public GameObject, public ObstacleEvent<const CharacterStatus_s> {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_moveSpeed;
		float m_gravityScale;

		int m_fromUnique;

	public:

		BulletBase(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const unsigned int fromUnique
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_fromUnique(fromUnique)
		{}
		~BulletBase() {}

		void Draw();
		void Move();
		void Destroy();

		unsigned int GetFromUnique() {
			return m_fromUnique;
		}
	};


	class Bullet :public BulletBase {
	public:
		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const unsigned int fromUnique
		) :
			BulletBase(StagePtr,
			pos,
			rot,
			scale,
			speed,
			gravity,
			fromUnique
			)
		{}
		virtual ~Bullet() {}

		virtual void OnCreate();
		virtual void OnUpdate();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

}