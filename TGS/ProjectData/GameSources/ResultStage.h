#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		int m_layer;
		int m_Amount;

		wstring m_Stage_Image;
		wstring m_Score_Image;
		wstring m_Score_frame_Image;

		shared_ptr<Result_Curtain> m_Cartain;
		shared_ptr<SoundItem> m_bgm;


		void CreateViewLight();
		void CreateUI();
		void CreateIcon();
	public:
		ResultStage() :Stage(),
			m_layer(5),
			m_Stage_Image(L""),
			m_Score_Image(L"Number_128_64.png"),
			m_Score_frame_Image(L"score_frame.png"),
			m_Cartain(NULL),
			m_Amount(5)
		{}
		virtual ~ResultStage() {}

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