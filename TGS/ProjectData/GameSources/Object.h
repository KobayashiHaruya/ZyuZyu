#pragma once
#include "stdafx.h"

namespace basecross {

	class ObjectBase :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;

	public:

		ObjectBase(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale)

		{}
		~ObjectBase() {}

		void BmfDateRead(wstring model, Vec3 mpos, Vec3 mrot, Vec3 mscale);
		void Draw();

	};

	class Object :public ObjectBase {
	public:

		Object(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			ObjectBase(
				StagePtr,
				pos,
				rot,
				scale
			)
		{}
		~Object() {}

		virtual void OnCreate() override;

	};

	class OilStage :public ObjectBase {
		Vec3 m_pos;
	public:

		OilStage(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			ObjectBase(
				StagePtr,
				pos,
				rot,
				scale
			),
			m_pos(pos)
		{}
		~OilStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class Oil :public ObjectBase {
		bool m_model;
	public:

		Oil(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const bool& model
		) :
			ObjectBase(
				StagePtr,
				pos,
				rot,
				scale
			),
			m_model(model)
		{}
		~Oil() {}

		virtual void OnCreate() override;

	};

	class Nabe :public ObjectBase {
	public:

		Nabe(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			ObjectBase(
				StagePtr,
				pos,
				rot,
				scale
			)
		{}
		~Nabe() {}

		virtual void OnCreate() override;

	};


	class Result_Icon : public GameObject {
		Vec3 m_pos;
		Quat m_qua;
		Vec3 m_scale = Vec3(1.0f);

		shared_ptr<MeshResource> m_SquareMeshResource;

		CharacterType m_type;

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}

	public:
		Result_Icon(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const CharacterType type
			) :
			GameObject(StagePtr),
			m_pos(pos),
			m_type(type)
		{}
		~Result_Icon() {}

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
	};

	class Wall : public GameObject {
		Vec3 m_Position;	
		Quat m_Qt;
		Vec3 m_Scale;

	public:
		//ç\ízÇ∆îjä¸
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Quat& Qt,
			const Vec3& Scale
		) :
			GameObject(StagePtr),
			m_Position(Position),
			m_Qt(Qt),
			m_Scale(Scale)
		{}
		~Wall() {}
		//èâä˙âª
		virtual void OnCreate() override;
	};
}