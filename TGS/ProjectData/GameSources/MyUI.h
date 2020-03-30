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

		void Remove();
	};


	//------------------------------------------------------------------------------------------------
	//スタティックな画像 : Class
	//------------------------------------------------------------------------------------------------

	class UI_Static_Image :public UI_Base {
	public:
		UI_Static_Image(const shared_ptr<Stage>& StagePtr,
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
		~UI_Static_Image() {}


		void Draw();
		virtual void OnCreate() override;

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
	//キャラクターステータス : 構造体
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
	//キル詳細 : 構造体
	//------------------------------------------------------------------------------------------------

	typedef struct CharacterKillDetails {
		wstring killName;
		int level;
	} CharacterKillDetails_s;


	//------------------------------------------------------------------------------------------------
	//タブ : Class
	//------------------------------------------------------------------------------------------------

	class UI_Tab: public GameObject {
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

	public:
		UI_Tab(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos) :
			GameObject(StagePtr),
			m_pos(pos),
			m_indexMin(0),
			m_indexMax(3),
			m_movingValue(App::GetApp()->GetGameWidth() / (m_indexMax + 1.0f)),
			m_startPosX(0.0f),
			m_maskIndex(0),
			m_oldFThumbLX(0.0f),
			m_tabImageName(L"PS_Tab.png"),
			m_tabMaskImageName(L"PS_Tab_Mask.png")
		{}
		~UI_Tab() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void MaskMove();
		void SetMaskIndex(int& index);

		int GetIndex() {
			return m_maskIndex;
		}
	};


	//------------------------------------------------------------------------------------------------
	//ポーズ画面 : Class
	//------------------------------------------------------------------------------------------------

	class UI_The_World :public GameObject {
		wstring m_fontName;

		wstring m_tableGroupName;

		wstring m_baseImageName;
		wstring m_separator1pxImageName;
		wstring m_separator3pxImageName;

		wstring m_playerBadgeImageName;

		std::shared_ptr<UI_Static_Image> m_base;

		vector<CharacterStatus_s> m_characterStatuses;
		vector<CharacterKillDetails_s> m_characterStatusKillDetails;

		std::shared_ptr<UI_Sprite_Text> m_title;

		int m_index;

		bool m_isShow;

		Col4 m_white;

		void Hide(bool e);
		void ShowTitle(bool e);
		void ShowTable(bool e);

		void ChangeTab(int index);

		void CreateTableHeader();

		void CreateTableLine(CharacterStatus_s &status, int index);
		void RemoveTableLine();

	public:
		UI_The_World(const shared_ptr<Stage>& StagePtr
		):
			GameObject(StagePtr),
			m_fontName(L"メイリオ"),
			m_tableGroupName(L"PauseTableGroup"),
			m_characterStatuses(vector<CharacterStatus_s>(0)),
			m_characterStatusKillDetails(vector<CharacterKillDetails_s>(0)),
			m_isShow(false),
			m_baseImageName(L"PS_Base.png"),
			m_separator1pxImageName(L"PS_Separator_1px.png"),
			m_separator3pxImageName(L"PS_Separator_3px.png"),
			m_playerBadgeImageName(L"PS_PlayerBadge.png"),
			m_base(NULL),
			m_title(NULL),
			m_index(0),
			m_white(Col4(1.0f, 1.0f, 1.0f, 1.0f))
		{}
		~UI_The_World() {}

		virtual void OnCreate() override;

		void SetCharacterStatuses(const vector<CharacterStatus_s>& characterStatuses) {
			m_characterStatuses = characterStatuses;
		}
		void SetCharacterStatus(const CharacterStatus_s& status);
		void SetCharacterKillDetails(const vector<CharacterKillDetails_s>& characterStatusKillDetails) {
			m_characterStatusKillDetails = characterStatusKillDetails;
		}
		void Show(bool e);

		bool GetShowing() {
			return m_isShow;
		}
	};
}