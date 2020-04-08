/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///時間
	//--------------------------------------------------------------------------------------

	Time::Time(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void Time::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		// ピボットを右端にする
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"Light_on.png");


		AddTag(L"UI_Time");



		SetDrawLayer(11);
		SetAlphaActive(true);

		//スプライトの厚さ		
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 11.1f));
	}


	void Time::OnUpdate() {

		// ドローコンポーネントを取得
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		//// Spotlight.cppのを持ってきた
		//auto on = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight")->GetOn();
		//if (on) {
		//	// ライトがついていたらON.jpgに張り替える
		//	ptrDraw->SetTextureResource(L"Light_on.png");
		//}
		//else {
		//	// その他はOFF.jpgに張り替える
		//	ptrDraw->SetTextureResource(L"Light_off.png");
		//}


	}

}