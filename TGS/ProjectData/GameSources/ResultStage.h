#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		int m_layer;
		int m_Amount;
		float m_Move;
		float m_Second;

		int m_Score;
		int m_TrueScore;

		CharacterType m_type;
		int m_level;

		wstring m_Stage_Image;
		wstring m_Score_Image;
		wstring m_Score_frame_Image;

		shared_ptr<Result_Curtain> m_Cartain;
		shared_ptr<SoundItem> m_bgm;

		shared_ptr<Result_Icon_UI> m_ResultIcon;

		shared_ptr<Score_UI> m_Score_UI;


	public:
		ResultStage() :Stage(),
			m_layer(5),
			m_Score_Image(L"Number_695_Gold.png"),
			m_Stage_Image(L"ScoreBoard_Sample.png"),
			m_Cartain(NULL),
			m_Amount(5),
			m_Second(0.0f),
			m_Move(500.0f),
			m_Score(000000),
			m_TrueScore(0),
			m_type(POTATO),
			m_level(0)
		{}
		virtual ~ResultStage() {}

		void CreateViewLight();
		void CreateUI();
		void CreateIcon(CharacterType type, int level);
		void ScoreMove();

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

		int GetScore() const {
			return m_Score;
		}

		void AddScore(int value) {
			m_Score += value;
		}

	};

}