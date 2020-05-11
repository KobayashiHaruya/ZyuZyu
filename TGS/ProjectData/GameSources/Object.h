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
	public:

		Oil(const shared_ptr<Stage>& StagePtr,
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

}