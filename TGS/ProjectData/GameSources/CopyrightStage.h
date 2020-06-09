#pragma once
#include "stdafx.h"

namespace basecross {

	class CopyrightStage : public Stage {
		int m_baseLayer;

		shared_ptr<UI_Copyright_Splash> m_splash;

		float m_splashCount;
		float m_splashTime;

		unsigned int m_bannerIndex;
		vector<shared_ptr<UI_Static_Image>> m_banners;
		float m_bannerCount;
		float m_bannerChangeTime;

		shared_ptr<SoundItem> m_bgm;

		void CreateViewLight();

		void CreateSplash();

		void CreateBanners();
		void UpdateBanners();


	public:
		CopyrightStage() :Stage(),
			m_baseLayer(10),
			m_splash(NULL),
			m_splashCount(NULL),
			m_splashTime(3.0f),
			m_bannerIndex(NULL),
			m_banners(vector<shared_ptr<UI_Static_Image>>()),
			m_bannerCount(4.0f),
			m_bannerChangeTime(4.0f),
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