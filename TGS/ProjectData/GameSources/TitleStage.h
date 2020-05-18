#pragma once
#include "stdafx.h"

namespace basecross {

	class TitleStage : public Stage {
		wstring m_Standard;
		wstring m_Shrimp_Title;
		wstring m_Chicken_Title;
		wstring m_Potato_Title;
		wstring m_Donut_Title;
		shared_ptr<SoundItem> m_bgm;

		bool m_Update;

		int m_Rand;

		void CreateViewLight();
		void CreateUI();

		void CreateOperationUI();
		int RandGenerator();

	public:
		TitleStage() :Stage(),
			m_Standard(L"GameTitle_ver2.png"),
			m_Shrimp_Title(L"title_Shrimp.png"),
			m_Chicken_Title(L"title_Chicken.png"),
			m_Potato_Title(L"title_Potato.png"),
			m_Donut_Title(L"title_Donut.png"),

			m_Update(false),
			m_Rand(0)
		{}
		virtual ~TitleStage() {}

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