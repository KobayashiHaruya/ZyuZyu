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

	void UI_Sprite_Text::UpdateText(const wstring value) {
		auto text = GetComponent<StringSprite>();
		text->SetText(value);
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

	void UI_Static_Image::Draw() {
		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		m_vertices.push_back(VertexPositionColorTexture(Vec3(-m_xHalf, m_yHalf, 0.0f), color, Vec2(0.0f, 0.0f)));
		m_vertices.push_back(VertexPositionColorTexture(Vec3(m_xHalf, m_yHalf, 0.0f), color, Vec2(1.0f, 0.0f)));
		m_vertices.push_back(VertexPositionColorTexture(Vec3(-m_xHalf, -m_yHalf, 0.0f), color, Vec2(0.0f, 1.0f)));
		m_vertices.push_back(VertexPositionColorTexture(Vec3(m_xHalf, -m_yHalf, 0.0f), color, Vec2(1.0f, 1.0f)));

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);
	}

	void UI_Static_Image::SetTexture(const wstring& texture) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetTextureResource(texture);
	}

	void UI_Static_Image::SetTexture(const wstring& texture, Vec2& vertex) {
		m_xHalf = vertex.x / 2.0f;
		m_yHalf = vertex.y / 2.0f;	
		m_vertices[0].position = Vec3(-m_xHalf, m_yHalf, 0.0f);
		m_vertices[1].position = Vec3(m_xHalf, m_yHalf, 0.0f);
		m_vertices[2].position = Vec3(-m_xHalf, -m_yHalf, 0.0f);
		m_vertices[3].position = Vec3(m_xHalf, -m_yHalf, 0.0f);
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->UpdateVertices(m_vertices);
		SetTexture(texture);
	}

	void UI_Static_Image::SetTexture(const wstring& texture, Vec2& vertex, const Vec3& scale) {
		m_scale = scale;
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		SetTexture(texture, vertex);
	}

	void UI_Static_Image::Hidden(bool e) {
		SetDrawActive(!e);
		SetUpdateActive(!e);
	}


	//------------------------------------------------------------------------------------------------
	//水平なスプライト画像 : Class
	//------------------------------------------------------------------------------------------------

	void UI_Horizontal_Sprite_Image::Draw() {

		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		m_vertices.push_back(VertexPositionColorTexture(Vec3(-m_xHalf, m_yHalf, 0.0f), color, Vec2(0.0f, 0.0f)));
		m_vertices.push_back(VertexPositionColorTexture(Vec3(m_xHalf, m_yHalf, 0.0f), color, Vec2(1.0f, 0.0f)));
		m_vertices.push_back(VertexPositionColorTexture(Vec3(-m_xHalf, -m_yHalf, 0.0f), color, Vec2(0.0f, 1.0f)));
		m_vertices.push_back(VertexPositionColorTexture(Vec3(m_xHalf, -m_yHalf, 0.0f), color, Vec2(1.0f, 1.0f)));

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);
	}

	void UI_Horizontal_Sprite_Image::SetIndex(int index) {
		if (index < 0) m_index = 0;
		if (index > GetMaxIndex()) m_index = GetMaxIndex();
		m_index = index;
		UpdateVertices();
	}

	void UI_Horizontal_Sprite_Image::UpdateVertices() {
		m_vertices[0].textureCoordinate = Vec2((m_index * m_cutOut.x) / m_vertex.x, 0.0f);
		m_vertices[1].textureCoordinate = Vec2(((m_index * m_cutOut.x) + m_cutOut.x) / m_vertex.x, 0.0f);
		m_vertices[2].textureCoordinate = Vec2((m_index * m_cutOut.x) / m_vertex.x, 1.0f);
		m_vertices[3].textureCoordinate = Vec2(((m_index * m_cutOut.x) + m_cutOut.x) / m_vertex.x, 1.0f);

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->UpdateVertices(m_vertices);
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
		CreateTab();
		CreateMasks();
		SetMaskIndex(m_maskIndex);
	}

	void UI_Tab::OnUpdate() {
		MaskMove();
	}

	void UI_Tab::Show(bool e) {
		Hidden(!e);
		if(e) SetMaskIndex(m_maskIndex);
	}

	void UI_Tab::Hidden(bool e) {
		if (!m_tab) return;
		m_tab->SetDrawActive(!e);
		for (auto& mask : m_masks) mask->SetDrawActive(!e);
		SetUpdateActive(!e);
	}

	void UI_Tab::CreateTab() {
		m_tab = GetStage()->AddGameObject<UI_Static_Image>(
			/*Vec2(1337.05f, 41.6f),*/
			Vec2(2048.0f * m_magnification, 64.0f * m_magnification),
			m_pos,
			Vec3(1.0f, 1.0f, 1.0f),
			m_layer,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_tabImageName
			);
	}

	void UI_Tab::CreateMasks() {
		Vec2 size = Vec2(512.0f, 64.0f) * m_magnification;
		for (int i = 0; i <= m_indexMax; i++) {
			auto mask = GetStage()->AddGameObject<UI_Static_Image>(
				size,
				/*Vec3(m_pos.x - ((size.x + (size.x / 2.0f) + m_space + m_space) - ((size.x + m_space) * i)), m_pos.y, m_pos.z),*/
				Vec3(m_pos.x - ((size.x + (size.x / 2.0f)) - (size.x * i)), m_pos.y, m_pos.z),
				Vec3(1.0f, 1.0f, 1.0f),
				m_layer,
				Col4(1.0f, 1.0f, 1.0f, 0.85f),
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
		for (int i = 0; i <= m_indexMax; i++) m_masks[i]->SetDrawActive(true);
		auto& mask = m_masks[index];
		mask->SetDrawActive(false);
	}


	//------------------------------------------------------------------------------------------------
	//食材アイコン : Class
	//------------------------------------------------------------------------------------------------

	void UI_Food_Icon::OnCreate() {
		Draw();
	}

	void UI_Food_Icon::SetCharacter(CharacterType type, int level) {
		if (level < 1) level = 1;
		if (level > 3) level = 3;
		m_type = type;
		m_level = level - 1;

		int index = 0;
		switch (m_type)
		{
		case CharacterType::SHRIMP:
			index = 3;
			break;
		case CharacterType::CHICKEN:
			index = 6;
			break;
		case CharacterType::DOUGHNUT:
			index = 9;
			break;
		}
		index += m_level;
		SetIndex(index);
	}


	//------------------------------------------------------------------------------------------------
	//スコア表 : Class
	//------------------------------------------------------------------------------------------------

	void UI_Score_Table::Show(bool e) {
		m_isShow = e;
		Hidden(!e);
		if (!e) return;

		UpdateTable();

		if (!m_isCreate) {
			CreateTableHeader();
			m_isCreate = true;
		}

		Sort();
		for (int i = m_lines.size(); i < m_characterStatuses.size(); i++) {
			CreateLine(m_characterStatuses[i], i);
		}
	}

	void UI_Score_Table::SetCharacterStatus(const CharacterStatus_s& status) {
		vector<CharacterStatus_s>::iterator it = find_if(m_characterStatuses.begin(), m_characterStatuses.end(), [status](const CharacterStatus_s& i) {
			return i.unique == status.unique;
		});
		it->playerName = status.playerName;
		it->kill = status.kill;
		it->death = status.death;
		it->score = status.score;
		it->isPlayer = status.isPlayer;
		UpdateTable();
	}

	void UI_Score_Table::CreateTableHeader() {
		float i = 363.0f;
		float iPlus = 330.0f;
		float t = 250.0f;
		float b = 380.0f;

		auto stage = GetStage();

		auto text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_headerFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 1), t, 1000.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"キル",
			m_layer,
			false
			);
		m_headerTexts.push_back(text);

		text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_headerFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 2), t, 1320.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"デス",
			m_layer,
			false
			);
		m_headerTexts.push_back(text);

		text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_headerFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 3), t, 1620.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"スコア",
			m_layer,
			false
			);
		m_headerTexts.push_back(text);
	}

	void UI_Score_Table::CreateLine(CharacterStatus_s& status, int index) {
		float space = 80.0f;
		float i = 363.0f;
		float iPlus = 337.0f;
		float t = 330.0f;
		float b = 330.0f;

		auto stage = GetStage();

		ScoreTableLine_s line;

		if (index) {
			auto separator = stage->AddGameObject<UI_Static_Image>(
				Vec2(1200.0f, 1.0f),
				Vec3(0.0f, 220.0f - (index * space), 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				m_layer,
				m_white,
				m_separatorImageName
				);
			line.separator = separator;
		} else {
			auto separator = stage->AddGameObject<UI_Static_Image>(
				Vec2(1200.0f, 3.0f),
				Vec3(0.0f, 220.0f - (index * space), 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				m_layer,
				m_white,
				m_separatorImageName
				);
			line.separator = separator;
		}

		auto playerBadge = stage->AddGameObject<UI_Static_Image>(
			Vec2(64.0f, 32.0f),
			Vec3(-650.0f, 175.0f - (index * space), 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			m_layer,
			m_white,
			m_playerBadgeImageName
			);
		playerBadge->Hidden(!status.isPlayer);
		line.playerBadge = playerBadge;

		auto text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_lineFontSize,
			m_white,
			Rect2D<float>(i, t + (index * space), 1556.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Left,
			status.playerName,
			m_layer,
			false
			);
		line.name = text;

		text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_lineFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 1), t + (index * space), 1000.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Center,
			to_wstring(status.kill),
			m_layer,
			false
			);
		line.kill = text;

		text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_lineFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 2), t + (index * space), 1300.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Center,
			to_wstring(status.death),
			m_layer,
			false
			);
		line.death = text;

		text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_lineFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 3), t + (index * space), 1580.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Center,
			to_wstring(status.score),
			m_layer,
			false
			);
		line.score = text;
		
		m_lines.push_back(line);
	}

	void UI_Score_Table::UpdateTable() {
		if (!m_isShow) return;
		Sort();
		for (int i = 0; i < m_lines.size(); i++) {
			auto& status = m_characterStatuses[i];
			auto& line = m_lines[i];
			line.name->UpdateText(status.playerName);
			line.kill->UpdateText(to_wstring(status.kill));
			line.death->UpdateText(to_wstring(status.death));
			line.score->UpdateText(to_wstring(status.score));
			line.playerBadge->Hidden(!status.isPlayer);
		}
	}

	void UI_Score_Table::Sort() {
		sort(m_characterStatuses.begin(), m_characterStatuses.end(), [](const CharacterStatus_s& a, const CharacterStatus_s& b) {
			return a.score > b.score;
		});
	}

	void UI_Score_Table::Hidden(bool e) {
		for (auto& text : m_headerTexts) text->SetDrawActive(!e);
		for (auto& line : m_lines) {
			line.name->SetDrawActive(!e);
			line.kill->SetDrawActive(!e);
			line.death->SetDrawActive(!e);
			line.score->SetDrawActive(!e);
			line.playerBadge->SetDrawActive(!e);
			line.separator->SetDrawActive(!e);
		}
	}


	//------------------------------------------------------------------------------------------------
	//キル詳細 : Class
	//------------------------------------------------------------------------------------------------
	
	void UI_Kill_Details::Show(bool e) {
		m_isShow = e;
		Hidden(!e);
		if (!e || !m_characterStatusKillDetails.size()) {
			return;
		}

		UpdateInfo();

		if (!m_isCreate) {
			CreateInfo();
			m_isCreate = true;
		}

		for (int i = m_icons.size(); i < m_characterStatusKillDetails.size(); i++) {
			CreateKillIcon(m_characterStatusKillDetails[i], i);
		}
	}

	void UI_Kill_Details::CreateKillIcon(CharacterKillDetails_s& details, int index) {
		Vec3 pos = Vec3(-625.0f, -215.0f, 0.0f);
		Vec2 size = Vec2(256.0f, 256.0f);
		Vec3 scale = Vec3(0.5f, 0.5f, 0.5f);
		int  digit = GetDigit(index);
		if (digit > 1) digit--;
		auto icon = GetStage()->AddGameObject<UI_Food_Icon>(
			Vec3(pos.x + ((size.x * scale.x + 10.0f) * (index % (int)pow(10, digit))), -(pos.y + ((index / 10) * (size.x * scale.x + 10.0f))), pos.z),
			scale,
			m_layer
			);
		icon->SetCharacter(details.type, details.level);
		m_icons.push_back(icon);
	}

	void UI_Kill_Details::CreateInfo() {
		auto stage = GetStage();
		m_killText = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_infoFontSize,
			m_white,
			Rect2D<float>(900.0f, 1000.0f, 1300.0f, m_infoFontSize + 18.0f + 1000.0f),
			StringSprite::TextAlignment::m_Center,
			L"キル： " + to_wstring(m_characterStatusKillDetails.size()),
			m_layer,
			false
			);

		m_scoreText = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_infoFontSize,
			m_white,
			Rect2D<float>(1300.0f, 1000.0f, 1700.0f, m_infoFontSize + 18.0f + 1000.0f),
			StringSprite::TextAlignment::m_Left,
			L"スコア： " + to_wstring(m_score),
			m_layer,
			false
			);
	}

	void UI_Kill_Details::UpdateInfo() {
		if (!m_killText || !m_scoreText || !m_isShow) return;
		m_killText->UpdateText(L"キル： " + to_wstring(m_characterStatusKillDetails.size()));
		m_scoreText->UpdateText(L"スコア： " + to_wstring(m_score));
	}

	void UI_Kill_Details::Hidden(bool e) {
		for (auto& icon : m_icons) icon->SetDrawActive(!e);
		if (!m_killText || !m_scoreText) return;
		m_killText->SetDrawActive(!e);
		m_scoreText->SetDrawActive(!e);
	}

	int UI_Kill_Details::GetDigit(int num) {
		int digit = 0;
		while (num != 0) {
			num /= 10;
			digit++;
		}
		return digit;
	}


	//------------------------------------------------------------------------------------------------
	//ポーズ画面 : Class
	//------------------------------------------------------------------------------------------------

	void UI_The_World::OnCreate() {
		auto stage = GetStage();

		m_scoreTable = stage->AddGameObject<UI_Score_Table>(8, m_layer);
		m_scoreTable->SetCharacterStatuses(m_characterStatuses);
		m_killDetails = stage->AddGameObject<UI_Kill_Details>(m_layer);

		SetTestDeta();
	}

	void UI_The_World::OnUpdate() {
		Key();
	}

	void UI_The_World::OnUpdate2() {
		ChangeTab();
	}

	void UI_The_World::Show(bool e) {
		m_isShow = e;
		if (!e) {
			AllHidden(!e);
			m_oldIndex = -1;
			return;
		}
		ShowBase(e);
		ShowTitle(e);
		ShowTab(e);
		ShowBack(e);
	}

	void UI_The_World::AllHidden(bool e) {
		ShowBase(!e);
		ShowTitle(!e);
		ShowTab(!e);
		m_scoreTable->Show(!e);
		ShowOperation(!e);
		m_killDetails->Show(!e);
		ShowTitleback(!e);
		ShowBack(!e);
	}

	void UI_The_World::ChangeTab() {
		if (!m_isShow) return;
		m_index = m_tab->GetIndex();
		if (m_index == m_oldIndex) return;
		switch (m_index)
		{
		case 0:
			m_scoreTable->Show(true);
			ShowOperation(false);
			m_killDetails->Show(false);
			ShowTitleback(false);
			break;
		case 1:
			m_scoreTable->Show(false);
			ShowOperation(true);
			m_killDetails->Show(false);
			ShowTitleback(false);
			break;
		case 2:
			m_scoreTable->Show(false);
			ShowOperation(false);
			m_killDetails->Show(true);
			m_killDetails->SetScore(m_scoreTable->GetPlayerStatus().score);
			ShowTitleback(false);
			break;
		case 3:
			m_scoreTable->Show(false);
			ShowOperation(false);
			m_killDetails->Show(false);
			ShowTitleback(true);
			break;
		}
		m_oldIndex = m_index;
	}

	void UI_The_World::ShowBase(bool e) {
		if (!m_base && !e) return;
		if (m_base) {
			m_base->SetDrawActive(e);
		}
		else {
			m_base = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(1920.0f, 1080.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				m_baseLayer,
				Col4(1.0f, 1.0f, 1.0f, 0.9f),
				m_baseImageName
				);
		}
	}

	void UI_The_World::ShowTab(bool e) {
		if (!m_tab && !e) return;
		if (m_tab) {
			m_tab->Show(e);
		}
		else {
			m_tab = GetStage()->AddGameObject<UI_Tab>(Vec3(0.0f, 400.0f, 0.0f), 0.7f, m_layer);
		}
	}

	void UI_The_World::ShowTitle(bool e) {
		if (!m_title && !e) return;
		if (m_title) {
			m_title->SetDrawActive(e);
		} else {
			m_title = GetStage()->AddGameObject<UI_Sprite_Text>(
				m_fontName,
				m_titleFontSize,
				m_white,
				Rect2D<float>(0.0f, 30.0f, 1920.0f, m_titleFontSize + 18.0f + 30.0f),
				StringSprite::TextAlignment::m_Center,
				L"ポーズ",
				m_layer,
				false
				);
		}
	}

	void UI_The_World::ShowOperation(bool e) {
		if (m_operation) {
			m_operation->SetDrawActive(e);
		} else {
			m_operation = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(1280.0f, 720.0f),
				Vec3(0.0f, -80.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				m_layer,
				m_white,
				m_operationImageName
				);
			ShowOperation(e);
		}
	}

	void UI_The_World::ShowTitleback(bool e) {
		if (m_titleback) {
			m_titleback->SetDrawActive(e);
		}
		else {
			m_titleback = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(1255.0f, 203.0f),
				Vec3(0.0f, -80.0f, 0.0f),
				Vec3(0.8f, 0.8f, 0.8f),
				m_layer,
				m_white,
				m_titlebackImageName
				);
			ShowTitleback(e);
		}
	}

	void UI_The_World::ShowBack(bool e) {
		if (m_back) {
			m_back->SetDrawActive(e);
		}
		else {
			m_back = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(541.0f, 204.0f),
				Vec3(-820.0f, -470.0f, 0.0f),
				Vec3(0.4f, 0.4f, 0.4f),
				m_layer,
				m_white,
				m_backImageName
				);
			ShowBack(e);
		}
	}

	void UI_The_World::Key() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_index == 3 && (KeyState.m_bPressedKeyTbl['Q'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}
		if (m_index == 3 && (KeyState.m_bPressedKeyTbl['E'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}
		if (KeyState.m_bPressedKeyTbl['P'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
			Show(false);
		}
	}

	void UI_The_World::SetTestDeta() {
		vector<CharacterStatus_s> statuses;
		statuses.push_back({ L"ポテト", 10, 2, 5260, true, 0 });
		statuses.push_back({ L"チキン", 10, 2, 3000, false, 1 });
		statuses.push_back({ L"ドーナツ", 10, 2, 3000, false, 2 });
		statuses.push_back({ L"エビ", 10, 2, 3000, false, 3 });
		statuses.push_back({ L"ポテト", 10, 2, 3000, false, 4 });
		statuses.push_back({ L"チキン", 10, 2, 3000, false, 5 });
		statuses.push_back({ L"ドーナツ", 10, 2, 3000, false, 6 });
		statuses.push_back({ L"エビ", 10, 2, 3000, false, 7 });
		SetCharacterStatuses(statuses);

		vector<CharacterKillDetails_s> killDetails;
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		SetCharacterKillDetails(killDetails);
	}


	//------------------------------------------------------------------------------------------------
	//キャラクターステータス : Class
	//------------------------------------------------------------------------------------------------

	void UI_Character_Status::OnCreate() {
		SetDrawLayer(m_layer);
		Mat4x4 mat;
		mat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		SetToAnimeMatrix(mat);

		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_scale);
		PtrTrans->SetPosition(m_pos);
		SS5ssae::OnCreate();
	}

	void UI_Character_Status::OnUpdate() {
		float time = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(time);
	}

	void UI_Character_Status::ChangeCharacterStatus(CharacterType type) {
		wstring animName = L"";
		float time = 0.0f;
		switch (type)
		{
		case basecross::POTATO:
			animName = L"Status_ver2_Potato";
			break;
		case basecross::SHRIMP:
			animName = L"Status_ver2_Shrimp";
			break;
		case basecross::CHICKEN:
			animName = L"Status_ver2_Chicken";
			break;
		case basecross::DOUGHNUT:
			animName = L"Status_ver2_Doughnut";
			break;
		}
		ChangeAnimation(animName, time);
		SetFps(15.0f);
		SetLooped(false);
	}


}