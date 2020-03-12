/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Character : public GameObject {
		float m_moveSpeed;
		float m_gravityScale;
		float m_jumpPower;


		void Move();
		void Jump();

	public:

		Character(const shared_ptr<Stage>& StagePtr,
			const float& speed,
			const float& gravity,
			const float& jump
		) :
			GameObject(StagePtr),
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
