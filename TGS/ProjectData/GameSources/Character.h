/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Character : public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_moveSpeed;
		float m_rotSpeed = 1.5f;
		float m_gravityScale;
		float m_jumpPower;

		float m_force = 1.0f;
		bool m_jump = true;


	public:

		Character(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const float& jump
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_jumpPower(jump)
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
	
	
	};


	class TestPlayer : public Character {
	public:
		TestPlayer(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const float& speed,
			const float& gravity,
			const float& jump
		) :
			Character(StagePtr,
			pos,
			rot,
			scale,
			speed,
			gravity,
			jump
			)
		{}
		~TestPlayer() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};


}
//end basecross
