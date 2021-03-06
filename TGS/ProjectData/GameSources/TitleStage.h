#pragma once
#include "stdafx.h"

namespace basecross {

	class TitleStage : public Stage {
		int m_baseLayer;
		wstring m_bgImageName;
		wstring m_titleLogoImageName;
		wstring m_startButtonImageName;
		wstring m_explanationButtonImageName;
		wstring m_explanationImageName;
		wstring m_explanationTitleImageName;
		wstring m_explanationReturnImageName;
		wstring m_explanationStartImageName;
		vector<wstring> m_iconImageNames;

		shared_ptr<UI_Static_Image> m_explanationImage;
		shared_ptr<UI_Static_Image> m_explanationTitleImage;
		shared_ptr<UI_Static_Image> m_explanationReturnImage;
		shared_ptr<UI_Static_Image> m_explanationStartImage;
		vector<shared_ptr<UI_Static_Image>> m_iconImages;

		shared_ptr<SoundItem> m_bgm;

		shared_ptr<UI_Curtain> m_curtain;

		int m_state;

		void CreateViewLight();
		void CreateUI();

		void CreateIcons();

		void ToggleExplanationImage();
		void UpdateInput();

		void NextStage();

	public:
		TitleStage() :Stage(),
			m_baseLayer(10),
			m_bgImageName(L"dot.png"),
			m_titleLogoImageName(L"TitleLogo_1024.png"),
			m_startButtonImageName(L"StartButton.png"),
			m_explanationButtonImageName(L"ExplanationButton.png"),
			m_explanationImageName(L"Operation.png"),
			m_explanationTitleImageName(L"OperationTitle.png"),
			m_explanationReturnImageName(L"OperationReturn.png"),
			m_explanationStartImageName(L"OperationStart.png"),
			m_iconImageNames({ L"Chicken1.png", L"Chicken2.png", L"Chicken3.png", L"Doughnut1.png", L"Doughnut2.png", L"Doughnut3.png", L"Potato1.png", L"Potato2.png", L"Shrimp1.png", L"Shrimp2.png" }),
			m_explanationImage(NULL),
			m_explanationTitleImage(NULL),
			m_explanationReturnImage(NULL),
			m_explanationStartImage(NULL),
			m_iconImages(NULL),
			m_bgm(NULL),
			m_curtain(NULL),
			m_state(NULL)
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
			auto bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}
	};

}