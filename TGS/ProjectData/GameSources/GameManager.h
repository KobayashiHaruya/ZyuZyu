/*!
@file GameManager.h
@brief �Q�[���S�̂��Ǘ�����}�l�[�W���[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Q�[���S�̂��Ǘ�����}�l�[�W���[
	//--------------------------------------------------------------------------------------
	class GameManager {
	private:
		static GameManager* m_GM;


	public:
		GameManager()
		{
		};
		~GameManager() {};
		static void CreateGM();
		static GameManager* getInstance();
		
	};

}

