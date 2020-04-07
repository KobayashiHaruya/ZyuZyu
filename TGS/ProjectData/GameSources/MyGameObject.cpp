/*!
@file MyGameObject.cpp
@brief このゲーム用のゲームオブジェクトクラス
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyGameObject::MyGameObject(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{
	}
}
//end basecross