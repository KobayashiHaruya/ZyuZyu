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

	void Title_UI::OnCreate() {
		Draw();
	}

	void Operation_UI::OnCreate() {
		Draw();
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
		SetScale(scale);
		SetTexture(texture, vertex);
	}

	void UI_Static_Image::SetPosition(const Vec3& pos) {
		m_pos = pos;
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(pos);
	}

	void UI_Static_Image::SetScale(const Vec3& scale) {
		m_scale = scale;
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(scale);
	}

	void UI_Static_Image::SetColor(const Col4& color) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(color);
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
		UpdateVertices();
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

	void UI_Horizontal_Sprite_Image::SetColor(const Col4& color) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(color);
	}

	void UI_Horizontal_Sprite_Image::Hidden(const bool e) {
		SetDrawActive(!e);
		SetUpdateActive(!e);
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

	void Result_UI::OnCreate() {
		Draw();
	}

	void Score_UI::OnCreate() {
		float score = static_cast<float>(m_Score / m_place % 10);
		float Width = 69.1f / 691.0f;	//各数字の幅をテクスチャ座標に変換

		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices = {
			{Vec3(0,    0, 0), color, Vec2((score + 0) * Width, 0.0f)}, // 頂点１
			{Vec3(50,    0, 0), color, Vec2((score + 1) * Width, 0.0f)}, // 頂点２
			{Vec3(0, -100, 0), color, Vec2((score + 0) * Width, 1.0f)}, // 頂点３
			{Vec3(50, -100, 0), color, Vec2((score + 1) * Width, 1.0f)}, // 頂点４

		};
		indices = {0, 1, 2, 2, 1, 3 };
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);
	}

	void Score_UI::OnUpdate2() {
		auto resultstage = dynamic_pointer_cast<ResultStage>(GetStage());

		float n = static_cast<float>(resultstage->GetScore() / m_place % 10); // 表示したい数字
		float w = 69.1f / 691.0f; // 各数字の幅をテクスチャ座標に変換する

		vertices[0].textureCoordinate.x = (n + 0) * w;
		vertices[1].textureCoordinate.x = (n + 1) * w;
		vertices[2].textureCoordinate.x = (n + 0) * w;
		vertices[3].textureCoordinate.x = (n + 1) * w;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->UpdateVertices(vertices); // 頂点データを更新する

	}

	void UI_Character_Select_Mask_Image::MaskMove() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLX = 0.0f;
		if (cntlVec[0].bConnected) {
			fThumbLX = cntlVec[0].fThumbLX;
		}

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
		it->type = status.type;
		it->kill = status.kill;
		it->death = status.death;
		it->score = status.score;
		it->isPlayer = status.isPlayer;
		UpdateTable();
	}

	void UI_Score_Table::ChangeLogo(const shared_ptr<UI_Static_Image>& image, const CharacterType& type) {
		switch (type)
		{
		case CharacterType::CHICKEN:
			image->SetTexture(L"ChickenLogo.png", Vec2(631.0f, 278.0f), Vec3(0.2f));
			break;
		case CharacterType::DOUGHNUT:
			image->SetTexture(L"DoughnutLogo.png", Vec2(631.0f, 264.0f), Vec3(0.2f));
			break;
		case CharacterType::POTATO:
			image->SetTexture(L"PotatoLogo.png", Vec2(621.0f, 285.0f), Vec3(0.2f));
			break;
		case CharacterType::SHRIMP:
			image->SetTexture(L"ShrimpLogo.png", Vec2(631.0f, 298.0f), Vec3(0.2f));
			break;
		default:
			break;
		}
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
			Rect2D<float>(i + (iPlus * 0 - 500.0f), t, 1000.0f, b),
			StringSprite::TextAlignment::m_Center,
			L"ランク",
			m_layer,
			false
			);
		m_headerTexts.push_back(text);

		text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_headerFontSize,
			m_white,
			Rect2D<float>(i + (iPlus * 1 + 250.0f), t, 1080.0f, b),
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
			Rect2D<float>(i + (iPlus * 2 + 125.0f), t, 1330.0f, b),
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
		}
		else {
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

		auto rank = stage->AddGameObject<UI_Number>(
			Vec2(-525.0f, 180.0f - (index * 80.0f)),
			1,
			Col4(1.0f),
			Number::NumberAlign::CENTER,
			0.0f,
			Vec2(0.4f),
			m_layer
			);
		rank->SetValue(index + 1);
		m_ranks.push_back(rank);

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

		shared_ptr<UI_Static_Image> logo = stage->AddGameObject<UI_Static_Image>(
			Vec2(64.0f, 32.0f),
			Vec3(-260.0f, 180.0f - (index * space), 0.0f),
			Vec3(0.2f),
			m_layer,
			m_white,
			L"dot.png"
			);
		ChangeLogo(logo, status.type);
		line.logo = logo;
/*
		auto text = stage->AddGameObject<UI_Sprite_Text>(
			m_fontName,
			m_lineFontSize,
			m_white,
			Rect2D<float>(i + 180.0f, t + (index * space), 1556.0f, b + (index * space)),
			StringSprite::TextAlignment::m_Left,
			GetCharacterTypeToString(status.type),
			m_layer,
			false
			);
		line.name = text;*/

		auto number = stage->AddGameObject<UI_Number>(
			Vec2(50.0f, 180.0f - (index * 80.0f)),
			5,
			Col4(1.0f),
			Number::NumberAlign::CENTER,
			10.0f,
			Vec2(0.4f),
			m_layer
			);
		number->SetValue(status.kill);
		line.kill = number;

		number = stage->AddGameObject<UI_Number>(
			Vec2(280.0f, 180.0f - (index * 80.0f)),
			5,
			Col4(1.0f),
			Number::NumberAlign::CENTER,
			10.0f,
			Vec2(0.4f),
			m_layer
			);
		number->SetValue(status.death);
		line.death = number;

		number = stage->AddGameObject<UI_Number>(
			Vec2(520.0f, 180.0f - (index * 80.0f)),
			5,
			Col4(1.0f),
			Number::NumberAlign::CENTER,
			10.0f,
			Vec2(0.4f),
			m_layer
			);
		number->SetValue(status.score);
		line.score = number;
		
		m_lines.push_back(line);
	}

	void UI_Score_Table::UpdateTable() {
		if (!m_isShow) return;
		Sort();
		for (int i = 0; i < m_lines.size(); i++) {
			auto& status = m_characterStatuses[i];
			auto& line = m_lines[i];
			ChangeLogo(line.logo, status.type);
			//line.name->UpdateText(GetCharacterTypeToString(status.type));
			line.kill->SetValue(status.kill);
			line.death->SetValue(status.death);
			line.score->SetValue(status.score);
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
		for (auto& rank : m_ranks) rank->Hidden(e);
		for (auto& line : m_lines) {
			line.logo->Hidden(e);
			line.kill->Hidden(e);
			line.death->Hidden(e);
			line.score->Hidden(e);
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
			m_base->Hidden(!e);
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
			m_title->Hidden(!e);
		} else {
			m_title = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(531.0f, 171.0f),
				Vec3(0.0f, 485.0f, 0.0f),
				Vec3(0.4f),
				m_layer,
				m_white,
				m_titleImageName
				);
		}
	}

	void UI_The_World::ShowOperation(bool e) {
		if (m_operation) {
			m_operation->Hidden(!e);
		} else {
			m_operation = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(1280.0f, 720.0f),
				Vec3(0.0f, -80.0f, 0.0f),
				Vec3(1.0f),
				m_layer,
				m_white,
				m_operationImageName
				);
			ShowOperation(e);
		}
	}

	void UI_The_World::ShowTitleback(bool e) {
		if (m_titleback) {
			m_titleback->Hidden(!e);
			m_selectback->Hidden(!e);
		}
		else {
			m_titleback = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(532.0f, 147.0f),
				Vec3(0.0f, -180.0f, 0.0f),
				Vec3(0.8f),
				m_layer,
				m_white,
				m_titlebackImageName
				);
			m_selectback = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(524.0f, 147.0f),
				Vec3(0.0f, 100.0f, 0.0f),
				Vec3(0.8f),
				m_layer,
				m_white,
				m_selectbackImageName
				);
			ShowTitleback(e);
		}
	}

	void UI_The_World::ShowBack(bool e) {
		if (m_return && m_move) {
			m_return->Hidden(!e);
			m_move->Hidden(!e);
		}
		else {
			m_return = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(614.0f, 82.0f),
				Vec3(-820.0f, -450.0f, 0.0f),
				Vec3(0.4f, 0.4f, 0.4f),
				m_layer,
				m_white,
				m_returnImageName
				);
			m_move = GetStage()->AddGameObject<UI_Static_Image>(
				Vec2(825.0f, 83.0f),
				Vec3(-779.0f, -500.0f, 0.0f),
				Vec3(0.4f, 0.4f, 0.4f),
				m_layer,
				m_white,
				m_moveImageName
				);
			ShowBack(e);
		}
	}

	void UI_The_World::Key() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_index == 3 && (KeyState.m_bPressedKeyTbl['Q'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			//App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}
		if (m_index == 3 && (KeyState.m_bPressedKeyTbl['E'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			//App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}
		/*if (KeyState.m_bPressedKeyTbl['P'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
			Show(false);
		}*/
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


	//------------------------------------------------------------------------------------------------
	//PinP : Class
	//------------------------------------------------------------------------------------------------

	void PinP::OnCreate() {
		CreateCamera();
		if (m_isEdge && !m_edgeImage) CreateEdge();

		m_oldShowViewTopLeftPos = m_showViewTopLeftPos;
		m_oldHideViewTopLeftPos = m_hideViewTopLeftPos;
		Hidden(true);
	}

	void PinP::OnUpdate() {
		if (m_isEdge && !m_edgeImage) CreateEdge();
		m_camera->OnUpdate();
		Move();
	}

	Vec2 PinP::GetResolution() {
		switch (m_aspectType)
		{
		case PinPAspectType::SQUARE:
			return Vec2(1.0f, 1.0f);
		case PinPAspectType::HD:
			return Vec2(16.0f, 9.0f);
		case PinPAspectType::SD:
			return Vec2(4.0f, 3.0f);
		}
	}

	void PinP::In(const PinPAction action) {
		m_mode = true;
		m_active = true;
		m_action = action;
		m_showViewTopLeftPos = m_oldShowViewTopLeftPos;
		m_hideViewTopLeftPos = GetHideTopLeftPos(action);

		//UpdateEdge(Vec2(m_hideViewTopLeftPos.x, m_hideViewTopLeftPos.y));
		//if(m_edgeImage) m_edgeImage->Hidden(false);

		SetViewTopLeftPos(m_hideViewTopLeftPos);
	}

	void PinP::Out(const PinPAction action) {
		m_mode = false;
		m_active = true;
		m_action = action;
		m_showViewTopLeftPos = m_oldShowViewTopLeftPos;
		m_hideViewTopLeftPos = GetHideTopLeftPos(action);
		SetViewTopLeftPos(m_showViewTopLeftPos);
	}

	void PinP::Hidden(const bool e) {
		m_active = !e;
		auto& app = App::GetApp();
		m_edgeImage->Hidden(e);

		if (e) {
			auto zero = Vec2(app->GetGameWidth(), app->GetGameHeight());
			m_showViewTopLeftPos = zero;
			m_hideViewTopLeftPos = zero;
			SetViewTopLeftPos(zero);
		}
		else
		{
			if (m_useCharacter.unique != 0) In(m_action);
		}
	}

	void PinP::SetAt(const Vec3& at) {
		m_camera->SetAt(at);
	}

	void PinP::SetEye(const Vec3& eye) {
		m_camera->SetEye(eye);
	}

	void PinP::CreateCamera() {
		auto resolution = GetResolution();
		resolution.x *= m_scale;
		resolution.y *= m_scale;

		m_view = { m_showViewTopLeftPos.x, m_showViewTopLeftPos.y, resolution.x, resolution.y, 0.0f, 1.0f };

		m_camera = ObjectFactory::Create<Camera>();
		m_camera->SetViewPort(m_view);
		m_camera->CalculateMatrix();
		m_camera->SetNear(2);

		auto viewPort = dynamic_pointer_cast<MultiView>(GetStage()->GetView());
		m_viewIndex = viewPort->AddView(m_view, m_camera);
	}

	void PinP::CreateEdge() {
		auto resolution = GetResolution();
		resolution.x *= m_scale;
		resolution.y *= m_scale;

		m_edgeImage = GetStage()->AddGameObject<UI_Static_Image>(
			resolution,
			Vec3(0.0f),
			Vec3(m_edgeScale),
			m_edgeLayer,
			m_edgeColor,
			m_edgeImageName
			);
		m_edgeImage->Hidden(true);
	}

	void PinP::UpdateEdge(const Vec2& pos) {
		if (!m_edgeImage || !m_active) return;
		if (!m_edgeImage->GetDrawActive()) m_edgeImage->Hidden(false);
		auto& app = App::GetApp();
		auto halfGame = Vec2(app->GetGameWidth() / 2.0f, app->GetGameHeight() / 2.0f);

		auto resolution = GetResolution();
		resolution.x *= m_scale;
		resolution.y *= m_scale;
		auto halfResolution = Vec2(resolution.x / 2.0f, resolution.y / 2.0f);

		auto movePos = Vec3(0.0f);
		if (pos.x <= halfGame.x) movePos.x = (pos.x + halfResolution.x) - halfGame.x;
		if (pos.x >= halfGame.x) movePos.x = halfGame.x + pos.x;
		if (pos.y <= halfGame.y) movePos.y = halfGame.y - (pos.y + halfResolution.y);
		if (pos.y >= halfGame.y) movePos.y = pos.y + halfGame.y;
		m_edgeImage->SetPosition(movePos);
	}

	Vec2 PinP::GetHideTopLeftPos(const PinPAction action) {
		auto& app = App::GetApp();
		auto w = app->GetGameWidth();
		auto h = app->GetGameHeight();

		switch (action)
		{
		case PinPAction::LEFT:
			return Vec2(-(m_view.Width + m_showViewTopLeftPos.x), m_showViewTopLeftPos.y);
		case PinPAction::RIGHT:
			return Vec2(w, m_showViewTopLeftPos.y);
		case PinPAction::TOP:
			return Vec2(m_showViewTopLeftPos.x, -(m_view.Height + m_showViewTopLeftPos.y));
		case PinPAction::UNDER:
			return Vec2(m_showViewTopLeftPos.x, h);
		case PinPAction::NONE:
			return Vec2(m_showViewTopLeftPos.x, m_showViewTopLeftPos.y);
		}
	}

	void PinP::SetViewTopLeftPos(Vec2& pos) {
		auto viewPort = dynamic_pointer_cast<MultiView>(GetStage()->GetView());
		m_view.TopLeftX = pos.x;
		m_view.TopLeftY = pos.y;
		viewPort->SetViewport(m_viewIndex, m_view);
	}

	Viewport PinP::GetView() {
		return dynamic_pointer_cast<MultiView>(GetStage()->GetView())->GetViewport(m_viewIndex);
	}

	void PinP::Move() {
		auto time = App::GetApp()->GetElapsedTime();

		Easing<Vec2> easing;

		//現在のTopLeftPosを取得する
		Vec2 nowTopLeftPos(m_view.TopLeftX, m_view.TopLeftY);
		Vec2 movePos(0.0f);

		if (m_active && m_mode) {
			movePos = easing.Linear(Vec2(nowTopLeftPos.x, nowTopLeftPos.y), m_showViewTopLeftPos, time, 0.4);
			SetViewTopLeftPos(movePos);
			UpdateEdge(movePos);
		}
		
		if(m_active && !m_mode) {
			movePos = easing.Linear(Vec2(nowTopLeftPos.x, nowTopLeftPos.y), m_hideViewTopLeftPos, time, 0.4);
			SetViewTopLeftPos(movePos);
			UpdateEdge(movePos);
		}
	}


	//------------------------------------------------------------------------------------------------
	//数字 : Class
	//------------------------------------------------------------------------------------------------

	void UI_Number::OnCreate() {
		CreateNumberImagies();
	}

	void UI_Number::SetValue(const unsigned int value) {
		m_value = value;
		UpdateNumberImagies();
	}

	void UI_Number::SetColor(const Col4& color) {
		m_color = color;
		UpdateNumberImagies();
	}

	void UI_Number::Hidden(const bool e) {
		for (auto& image : m_numberImagies) {
			image->Hidden(e);
		}
		SetDrawActive(!e);
		SetUpdateActive(!e);
	}

	void UI_Number::CreateNumberImagies() {
		auto stage = GetStage();
		for (int i = 0; i < m_digit; i++) {
			auto pos = GetImagePosition(m_digit, i, m_position, m_align);
			auto number = GetNumber(m_value, (m_digit - 1) - i);
			auto image = stage->AddGameObject<UI_Horizontal_Sprite_Image>(
				m_vertex,
				Vec3(pos),
				Vec3(m_scale),
				m_layer,
				m_color,
				m_numberImageName,
				m_cutOut
				);
			image->Draw();
			image->SetIndex(number);
			m_numberImagies.push_back(image);
		}
		UpdateNumberImagies();
	}

	void UI_Number::UpdateNumberImagies() {
		for (int i = 0; i < m_numberImagies.size(); i++) {
			auto number = GetNumber(m_value, (m_digit - 1) - i);
			auto image = m_numberImagies[i];
			image->SetColor(m_color);
			image->SetIndex(number);
			image->Hidden(false);
		}

		if (m_align == Number::NumberAlign::LEFT || m_align == Number::NumberAlign::CENTER || m_align == Number::NumberAlign::RIGHT) {
			auto zeroEndIndex = 0;
			for (auto& image : m_numberImagies) {
				if (!image->GetIndex() && zeroEndIndex + 1 != m_numberImagies.size()) {
					image->Hidden(true);
					zeroEndIndex++;
				}
				else
				{
					break;
				}
			}

			if (m_align == Number::NumberAlign::CENTER || m_align == Number::NumberAlign::RIGHT) {

				for (int i = zeroEndIndex, j = 0; i < m_numberImagies.size(); i++, j++) {
					auto image = m_numberImagies[i];
					auto trans = image->GetComponent<Transform>();
					auto pos = GetImagePosition(m_digit - zeroEndIndex ,j, m_position, m_align);
					trans->SetPosition(Vec3(pos));
				}
			}
		}
	}

	unsigned int UI_Number::CheckDigit(const unsigned int value) {
		unsigned int digit = 0;
		unsigned int target = value;
		while (target) {
			target /= 10;
			digit++;
		}
		return digit;
	}

	Vec2 UI_Number::GetImagePosition(const unsigned int digit, const unsigned int index, const Vec2& startPosition, const Number::NumberAlign align) {
		auto res = Vec2(startPosition.x, startPosition.y);
		float c, d, t, e;
		switch (align)
		{
		case Number::NumberAlign::LEFT:
		case Number::NumberAlign::ZERO_LEFT:
			c = (digit - 1);
			d = c * m_cutOut.x;
			t = index * m_cutOut.x + (m_space * index);
			e = t - d;
			res.x += (e * m_scale.x) - (m_space * c * (m_scale.x));
			break;
		case Number::NumberAlign::CENTER:
		case Number::NumberAlign::ZERO_CENTER:
			c = ((digit - 1) / 2.0f);
			d = c * m_cutOut.x;
			t = index * m_cutOut.x + (m_space * index);
			e = t - d;
			res.x += (e * m_scale.x) - (m_space * c * (m_scale.x));
			break;
		case Number::NumberAlign::RIGHT:
		case Number::NumberAlign::ZERO_RIGHT:
			res.x += ((m_cutOut.x + m_space) * m_scale.x) * index;
			break;
		}

		return res;
	}

	unsigned int UI_Number::GetNumber(const unsigned int value, const unsigned int index) {
		auto res = 0;
		res = (value / pow(10, index));
		res %= 10;
		return res;
	}


	//------------------------------------------------------------------------------------------------
	//プレイヤーUI : Class
	//------------------------------------------------------------------------------------------------


	void UI_Player::OnCreate() {
		Draw();
	}

	void UI_PlayerGun::OnCreate() {
		Draw();
	}

	void UI_PlayerGun::OnUpdate() {
		bool weapon = GetStage()->GetSharedGameObject<Player>(L"Player")->GetGun();
		auto trans = GetComponent<Transform>();
		if (weapon) {
			trans->SetScale(m_scale);
		}
		else {
			trans->SetScale(Vec3(-m_scale.x, m_scale.y, m_scale.z));
		}

	}


	void UI_PlayerWeapon::OnCreate() {
		Draw();
	}

	void UI_PlayerWeapon::OnUpdate() {
		int index;
		if (m_weapon) {
			index = GetStage()->GetSharedGameObject<Player>(L"Player")->GetWeaponO();
		}
		else {

			index = GetStage()->GetSharedGameObject<Player>(L"Player")->GetWeaponT();
		}
		SetIndex(index);

	}

	void UI_PlayerGrenade::OnCreate() {
		Draw();
		X = Vec2(1.0f,-1.0f) * m_Vertex.x / 2.0f;
		Y = m_Vertex.y / 2.0f;

	}

	void UI_PlayerGrenade::OnUpdate() {

		float time;
		if (m_type) {
			time = GetStage()->GetSharedGameObject<Player>(L"Player")->GetSGTime();

		}
		else {
			time = GetStage()->GetSharedGameObject<Player>(L"Player")->GetTGTime();
		}

		if (time < m_time) {
			X.y = time / m_time;
			X.y = (m_Vertex.x * X.y) - X.x;

			vector<VertexPositionColorTexture> vertices;
			Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			vertices.push_back(VertexPositionColorTexture(Vec3(-X.y, Y, 0), color, Vec2(0.0f, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(X.x, Y, 0), color, Vec2(1.0f, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-X.y, -Y, 0), color, Vec2(0.0f, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(X.x, -Y, 0), color, Vec2(1.0f, 1.0f)));

			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->UpdateVertices(vertices);
		}
	}

	void UI_PlayerAmmo::OnCreate() {
		float xPiecesize = 1.0f / (float)m_NumberOfDigits;
		float helfSize = 0.5f;

		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;
			float vertex1 = vertex0 + xPiecesize;
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 1.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 1.0f)));
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);

		ptrDraw->SetDiffuse(Col4(0.2f, 0.2f, 0.2f, 1.0f));

		SetDrawLayer(15);
	
		SetAlphaActive(true);		

	}

	void UI_PlayerAmmo::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		float ammo;
		m_gun = player->GetGun();
		if (m_rem) {
			if (m_gun) {
				ammo = player->GetAmmoO();
			}
			else {
				ammo = player->GetAmmoT();
			}
		}
		else {
			if (m_gun) {
				ammo = player->GetDAmmoO();
			}
			else {
				ammo = player->GetDAmmoT();
			}
		}

		if (ammo < 10) {
			m_NumberOfDigits = 1;
		}
		else if (ammo < 100) {
			m_NumberOfDigits = 2;
		}
		else if(ammo < 1000) {
			m_NumberOfDigits = 3;
		}
		else {
			m_NumberOfDigits = 4;
		}


		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)ammo) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(m_BackupVertices[verNum].position, uv0);
			newVertices.push_back(v);

			Vec2 uv1 = m_BackupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(m_BackupVertices[verNum + 1].position, uv1);
			newVertices.push_back(v);

			Vec2 uv2 = m_BackupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(m_BackupVertices[verNum + 2].position, uv2);
			newVertices.push_back(v);

			Vec2 uv3 = m_BackupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(m_BackupVertices[verNum + 3].position, uv3);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}

	void UI_PlayerGatling::OnCreate() {
		Draw();
	}

	void UI_PlayerGatlingAmmo::OnCreate() {
		float xPiecesize = 1.0f / (float)m_NumberOfDigits;
		float helfSize = 0.5f;

		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;
			float vertex1 = vertex0 + xPiecesize;
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 1.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 1.0f)));
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);

		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));

		SetDrawLayer(15);

		SetAlphaActive(true);

	}

	void UI_PlayerGatlingAmmo::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		float ammo = player->GetGatlingAmmo();


		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)ammo) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(m_BackupVertices[verNum].position, uv0);
			newVertices.push_back(v);

			Vec2 uv1 = m_BackupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(m_BackupVertices[verNum + 1].position, uv1);
			newVertices.push_back(v);

			Vec2 uv2 = m_BackupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(m_BackupVertices[verNum + 2].position, uv2);
			newVertices.push_back(v);

			Vec2 uv3 = m_BackupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(m_BackupVertices[verNum + 3].position, uv3);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}

	void UI_PlayerDamage::OnCreate() {
		float xPiecesize = 1.0f / (float)m_NumberOfDigits;
		float helfSize = 0.5f;

		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;
			float vertex1 = vertex0 + xPiecesize;
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 1.0f)));
			m_BackupVertices.push_back(VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 1.0f)));
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);

		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));

		SetDrawLayer(12);

		SetAlphaActive(true);

	}

	void UI_PlayerDamage::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		int damage = GetStage()->GetSharedGameObject<Player>(L"Player")->GetDamage();

		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)damage) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(m_BackupVertices[verNum].position, uv0);
			newVertices.push_back(v);

			Vec2 uv1 = m_BackupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(m_BackupVertices[verNum + 1].position, uv1);
			newVertices.push_back(v);

			Vec2 uv2 = m_BackupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(m_BackupVertices[verNum + 2].position, uv2);
			newVertices.push_back(v);

			Vec2 uv3 = m_BackupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(m_BackupVertices[verNum + 3].position, uv3);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}

	void UI_CountdownTimer::OnCreate() {
		auto stage = GetStage();
		auto pos = Vec2(60.0f * m_scale.x, 0.0f * m_scale.y);
		m_second = stage->AddGameObject<UI_Number>(
			m_pos + pos,
			m_digit,
			m_color,
			Number::NumberAlign::ZERO_RIGHT,
			m_space,
			m_scale,
			m_layer
			);
		m_minute = stage->AddGameObject<UI_Number>(
			m_pos - pos,
			m_digit,
			m_color,
			Number::NumberAlign::ZERO_LEFT,
			m_space,
			m_scale,
			m_layer
			);
		m_colon = stage->AddGameObject<UI_Static_Image>(
			Vec2(64.0f, 128.0f),
			Vec3(m_pos),
			Vec3(m_scale),
			m_layer,
			m_color,
			m_colonImageName
			);

		UpdateTime();
	}

	void UI_CountdownTimer::OnUpdate2() {
		if (!m_isStart) return;
		auto eTime = App::GetApp()->GetElapsedTime();
		m_count += eTime;

		if (m_count >= 1.0f && m_time > 0) {
			m_count = NULL;
			m_time--;
			if (m_time < m_showingTime) {
				m_showingTime--;
				UpdateTime();
			}
		}
	}

	void UI_CountdownTimer::UpdateTime() {
		auto a = m_showingTime / 60;
		auto b = m_showingTime % 60;
		m_second->SetValue(b);
		m_minute->SetValue(a);
	}


	//------------------------------------------------------------------------------------------------
	//キルアイコン : Class
	//------------------------------------------------------------------------------------------------

	void UI_Kill_Icon::OnCreate() {
		if (m_level < 1) m_level = 1;
		if (m_level > 3) m_level = 3;
		m_level = m_level - 1;

		int index = 0;
		switch (m_type)
		{
		case CharacterType::CHICKEN:
			index = 3;
			break;
		case CharacterType::POTATO:
			index = 6;
			break;
		case CharacterType::DOUGHNUT:
			index = 9;
			break;
		}
		index += m_level;
		Draw();
		SetIndex(index);
	}

	void UI_Kill_Icon::OnUpdate() {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		float time = App::GetApp()->GetElapsedTime();
		m_disTime -= time;
		if (m_color.w <= 0.0f) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
		if (m_disTime <= 0.0f) {
			m_color.w -= time * 5.0f;
		}
		ptrDraw->SetDiffuse(m_color);
	}


	void Result_Curtain::OnCreate() {
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
		SetLooped(false);
	}

	void Result_Curtain::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float time = App::GetApp()->GetElapsedTime()*2.5f;
		int flame = 70;
		if (m_time <= 32.0f / 24.0f) {
			UpdateAnimeTime(time);
		}
		else {
			UpdateAnimeTime(0);
		}
		m_count += 1;
		m_time += time;

		if (KeyState.m_bPressedKeyTbl[VK_SPACE] || KeyState.m_bPushKeyTbl['W'] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			m_time = -10;
		}


	}


	//------------------------------------------------------------------------------------------------
	//UI_Flash_Image : Class
	//------------------------------------------------------------------------------------------------

	void UI_Flash_Image::OnCreate() {
		Draw();
		auto color = GetColor();
		color.setW(0.0f);
		SetColor(color);
	}

	void UI_Flash_Image::OnUpdate2() {
		if (m_in)
			In();
		else
			Out();
	}

	void UI_Flash_Image::In() {
		auto time = App::GetApp()->GetElapsedTime();
		auto color = GetColor();
		if (m_count <= m_flashinterval) {
			m_count += time;
			auto alpha = m_count / m_flashinterval;
			color.w = alpha;
			SetColor(color);
		}
		else
		{
			m_in = false;
		}
	}

	void UI_Flash_Image::Out() {
		auto time = App::GetApp()->GetElapsedTime();
		auto color = GetColor();
		if (m_count >= 0.0f) {
			m_count -= time;
			auto alpha = m_count / m_flashinterval;
			color.w = alpha;
			SetColor(color);
		}
		else
		{
			m_in = true;
		}
	}


	void Result_Icon_UI::OnCreate() {
		if (m_level < 1) m_level = 1;
		if (m_level > 3) m_level = 3;
		m_level = m_level - 1;

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
		Draw();
		SetIndex(index);
	}


	//------------------------------------------------------------------------------------------------
	//リザルトアニメーション3 : Class
	//------------------------------------------------------------------------------------------------

	void UI_Result_Three::OnCreate() {
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
		SetLooped(false);
	}

	void UI_Result_Three::OnUpdate() {
		if (m_isPlay) {
			float time = App::GetApp()->GetElapsedTime();
			UpdateAnimeTime(time);
		}
	}


	//------------------------------------------------------------------------------------------------
	//リザルトアニメーション2 : Class
	//------------------------------------------------------------------------------------------------

	void UI_Result_Two::OnCreate() {
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

	void UI_Result_Two::OnUpdate() {
		if (m_isPlay) {
			float time = App::GetApp()->GetElapsedTime();
			UpdateAnimeTime(time);
		}
	}

	void UI_Result_Two::ChangeCharacter(const CharacterType type) {
		wstring animName = L"";
		float time = 0.0f;
		switch (type)
		{
		case basecross::POTATO:
			animName = L"anime_Potato";
			break;
		case basecross::SHRIMP:
			animName = L"anime_Shrimp";
			break;
		case basecross::CHICKEN:
			animName = L"anime_Chicken";
			break;
		case basecross::DOUGHNUT:
			animName = L"anime_Doughnut";
			break;
		}
		ChangeAnimation(animName, time);
		SetFps(30.0f);
		SetLooped(false);
	}


	//------------------------------------------------------------------------------------------------
	//コピーライトスプラッシュ : Class
	//------------------------------------------------------------------------------------------------

	void UI_Copyright_Splash::OnCreate() {
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
		SetFps(60.0f);
		SetLooped(false);
	}

	void UI_Copyright_Splash::OnUpdate() {
		if (m_isPlay) {
			float time = App::GetApp()->GetElapsedTime();
			UpdateAnimeTime(time);
			//Out();
/*
			if (m_frame >= 10.0f) {
				m_count += time;
			}
			else {
				m_frame += time;
			}

			if (m_count >= m_outTime) Out();*/
		}
	}

	void UI_Copyright_Splash::Out() {
		ChangeAnimation(L"out", 0.0f);
	}


	//デバックテキスト
	void DebugText::OnCreate() {
		auto sp = AddComponent<StringSprite>();
		sp->SetStartPosition(Point2D<float>(300, 10));
	}

	void DebugText::OnUpdate2() {
		auto sp = GetComponent<StringSprite>();
		sp->SetText(m_text);
	}


	//------------------------------------------------------------------------------------------------
	//CountSignal : Class
	//------------------------------------------------------------------------------------------------

	void UI_Count_Signal::OnCreate() {
		if (m_isStart) {
			CreateStart();
		}
		else {
			CreateEnd();
		}
		m_signalImage->Hidden(true);

		m_number = GetStage()->AddGameObject<UI_Number>(
			Vec2(m_numberPos.x, m_numberPos.y),
			1,
			Col4(1.0f),
			Number::NumberAlign::ZERO_CENTER,
			0.0f,
			Vec2(m_numberScale.x, m_numberScale.y),
			1000
			);
		m_number->Hidden(true);
	}

	void UI_Count_Signal::CreateStart() {
		m_signalImage = GetStage()->AddGameObject<UI_Static_Image>(
			Vec2(1024.0f, 256.0f),
			m_signalPos,
			m_signalScale,
			m_layer,
			Col4(1.0f),
			m_startSignalImageName
			);
	}

	void UI_Count_Signal::CreateEnd() {
		m_signalImage = GetStage()->AddGameObject<UI_Static_Image>(
			Vec2(1472.0f, 256.0f),
			m_signalPos,
			m_signalScale,
			m_layer,
			Col4(1.0f),
			m_endSignalImageName
			);
	}

	void UI_Count_Signal::SignalUpdate() {
		if (m_isStart) {
			int num = m_nowTime - m_endTime;
			if (num > 0) {
				m_number->Hidden(false);
				m_number->SetValue(num);
			}
			else if (num == 0) {
				m_number->Hidden(true);
				m_signalImage->Hidden(false);
			}
			else {
				m_number->Hidden(true);
				m_signalImage->Hidden(true);
			}
		}
		else {
			int num = m_startTime - m_nowTime;
			if (num < 0) return;
			if (m_nowTime > 0) {
				m_number->Hidden(false);
				m_number->SetValue(m_nowTime);
			}
			else if (m_nowTime == 0) {
				m_number->Hidden(true);
				m_signalImage->Hidden(false);
			}
		}
	}


	//------------------------------------------------------------------------------------------------
	//カーテン : Class
	//------------------------------------------------------------------------------------------------
	
	void UI_Curtain::FrameUpdate() {
		auto time = App::GetApp()->GetElapsedTime();
		if (m_frameCount <= m_endFrame / m_baseFps) {
			UpdateAnimeTime(time);
			m_frameCount += time;
		}
		else {
			m_finished = true;
		}
	}

	void UI_Curtain::OnCreate() {
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
		SetFps(m_baseFps);
		SetLooped(false);
	}

	void UI_Curtain::OnUpdate() {
		FrameUpdate();
	}
}