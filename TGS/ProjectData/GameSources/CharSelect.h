#pragma once
#include "stdafx.h"

namespace basecross {

	class CharSelectStage : public Stage {
		int m_layer;

		wstring m_baseImageName;
		wstring m_maskImageName;
		wstring m_chickenImageName;
		wstring m_potatoImageName;
		wstring m_shrimpImageName;
		wstring m_doughnutImageName;

		shared_ptr<UI_Character_Select_Mask_Image> m_mask;
		shared_ptr<UI_Static_Image> m_characterLogo;
		shared_ptr<UI_Character_Status> m_characterStatus;

		int m_startIndex;
		int m_oldIndex;

		void CreateViewLight();
		void CreateUI();
		void ChangeCharacter(int index);
		void Select();

		shared_ptr<UI_The_World> m_theWorld;  //本番時にはコメントアウトしてください
		void TestFunc();  //ポーズ画面を表示します。本番時にはコメントアウトしてください

	public:
		CharSelectStage() :Stage(),
			m_layer(5),
			m_baseImageName(L"CS_Base.png"),
			m_maskImageName(L"CS_Mask.png"),
			m_chickenImageName(L"CS_Chicken_Logo.png"),
			m_potatoImageName(L"CS_Potato_Logo.png"),
			m_shrimpImageName(L"CS_Shrimp_Logo.png"),
			m_doughnutImageName(L"CS_Doughnut_Logo.png"),
			m_startIndex(0),
			m_oldIndex(-1),
			m_mask(NULL),
			m_characterLogo(NULL),
			m_characterStatus(NULL),
			m_theWorld(NULL)
		{}
		virtual ~CharSelectStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		int GetIndex() {
			if (!m_mask) return m_startIndex;
			return m_mask->GetIndex();
		}
	};

}