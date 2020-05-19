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

		void CreateViewLight();
		void CreateUI();

		void CreateIcons();

		void ToggleExplanationImage();
		void UpdateInput();


	public:
		TitleStage() :Stage(),
			m_baseLayer(10),
			m_bgImageName(L"dot.png"),
			m_titleLogoImageName(L"TitleLogo_1024.png"),
			m_startButtonImageName(L"dot.png"),
			m_explanationButtonImageName(L"dot.png"),
			m_explanationImageName(L"Operation.png"),
			m_explanationTitleImageName(L"dot.png"),
			m_explanationReturnImageName(L"dot.png"),
			m_explanationStartImageName(L"dot.png"),
			m_iconImageNames({ L"Chicken1.png", L"Chicken2.png", L"Chicken3.png", L"Doughnut1.png", L"Doughnut2.png", L"Doughnut3.png", L"Potato1.png", L"Potato2.png", L"Shrimp1.png", L"Shrimp2.png" }),
			m_explanationImage(NULL),
			m_explanationTitleImage(NULL),
			m_explanationReturnImage(NULL),
			m_explanationStartImage(NULL),
			m_iconImages(NULL)
		{}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}