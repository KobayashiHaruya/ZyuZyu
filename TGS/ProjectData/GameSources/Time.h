/*!
@file UI.h
@brief UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ŽžŠÔ
	//--------------------------------------------------------------------------------------
	class Time : public GameObject {
	protected:
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		Time(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~Time() {};
		virtual void OnCreate()override;
	};

}