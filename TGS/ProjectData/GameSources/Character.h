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
		float m_gravityScale;
		float m_jumpPower;

		void Draw();
		void PlayerCamera();
		Vec3 PlayerMove();
		void PlayerJump();

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

		virtual void OnCreate();
		virtual void OnUpdate();
	};

}
//end basecross
