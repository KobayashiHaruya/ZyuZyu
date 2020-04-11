#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		//�A�C�R��

		//�~���Ă���A�C�R���̐�
		int m_Amount;
		//�X�e�[�W
		wstring m_Stage_Image;
		//�J�[�e��
		wstring m_Curtain_Image;
		//�X�R�A
		wstring m_Score_Image;
		wstring m_Score_frame_Image;

		void CreateViewLight();
		void CreateUI();
	public:
		ResultStage() :Stage(),
			//""���Ƀe�N�X�`���̖��O

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