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


	//------------------------------------------------------------------------------------------------
	//テキスト : Class
	//------------------------------------------------------------------------------------------------

	void UI_Sprite_Text::OnCreate() {
		SetDrawLayer(m_layer);
		auto text = AddComponent<StringSprite>();
		text->SetTextAlignment(m_textAlignment);
		text->SetFont(m_fontName, m_fontSize);
		text->SetTextRect(m_rect);
		text->SetFontColor(m_color);
		text->SetText(m_text);
		if (m_isBk) text->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void UI_Sprite_Text::Remove() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<UI_Sprite_Text>());
	}


	//------------------------------------------------------------------------------------------------
	//スタティックな画像 : Class
	//------------------------------------------------------------------------------------------------

	void UI_Static_Image::OnCreate() {
		Draw();
	}


	//------------------------------------------------------------------------------------------------
	//キャラクターセレクトの選択マスク : Class
	//------------------------------------------------------------------------------------------------

	void UI_Character_Select_Mask_Image::OnCreate() {
		Draw();
		SetMaskIndex(m_maskIndex);
	}

	void UI_Character_Select_Mask_Image::OnUpdate() {
		MaskMove();
	}

	void Title_UI::OnCreate() {
		Draw();
	}

	void Operation_UI::OnCreate() {
		Draw();
	}

	void UI_Character_Select_Mask_Image::MaskMove() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLX = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbLX = cntlVec[0].fThumbLX;
		}

		Draw();
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


	//------------------------------------------------------------------------------------------------
	//タブ : Class
	//------------------------------------------------------------------------------------------------

	void UI_Tab::OnCreate() {
		//SetMaskIndex(m_maskIndex);
		CreateTab();
		CreateMasks();
	}

	void UI_Tab::OnUpdate() {
		MaskMove();
	}

	void UI_Tab::CreateTab() {
		m_tab = GetStage()->AddGameObject<UI_Static_Image>(
			Vec2(1337.05f, 41.6f),
			m_pos,
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_tabImageName
			);
	}

	void UI_Tab::CreateMasks() {
		Vec2 size = Vec2(332.8f, 41.6f);
		for (int i = 0; i < m_indexMax; i++) {
			auto mask = GetStage()->AddGameObject<UI_Static_Image>(
				size,
				Vec3(m_pos.x - (size.x), m_pos.y, m_pos.z),
				Vec3(1.0f, 1.0f, 1.0f),
				5,
				Col4(1.0f, 1.0f, 1.0f, 0.75f),
				m_tabMaskImageName
				);
			m_masks.push_back(mask);
		}
	}

	void UI_Tab::MaskMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLX = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbLX = cntlVec[0].fThumbLX;
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

	void UI_Tab::SetMaskIndex(int& index) {
		if (index < m_indexMin) index = m_indexMax;
		if (index > m_indexMax) index = m_indexMin;
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();
		pos.x = m_startPosX + (index * m_movingValue);
		trans->SetPosition(pos);
	}


	//------------------------------------------------------------------------------------------------
	//ポーズ画面 : Class
	//------------------------------------------------------------------------------------------------

	void UI_The_World::OnCreate() {
		SetDrawLayer(2);

		GetStage()->CreateSharedObjectGroup(m_tableGroupName);

		auto stage = GetStage();

		m_base = stage->AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 0.75f),
			m_baseImageName
			);

		stage->AddGameObject<UI_Tab>(Vec3(0.0f));

		Hide(false);
	}

	void UI_The_World::Show(bool e) {
		m_isShow = e;
		ShowTitle(e);
		if (!e) {
			Hide(e);
			return;
		}
		m_base->SetDrawActive(e);
		ChangeTab(m_index);
	}

	void UI_The_World::Hide(bool e) {
		m_base->SetDrawActive(e);
		RemoveTableLine();
	}

	void UI_The_World::ChangeTab(int index) {
		switch (index)
		{
		case 0:
			ShowTable(true);
			break;
		default:
			break;
		}
	}

	void UI_The_World::ShowTitle(bool e) {
		if (!m_title && !e) return;
		if (m_title && !e) {
			m_title->Remove();
		} else {
			m_title = GetStage()->AddGameObject<UI_Sprite_Text>(
				m_fontName,
				100.0f,
				Col4(1.0f, 0.0f, 0.0f, 1.0f),
				Rect2D<float>(0.0f, 0.0f, 1920.0f, 100.0f),
				StringSprite::TextAlignment::m_Center,
				L"ポーズ",
				5,
				false
				);
		}
	}

	void UI_The_World::ShowTable(bool e) {
		CreateTableHeader();

		sort(m_characterStatuses.begin(), m_characterStatuses.end(), [](const CharacterStatus_s& a, const CharacterStatus_s& b) {
			return a.score > b.score;
		});
		int i = 0;
		for (auto& status : m_characterStatuses) {
			CreateTableLine(status, i);
			i++;
		}
	}

	void UI_The_World::CreateTableHeader() {
		float fontSize = 50.0f;
		float i = 363.0f;
		float iPlus = 330.0f;
		float t = 320.0f;
		float b = 380.0f;
		int layer = 5;

		auto stage = GetStage();

		auto separator = stage->AddGameObject<UI_Static_Image>(
			Vec2(1200.0f, 3.0f),
			Vec3(0.0f, 145.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			layer,
			m_white,
			m_separator3pxImageName
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(separator);

		auto text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 1), t, 1000.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"キル",
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);

		text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 2), t, 1320.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"デス",
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);

		text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 3), t, 1620.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"スコア",
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);
	}

	void UI_The_World::CreateTableLine(CharacterStatus_s &status, int index) {
		float space = 80.0f;
		float i = 363.0f;
		float iPlus = 337.0f;
		float t = 410.0f;
		float b = 330.0f;
		float fontSize = 40.0f;
		int layer = 5;

		auto stage = GetStage();

		if (index) {
			auto separator = stage->AddGameObject<UI_Static_Image>(
				Vec2(1200.0f, 1.0f),
				Vec3(0.0f, 145.0f - (index * space), 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				1,
				m_white,
				m_separator1pxImageName
				);
			stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(separator);
		}

		if (status.isPlayer) {
			auto playerBadge = stage->AddGameObject<UI_Static_Image>(
				Vec2(64.0f, 32.0f),
				Vec3(-650.0f, 102.5f - (index * space), 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				1,
				m_white,
				m_playerBadgeImageName
				);
			stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(playerBadge);
		}

		auto text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i, t + (index * space), 1556.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Left,
		    status.playerName,
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);

		text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 1), t + (index * space), 1000.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Center,
			to_wstring(status.kill),
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);

		text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 2), t + (index * space), 1300.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Center,
			to_wstring(status.death),
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);

		text = GetStage()->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			fontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 3), t + (index * space), 1580.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Center,
			to_wstring(status.score),
			layer,
			false
			);
		stage->GetSharedObjectGroup(m_tableGroupName)->IntoGroup(text);
	}

	void UI_The_World::SetCharacterStatus(const CharacterStatus_s& status) {
		vector<CharacterStatus_s>::iterator it = find_if(m_characterStatuses.begin(), m_characterStatuses.end(), [status](const CharacterStatus_s& i) {
			return i.unique == status.unique;
		});
		it->playerName = status.playerName;
		it->kill = status.kill;
		it->death = status.death;
		it->score = status.score;
		it->isPlayer = status.isPlayer;
	}

	void UI_The_World::RemoveTableLine() {
		auto tableTexts = GetStage()->GetSharedObjectGroup(m_tableGroupName)->GetGroupVector();
		for (auto& text : tableTexts) {
			auto obj = dynamic_pointer_cast<UI_Sprite_Text>(text.lock());
			if (obj) obj->Remove();
			auto obj1 = dynamic_pointer_cast<UI_Static_Image>(text.lock());
			if (obj1) GetStage()->RemoveGameObject<GameObject>(obj1);
		}
	}
}