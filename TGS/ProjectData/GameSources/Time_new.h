/*!
@file UI.h
@brief UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	時間
	//--------------------------------------------------------------------------------------
	class Time01 : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Time = 5.9f;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	NumberOfDigits	桁数
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		Time01(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~Time01() {}
		void SetTime(float f) {
			m_Time = f;
		}

		//トータル時間
		float m_TotalTime = 5.9f;
		float m_Count = 0;

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
	};



//--------------------------------------------------------------------------------------
///	スタートスイッチ
//--------------------------------------------------------------------------------------

	class Time_Start : public Sprite {

	public:
		Time_Start(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~Time_Start() {}

		float time_ON = 0;
		//トータル時間
		float m_TotalTime;

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		

	};

	//--------------------------------------------------------------------------------------
	///	時間
	//--------------------------------------------------------------------------------------
	class EndTime : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Time;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	NumberOfDigits	桁数
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		EndTime(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~EndTime() {}
		void SetTime(float f) {
			m_Time = f;
		}

		//トータル時間
		float m_TotalTime;
		float m_Count = 0;

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
	};

//--------------------------------------------------------------------------------------
///	エンドスイッチ
//--------------------------------------------------------------------------------------

	class End : public Sprite {

	public:
		End(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~End() {}

		float time_ON = 0;
		//トータル時間
		float m_TotalTime;

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate()override;


	};

}
