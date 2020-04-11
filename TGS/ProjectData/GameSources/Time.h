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
	class Time01 : public GameObject {
	protected:
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		
	public:
		Time01(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		int time01 = 0;

		int time02 = 0;

		int time03 = 0;

		int GetTime01() {
			return time01;
		}

		int GetTime03() {
			return time03;
		}

		virtual ~Time01() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

   //--------------------------------------------------------------------------------------
   ///	ŽžŠÔ
   //--------------------------------------------------------------------------------------
	class Time10 : public GameObject {
	protected:
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		Time10(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~Time10() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

//--------------------------------------------------------------------------------------
///	ŽžŠÔ
//--------------------------------------------------------------------------------------
	class Time100 : public GameObject {
	protected:
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		Time100(const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~Time100() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}