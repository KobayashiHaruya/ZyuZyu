/*!
@file UI.h
@brief UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ŠÔ
	//--------------------------------------------------------------------------------------

	class Time : public Sprite {

	public:
		Time(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~Time() {}

		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

	};

}