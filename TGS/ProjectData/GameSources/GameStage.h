/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

#include "MyUI.h"
#include "Character.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<UI_The_World> m_pause;
		shared_ptr<TestPlayer> m_player;
		shared_ptr<TestEnemy> m_enemy;

		//�r���[�̍쐬
		void CreateViewLight();
		void CreateUI();

		void ShowPause();

	public:
		//�\�z�Ɣj��
		GameStage() :
			Stage(),
			m_pause(NULL),
			m_player(NULL),
			m_enemy(NULL)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

