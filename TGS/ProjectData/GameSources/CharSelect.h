#pragma once
#include "stdafx.h"

namespace basecross {

	class CharSelectStage : public Stage {
		void CreateViewLight();
		void CreateUI();

	public:
		CharSelectStage() :Stage() {}
		virtual ~CharSelectStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}