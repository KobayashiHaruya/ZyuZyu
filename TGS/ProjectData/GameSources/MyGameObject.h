/*!
@file MyGameObject.h
@brief このゲーム用のゲームオブジェクトクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyGameObject : public GameObject {
	public:
		MyGameObject(const shared_ptr<Stage>& stagePtr);
		~MyGameObject() {}
	};
}
//end basecross