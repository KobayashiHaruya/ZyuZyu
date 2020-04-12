/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

//	//--------------------------------------------------------------------------------------
//	///	時間
//	//--------------------------------------------------------------------------------------
//	Time01::Time01(const shared_ptr<Stage>& stagePtr,
//		const wstring& textureKey,
//		const Vec2& startScale,
//		const Vec2& startPos) :
//		GameObject(stagePtr),
//		m_TextureKey(textureKey),
//		m_StartScale(startScale),
//		m_StartPos(startPos)
//	{}
//
//	void Time01::OnCreate() {
//		float helfSize = 0.5f;
//		//頂点配列(縦横5個ずつ表示)
//		vector<VertexPositionColorTexture> vertices = {
//			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
//			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
//		};
//		//インデックス配列
//		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
//		//0  1
//		//2  3
//		//
//		SetAlphaActive(true);
//
//		auto ptrTransform = GetComponent<Transform>();
//		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
//		ptrTransform->SetRotation(0, 0, 0);
//		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
//
//		//頂点とインデックスを指定してスプライト作成
//		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
//		ptrDraw->SetTextureResource(m_TextureKey);
//		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//
//		//AddTag(L"Time01");
//	}
//
//	void Time01::OnUpdate() {
//
//		auto transComp = GetComponent<Transform>();
//		auto scale = transComp->GetScale();
//		//ここにscale - Player_HP
//		scale.x = scale.x;
//		//透過処理
//		SetAlphaActive(true);
//
//		float helfSize = 1.0f;
//		//頂点配列(縦横5個ずつ表示)
//		vector<VertexPositionColorTexture> vertices = {
//			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
//			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
//		};
//		//インデックス配列
//		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
//
//		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);	
//
//		if (time01 == 10)
//		{
//			time02 += 1;
//			time01 -= 10;
//		}
//
//		if (time02 == 10)
//		{
//			time03 += 1;
//			time02 -= 10;
//		}
//
//		if (time03 == 10)
//		{
//			time03 -= 10;
//		}
//
//		if (time03 == 0)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"0.png");
//		}
//
//		if (time03 == 1)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"1.png");
//		}
//
//		if (time03 == 2)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"2.png");
//		}
//
//		if (time03 == 3)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"3.png");
//		}
//
//		if (time03 == 4)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"4.png");
//		}
//
//		if (time03 == 5)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"5.png");
//		}
//
//		if (time03 == 6)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"6.png");
//		}
//
//		if (time03 == 7)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"7.png");
//		}
//
//		if (time03 == 8)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"8.png");
//		}
//
//		if (time03 == 9)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"9.png");
//		}
//
//		time01 += 1;
//	}
//
//   //--------------------------------------------------------------------------------------
//   ///	時間
//   //--------------------------------------------------------------------------------------
//	Time10::Time10(const shared_ptr<Stage>& stagePtr,
//		const wstring& textureKey,
//		const Vec2& startScale,
//		const Vec2& startPos) :
//		GameObject(stagePtr),
//		m_TextureKey(textureKey),
//		m_StartScale(startScale),
//		m_StartPos(startPos)
//	{}
//
//	void Time10::OnCreate() {
//		float helfSize = 0.5f;
//		//頂点配列(縦横5個ずつ表示)
//		vector<VertexPositionColorTexture> vertices = {
//			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
//			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
//		};
//		//インデックス配列
//		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
//		//0  1
//		//2  3
//		//
//		SetAlphaActive(true);
//
//		auto ptrTransform = GetComponent<Transform>();
//		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
//		ptrTransform->SetRotation(0, 0, 0);
//		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
//
//		//頂点とインデックスを指定してスプライト作成
//		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
//		ptrDraw->SetTextureResource(m_TextureKey);
//		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//
//	}
//
//	void Time10::OnUpdate() {
//
//		auto transComp = GetComponent<Transform>();
//		auto scale = transComp->GetScale();
//		//ここにscale - Player_HP
//		scale.x = scale.x;
//		//透過処理
//		SetAlphaActive(true);
//
//		float helfSize = 1.0f;
//		//頂点配列(縦横5個ずつ表示)
//		vector<VertexPositionColorTexture> vertices = {
//			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
//			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
//		};
//		//インデックス配列
//		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
//
//		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
//
//
//		if (time01 == 10)
//		{
//			time02 += 1;
//			time01 -= 10;
//		}
//
//		if (time02 == 10)
//		{
//			time03 += 1;
//			time02 -= 10;
//		}
//
//		if (time03 == 10)
//		{
//			time04 += 1;
//			time03 -= 10;
//		}
//
//		if (time04 == 6)
//		{
//			time04 -= 6;
//		}
//
//		if (time04 == 0)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"0.png");
//		}
//
//		if (time04 == 1)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"1.png");
//		}
//
//		if (time04 == 2)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"2.png");
//		}
//
//		if (time04 == 3)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"3.png");
//		}
//
//		if (time04 == 4)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"4.png");
//		}
//
//		if (time04 == 5)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"5.png");
//		}
//
//		time01 += 1;
//		
//	}
//
////--------------------------------------------------------------------------------------
/////	時間
////--------------------------------------------------------------------------------------
//	Time100::Time100(const shared_ptr<Stage>& stagePtr,
//		const wstring& textureKey,
//		const Vec2& startScale,
//		const Vec2& startPos) :
//		GameObject(stagePtr),
//		m_TextureKey(textureKey),
//		m_StartScale(startScale),
//		m_StartPos(startPos)
//	{}
//
//	void Time100::OnCreate() {
//		float helfSize = 0.5f;
//		//頂点配列(縦横5個ずつ表示)
//		vector<VertexPositionColorTexture> vertices = {
//			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
//			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
//		};
//		//インデックス配列
//		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
//		//0  1
//		//2  3
//		//
//		SetAlphaActive(true);
//
//		auto ptrTransform = GetComponent<Transform>();
//		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
//		ptrTransform->SetRotation(0, 0, 0);
//		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
//
//		//頂点とインデックスを指定してスプライト作成
//		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
//		ptrDraw->SetTextureResource(m_TextureKey);
//		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//
//	}
//
//	void Time100::OnUpdate() {
//
//		auto transComp = GetComponent<Transform>();
//		auto scale = transComp->GetScale();
//		//ここにscale - Player_HP
//		scale.x = scale.x;
//		//透過処理
//		SetAlphaActive(true);
//
//		float helfSize = 1.0f;
//		//頂点配列(縦横5個ずつ表示)
//		vector<VertexPositionColorTexture> vertices = {
//			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
//			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
//			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
//		};
//		//インデックス配列
//		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
//
//		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
//
//
//		if (time01 == 10)
//		{
//			time02 += 1;
//			time01 -= 10;
//		}
//
//		if (time02 == 10)
//		{
//			time03 += 1;
//			time02 -= 10;
//		}
//
//		if (time03 == 10)
//		{
//			time04 += 1;
//			time03 -= 10;
//		}
//
//		if (time04 == 6)
//		{
//			time05 += 1;
//			time04 -= 6;
//			
//		}
//
//		if (time05 == 3)
//		{
//
//		}
//
//		if (time05 == 0)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"0.png");
//		}
//
//		if (time05 == 1)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"1.png");
//		}
//
//		if (time05 == 2)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"2.png");
//		}
//
//		if (time05 == 3)
//		{
//			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
//			ptrDraw->SetTextureResource(L"3.png");
//		}
//
//		time01 += 1;
//	}
//
}