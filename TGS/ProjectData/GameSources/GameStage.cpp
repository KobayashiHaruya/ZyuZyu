/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, -10.0f, -15.0f);
		const Vec3 at(0.0f);

		//auto PtrView = CreateView<SingleView>();
		////ビューのカメラの設定
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(eye);
		//PtrCamera->SetAt(at);
		////マルチライトの作成
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////デフォルトのライティングを指定
		//PtrMultiLight->SetDefaultLighting();


		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateUI() {

	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			CreateUI();
			AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(100.0f, 0.5f, 100.0f)
				);
			//AddGameObject<Oil>(
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(150.0f, 0.1f, 150.0f)
			//	);
			AddGameObject<TestPlayer>(
				Vec3(0.0f, 3.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				8.0f, 10.0f, 5.0f, 0
				);

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['E']) {
			Vec3 rot;
			rot.y = (180.0f * 3.14f) / 180.0f;
			AddGameObject<Bullet>(
				Vec3(0.0f, 2.0f, 15.0f),
				rot,
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f, 0
				);
		}

	}

}
//end basecross
