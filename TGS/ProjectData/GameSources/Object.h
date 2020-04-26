#pragma once
#include "stdafx.h"

namespace basecross {

	class Object :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;

	public:

		Object(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_scale(scale)

		{}
		~Object() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void BmfDateRead(wstring model, Vec3 mpos, Vec3 mrot, Vec3 mscale);
		void Draw();

	};


	class Oil :public Object {
	public:

		Oil(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			Object(
				StagePtr,
				pos,
				rot,
				scale
			)
		{}
		~Oil() {}

		virtual void OnCreate() override;

	};

	class Nabe :public Object {
	public:

		Nabe(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		) :
			Object(
				StagePtr,
				pos,
				rot,
				scale
			)
		{}
		~Nabe() {}

		virtual void OnCreate() override;

	};

}