#pragma once
#include "stdafx.h"

namespace basecross {

	class CopyrightStage : public Stage {
		int m_baseLayer;
		shared_ptr<UI_Copyright_Splash> m_splash;

		float m_count;
		float m_titleTime;

		shared_ptr<SoundItem> m_bgm;

		void CreateViewLight();
		void CreateSplash();

	public:
		CopyrightStage() :Stage(),
			m_baseLayer(10),
			m_splash(NULL),
			m_count(NULL),
			m_titleTime(3.0f),
			m_bgm(NULL)
		{}
		virtual ~CopyrightStage() {}

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
			auto bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}
	};

}