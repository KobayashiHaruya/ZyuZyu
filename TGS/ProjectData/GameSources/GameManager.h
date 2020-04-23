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

		int m_MaxTime = 10;

		int m_MinTime = 1;

		int m_Notime = 0;

		int m_time01 = m_Notime;

		int m_time02 = m_Notime;

		int m_time03 = m_Notime;

		int m_time04 = m_Notime;

		int m_time05 = m_Notime;

	public:
		GameManager()
		{
		};
		~GameManager() {};
		static void CreateGM();
		static GameManager* getInstance();
		
		//get

		int GetMaxtime() const { return m_MaxTime; }

		int GetMintime() const { return m_MinTime; }

		int GetNotime() const { return m_Notime; }

		int Gettime01() const { return m_time01; }

		int Gettime02() const { return m_time02; }

		int Gettime03() const { return m_time03; }

		int Gettime04() const { return m_time04; }

		int Gettime05() const { return m_time05; }

	};

}

