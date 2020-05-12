/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include <chrono>
#include <thread>

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, -6.0f, -6.0f);
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

		AddGameObject<Time01>(1, L"0_9.png", true,
			Vec2(225.0f, 225.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//時間を更新する
		auto Time = AddGameObject<Time_Start>(L"Start.png",
			Vec2(800.0f, 400.0f),
			Vec2(-400.0f, 0.0f));

	}



	void GameStage::WeaponUpdate() {
		m_weaponTime -= App::GetApp()->GetElapsedTime();

		if (m_weaponTime <= 0.0f) {
			AddGameObject<Weapon>();
			m_weaponTime = 10.0f;
		}

	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			CreateUI();
			CreateTime();
			AddGameObject<Object>(
				Vec3(10.0f, -8.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f, 5.0f, 5.0f)
				);
			AddGameObject<Object>(
				Vec3(10.0f, -8.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(4.0f, 2.0f, 3.0f)
				);
			AddGameObject<Object>(
				Vec3(-5.0f, -8.0f, -10.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f, 1.0f, 2.5f)
				);
			AddGameObject<Object>(
				Vec3(20.0f, -8.0f, -15.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(5.0f, 1.0f, 10.0f)
				);
			AddGameObject<Object>(
				Vec3(10.0f, -8.0f, 20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f, 2.0f, 8.0f)
				);
			AddGameObject<Object>(
				Vec3(20.0f, -8.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(5.0f, 5.0f, 5.0f)
				);
			AddGameObject<OilStage>(
				Vec3(0.0f, -10.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 60.0f, 60.0f)
				);
			AddGameObject<Oil>(
				Vec3(0.0f, -40.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 60.0f, 60.0f)
				);
			AddGameObject<Nabe>(
				Vec3(0.0f, -80.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 60.0f, 60.0f)
				);
			m_player = AddGameObject<Player>(
				CharacterType::SHRIMP,
				true,
				0, 0
				10, 1
				);
			SetSharedGameObject(L"Player", m_player);

			auto characterGroup = CreateSharedObjectGroup(L"CharacterGroup");
			characterGroup->IntoGroup(m_player);

			//for (int i = 1; i < 8; i++) {

			//	CharacterType p;
			//	int Rand = rand() % 5;
			//	switch (Rand) {
			//	case 0:
			//		p = CharacterType::CHICKEN;
			//		break;
			//	case 1:
			//		p = CharacterType::DOUGHNUT;
			//		break;
			//	case 2:
			//		p = CharacterType::POTATO;
			//		break;
			//	case 3:
			//		p = CharacterType::SHRIMP;
			//		break;
			//	}

			//	auto AIparam = AIParam_s{
			//		vector<Vec3> { Vec3(0.0f, -10.0f, 0.0f), Vec3(30.0f, -10.0f, 10.0f), Vec3(-30.0f, -10.0f, 40.0f), Vec3(10, -10.0f, 40) },
			//		1.0f, 5.0f, 15.0f, 10, 0.0f, 10, 15.0f, 15.0f,
			//		3, 3,
			//		0,
			//		true
			//	};

			//	m_enemy = AddGameObject<AIchan>(
			//		p,
			//		false,
			//		i, i,
			//		AIparam
			//		);

			//	characterGroup->IntoGroup(m_enemy);
			//}

			AddGameObject<Enemy>(
				CharacterType::CHICKEN,
				false,
				1, 1
				1, 0
				);

			characterGroup->IntoGroup(m_enemy);

			for (int i = 0; i < 5; i++) {
				AddGameObject<Weapon>();
			}
			m_weaponTime = 10.0f;

			AddGameObject<SetGun>(true);


			CreatePinP();

			/*m_enemy = AddGameObject<Enemy>(
				CharacterType::CHICKEN,
				false,
				1,0
				);*/


			//CreateAIchan();
			AddGameObject<UI_CountdownTimer>(180, Vec2(870.0f, 500.0f), Vec2(0.5f), Col4(1.0f), 5);

		}

		catch (...) {
			throw;

		}

	}

	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['Z']) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
		}

		WeaponUpdate();

		m_time_ON += 0.1;

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['Z']) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
		}

		if (m_TotalTime > 1.001 && m_TotalTime < 4.0f)
		{
			//時間を更新する
			auto ptrScor = GetSharedGameObject<Time01>(L"Time01");
			ptrScor->SetScore(m_TotalTime);
		}
		else
		{
			//時間を更新する
			auto ptrtime = GetSharedGameObject<Time01>(L"Time01");
			ptrtime->SetScore(m_TotalTime);
			ptrtime->SetDrawActive(false);
		}

		ShowPause();
	}

	void GameStage::ShowPause() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Rキーもしくはパッドのスタートボタンを押したらポーズ画面を表示する
		if (KeyState.m_bPressedKeyTbl['P'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {

			m_pinp->Hidden(m_pinp->GetActive());

			//ここでは毎回配列を生成してステータスを設定しているが実際には１度だけ処理してChangeStatusをする
			vector<CharacterStatus_s> statuses;
			//statuses.push_back(m_player->GetMyData());
			auto group = GetSharedObjectGroup(L"CharacterGroup");
			auto vec = group->GetGroupVector();
			for (auto& v : vec) {
				auto obj = v.lock();
				if (obj) {
					auto character = dynamic_pointer_cast<Character>(obj);
					statuses.push_back(character->GetMyData());
				}

			}
			//statuses.push_back(m_enemy->GetMyData());
			m_pause->SetCharacterStatuses(statuses);

			//キルの情報詳細を表示したいCharacterから情報を取得してポーズ画面に値を渡す
			m_pause->SetCharacterKillDetails(m_player->GetKillCharacters());

			//実際にポーズ画面を表示する
			//引数は現在ポーズ画面がアクティブかどうかを取得してそのフラグを反転させることで表示非表示を切り替えている
			m_pause->Show(!(m_pause->GetShowing()));
		}
	}

	void GameStage::CreatePinP() {
		m_pinp = AddGameObject<PinP>(
			PinPAspectType::HD,
			35.0f,
			Vec2(10.0f, 10.0f),
			true,
			Col4(1.0f, 0.0f, 0.0f, 1.0f),
			1.02f,
			10
			);
		SetSharedGameObject(L"BlownPinP", m_pinp);  //shareObjectとしてPinPを登録
	}

	void GameStage::CreateAIchan() {
		auto AIparam = AIParam_s{
			vector<Vec3> { Vec3(0.0f, -10.0f, 0.0f), Vec3(30.0f, -10.0f, 10.0f), Vec3(-30.0f, -10.0f, 40.0f), Vec3(10, -10.0f, 40) },
			1.0f, 5.0f, 15.0f, 10, 0.0f, 10, 15.0f, 15.0f,
			3, 3,
			0,
			true
		};
		AddGameObject<AIchan>(
			CharacterType::CHICKEN,
			false,
			1000, 1000,
			AIparam
			);
	}

}
//end basecross
