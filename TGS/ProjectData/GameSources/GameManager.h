/*!
@file GameManager.h
@brief ゲーム全体を管理するマネージャー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	ゲーム全体を管理するマネージャー
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

