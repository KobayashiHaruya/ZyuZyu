#pragma once
#include "stdafx.h"

namespace basecross {

	class TitleStage : public Stage {
		void CreateViewLight();
		void CreateUI();

	public:
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}