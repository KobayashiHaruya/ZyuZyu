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


	public:

		BulletBase(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_moveSpeed(speed),
			m_gravityScale(gravity)
		{}
		~BulletBase() {}

		void Draw();
		void Move();
		void Destroy();
	};


	class Bullet :public BulletBase {
	public:
		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity
		) :
			BulletBase(StagePtr,
			pos,
			rot,
			scale,
			speed,
			gravity
			)
		{}
		virtual ~Bullet() {}

		virtual void OnCreate();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

}