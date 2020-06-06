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
				10,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				m_Score_Image,
				static_cast<int>((powf(10.0f, n))),
				static_cast<int>(m_Score)
				);
			m_Score_UI[i]->SetDrawActive(false);
		}

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		m_Cartain = AddGameObject<Result_Curtain>(mediaDir + L"Texters/ResultImagis/ResultAnimation/SpriteStadio/", Vec3(0.0f, 0.0f, 0.0f), Vec3(32.0f), m_layer);
		m_resultThree = AddGameObject<UI_Result_Three>(mediaDir + L"Texters/ResultImagis/ResultAnimation3/", Vec3(0.0f), Vec3(32.0f), m_layer - 9);
		m_resultTwo = AddGameObject<UI_Result_Two>(mediaDir + L"Texters/ResultImagis/ResultAnimation2_ver4/", Vec3(0.0f), Vec3(32.0f), m_layer - 1);

		m_resultTwo->ChangeCharacter(CharacterType::DOUGHNUT);
		m_resultTwo->Play();
	}

	void ResultStage::CreateIcon(CharacterType type) {
		m_randpos = rand() % 5;
		m_randpos -= rand() % 5;
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
		if (m_Second <= 13.0f) {
			SetScore(rand());
		}
		else {
			SetScore(m_TrueScore);
		}
	}

	void ResultStage::OnCreate() {
		try {
			StopBGM();
			CreateViewLight();
			CreateUI();		
			CreateIcon(m_type);
			CreateWall();
			//AddGameObject<ResultScore>();
			PlayBGM(L"rezult_bgm.wav", 0.5f);
		}
		catch (...) {
			throw;
		}
	}


	void ResultStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		m_Second += App::GetApp()->GetElapsedTime();

		if (KeyState.m_bUpKeyTbl[VK_LBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}

		if (KeyState.m_bUpKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}

		if (KeyState.m_bUpKeyTbl[VK_DOWN] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)){
			CreateIcon(m_type);
		}


		ScoreMove();

		if (m_Cartain->GetCount() >= 40) m_resultThree->Play();
	}

	void ResultStage::OnUpdate2() {
		m_Second += App::GetApp()->GetElapsedTime();
		for (int i = 0; i < 5; i++) {	//ループ数で桁変更

			if (m_Second >= 8.0f) {
				m_Score_UI[i]->SetDrawActive(true);

			}
		}
	}
}