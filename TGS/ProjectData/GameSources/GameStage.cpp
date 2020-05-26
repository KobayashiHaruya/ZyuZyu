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
		auto Time = AddGameObject<Time_Start>(L"GameStart.png",
			Vec2(600.0f, 300.0f),
			Vec2(-300.0f, 0.0f));

	}

	void GameStage::CreateEndTime() {

		    AddGameObject<EndTime>(1, L"0_9.png", true,
				 Vec2(200.0f, 250.0f),
				 Vec3(0.0f, 0.0f, 0.0f));

				//時間を更新する
				auto Time = AddGameObject<End>(L"GameFinish.png",
					Vec2(600.0f, 300.0f),
					Vec2(-300.0f, 0.0f));			
	}

	void GameStage::WeaponUpdate() {
		m_weaponTime -= App::GetApp()->GetElapsedTime();

		if (m_weaponTime <= 0.0f) {
			AddGameObject<Weapon>();
			m_weaponTime = 10.0f;
		}

	}

	CharacterType GameStage::SelectedChar()
	{
		wstring dataDir;

		App::GetApp()->GetDataDirectory(dataDir);
		unique_ptr<XmlDocReader> xmlDocReader = nullptr;

		xmlDocReader.reset(new XmlDocReader(dataDir + L"XML/" + L"CharSelect.xml"));

		wstring SetGameDataStr = XmlDocReader::GetText(xmlDocReader->GetSelectSingleNode(L"CharSelect/Character"));
		int character = (int)stoi(SetGameDataStr);

		CharacterType player;

		switch (character)
		{
		case 0:
			player = CharacterType::SHRIMP;
			break;
		case 1:
			player = CharacterType::CHICKEN;
			break;
		case 2:
			player = CharacterType::POTATO;
			break;
		case 3:
			player = CharacterType::DOUGHNUT;
			break;
		default:
			break;
		}

		return player;

	}

	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			CreateUI();
			CreateTime();
			CreateEndTime();

			auto obstacleGroup = CreateSharedObjectGroup(L"ObstacleGroup");
			auto obstacle = AddGameObject<Object>(
				Vec3(10.0f, -7.5f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f, 5.0f, 5.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(10.0f, -7.5f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(4.0f, 2.0f, 3.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-5.0f, -7.5f, -10.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f, 1.0f, 2.5f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(20.0f, -7.5f, -15.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(5.0f, 1.0f, 10.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(10.0f, -7.5f, 20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f, 5.0f, 10.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(20.0f, -7.5f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(10.0f, 10.0f, 10.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-20.0f, -7.5f, 13.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(4.0f, 3.0f, 8.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(24.0f, -7.5f, 10.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(5.0f, 3.0f, 3.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(10.0f, -7.5f, -26.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(14.0f, 2.0f, 6.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-15.0f, -7.5f, -20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(8.0f, 5.0f, 10.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-30.0f, -7.5f, -11.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(6.0f, 2.0f, 8.0f)
				);
			obstacleGroup->IntoGroup(obstacle);
			auto oil = AddGameObject<OilStage>(
				Vec3(0.0f, -10.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f)
				);
			oil->AddTag(L"Obstacle");
			AddGameObject<Oil>(
				Vec3(0.0f, -20.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f)
				);
			AddGameObject<Nabe>(
				Vec3(0.0f, -10.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f)
				);

			m_player = AddGameObject<Player>(
				SelectedChar(),
				true,
				0, 0
				);
			SetSharedGameObject(L"Player", m_player);

			auto characterGroup = CreateSharedObjectGroup(L"CharacterGroup");
			characterGroup->IntoGroup(m_player);



			for (int i = 1; i < 0; i++) {

				CharacterType p;
				int Rand = rand() % 4;
				switch (Rand) {
				case 0:
					p = CharacterType::SHRIMP;
					break;
				case 1:
					p = CharacterType::CHICKEN;
					break;
				case 2:
					p = CharacterType::POTATO;
					break;
				case 3:
					p = CharacterType::DOUGHNUT;
					break;
				}

				auto AIparam = AIParam_s{
					vector<Vec3> { Vec3(0.0f, -10.0f, 0.0f), Vec3(30.0f, -10.0f, 10.0f), Vec3(-30.0f, -10.0f, 40.0f), Vec3(10, -10.0f, 40) },
					1.0f, 5.0f, 15.0f, 10, 0.0f, 10, 15.0f, 15.0f,
					3, 3,
					0,
					15.0f,
					true
				};

				m_enemy = AddGameObject<AIchan>(
					p,
					false,
					i, i,
					AIparam
					);

				characterGroup->IntoGroup(m_enemy);
			}

			for (int i = 0; i < 5; i++) {
				AddGameObject<Weapon>();
			}
			m_weaponTime = 10.0f;

			AddGameObject<GunSeat>(
				Vec3(-10.0f, -8.2f, 0.0f),
				Quat(0.0f),
				true
				);

			AddGameObject<SetGun>(
				Vec3(0.0f, -8.2f, 0.0f),
				Quat(0.0f),
				false
				);

			AddGameObject<CannonAmmoBox>(
				Vec3(0.0f, -8.0f, 5.0f)
				);

			CreatePinP();

			//m_enemy = AddGameObject<Enemy>(
			//	CharacterType::CHICKEN,
			//	false,
			//	1,0
			//	);


			CreateAIchan();
			AddGameObject<UI_CountdownTimer>(180, Vec2(870.0f, 500.0f), Vec2(0.5f), Col4(1.0f), 5);


			//PlaySE(L"爆発_色々01.wav", 0.5f);
			PlayBGM(L"Main_BGM01.wav", 0.2f);
		}
		catch (...) {
			throw;

		}

	}

	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['Z']) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
			StopBGM();
			GameFinishScore();
		}

		WeaponUpdate();

		ShowPause();
	}

	void GameStage::GameFinishScore() {
		wstring ss;
		App::GetApp()->GetDataDirectory(ss);

		auto key = new XmlDoc(ss + L"/XML/" + L"ResultScore.xml");


		vector<CharacterStatus_s> statuses;
		vector<CharacterKillList_s> m_killList;

		auto group = GetSharedObjectGroup(L"CharacterGroup");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto obj = v.lock();
			if (obj) {
				auto character = dynamic_pointer_cast<Character>(obj);
				statuses.push_back(character->GetMyData());
			}
		}

		vector<CharacterStatus_s> m_charState = statuses;

		for (int i = 0; i < 8; i++) {
			wstring id = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/ID";
			wstring type = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Type";
			wstring kill = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Kill";
			wstring death = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Death";
			wstring score = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Score";
			wstring player = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Player";
			wstring list = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/List";

			wstring listSave = L"";

			if (m_charState[i].kill) {
				auto& obj = vec[i].lock();
				if (obj) {
					auto character = dynamic_pointer_cast<Character>(obj);
					m_killList = character->GetKillList();
				}
				for (int j = 0; j < m_charState[i].kill; j++)
				{
					listSave += Util::IntToWStr(m_killList[j].killState) + L",";
				}
			}
			else {
				listSave = L"None";
			}

			vector<wstring> Save = {
				Util::IntToWStr(m_charState[i].unique),
				Util::IntToWStr(m_charState[i].type),
				Util::IntToWStr(m_charState[i].kill),
				Util::IntToWStr(m_charState[i].death),
				Util::IntToWStr(m_charState[i].score),
				Util::IntToWStr(m_charState[i].isPlayer),
				listSave
			};

			vector<IXMLDOMNodePtr> Data = {
				key->GetSelectSingleNode(id.c_str()),
				key->GetSelectSingleNode(type.c_str()),
				key->GetSelectSingleNode(kill.c_str()),
				key->GetSelectSingleNode(death.c_str()),
				key->GetSelectSingleNode(score.c_str()),
				key->GetSelectSingleNode(player.c_str()),
				key->GetSelectSingleNode(list.c_str())
			};

			for (int j = 0; j < Data.size(); j++) {
				key->SetText(Data[j], Save[j].c_str());
			}

			key->Save(ss + L"/XML/" + L"ResultScore.xml");

		}

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
			10.0f,
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
