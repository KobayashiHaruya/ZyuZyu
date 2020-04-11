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

		auto& app = App::GetApp();
		Viewport view = { 0.0f, 0.0f, app->GetGameWidth(), app->GetGameHeight(), 0.0f, 1.0f };
		auto ptrView = CreateView<MultiView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		//ptrView->SetCamera(ptrMyCamera);
		//ptrView->SetViewport(view);
		//ptrMyCamera->SetViewPort(ptrView->GetViewport());
		//ptrView->SetViewport(ptrMyCamera->getv);
		ptrView->AddView(view, ptrMyCamera);
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateUI() {
		m_pause = AddGameObject<UI_The_World>(5);


	}

	void GameStage::CreateTime() {
		// 時間
		AddGameObject<Time01>(L"0.png",
			Vec2(250.0f, 250.0f),
			Vec2(0.0f, -400.0f));

		// 時間
		AddGameObject<Time10>(L"0.png",
			Vec2(250.0f, 250.0f),
			Vec2(-25.0f, -400.0f));

		// 時間
		AddGameObject<Time100>(L"0.png",
			Vec2(250.0f, 250.0f),
			Vec2(-50.0f, -400.0f));

	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			CreateUI();
			CreateTime();
			AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(100.0f, 0.5f, 100.0f)
				);
			AddGameObject<Oil>(
				Vec3(0.0f, -10.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(150.0f, 0.1f, 150.0f)
				);
			m_player = AddGameObject<TestPlayer>(
				Vec3(0.0f, 3.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				0.15f, 10.0f, 5.0f,
				CharacterType::CHICKEN,
				true,
				0
				);
			m_enemy = AddGameObject<TestEnemy>(
				Vec3(0.0f, 3.0f, 50.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				0.15f, 10.0f, 5.0f,
				CharacterType::POTATO,
				false,
				1
				);

			m_pinp = AddGameObject<PinP>(
				PinPAspectType::HD,
				35.0f,
				Vec2(10.0f, 10.0f)
				);
			m_pinp->SetEye(Vec3(0.0f, 10.0f, 100.0f));
			m_pinp->In(PinPAction::UNDER);

		}
		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['E']) {


		}
<<<<<<< HEAD

=======
>>>>>>> 69926f9430785b7b9747f213cd0d3e34f935e481

		//とりあえずPinPのカメラがプレイヤーを追尾する
		auto playerTrans = m_player->GetComponent<Transform>();
		m_pinp->SetAt(playerTrans->GetPosition());

		ShowPause();
	}

	void GameStage::ShowPause() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Rキーもしくはパッドのスタートボタンを押したらポーズ画面を表示する
		if (KeyState.m_bPressedKeyTbl['R'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {

			//ポーズ中にPinPがあるとそこにもUIを表示してしまうので非表示にする
			if(m_pause->GetShowing())
				m_pinp->In(PinPAction::LEFT);
			else
				m_pinp->Hidden();

			//ここでは毎回配列を生成してステータスを設定しているが実際には１度だけ処理してChangeStatusをする
			vector<CharacterStatus_s> statuses;
			statuses.push_back(m_player->GetMyData());
			statuses.push_back(m_enemy->GetMyData());
			m_pause->SetCharacterStatuses(statuses);

			//キルの情報詳細を表示したいCharacterから情報を取得してポーズ画面に値を渡す
			m_pause->SetCharacterKillDetails(m_player->GetKillCharacters());

			//実際にポーズ画面を表示する
			//引数は現在ポーズ画面がアクティブかどうかを取得してそのフラグを反転させることで表示非表示を切り替えている
			m_pause->Show(!(m_pause->GetShowing()));
		}
<<<<<<< HEAD

=======
>>>>>>> 69926f9430785b7b9747f213cd0d3e34f935e481
	}

}
//end basecross
