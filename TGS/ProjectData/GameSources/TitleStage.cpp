#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
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

	void TitleStage::CreateUI() {
		AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f),
			Vec3(1.0f),
			m_baseLayer,
			Col4(0.0f),
			m_bgImageName
			);

		AddGameObject<UI_Static_Image>(
			Vec2(1024.0f, 689.0f),
			Vec3(0.0f, 180.0f, 0.0f),
			Vec3(0.8f),
			m_baseLayer + 2,
			Col4(1.0f),
			m_titleLogoImageName
			);

		AddGameObject<UI_Flash_Image>(
			Vec2(842.0f, 138.0f),
			Vec3(0.0f, -300.0f, 0.0f),
			Vec3(1.0f),
			m_baseLayer + 2,
			Col4(1.0f),
			m_startButtonImageName,
			1.0f
			);

		AddGameObject<UI_Static_Image>(
			Vec2(419.0f, 70.0f),
			Vec3(745.0f, -500.0f, 0.0f),
			Vec3(1.0f),
			m_baseLayer + 2,
			Col4(1.0f),
			m_explanationButtonImageName
			);

		m_explanationImage = AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			m_baseLayer + 3,
			Col4(1.0f),
			m_explanationImageName
			);

		m_explanationTitleImage = AddGameObject<UI_Static_Image>(
			Vec2(421.0f, 115.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			m_baseLayer + 4,
			Col4(1.0f),
			m_explanationTitleImageName
			);

		m_explanationReturnImage = AddGameObject<UI_Static_Image>(
			Vec2(256.0f, 68.0f),
			Vec3(500.0f, 0.0f, 0.0f),
			Vec3(0.8f),
			m_baseLayer + 4,
			Col4(1.0f),
			m_explanationReturnImageName
			);

		m_explanationStartImage = AddGameObject<UI_Static_Image>(
			Vec2(256.0f, 68.0f),
			Vec3(-500.0f, 0.0f, 0.0f),
			Vec3(0.8f),
			m_baseLayer + 4,
			Col4(1.0f),
			m_explanationStartImageName
			);

		ToggleExplanationImage();

		CreateIcons();
	}

	void TitleStage::CreateIcons() {
		mt19937_64 mt{ random_device{}() };
		uniform_int_distribution<unsigned int> dist(0, m_iconImageNames.size() - 1);
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 4; j++) {
				m_iconImages.push_back(
					AddGameObject<UI_Flash_Image>(
						Vec2(256.0f, 256.0f),
						Vec3(-900.0f + (300.0f * i), 450.0f - (300.0f * j), 0.0f),
						Vec3(0.5f),
						m_baseLayer + 1,
						Col4(1.0f),
						m_iconImageNames[dist(mt)],
						(i * 0.1f) + (j * 0.1f) + 2.0f
						)
				);
			}
		}
	}

	void TitleStage::ToggleExplanationImage() {
		auto e = m_explanationImage->GetDrawActive();
		m_explanationImage->Hidden(e);
		m_explanationTitleImage->Hidden(e);
		m_explanationReturnImage->Hidden(e);
		m_explanationStartImage->Hidden(e);
	}

	void TitleStage::UpdateInput() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bUpKeyTbl[VK_LBUTTON] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}
		if (KeyState.m_bUpKeyTbl[VK_RBUTTON] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			ToggleExplanationImage();
			PlaySE(L"button_pause_se.wav", 0.5f);
		}
	}

	void TitleStage::OnCreate() {
		try {
			StopBGM();

			CreateViewLight();
			CreateUI();

			PlaySE(L"爆発_色々01.wav", 0.5f);
			PlayBGM(L"title_bgm.wav", 0.5f);
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		UpdateInput();
	}
}