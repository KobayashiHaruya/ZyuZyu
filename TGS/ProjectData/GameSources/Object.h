#pragma once
#include "stdafx.h"

namespace basecross {

	enum ObjectType {
		Oil,
		Kakiage,
		Nabe,
		Asupara,
		Azi,
		Harumaki,
		Kabotya,
		Katu,
		Korokke,
		Nasu,
		Imo,
		Siitake
	};

	class Object :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;

		Vec3 m_modelPos;
		Vec3 m_modelRot;
		Vec3 m_colSize;

		wstring m_modelName;

		ObjectType m_food;

	public:

		Object(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale,
			const ObjectType& food
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale),
			m_food(food)

		{}
		~Object() {}

		virtual void OnCreate() override;
		void BmfDateRead(wstring model, Vec3 mpos);
		void ObjectModel();
		void Collision();

	};


	class Result_Icon : public GameObject {
		Vec3 m_pos;
		Vec3 m_scale = Vec3(1.0f);

		shared_ptr<MeshResource> m_SquareMeshResource;

		int m_type;

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
			const int& type
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