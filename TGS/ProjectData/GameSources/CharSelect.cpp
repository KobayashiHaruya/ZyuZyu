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
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			m_layer,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_chickenImageName
			);

		m_mask = AddGameObject<UI_Character_Select_Mask_Image>(
			Vec2(3360.0f, 720.0),
			Vec3(-720.0f + (480.0f * 0), 180.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			m_layer,
			Col4(1.0f, 1.0f, 1.0f, 1.8f),
			m_maskImageName,
			m_startIndex
			);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		m_characterStatus = AddGameObject<UI_Character_Status>(mediaDir + L"Texters/StageSelectImagies/Status_Animation/SpriteStudio/", Vec3(230.0f, -375.0f, 0.0f), Vec3(30.0f), m_layer);
		m_curtain = AddGameObject<UI_Curtain>(mediaDir + L"Texters/ShareImagies/CurtainAnimation/", Vec3(0.0f), Vec3(34.0f), m_layer + 100);
		m_curtain->Open();

		ChangeCharacter(m_startIndex);
	}

	void CharSelectStage::OnCreate() {
		try {
			CreateViewLight();
			CreateUI();
			PlayBGM(L"title_bgm.wav", 0.5f);
		}
		catch (...) {
			throw;
		}
	}

	void CharSelectStage::OnUpdate() {
		ChangeCharacter(m_mask->GetIndex());
		Select();

		if (m_curtain->Finished() && m_state != 0) {
			switch (m_state)
			{
			case 1:
				NextStage();
				break;
			case 2:
				PrevStage();
				break;
			default:
				break;
			}
		}
	}

	void CharSelectStage::ChangeCharacter(int index) {
		if (m_oldIndex == index) return;
		switch (index)
		{
		case 0:
			m_characterLogo->SetTexture(
				m_shrimpImageName,
				Vec2(1920.0f, 1080.0f),
				Vec3(1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::SHRIMP);
			break;
		case 1:
			m_characterLogo->SetTexture(
				m_chickenImageName,
				Vec2(1920.0f, 1080.0f),
				Vec3(1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::CHICKEN);
			break;
		case 2:
			m_characterLogo->SetTexture(
				m_potatoImageName,
				Vec2(1920.0f, 1080.0f),
				Vec3(1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::POTATO);
			break;
		case 3:
			m_characterLogo->SetTexture(
				m_doughnutImageName,
				Vec2(1920.0f, 1080.0f),
				Vec3(1.0f)
			);
			m_characterStatus->ChangeCharacterStatus(CharacterType::DOUGHNUT);
			break;
		}
		m_oldIndex = index;
		PlaySE(L"button_pause_se.wav", 0.5f);
	}

	void CharSelectStage::Select() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if ((KeyState.m_bUpKeyTbl[VK_LBUTTON] || KeyState.m_bPressedKeyTbl[VK_SPACE] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) && m_state == 0) {
			PlaySE(L"button_pause_se.wav", 0.5f);
			m_curtain->Close();
			m_state = 1;
		}
		if ((KeyState.m_bUpKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) && m_state == 0) {
			PlaySE(L"button_pause_se.wav", 0.5f);
			m_curtain->Close();
			m_state = 2;
		}
	}

	void CharSelectStage::NextStage() {
		//ここにゲームステージへ遷移する処理を書く
		SelectData();
		StopBGM();
		App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
	}

	void CharSelectStage::PrevStage() {
		App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		StopBGM();
	}

	void CharSelectStage::SelectData() {
		wstring ss;
		App::GetApp()->GetDataDirectory(ss);

		auto key = new XmlDoc(ss + L"/XML/" + L"CharSelect.xml");

		//GetIndex()で選択したキャラクターのIndexを取得できます
		int index = GetIndex();

		key->SetText(key->GetSelectSingleNode(L"CharSelect/Character"), Util::FloatToWStr(index, 1, Util::Fixed).c_str());

		//key->Save(ss + L"/XML/" + L"CharSelect.xml");
	}


}