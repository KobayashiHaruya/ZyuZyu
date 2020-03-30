#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void UI_Base::Draw() {

		float X = m_Vertex.x / 2.0f;
		float Y = m_Vertex.y / 2.0f;


		vector<VertexPositionColorTexture> vertices;
		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices.push_back(VertexPositionColorTexture(Vec3(-X, Y, 0), color, Vec2(0.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(X, Y, 0), color, Vec2(1.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(-X, -Y, 0), color, Vec2(0.0f, 1.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(X, -Y, 0), color, Vec2(1.0f, 1.0f)));

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);

	}

	void UI_Character_Select_Static_Image::OnCreate() {
		Draw();
	}

	void UI_Character_Select_Mask_Image::OnCreate() {
		Draw();
		SetMaskIndex(m_maskIndex);
	}

	void UI_Character_Select_Mask_Image::OnUpdate() {
		MaskMove();
	}

	void UI_Character_Select_Mask_Image::MaskMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLX = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbLX = cntlVec[0].fThumbLX;
		}

	void Title_UI::OnCreate() {
		Draw();
	}

	void Operation_UI::OnCreate() {
		Draw();
	}



		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl['A'] || (fThumbLX < 0.0f && m_oldFThumbLX == 0.0f)) {
			SetMaskIndex(--m_maskIndex);
		}

		if (KeyState.m_bPressedKeyTbl['D'] || (fThumbLX > 0.0f && m_oldFThumbLX == 0.0f)) {
			SetMaskIndex(++m_maskIndex);
		}

		m_oldFThumbLX = fThumbLX;
	}

	void UI_Character_Select_Mask_Image::SetMaskIndex(int& index) {
		if (index < m_indexMin) index = m_indexMax;
		if (index > m_indexMax) index = m_indexMin;
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();
		pos.x = m_startPosX + (index * m_movingValue);
		trans->SetPosition(pos);
	}
}