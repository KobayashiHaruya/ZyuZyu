#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
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
		//ステージ
		/*AddGameObject<Result_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			0,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_Stage_Image
			);*/

		//スコア
		m_TrueScore = 00000;


		for (int i = 0; i < 5; i++) {	//ループ数で桁変更
			float n = static_cast<float>(i);
			m_Score_UI = AddGameObject<Score_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(0.0f, -200.0f, 0.0f),
				Vec3(1.5f, 1.5f, 1.5f),
				3,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				m_Score_Image,
				static_cast<int>((powf(10.0f, n))),
				static_cast<int>(m_Score)	//表示するスコア
				);
			auto trans = m_Score_UI->GetComponent<Transform>();
			trans->SetPosition(300.0f * 0.5f - n * 64.0f - 64.0f, 150.0f * 0.5f, 0.0f);
		}


		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		m_Cartain = AddGameObject<Result_Curtain>(mediaDir + L"Texters/ResultImagis/ResultAnimation/SpriteStadio/", Vec3(0.0f, 0.0f, 0.0f), Vec3(32.0f), m_layer);
		m_resultThree = AddGameObject<UI_Result_Three>(mediaDir + L"Texters/ResultImagis/ResultAnimation3/", Vec3(0.0f), Vec3(32.0f), m_layer - 6);
		m_resultTwo = AddGameObject<UI_Result_Two>(mediaDir + L"Texters/ResultImagis/ResultAnimation2/", Vec3(0.0f), Vec3(32.0f), m_layer - 3);

		m_resultTwo->ChangeCharacter(CharacterType::DOUGHNUT);
		m_resultTwo->Play();
	}

	void ResultStage::CreateIcon(CharacterType type, int level) {
		m_ResultIcon = AddGameObject<Result_Icon_UI>(
			Vec3(0.0f, 500.0f, 0.0f),
			Vec3(0.3f, 0.3f, 0.3f),
			0,
			type,
			level
			);
	}

	void ResultStage::ScoreMove() {
		m_Second += App::GetApp()->GetElapsedTime();
		int Po_1 = m_TrueScore % 10;	//1の位抽出

		int Po_2 = m_TrueScore / 10;	//2の位抽出
		Po_2 = Po_2 % 10;

		int Po_3 = m_TrueScore / 100;	//3の位抽出
		Po_3 = Po_3 % 10;

		int Po_4 = m_TrueScore / 1000;	//4の位抽出
		Po_4 = Po_4 % 10;

		int Po_5 = m_TrueScore / 10000;	//5の位抽出
		Po_5 = Po_5 % 10;


		int score = GetScore();
		int aPo_1 = score % 10;	//1の位抽出

		int aPo_2 = score / 10;	//2の位抽出
		aPo_2 = aPo_2 % 10;

		int aPo_3 = score / 100;	//3の位抽出
		aPo_3 = aPo_3 % 10;

		int aPo_4 = score / 1000;	//4の位抽出
		aPo_4 = aPo_4 % 10;

		int aPo_5 = score / 10000;	//5の位抽出
		aPo_5 = aPo_5 % 10;

		if (m_Second <= 1.0f) {
			AddScore(rand());
		}


		if (Po_1 != aPo_1 || Po_2 != aPo_2 || Po_3 != aPo_3 || Po_4 != aPo_4 || Po_5 != aPo_5 && m_Second >= 1.0f) {
			if (Po_1 != aPo_1) {
				AddScore(rand());
				//m_Score_UI->SetScore1(aPo_1);
			}
			else if (Po_1 == aPo_1) {
				m_Score_UI->SetScore1(aPo_1);
			}

			if (Po_1 == aPo_1 && Po_2 != aPo_2 && m_Second >= 1.5f) {
				AddScore(rand() * 10);
				//m_Score_UI->SetScore2(aPo_2);
			}
			else if (Po_2 == aPo_2) {
				m_Score_UI->SetScore2(aPo_2);
			}

			if (Po_2 == aPo_2 && Po_3 != aPo_3 && m_Second >= 2.0f) {
				AddScore(rand() * 100);
				//m_Score_UI->SetScore3(aPo_3);
			}
			else if (Po_3 == aPo_3) {
				m_Score_UI->SetScore3(aPo_3);
			}

			if (Po_3 == aPo_3 && Po_4 != aPo_4 && m_Second >= 3.0f) {
				AddScore(rand() * 1000);
				//AddScore(-5000);
				//m_Score_UI->SetScore4(aPo_4);
				AddScore(-10000);
			}
			else if (Po_4 == aPo_4) {
				m_Score_UI->SetScore4(aPo_4);
			}

			if (Po_4 == aPo_4 && Po_5 != aPo_5 && m_Second >= 4.0f) {
				AddScore(rand() * 10000);
				AddScore(-50000);
				//m_Score_UI->SetScore5(aPo_5);
				//AddScore(0);
				if (aPo_5 == 0) {
					m_Score_UI->SetScore5(aPo_5);
				}
			}
			else if (Po_5 == aPo_5) {
				m_Score_UI->SetScore5(aPo_5);
			}
		}
	}

	void ResultStage::OnCreate() {
		try {
			StopBGM();
			CreateViewLight();
			CreateUI();
			//AddGameObject<ResultScore>();
			CreateIcon(m_type, m_level);
			PlayBGM(L"rezult_bgm.wav", 0.5f);
		}
		catch (...) {
			throw;
		}
	}


	void ResultStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bUpKeyTbl[VK_LBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}

		if (KeyState.m_bUpKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}

		ScoreMove();


		auto Trans = m_ResultIcon->GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		if (Pos.y > -10.0f) {
			Trans->SetPosition(0.0f, m_Move, 0.0f);
			m_Move -= 10.0f;
		}

		if (m_Cartain->GetCount() >= 40) m_resultThree->Play();
	}

}