#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void ResultStage::CreateUI() {
		//スコア
		m_TrueScore = 10000;

		for (int i = 0; i < 5; i++) {	//ループ数で桁変更
			float n = static_cast<float>(i);
			m_Score_UI[i] = AddGameObject<Score_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(300.0f * 0.5f - n * 64.0f - 64.0f, 460.0f * 0.5f, 0.0f),
				Vec3(1.5f, 1.5f, 1.5f),
				m_layer,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				m_Score_Image,
				static_cast<int>((powf(10.0f, n))),
				static_cast<int>(m_Score)
				);
			m_Score_UI[i]->SetDrawActive(false);
		}
	}

	void ResultStage::CreateIcon(CharacterType type) {
		m_Second2 += App::GetApp()->GetElapsedTime();
		m_randpos = rand() % 5;
		m_randpos -= rand() % 5;
		if (m_Second2 > 0.5f) {
			switch (m_type)
			{
			case POTATO:
				AddGameObject<Result_Icon>(
					m_position + Vec3(m_randpos, 0.0f, 0.0f),
					type
					);
				m_type = DOUGHNUT;
				break;
			case SHRIMP:
				AddGameObject<Result_Icon>(
					m_position + Vec3(m_randpos, 0.0f, 0.0f),
					type
					);
				m_type = POTATO;

				break;
			case CHICKEN:
				AddGameObject<Result_Icon>(
					m_position + Vec3(m_randpos, 0.0f, 0.0f),
					type
					);
				m_type = SHRIMP;

				break;
			case DOUGHNUT:
				AddGameObject<Result_Icon>(
					m_position + Vec3(m_randpos, 0.0f, 0.0f),
					type
					);
				m_type = CHICKEN;

				break;
			}
			m_Second2 = 0.0f;
		}
	}

	void ResultStage::CreateWall() {
		AddGameObject<Wall>(
			Vec3(0.0f, -2.5f, 5.0f),
			Quat(),
			Vec3(10.0f, 1.0f, 100.0f)
			);
		//m_Object->SetDrawActive(false);


	}

	void ResultStage::ScoreMove() {
		m_Second += App::GetApp()->GetElapsedTime();
		if (m_Second < 13.0f) {
			SetScore(rand());
		}
		else if (m_Onoff) {
			SetScore(m_TrueScore);
			PlaySE(L"Curia02.wav", 0.5f);
			m_Onoff = false;

			PlayStarEffect();
			PlayCrackerEffect();
		}
	}

	void ResultStage::OnDraw()
	{
		auto& camera = GetView()->GetTargetCamera();
		m_efkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_efkInterface->OnDraw();
	}


	void ResultStage::OnCreate() {
		try {
			CreateScoreTable();
			ShowScoreTable(false);

			m_efkInterface = ObjectFactory::Create<EfkInterface>();
			
			//m_efkEffect = GetEffect(エフェクトの名前);
			//m_efkPlay = ObjectFactory::Create<EfkPlay>(m_efkEffect, ptr->GetPosition());
			//m_efkPlay->Play(m_efkEffect, ptr->GetPosition());

			ReadScore();
			StopBGM();
			CreateViewLight();
			CreateUI();		
			CreateWall();

			CreateSplash();
			//PlayBGM(L"rezult_bgm.wav", 0.5f);
			PlaySE(L"Doram01.wav", 0.5f);
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		m_Second += App::GetApp()->GetElapsedTime();

		m_efkInterface->OnUpdate();

		if ((KeyState.m_bUpKeyTbl[VK_LBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) && m_state == 10) {
			m_curtain->Close();
			m_state = 1;
		}

		if ((KeyState.m_bUpKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) && m_state == 10) {
			m_curtain->Close();
			m_state = 2;
		}

		if (KeyState.m_bPressedKeyTbl['P'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
			ShowScoreTable(m_isScoreTableShow = !m_isScoreTableShow);
		}

		if (m_curtain->Finished()) {
			switch (m_state)
			{
			case 0:
				m_resultThree->Play();
				m_state = 10;
				break;
			case 1:
				StopBGM();
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
				m_state = 100;
				break;
			case 2:
				StopBGM();
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
				m_state = 100;
				break;
			default:
				break;
			}
		}

		ScoreMove();
		if (m_Second > 5.0f) {
			if (m_Second < 35.0f) {
				CreateIcon(m_type);
			}
		}
		//if (m_Cartain->GetCount() >= 40) m_resultThree->Play();
		UpdateEffectWaitTimert();
	}

	void ResultStage::OnUpdate2() {
		m_Second += App::GetApp()->GetElapsedTime();
		for (int i = 0; i < 5; i++) {

			if (m_Second >= 8.0f) {
				m_Score_UI[i]->SetDrawActive(true);
			}
		}
	}

	void ResultStage::ReadScore() {
		wstring key;
		App::GetApp()->GetDataDirectory(key);

		unique_ptr<XmlDocReader> m_XmlDocReader;
		m_XmlDocReader.reset(new XmlDocReader(key + L"XML/" + L"ResultScore.xml"));

		wstring table = L"ScoreTable/Char";


		for (int i = 0; i < 8; i++) {
			CharacterStatus_s m_myData;
			vector<int> killList;

			wstring id = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/ID";
			wstring type = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Type";
			wstring kill = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Kill";
			wstring death = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Death";
			wstring score = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Score";
			wstring player = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Player";
			wstring list = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/List";

			m_myData.unique = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(id.c_str())));
			m_myData.type = (CharacterType)std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(type.c_str())));
			m_myData.kill = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(kill.c_str())));
			m_myData.death = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(death.c_str())));
			m_myData.score = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(score.c_str())));
			m_myData.isPlayer = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(player.c_str())));

			wstring kills = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(list.c_str()));

			int killState = 0;
			wstring num = L"";
			for (int j = 0; j < kills.size(); j++) {
				if (kills[j] == L'|') {
					if (num != L"") {
						killState = std::stoi(num);
						killList.push_back(killState);
					}
					num = L"";
				}
				else {
					num += kills[j];
				}
			}

			m_charState.push_back(m_myData);
			m_KillList.push_back(killList);

		}
	}

	void ResultStage::CreateSplash() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		m_curtain = AddGameObject<UI_Curtain>(mediaDir + L"Texters/ShareImagies/CurtainAnimation/", Vec3(0.0f), Vec3(34.0f), m_layer + 200);
		m_curtain->Open();
		
		m_resultThree = AddGameObject<UI_Result_Three>(mediaDir + L"Texters/ResultImagis/ResultAnimation3/", Vec3(0.0f), Vec3(32.0f), m_layer - 9);
		m_resultTwo = AddGameObject<UI_Result_Two>(mediaDir + L"Texters/ResultImagis/ResultAnimation2_ver4/", Vec3(0.0f), Vec3(32.0f), m_layer - 1);

		m_resultTwo->ChangeCharacter(CharacterType::DOUGHNUT);  //スプラッシュにキャラクターのタイプを指定
		m_resultTwo->Play();
	}

	void ResultStage::CreateScoreTable() {
		m_scoreTableBack = AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f),
			Vec3(1.0f),
			m_layer + 100,
			Col4(0.0f, 0.0f, 0.0f, 0.5f),
			L"dot.png"
			);

		m_scoreTable = AddGameObject<UI_Score_Table>(8, m_layer + 101);
		//m_scoreTable->SetCharacterStatuses(m_characterStatuses);  //スコアテーブルにキャラクターのステータスを指定
	}

	void ResultStage::ShowScoreTable(const bool e) {
		m_scoreTableBack->Hidden(!e);
		m_scoreTable->Show(e);
		m_isScoreTableShow = e;
	}

	void ResultStage::UpdateEffectWaitTimert() {
		if (m_effectWaitTimaer <= -1.0f) return;
		m_effectWaitTimaer += App::GetApp()->GetElapsedTime();
		if (m_effectWaitTimaer >= 8.0f) {
			AddGameObject<UI_Static_Image>(
				Vec2(863.0f, 82.0f),
				Vec3(-730.0f, -500.0f, 0.0f),
				Vec3(0.5f),
				m_layer + 101,
				Col4(1.0f),
				m_resultFont
				);

			ShowScoreTable(true);

			m_effectWaitTimaer *= -1.0f;
		}
	}

	void ResultStage::PlayStarEffect() {
		m_starEffect = GetEffect(L"ShiningStar.efk");
		m_starEffectPlay = ObjectFactory::Create<EfkPlay>(m_starEffect, Vec3(0.0f));
		m_starEffectPlay->Play(m_starEffect, Vec3(0.0f, 0.0f, 15.0f));
	}

	void ResultStage::PlayCrackerEffect() {
		m_crackerEffect = GetEffect(L"Cracker.efk");
		m_crackerEffectPlay = ObjectFactory::Create<EfkPlay>(m_crackerEffect, Vec3(0.0f));
		m_crackerEffectPlay->Play(m_crackerEffect, Vec3(0.0f, -10.0f, 20.0f));
	}
}