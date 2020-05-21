#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		int m_layer;
		int m_Amount;
		float m_Move;

		CharacterType m_type;
		int m_level;

		wstring m_Stage_Image;
		wstring m_Score_Image;
		wstring m_Score_frame_Image;

		shared_ptr<Result_Curtain> m_Cartain;

		shared_ptr<Result_Icon_UI> m_ResultIcon;


	public:
		ResultStage() :Stage(),
			m_layer(5),
			m_Stage_Image(L""),
			m_Score_Image(L"Number_128_64.png"),
			m_Score_frame_Image(L"score_frame.png"),
			m_Cartain(NULL),
			m_Amount(5),
			m_Move(500.0f),
			m_type(POTATO),
			m_level(0)
		{}
		virtual ~ResultStage() {}

		void CreateViewLight();
		void CreateUI();
		void CreateIcon(CharacterType type, int level);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}