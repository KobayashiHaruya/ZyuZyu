#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}


	void ResultStage::CreateUI() {
		//�X�e�[�W
		/*AddGameObject<Result_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			0,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_Stage_Image
			);*/

		//�X�R�A
		m_TrueScore = 10000;


		for (int i = 0; i < 5; i++) {	//���[�v���Ō��ύX
			float n = static_cast<float>(i);
			m_Score_UI[i] = AddGameObject<Score_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(300.0f * 0.5f - n * 64.0f - 64.0f, 150.0f * 0.5f, 0.0f),
				Vec3(1.5f, 1.5f, 1.5f),
				3,
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
		m_resultThree = AddGameObject<UI_Result_Three>(mediaDir + L"Texters/ResultImagis/ResultAnimation3/", Vec3(0.0f), Vec3(32.0f), m_layer - 6);
		m_resultTwo = AddGameObject<UI_Result_Two>(mediaDir + L"Texters/ResultImagis/ResultAnimation2/", Vec3(0.0f), Vec3(32.0f), m_layer - 3);

		m_resultTwo->ChangeCharacter(CharacterType::DOUGHNUT);
		m_resultTwo->Play();
	}

	void ResultStage::CreateIcon(CharacterType type, int level) {
		//m_ResultIcon = AddGameObject<Result_Icon_UI>(
		//	Vec3(0.0f, 500.0f, 0.0f),
		//	Vec3(0.3f, 0.3f, 0.3f),
		//	0,
		//	type,
		//	level
		//	);
	}

	void ResultStage::ScoreMove() {
		m_Second += App::GetApp()->GetElapsedTime();
		if (m_Second <= 13.0f) {
			SetScore(rand());
		}
		else {
			SetScore(m_TrueScore);
		}

		//auto Trans = m_Score_UI->GetComponent<Transform>();
		//if (m_PosY > -10.0f) {
		//	Trans->SetPosition(0.0f, m_PosY, 0.0f);
		//	m_PosY -= 10.0f;
		//}
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
		m_Second += App::GetApp()->GetElapsedTime();

		if (KeyState.m_bUpKeyTbl[VK_LBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}

		if (KeyState.m_bUpKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}

		ScoreMove();


		//auto Trans = m_ResultIcon->GetComponent<Transform>();
		//auto Pos = Trans->GetPosition();
		//if (Pos.y > -10.0f) {
		//	Trans->SetPosition(0.0f, m_Move, 0.0f);
		//	m_Move -= 10.0f;
		//}
		
		if (m_Cartain->GetCount() >= 40) m_resultThree->Play();
	}

	void ResultStage::OnUpdate2() {
		m_Second += App::GetApp()->GetElapsedTime();
		for (int i = 0; i < 5; i++) {	//���[�v���Ō��ύX

			if (m_Second >= 8.0f) {
				m_Score_UI[i]->SetDrawActive(true);

			}
		}
	}
}