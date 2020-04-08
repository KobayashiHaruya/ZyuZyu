/*!
@file GameManager.cpp
@brief ゲーム全体を管理するマネージャー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	ゲーム全体を管理するマネージャー
	//--------------------------------------------------------------------------------------
	GameManager* GameManager::m_GM = nullptr;

	void GameManager::CreateGM() {
		m_GM = new GameManager();
	}

	GameManager* GameManager::getInstance() {
		if (m_GM == nullptr) {
			m_GM = new GameManager();
		}
		return m_GM;
	}



}