#pragma once
#include "stdafx.h"

namespace basecross {


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


	class BulletBase : public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_moveSpeed;
		float m_gravityScale;
		int ID;

	public:

		BulletBase(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			ID(id)
		{}
		~BulletBase() {}

		void Draw();
		void Move();
		void Destroy();
	};


	class Grenade :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_moveSpeed;
		float m_gravityScale;
		int ID;

		bool m_grenade;

	public :
		Grenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const bool& grenade,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
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
		Vec3 m_rot;
		Vec3 m_scale;
		int ID;

		float m_time;

	public:
		SmokeGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
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
		Vec3 m_rot;
		Vec3 m_scale;
		int ID;

		float m_time;

	public:
		TorimotiGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
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


	class Bullet :public BulletBase {
	public:
		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const int& id
		) :
			BulletBase(StagePtr,
				pos,
				rot,
				scale,
				speed,
				gravity,
				id
			)
		{}
		virtual ~Bullet() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

}