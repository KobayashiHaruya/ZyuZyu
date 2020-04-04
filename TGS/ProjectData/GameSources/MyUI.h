#pragma once
#include "stdafx.h"

namespace basecross {


	class UI_Base :public GameObject {
		Vec2 m_Vertex;
		float m_size;
		Vec3 m_pos;
		Vec3 m_scale;
		Col4 m_color;
		int m_layer;
		wstring m_textures;

	public:

		UI_Base(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			GameObject(StagePtr),
			m_Vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures)

		{}
		~UI_Base() {}
		void Draw();

	};


	//------------------------------------------------------------------------------------------------
	//テキスト : Class
	//------------------------------------------------------------------------------------------------

	class UI_Sprite_Text :public GameObject {
		wstring m_fontName;
		float m_fontSize;
		Col4 m_color;
		Rect2D<float> m_rect;
		StringSprite::TextAlignment m_textAlignment;
		wstring m_text;
		int m_layer;
		bool m_isBk;

	public:
		UI_Sprite_Text(const shared_ptr<Stage>& StagePtr,
			const wstring& fontName,
			const float fontSize,
			const Col4& color,
			const Rect2D<float>& rect,
			const StringSprite::TextAlignment textAlignment,
			const wstring& text,
			const int layer,
			const bool isBk
		) :
			GameObject(StagePtr),
			m_fontName(fontName),
			m_fontSize(fontSize),
			m_color(color),
			m_rect(rect),
			m_textAlignment(textAlignment),
			m_text(text),
			m_layer(layer),
			m_isBk(isBk)
		{}
		~UI_Sprite_Text() {}

		virtual void OnCreate() override;

		void UpdateText(const wstring value);

		void Remove();
	};


	//------------------------------------------------------------------------------------------------
	//スタティックな画像 : Class
	//------------------------------------------------------------------------------------------------

	class UI_Static_Image :public GameObject {
		Vec2 m_vertex;
		float m_size;
		Vec3 m_pos;
		Vec3 m_scale;
		Col4 m_color;
		int m_layer;
		wstring m_textures;

		float m_xHalf;
		float m_yHalf;

		vector<VertexPositionColorTexture> m_vertices;

	public:
		UI_Static_Image(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			GameObject(StagePtr),
			m_vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures),
			m_xHalf(m_vertex.x / 2.0f),
			m_yHalf(m_vertex.y / 2.0f)
		{}
		~UI_Static_Image() {}

		virtual void OnCreate() override;

		void Draw();
		void SetTexture(const wstring& texture);
		void SetTexture(const wstring& texture, Vec2& vertex);
		void SetTexture(const wstring& texture, Vec2& vertex, const Vec3& scale);
		void Hidden(bool e);
	};

	class Title_UI : public UI_Base {
	public:

		Title_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Title_UI() {}

		virtual void OnCreate() override;

	};

	class Operation_UI : public UI_Base {
	public:

		Operation_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Operation_UI() {}

		virtual void OnCreate() override;
	};


	//------------------------------------------------------------------------------------------------
	//水平なスプライト画像 : Class
	//------------------------------------------------------------------------------------------------

	class UI_Horizontal_Sprite_Image :public GameObject {
		Vec2 m_vertex;
		float m_size;
		Vec3 m_pos;
		Vec3 m_scale;
		Col4 m_color;
		int m_layer;
		wstring m_textures;

		Vec2 m_cutOut;
		int m_index;

		float m_xHalf;
		float m_yHalf;

		vector<VertexPositionColorTexture> m_vertices;

		void UpdateVertices();

	protected:

		void SetIndex(int index);

	public:

		UI_Horizontal_Sprite_Image(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			GameObject(StagePtr),
			m_vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures),
			m_cutOut(vertex),
			m_index(0),
			m_xHalf(m_vertex.x / 2.0f),
			m_yHalf(m_vertex.y / 2.0f)
		{}
		UI_Horizontal_Sprite_Image(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures,
			const Vec2& cutOut
		) :
			GameObject(StagePtr),
			m_vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures),
			m_cutOut(cutOut),
			m_index(0),
			m_xHalf(m_cutOut.x / 2.0f),
			m_yHalf(m_cutOut.y / 2.0f)
		{}
		~UI_Horizontal_Sprite_Image() {}

		void Draw();

		int GetMaxIndex() {
			return m_vertex.x / m_cutOut.x;
		}
	};


	//------------------------------------------------------------------------------------------------
	//キャラクターセレクトの選択マスク : Class
	//------------------------------------------------------------------------------------------------

	class UI_Character_Select_Mask_Image :public UI_Base {
		int m_indexMin;
		int m_indexMax;
		float m_movingValue;
		float m_startPosX;
		int m_maskIndex;

		float m_oldFThumbLX;
	public:
		UI_Character_Select_Mask_Image(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures,
			const int startIndex
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			),
			m_indexMin(0),
			m_indexMax(3),
			m_movingValue(App::GetApp()->GetGameWidth() / (m_indexMax + 1.0f)),
			m_startPosX(vertex.x - (m_movingValue * (vertex.x / m_movingValue + m_indexMax - 1.0f) - m_movingValue / 2.0f)),
			m_maskIndex(startIndex),
			m_oldFThumbLX(0.0f)
		{}
		~UI_Character_Select_Mask_Image() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void MaskMove();
		void SetMaskIndex(int& index);

		int GetIndex() {
			return m_maskIndex;
		}
	};


	//------------------------------------------------------------------------------------------------
	//キャラクタータイプ : enum
	//------------------------------------------------------------------------------------------------

	enum CharacterType {
		POTATO = 0,
		SHRIMP = 1,
		CHICKEN = 2,
		DOUGHNUT = 3
	};


	//------------------------------------------------------------------------------------------------
	//キャラクターステータス : struct
	//------------------------------------------------------------------------------------------------

	typedef struct CharacterStatus {
		wstring playerName;
		int kill;
		int death;
		int score;
		bool isPlayer;
		int unique;
	} CharacterStatus_s;


	//------------------------------------------------------------------------------------------------
	//キル詳細 : struct
	//------------------------------------------------------------------------------------------------

	typedef struct CharacterKillDetails {
		CharacterType type;
		int level;
	} CharacterKillDetails_s;


	//------------------------------------------------------------------------------------------------
	//スコア表 : struct
	//------------------------------------------------------------------------------------------------

	typedef struct ScoreTableLine {
		shared_ptr<UI_Sprite_Text> name;
		shared_ptr<UI_Sprite_Text> kill;
		shared_ptr<UI_Sprite_Text> death;
		shared_ptr<UI_Sprite_Text> score;
		shared_ptr<UI_Static_Image> playerBadge;
		shared_ptr<UI_Static_Image> separator;
	} ScoreTableLine_s;


	//------------------------------------------------------------------------------------------------
	//タブ : Class
	//------------------------------------------------------------------------------------------------

	class UI_Tab: public GameObject {
		int m_layer;
		int m_indexMin;
		int m_indexMax;
		float m_movingValue;
		float m_startPosX;
		int m_maskIndex;

		float m_space;

		float m_oldFThumbLX;

		wstring m_tabImageName;
		wstring m_tabMaskImageName;

		std::shared_ptr<UI_Static_Image> m_tab;
		vector<std::shared_ptr<UI_Static_Image>> m_masks;

		Vec3 m_pos;

		void CreateTab();
		void CreateMasks();

		float m_magnification;

		void Hidden(bool e);

	public:
		UI_Tab(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const float magnification,
			const int layer
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_layer(layer),
			m_indexMin(0),
			m_indexMax(3),
			m_movingValue(App::GetApp()->GetGameWidth() / (m_indexMax + 1.0f)),
			m_startPosX(0.0f),
			m_maskIndex(0),
			m_oldFThumbLX(0.0f),
			m_tabImageName(L"PS_Tab.png"),
			m_tabMaskImageName(L"PS_Tab_Mask.png"),
			m_space(2.0f * magnification),
			m_magnification(magnification)
		{}
		~UI_Tab() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void Show(bool e);

		void MaskMove();
		void SetMaskIndex(int& index);

		int GetIndex() {
			return m_maskIndex;
		}
	};


	//------------------------------------------------------------------------------------------------
	//食材アイコン : Class
	//------------------------------------------------------------------------------------------------

	class UI_Food_Icon :public UI_Horizontal_Sprite_Image {
		CharacterType m_type;
		int m_level;

	public:
		UI_Food_Icon(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& scale,
			const int layer
		) :
			UI_Horizontal_Sprite_Image(
				StagePtr,
				Vec2(3072.0f, 256.0f),
				pos,
				scale,
				5,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				L"PS_Characteres_Level_Sprite.png",
				Vec2(256.0f, 256.0f)
			),
			m_type(CharacterType::CHICKEN),
			m_level(0)
		{}
		~UI_Food_Icon() {}

		virtual void OnCreate() override;

		void SetCharacter(CharacterType type, int level);
	};


	//------------------------------------------------------------------------------------------------
	//スコア表 : Class
	//------------------------------------------------------------------------------------------------

	class UI_Score_Table :public GameObject {
		int m_lineNum;
		int m_layer;
		bool m_isShow;

		wstring m_playerBadgeImageName;
		wstring m_separatorImageName;

		vector<CharacterStatus_s> m_characterStatuses;

		float m_headerFontSize;
		float m_lineFontSize;
		wstring m_fontName;
		vector<shared_ptr<UI_Sprite_Text>> m_headerTexts;
		vector<ScoreTableLine_s> m_lines;

		Col4 m_white;

		bool m_isCreate;

		void CreateTableHeader();
		void CreateLine(CharacterStatus_s& status, int index);
		void UpdateTable();
		void Sort();
		void Hidden(bool e);

	public:
		UI_Score_Table(const shared_ptr<Stage>& StagePtr,
			const int lineNum,
			const int layer
		) :
			GameObject(StagePtr),
			m_lineNum(lineNum),
			m_layer(layer),
			m_isShow(false),
			m_playerBadgeImageName(L"PS_PlayerBadge.png"),
			m_separatorImageName(L"PS_Separator.png"),
			m_characterStatuses(vector<CharacterStatus_s>(lineNum)),
			m_headerFontSize(50.0f),
			m_lineFontSize(45.0f),
			m_fontName(L"メイリオ"),
			m_headerTexts(vector<shared_ptr<UI_Sprite_Text>>(0)),
			m_lines(vector<ScoreTableLine_s>(0)),
			m_white(Col4(1.0f)),
			m_isCreate(false)
		{}
		~UI_Score_Table() {}

		void Show(bool e);
		void SetCharacterStatuses(const vector<CharacterStatus_s>& characterStatuses) {
			m_characterStatuses = characterStatuses;
		}
		void SetCharacterStatus(const CharacterStatus_s& status);
		CharacterStatus_s GetPlayerStatus() {
			vector<CharacterStatus_s>::iterator it = find_if(m_characterStatuses.begin(), m_characterStatuses.end(), [](const CharacterStatus_s& i) {
				return i.isPlayer;
			});
			return *it;
		}
	};


	//------------------------------------------------------------------------------------------------
	//キル詳細 : Class
	//------------------------------------------------------------------------------------------------

	class UI_Kill_Details :public GameObject {
		int m_layer;
		bool m_isShow;

		wstring m_characterIconImageName;

		vector<CharacterKillDetails_s> m_characterStatusKillDetails;

		vector<shared_ptr<UI_Food_Icon>> m_icons;
		shared_ptr<UI_Sprite_Text> m_killText;
		shared_ptr<UI_Sprite_Text> m_scoreText;

		int m_score;

		wstring m_fontName;
		float m_infoFontSize;
		Col4 m_white;

		bool m_isCreate;

		void CreateKillIcon(CharacterKillDetails_s& details, int index);
		void CreateInfo();
		void UpdateInfo();
		void Hidden(bool e);
		int GetDigit(int num);

	public:
		UI_Kill_Details(const shared_ptr<Stage>& StagePtr,
			const int layer
		) :
			GameObject(StagePtr),
			m_layer(layer),
			m_characterIconImageName(L"PS_Characteres_Level_Sprite.png"),
			m_characterStatusKillDetails(vector<CharacterKillDetails_s>(0)),
			m_killText(NULL),
			m_scoreText(NULL),
			m_icons(vector<shared_ptr<UI_Food_Icon>>(0)),
			m_score(0),
			m_fontName(L"メイリオ"),
			m_infoFontSize(50.0f),
			m_white(Col4(1.0f)),
			m_isCreate(false)
		{}
		~UI_Kill_Details() {};

		void Show(bool e);
		void SetCharacterKillDetails(const vector<CharacterKillDetails_s>& characterStatusKillDetails) {
			m_characterStatusKillDetails = characterStatusKillDetails;
			UpdateInfo();
		}
		void SetScore(const int score) {
			m_score = score;
			UpdateInfo();
		}
	};


	//------------------------------------------------------------------------------------------------
	//ポーズ画面 : Class
	//------------------------------------------------------------------------------------------------

	class UI_The_World :public GameObject {
		int m_baseLayer;
		int m_layer;

		wstring m_fontName;
		float m_titleFontSize;

		wstring m_baseImageName;
		wstring m_operationImageName;
		wstring m_titlebackImageName;
		wstring m_backImageName;

		std::shared_ptr<UI_Static_Image> m_base;
		shared_ptr<UI_Sprite_Text> m_title;
		std::shared_ptr<UI_Tab> m_tab;
		shared_ptr<UI_Score_Table> m_scoreTable;
		std::shared_ptr<UI_Static_Image> m_operation;
		shared_ptr<UI_Kill_Details> m_killDetails;
		shared_ptr<UI_Static_Image> m_titleback;
		shared_ptr<UI_Static_Image> m_back;

		vector<CharacterStatus_s> m_characterStatuses;
		vector<CharacterKillDetails_s> m_characterStatusKillDetails;

		int m_index;
		int m_oldIndex;

		bool m_isShow;

		Col4 m_white;

		void AllHidden(bool e);
		void ShowBase(bool e);
		void ShowTab(bool e);
		void ShowTitle(bool e);
		void ShowOperation(bool e);
		void ShowTitleback(bool e);
		void ShowBack(bool e);
		void ChangeTab();
		void Key();

		void SetTestDeta();  //テスト用のデータを設定します。本番時にはコメントアウトしてください

	public:
		UI_The_World(const shared_ptr<Stage>& StagePtr,
			int layer
		) :
			GameObject(StagePtr),
			m_baseLayer(layer),
			m_layer(layer + 1),
			m_fontName(L"メイリオ"),
			m_titleFontSize(50.0f),
			m_characterStatuses(vector<CharacterStatus_s>(0)),
			m_characterStatusKillDetails(vector<CharacterKillDetails_s>(0)),
			m_isShow(false),
			m_baseImageName(L"PS_Base.png"),
			m_operationImageName(L"Operation.png"),
			m_titlebackImageName(L"PS_Back.png"),
			m_backImageName(L"PS_Other.png"),
			m_base(NULL),
			m_title(NULL),
			m_tab(NULL),
			m_scoreTable(NULL),
			m_operation(NULL),
			m_killDetails(NULL),
			m_titleback(NULL),
			m_back(NULL),
			m_index(0),
			m_oldIndex(-1),
			m_white(Col4(1.0f, 1.0f, 1.0f, 1.0f))
		{}
		~UI_The_World() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

		void Show(bool e);
		void SetCharacterStatuses(const vector<CharacterStatus_s>& characterStatuses) {
			if (m_scoreTable) m_scoreTable->SetCharacterStatuses(characterStatuses);
		}
		void SetCharacterStatus(const CharacterStatus_s& status) {
			if (m_scoreTable) m_scoreTable->SetCharacterStatus(status);
		};
		void SetCharacterKillDetails(const vector<CharacterKillDetails_s>& characterStatusKillDetails) {
			if(m_killDetails) m_killDetails->SetCharacterKillDetails(characterStatusKillDetails);
		}
		bool GetShowing() {
			return m_isShow;
		}
	};


	//------------------------------------------------------------------------------------------------
	//キャラクターステータス : Class
	//------------------------------------------------------------------------------------------------

	class UI_Character_Status :public SS5ssae {
		Vec3 m_pos;
		Vec3 m_scale;
		int m_layer;

	public:
		UI_Character_Status(const shared_ptr<Stage>& StagePtr,
			const wstring& BaseDir,
		    const Vec3& pos,
			const Vec3& scale,
			const int layer
		):
			SS5ssae(StagePtr, BaseDir, L"Status_Animation_ver2.ssae", L"Status_ver2_Chicken", true),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer)
		{}
		~UI_Character_Status() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void ChangeCharacterStatus(CharacterType type);
	};
}