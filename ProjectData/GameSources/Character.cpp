/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Character::Move() {

		auto trans = GetComponent<Transform>();

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bPushKeyTbl['W']) {
			
		}
	}

	void Character::Jump() {

	}



	void Character::OnCreate() {

	}

	void Character::OnUpdate() {

	}

}
//end basecross
