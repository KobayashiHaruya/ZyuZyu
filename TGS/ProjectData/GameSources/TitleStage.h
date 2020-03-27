#pragma once
#include "stdafx.h"

namespace basecross {

	class TitleStage : public Stage {
		void CreateViewLight();
		void CreateUI();
		void CreateOperationUI();
		bool m_Update;
	public:
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}