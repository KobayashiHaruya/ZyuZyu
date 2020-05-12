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

		//�g�[�^������
		float m_TotalTime;

		float Get_m_TotalTime() {
			return m_TotalTime;
		}
	
	};

}

