#pragma once
#include "stdafx.h"

namespace basecross {

	class CharSelectStage : public Stage {
		wstring m_baseImageName;
		wstring m_maskImageName;
		wstring m_chickenImageName;
		wstring m_potatoImageName;
		wstring m_shrimpImageName;
		wstring m_doughnutImageName;

		std::shared_ptr<UI_Character_Select_Mask_Image> m_mask;
		std::shared_ptr<UI_Character_Select_Static_Image> m_chicken;
		std::shared_ptr<UI_Character_Select_Static_Image> m_potato;
		std::shared_ptr<UI_Character_Select_Static_Image> m_shrimp;
		std::shared_ptr<UI_Character_Select_Static_Image> m_doughnut;

		int m_startIndex;

		void CreateViewLight();
		void CreateUI();

	public:
		CharSelectStage() :Stage(),
			m_baseImageName(L"CS_Base.png"),
			m_maskImageName(L"CS_Mask.png"),
			m_chickenImageName(L"CS_Chikin_Status.png"),
			m_potatoImageName(L"CS_Jagaimo_Status.png"),
			m_shrimpImageName(L"CS_Ebi_Status.png"),
			m_doughnutImageName(L"CS_Donatu_Status.png"),
			m_startIndex(0)
		{}
		virtual ~CharSelectStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetStatusImage(int index);
		int GetIndex() {
			if (!m_mask) return m_startIndex;
			return m_mask->GetIndex();
		}
		void Select();
	};

}