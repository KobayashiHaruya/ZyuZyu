#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		//アイコン

		//降ってくるアイコンの数
		int m_Amount;
		//ステージ
		wstring m_Stage_Image;
		//カーテン
		wstring m_Curtain_Image;
		//スコア
		wstring m_Score_Image;
		wstring m_Score_frame_Image;

		void CreateViewLight();
		void CreateUI();
	public:
		ResultStage() :Stage(),
			//""内にテクスチャの名前

			m_Stage_Image(L""),
			m_Curtain_Image(L"Curtain.png"),
			m_Score_Image(L"number.png"),
			m_Score_frame_Image(L"score_frame.png"),

			m_Amount(5)
		{}
		virtual ~ResultStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}