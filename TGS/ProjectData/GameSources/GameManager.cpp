/*!
@file GameManager.cpp
@brief �Q�[���S�̂��Ǘ�����}�l�[�W���[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Q�[���S�̂��Ǘ�����}�l�[�W���[
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