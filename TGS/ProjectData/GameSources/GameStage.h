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
		shared_ptr<Player> m_player;
		shared_ptr<Enemy> m_enemy;
		shared_ptr<PinP> m_pinp;

		//�r���[�̍쐬
		void CreateViewLight();
		void CreateUI();

		void ShowPause();

		void CreateTime();

		void CreatePinP();

		float m_weaponTime;
		void WeaponUpdate();

		//�g�[�^������
		float m_TotalTime;

		//�g�[�^������
		float m_TotalTime2;

		//�g�[�^������
		float m_TotalTime3;

	public:
		//�\�z�Ɣj��
		GameStage() :
			Stage(),
			m_pause(NULL),
			m_player(NULL),
			m_enemy(NULL),
			m_pinp(NULL)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

