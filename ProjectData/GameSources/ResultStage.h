#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		void CreateViewLight();
		void CreateUI();

	public:
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}