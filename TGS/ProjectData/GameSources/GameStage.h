/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

#include "MyUI.h"
#include "Character.h"
#include "AIchan.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<UI_The_World> m_pause;
		shared_ptr<Player> m_player;
		shared_ptr<AIchan> m_enemy;
		shared_ptr<PinP> m_pinp;
		shared_ptr<SoundItem> m_bgm;

		//�r���[�̍쐬
		void CreateViewLight();
		void CreateUI();

		void ShowPause();

		void CreateTime();

		void CreateEndTime();

		void CreatePinP();

		float m_weaponTime;
		void WeaponUpdate();


		//bool gather = false;
		void CreateAIchan();

	public:
		bool m_start = false;

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

		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		void StopBGM() {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Stop(m_bgm);
		}

	};


}
//end basecross

