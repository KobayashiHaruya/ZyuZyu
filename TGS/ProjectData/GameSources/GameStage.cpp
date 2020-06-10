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

		auto& app = App::GetApp();
		Viewport view = { 0.0f, 0.0f, app->GetGameWidth(), app->GetGameHeight(), 0.0f, 1.0f };
		auto ptrView = CreateView<MultiView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		m_camera = ptrMyCamera;
		ptrView->AddView(view, ptrMyCamera);
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateUI() {
		m_pause = AddGameObject<UI_The_World>(9999);

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
			m_weaponTime = 5.0f;
		}

	}

	void GameStage::WeaponState() {


		for (int i = 0; i < 9; i++) {
			WeaponState_s state;
			state.weapon = (BulletS)i;

			switch (state.weapon)
			{
			case BulletS::None:
				state.barrage = false;
				state.reAmmo = 0;
				state.ammo = 0;
				state.maxAmmo = 0;
				state.intTime = 0.0f;
				state.maxIntTime = 0.0f;
				state.reTime = 0.0f;
				state.maxreTime = 0.0f;
				break;
			case BulletS::Assault:
				state.barrage = true;
				state.reAmmo = 30;
				state.ammo = 30;
				state.maxAmmo = 0;
				state.intTime = 0.0f;
				state.maxIntTime = 0.15f;
				state.reTime = 0.0f;
				state.maxreTime = 0.65f;
				break;
			case BulletS::Hand:
				state.barrage = false;
				state.reAmmo = 15;
				state.ammo = 15;
				state.maxAmmo = 50;
				state.intTime = 0.0f;
				state.maxIntTime = 0.2f;
				state.reTime = 0.0f;
				state.maxreTime = 2.0f;
				break;
			case BulletS::Shot:
				state.barrage = false;
				state.reAmmo = 2;
				state.ammo = 2;
				state.maxAmmo = 14;
				state.intTime = 0.0f;
				state.maxIntTime = 0.4f;
				state.reTime = 0.0f;
				state.maxreTime = 1.6f;
				break;
			case BulletS::SMG:
				state.barrage = true;
				state.reAmmo = 20;
				state.ammo = 20;
				state.maxAmmo = 100;
				state.intTime = 0.0f;
				state.maxIntTime = 0.08f;
				state.reTime = 0.0f;
				state.maxreTime = 0.4f;
				break;
			case BulletS::Rocket:
				state.barrage = false;
				state.reAmmo = 1;
				state.ammo = 1; 
				state.maxAmmo = 8;
				state.intTime = 0.0f;
				state.maxIntTime = 0.0f;
				state.reTime = 0.0f;
				state.maxreTime = 2.5f;
				break;
			case BulletS::Sniper:
				state.barrage = false;
				state.reAmmo = 6;
				state.ammo = 6;
				state.maxAmmo = 18;
				state.intTime = 0.0f;
				state.maxIntTime = 0.8f;
				state.reTime = 0.0f;
				state.maxreTime = 1.5f;
				break;
			case BulletS::Laser:
				state.barrage = false;
				state.reAmmo = 50;
				state.ammo = 50;
				state.maxAmmo = 0;
				state.intTime = 0.0f;
				state.maxIntTime = 0.0f;
				state.reTime = 0.0f;
				state.maxreTime = 1.2f;
				break;
			case BulletS::Wind:
				state.barrage = true;
				state.reAmmo = 1500;
				state.ammo = 1500;
				state.maxAmmo = 0;
				state.maxIntTime = 1.0f / 60.0f;
				state.maxreTime = 1.0f;
				break;
			}
			state.intTime = 0.0f;
			state.reTime = 0.0f;

			m_weaponState.push_back(state);

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

	void GameStage::OnDraw()
	{
		auto& camera = GetView()->GetTargetCamera();
		m_efkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_efkInterface->OnDraw();
	}

	void GameStage::OnCreate() {
		try {
			m_efkInterface = ObjectFactory::Create<EfkInterface>();
			
			//SetPhysicsActive(true);
			//ビューとライトの作成.
			//CreateEffect();
			WeaponState();
			CreateViewLight();
			CreateUI();
			/*CreateTime();
			CreateEndTime();*/

			auto obstacleGroup = CreateSharedObjectGroup(L"ObstacleGroup");
			auto obstacle = AddGameObject<Object>(
				Vec3(-28.0f, 3.0f, 10.0f),
				Vec3(0.0f, 0.0f, -XM_PI / 20.0f),
				Vec3(3.0f),
				ObjectType::Harumaki
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(30.0f, 5.0f, -10.0f),
				Vec3(XM_PI / 2.0f, 0.0f, 0.0f),
				Vec3(1.5f),
				ObjectType::Asupara
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(30.0f, 5.0f, -5.0f),
				Vec3(XM_PI / 2.0f, 0.0f, 0.0f),
				Vec3(1.5f),
				ObjectType::Asupara
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(30.0f, 5.0f, 0.0f),
				Vec3(XM_PI / 2.0f, 0.0f, 0.0f),
				Vec3(1.5f),
				ObjectType::Asupara
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(30.0f, 5.0f, 5.0f),
				Vec3(XM_PI / 2.0f, 0.0f, 0.0f),
				Vec3(1.5f),
				ObjectType::Asupara
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(0.0f, 2.0f, 40.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f),
				ObjectType::Siitake
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(10.0f, 2.0f, 40.0f),
				Vec3(0.0f, 1.0f, 0.0f),
				Vec3(5.0f),
				ObjectType::Katu
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(20.0f, 4.0f, -40.0f),
				Vec3(0.0f, XM_PI / 4.0f, XM_PI / 2.0f),
				Vec3(7.0f),
				ObjectType::Korokke
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-40.0f, 2.0f, -30.0f),
				Vec3(0.0f, 1.5f, 0.0f),
				Vec3(6.0f),
				ObjectType::Nasu
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-40.0f, 1.5f, 10.0f),
				Vec3(0.0f, 0.0f, XM_PI / 8.0f),
				Vec3(5.0f),
				ObjectType::Imo
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-20.0f, 2.0f, 40.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				ObjectType::Azi
				);
			obstacleGroup->IntoGroup(obstacle);
			obstacle = AddGameObject<Object>(
				Vec3(-30.0f, 4.0f, 20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(3.0f, 3.0f, 3.0f),
				ObjectType::Kabotya
				);
			obstacleGroup->IntoGroup(obstacle);

			auto oil = AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.4f, 0.4f, 0.4f),
				ObjectType::Kakiage
				);
			oil->AddTag(L"Obstacle");
			AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.4f, 0.4f, 0.4f),
				ObjectType::Oil
				);
			AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.4f, 0.4f, 0.4f),
				ObjectType::Nabe
				);

			m_player = AddGameObject<Player>(
				SelectedChar(),
				true,
				0, 0
				);
			SetSharedGameObject(L"Player", m_player);

			auto characterGroup = CreateSharedObjectGroup(L"CharacterGroup");
			characterGroup->IntoGroup(m_player);



			for (int i = 1; i < 8; i++) {

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
			m_weaponTime = 5.0f;

			AddGameObject<GunSeat>(
				Vec3(-10.0f, 2.0f, 10.0f),
				Quat(0.0f),
				true
				);

			AddGameObject<SetGun>(
				Vec3(40.0f, 2.0f, -20.0f),
				Quat(0.0f),
				false
				);

			AddGameObject<CannonAmmoBox>(
				Vec3(0.0f, 2.0f, 5.0f)
				);


			CreatePinP();
			m_timer = AddGameObject<UI_CountdownTimer>(185, 180, Vec2(870.0f, 500.0f), Vec2(0.5f), Col4(1.0f), 5);
			m_startSignal = AddGameObject<UI_Count_Signal>(185, 180, Vec3(0.0f), Vec3(2.0f), Vec3(0.0f), Vec3(1.0f), 5, true);
			m_endSignal = AddGameObject<UI_Count_Signal>(5, 0, Vec3(0.0f, 420.0f, 0.0f), Vec3(1.5f), Vec3(0.0f), Vec3(0.8f), 5, false);

			wstring mediaDir;
			App::GetApp()->GetDataDirectory(mediaDir);
			m_curtain =  AddGameObject<UI_Curtain>(mediaDir + L"Texters/ShareImagies/CurtainAnimation/", Vec3(0.0f), Vec3(34.0f), 999999);
			m_curtain->Open();

			//PlaySE(L"爆発_色々01.wav", 0.5f);

			PlayBGM(L"Main_BGM01.wav", 0.1f);

		}
		catch (...) {
			throw;

		}

	}

	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (KeyState.m_bPressedKeyTbl['Z']) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
			StopBGM();
			GameFinishScore();
		}

		WeaponUpdate();
		//m_efkInterface->;
		m_efkInterface->OnUpdate();

		ShowPause();

		//ポーズ画面が開いていて特定のタブでボタンが押された時
		if (m_pause->GetShowing() && m_state == 1) {
			switch (m_pause->GetTabIndex())
			{
			case 3:
				m_state = (KeyState.m_bPressedKeyTbl[VK_LBUTTON] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) ? 5 : ((KeyState.m_bPressedKeyTbl[VK_RBUTTON] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) ? 6 : m_state);
				if ((m_state == 5 || m_state == 6)) {
					m_curtain->Close();
				}
				break;
			default:
				break;
			}
		}

		if (m_curtain->Finished()) {
			switch (m_state)
			{
			case 0:
				m_timer->Start();
				m_state = 1;
				break;
			case 1:
				if (m_timer->GetTime() == 0) {
					m_curtain->Close();
					m_state = 2;
				}
				break;
			case 3:
				NextStage();
				m_state = 10;
				break;
			case 5:
				PrevSelectStage();
				m_state = 10;
				break;
			case 6:
				PrevTitleStage();
				m_state = 10;
				break;
			default:
				break;
			}
		}
	}

	void GameStage::GameFinishScore() {
		wstring ss;
		App::GetApp()->GetDataDirectory(ss);

		auto key = new XmlDoc(ss + L"/XML/" + L"ResultScore.xml");

		vector<CharacterStatus_s> statuses;
		vector<CharacterKillDetails_s> kills;

		auto group = GetSharedObjectGroup(L"CharacterGroup");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto obj = v.lock();
			if (obj) {
				auto character = dynamic_pointer_cast<Character>(obj);
				statuses.push_back(character->GetMyData());
			}
		}

		m_charState = statuses;

		CharacterStatus_s top;

		for (int i = 0; i < m_charState.size(); i++) {
			wstring id = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/ID";
			wstring type = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Type";
			wstring kill = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Kill";
			wstring death = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Death";
			wstring score = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Score";
			wstring player = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Player";
			wstring list = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/List";

			wstring listSave = L"";

			auto& obj = vec[m_charState[i].unique].lock();
			if (obj) {
				auto character = dynamic_pointer_cast<Character>(obj);
				kills = character->GetKillCharacters();
			}
			if (kills.size() > 0) {
				for (int i = 0; i < kills.size(); i++)
				{
					int state = 0;
					CharacterType type = kills[i].type;
					switch (type)
					{
					case CharacterType::SHRIMP:
						state = 0;
						break;
					case CharacterType::CHICKEN:
						state = 3;
						break;
					case CharacterType::POTATO:
						state = 6;
						break;
					case CharacterType::DOUGHNUT:
						state = 9;
						break;
					default:
						break;
					}
					state += kills[i].level;
					listSave += Util::IntToWStr(state);
					listSave += L"|";
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

			for (int i = 0; i < Data.size(); i++) {
				key->SetText(Data[i], Save[i].c_str());
			}

			key->Save(ss + L"/XML/" + L"ResultScore.xml");

			//if (i != 0) {
			//	if (m_charState[i].score > top.score) {
			//		top = m_charState[i];
			//	}
			//	else if (m_charState[i].score == top.score) {
			//		if (m_charState[i].kill > top.kill) {
			//			top = m_charState[i];
			//		}
			//		else if (m_charState[i].kill == top.kill) {
			//			if (m_charState[i].death < top.death) {
			//				top = m_charState[i];
			//			}
			//		}
			//	}
			//}
			//else {
			//	top = m_charState[i];
			//}
		}

		//wstring id = L"ScoreTable/Top/ID";
		//wstring type = L"ScoreTable/Top/Type";
		//wstring kill = L"ScoreTable/Top/Kill";
		//wstring death = L"ScoreTable/Top/Death";
		//wstring score = L"ScoreTable/Top/Score";
		//wstring player = L"ScoreTable/Top/Player";
		//wstring list = L"ScoreTable/Top/List";

		//wstring listSave = L"";
	}

	void GameStage::OnUpdate2() {
		if (!m_timer->GetTime() && m_curtain->Finished()) {
			m_state = 3;
			m_start = false;
			StopBGM();
			m_curtain->Close();
		}
		if (m_timer->GetTime() == 180) m_start = true;

		m_startSignal->SetNowTime(m_timer->GetTime());
		m_endSignal->SetNowTime(m_timer->GetTime());
	}

	void GameStage::NextStage() {
		GameFinishScore();
		App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
	}

	void GameStage::PrevTitleStage() {
		StopBGM();
		App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
	}

	void GameStage::PrevSelectStage() {
		StopBGM();
		App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
	}

	void GameStage::ShowPause() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Rキーもしくはパッドのスタートボタンを押したらポーズ画面を表示する
		if (KeyState.m_bPressedKeyTbl['P'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {

			//m_pinp->Hidden(m_pinp->GetActive());

			if(m_timer->GetTime() < 180) m_start = m_pause->GetShowing();

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
