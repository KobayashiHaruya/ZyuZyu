/*!
@file Player.h
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ResultScore :public GameObject {
		wstring test;
		vector<CharacterStatus_s> m_charState;
		vector<int> m_KillList;

	public:
		ResultScore(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr) {}
		~ResultScore() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void ReadScore();
	};

}
//end basecross

