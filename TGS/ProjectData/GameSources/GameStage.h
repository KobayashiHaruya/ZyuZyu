/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

#include "MyUI.h"
#include "Character.h"
#include "AIchan.h"
#include "MyCamera.h"

namespace basecross {	

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<MyCamera> m_camera;

		shared_ptr<UI_The_World> m_pause;
		shared_ptr<Player> m_player;
		shared_ptr<AIchan> m_enemy;
		shared_ptr<PinP> m_pinp;
		shared_ptr<SoundItem> m_bgm;
		
		vector<CharacterStatus_s> m_charState;

		shared_ptr<UI_CountdownTimer> m_timer;
		shared_ptr<UI_Count_Signal> m_startSignal;
		shared_ptr<UI_Count_Signal> m_endSignal;

		shared_ptr<UI_Curtain> m_curtain;

		unsigned int m_state;

		//ビューの作成
		void CreateViewLight();
		void CreateUI();
		void WeaponState();

		void ShowPause();

		void CreateTime();

		void CreateEndTime();

		void CreatePinP();

		float m_weaponTime;
		void WeaponUpdate();

		CharacterType SelectedChar();

		//bool gather = false;
		void CreateAIchan();

		void NextStage();
		void PrevTitleStage();
		void PrevSelectStage();

	public:
		//エフェクト
		shared_ptr<EfkEffect> m_effect;
		shared_ptr<EfkInterface> m_efkInterface;
		vector<WeaponState_s> m_weaponState;
		bool m_start = false;

		//構築と破棄
		GameStage() :
			Stage(),
			m_camera(NULL),
			m_pause(NULL),
			m_player(NULL),
			m_enemy(NULL),
			m_pinp(NULL),
			m_timer(NULL),
			m_startSignal(NULL),
			m_endSignal(NULL),
			m_curtain(NULL),
			m_state(NULL)
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2() override;
		virtual void OnDraw()override;

		void GameFinishScore();

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

		shared_ptr<MyCamera> GetCamera() {
			return m_camera;
		}

		void TestFunc() {

		}

		shared_ptr<EfkEffect> GetEffect(wstring name) {
			wstring dir;
			App::GetApp()->GetDataDirectory(dir);
			wstring effectStr = dir + L"Effect\\";
			m_effect = ObjectFactory::Create<EfkEffect>(m_efkInterface, (effectStr + name));

			return m_effect;

		}

	};


}
//end basecross

