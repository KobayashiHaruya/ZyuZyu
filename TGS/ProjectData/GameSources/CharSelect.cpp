#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CharSelectStage::CreateViewLight() {
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

	void CharSelectStage::CreateUI() {
		AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_baseImageName
			);

		m_characterLogo = AddGameObject<UI_Static_Image>(
			Vec2(631.0f, 278.0f),
			Vec3(-480.0f, -380.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			m_layer,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_chickenImageName
			);

		m_mask = AddGameObject<UI_Character_Select_Mask_Image>(
			Vec2(3360.0f, 720.0),
			Vec3(-720.0f + (480.0f * 0), 180.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 0.85f),
			m_maskImageName,
			m_startIndex
			);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		m_characterStatus = AddGameObject<UI_Character_Status>(mediaDir + L"Texters/StageSelectImagies/Status_Animation/SpriteStudio/", Vec3(230.0f, -375.0f, 0.0f), Vec3(30.0f), m_layer);

		ChangeCharacter(m_startIndex);

		m_theWorld = AddGameObject<UI_The_World>(m_layer);
	}

	void CharSelectStage::OnCreate() {
		try {
			CreateViewLight();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void CharSelectStage::OnUpdate() {
		ChangeCharacter(m_mask->GetIndex());
		Select();
		TestFunc();
	}

	void CharSelectStage::ChangeCharacter(int index) {
		if (m_oldIndex == index) return;
		switch (index)
		{
		case 0:
			m_characterLogo->SetTexture(
				m_shrimpImageName,
				Vec2(631.0f, 298.0f),
				Vec3(0.95f, 0.95f, 0.95f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::SHRIMP);
			break;
		case 1:
			m_characterLogo->SetTexture(
				m_chickenImageName,
				Vec2(631.0f, 278.0f),
				Vec3(1.0f, 1.0f, 1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::CHICKEN);
			break;
		case 2:
			m_characterLogo->SetTexture(
				m_potatoImageName,
				Vec2(621.0f, 285.0f),
				Vec3(1.0f, 1.0f, 1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::POTATO);
			break;
		case 3:
			m_characterLogo->SetTexture(
				m_doughnutImageName,
				Vec2(631.0f, 264.0f),
				Vec3(1.0f, 1.0f, 1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::DOUGHNUT);
			break;
		}
		m_oldIndex = index;
	}

	void CharSelectStage::Select() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			//ここにゲームステージへ遷移する処理を書く
			//GetIndex()で選択したキャラクターのIndexを取得できます
			int index = GetIndex();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
		}
	}

	void CharSelectStage::TestFunc() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bPressedKeyTbl['W'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
			m_theWorld->Show(!(m_theWorld->GetShowing()));
		}
	}
}