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

	class UI_Character_Select_Static_Image :public UI_Base {
	public:
		UI_Character_Select_Static_Image(const shared_ptr<Stage>& StagePtr,
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
		~UI_Character_Select_Static_Image() {}


		void Draw();

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
}