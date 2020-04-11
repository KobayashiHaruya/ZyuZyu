/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Character : public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_moveSpeed;
		float m_rotSpeed = 2.0f;
		float m_gravityScale;
		float m_jumpPower;
		int ID;

		Vec2 m_force = Vec2(10.0f, 10.0f);
		bool m_jump = true;

	public:

		Character(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const float& jump,
			const int& id
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_jumpPower(jump),
			ID(id)
		{}
		~Character() {}

		void Draw();
		void PlayerCamera();
		void PlayerMove();
		void PlayerRotMove();
		void BulletFire();
		void AttackHit(Vec3 rot);

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;


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
			const int& id
		) :
			Character(StagePtr,
				pos,
				rot,
				scale,
				speed,
				gravity,
				jump,
				id
			)
		{}
		~TestPlayer() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


}
//end basecross
