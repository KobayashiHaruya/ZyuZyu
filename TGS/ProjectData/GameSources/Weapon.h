#pragma once
#include "stdafx.h"

namespace basecross {

	template<typename... T>
	class ObstacleEvent {
		vector<function<void(T...)>> m_fromEvents;
	public:
		ObstacleEvent() :
			m_fromEvents(vector<function<void(T...)>>(0))
		{};
		~ObstacleEvent() {};
		void AddEvent(const function<void(T...)>& event) {
			m_fromEvents.push_back(event);
		}
		void Run(T... args) {
			for (auto& event : m_fromEvents) event(args...);
		}
	};

	class Bullet :public GameObject, public ObstacleEvent<const CharacterStatus_s> {
		Vec3 m_pos;
		Quat m_rot;
		Vec3 m_scale;

		BulletS m_type;

		float m_moveSpeed;
		float m_gravityScale;
		float m_time;
		int ID;
 
		int m_fromUnique;

		CharacterStatus_s m_frome;

		shared_ptr<EfkEffect> m_efkEffect;
		shared_ptr<EfkPlay> m_efkPlay;


	public:

		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const BulletS& type,
			const unsigned int fromUnique,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_type(type),
			m_fromUnique(fromUnique),
			ID(id),
			m_frome(frome)
		{}

		~Bullet() {}

		void Draw();
		void Move();
		void Timer();
		void Destroy();
		void Effect(wstring name);
		void BulletState(BulletS state);
		void EffectState(BulletS state);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		unsigned int GetFromUnique() {
			return m_fromUnique;
		}

		CharacterStatus_s GetFrome() {
			return m_frome;
		}
	};


	class Weapon :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_time = 15.0f;
		int m_type;
		wstring text;
		wstring m_modelName;
	public:


		Weapon(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr) {}
		~Weapon() {}

		void Gun();
		void BmfDateRead(wstring model);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};


	class Grenade :public GameObject {
		Vec3 m_pos;
		Quat m_rot;
		float m_moveSpeed;
		float m_gravityScale;
		int ID;

		bool m_grenade;
		CharacterStatus_s m_frome;

	public:
		Grenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const float& speed,
			const float& gravity,
			const bool& grenade,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			m_moveSpeed(speed),
			m_gravityScale(gravity),
			m_grenade(grenade),
			ID(id),
			m_frome(frome)
		{}
		~Grenade() {}

		virtual void OnCreate() override;
		void Move();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};


	class SmokeGrenade :public GameObject, public ObstacleEvent<const CharacterStatus_s> {
		Vec3 m_pos;
		Quat m_rot;
		int ID;

		float m_time;
		CharacterStatus_s m_frome;

		shared_ptr<EfkEffect> m_efkEffect;
		shared_ptr<EfkPlay> m_efkPlay;

	public:
		SmokeGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			ID(id),
			m_frome(frome)
		{}
		~SmokeGrenade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Timer();

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		CharacterStatus_s GetFrome() {
			return m_frome;
		}

	};


	class TorimotiGrenade :public GameObject {
		Vec3 m_pos;
		Quat m_rot;
		int ID;

		float m_time;
		CharacterStatus_s m_frome;

	public:
		TorimotiGrenade(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& rot,
			const int& id,
			const CharacterStatus_s& frome
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_rot(rot),
			ID(id),
			m_frome(frome)
		{}
		~TorimotiGrenade() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Timer();

	};

	class GatlingAmmo :public GameObject {
		Vec3 m_pos;
		Quat m_qua;
		Vec3 m_scale = Vec3(1.0f);

		float m_time = 15.0f;

		wstring m_modelName = L"CornGatling.bmf";

		shared_ptr<MeshResource> m_SquareMeshResource;
		size_t m_Number;

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
		GatlingAmmo(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos
		) :
			GameObject(StagePtr),
			m_pos(pos)
		{}
		~GatlingAmmo() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);

	};

	class CannonAmmoBox :public GameObject {
		Vec3 m_pos;
		Quat m_qua;
		Vec3 m_scale = Vec3(1.0f);

		float m_time = 10.0f;

		wstring m_modelName = L"Tomato_ver1.bmf";

	public:
		CannonAmmoBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos
		) :
			GameObject(StagePtr),
			m_pos(pos)
		{}
		~CannonAmmoBox() {}

		virtual void BmfDateRead(wstring model);
		virtual void OnCreate() override;

	};

	class SetGun :public GameObject {
		Vec3 m_pos;
		Quat m_qua;
		Vec3 m_scale = Vec3(3.0f);

		bool m_gun;

	public:
		SetGun(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& quat,
			const bool& gun
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_qua(quat),
			m_gun(gun)
		{}
		~SetGun() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class GunSeat :public GameObject {
		Vec3 m_pos;
		Quat m_quat;
		Vec3 m_scale;

		bool m_gun;

	public:
		GunSeat(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Quat& quat,
			const bool& gun
		) :
			GameObject(StagePtr),
			m_pos(pos),
			m_quat(quat),
			m_gun(gun)
		{}
		~GunSeat() {}

		virtual void OnCreate() override;

	};


}