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

}