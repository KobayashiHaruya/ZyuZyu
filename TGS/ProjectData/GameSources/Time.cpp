/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	時間
	//--------------------------------------------------------------------------------------
	Time01::Time01(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		GameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void Time01::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}

	void Time01::OnUpdate() {


	}

   //--------------------------------------------------------------------------------------
   ///	時間
   //--------------------------------------------------------------------------------------
	Time10::Time10(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		GameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void Time10::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}

	void Time10::OnUpdate() {


	}

}