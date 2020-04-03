#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CharSelectStage::CreateViewLight() {
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

	void CharSelectStage::CreateUI() {
		AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_baseImageName
			);

		m_chicken = AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 360.0f),
			Vec3(0.0f, -360.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_chickenImageName
			);

		m_potato = AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 360.0f),
			Vec3(0.0f, -360.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_potatoImageName
			);

		m_shrimp = AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 360.0f),
			Vec3(0.0f, -360.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_shrimpImageName
			);

		m_doughnut = AddGameObject<UI_Static_Image>(
			Vec2(1920.0f, 360.0f),
			Vec3(0.0f, -360.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_doughnutImageName
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

		SetStatusImage(m_startIndex);





		m_theWorld = AddGameObject<UI_The_World>(5);

		vector<CharacterStatus_s> statuses;
		statuses.push_back({ L"�|�e�g", 10, 2, 5260, true, 0 });
		statuses.push_back({ L"�`�L��", 10, 2, 3000, false, 1 });
		statuses.push_back({ L"�h�[�i�c", 10, 2, 3000, false, 2 });
		statuses.push_back({ L"�G�r", 10, 2, 3000, false, 3 });
		statuses.push_back({ L"�|�e�g", 10, 2, 3000, false, 4 });
		statuses.push_back({ L"�`�L��", 10, 2, 3000, false, 5 });
		statuses.push_back({ L"�h�[�i�c", 10, 2, 3000, false, 6 });
		statuses.push_back({ L"�G�r", 10, 2, 3000, false, 7 });
		m_theWorld->SetCharacterStatuses(statuses);

		vector<CharacterKillDetails_s> killDetails;
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		killDetails.push_back({ CharacterType::SHRIMP, 1 });
		killDetails.push_back({ CharacterType::CHICKEN, 2 });
		killDetails.push_back({ CharacterType::POTATO, 3 });
		killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
		m_theWorld->SetCharacterKillDetails(killDetails);
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
		SetStatusImage(m_mask->GetIndex());
		Select();
		TestFunc();
	}

	void CharSelectStage::SetStatusImage(int index) {
		m_chicken->SetDrawActive(false);
		m_potato->SetDrawActive(false);
		m_shrimp->SetDrawActive(false);
		m_doughnut->SetDrawActive(false);
		return;
		switch (index)
		{
		case 0:
			m_potato->SetDrawActive(true);
			break;
		case 1:
			m_shrimp->SetDrawActive(true);
			break;
		case 2:
			m_chicken->SetDrawActive(true);
			break;
		case 3:
			m_doughnut->SetDrawActive(true);
			break;
		default:
			break;
		}
	}

	void CharSelectStage::Select() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			//�����ɃQ�[���X�e�[�W�֑J�ڂ��鏈��������
			//GetIndex()�őI�������L�����N�^�[��Index���擾�ł��܂�
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

		if (KeyState.m_bPressedKeyTbl['S']) {
			CharacterStatus_s status = { L"�|�e�g", 1000, 102, 50, true, 0 };
			m_theWorld->SetCharacterStatus(status);

			vector<CharacterKillDetails_s> killDetails;
			killDetails.push_back({ CharacterType::SHRIMP, 1 });
			killDetails.push_back({ CharacterType::CHICKEN, 2 });
			killDetails.push_back({ CharacterType::POTATO, 3 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::SHRIMP, 1 });
			killDetails.push_back({ CharacterType::CHICKEN, 2 });
			killDetails.push_back({ CharacterType::POTATO, 3 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::SHRIMP, 1 });
			killDetails.push_back({ CharacterType::CHICKEN, 2 });
			killDetails.push_back({ CharacterType::POTATO, 3 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::SHRIMP, 1 });
			killDetails.push_back({ CharacterType::CHICKEN, 2 });
			killDetails.push_back({ CharacterType::POTATO, 3 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			killDetails.push_back({ CharacterType::DOUGHNUT, 1 });
			m_theWorld->SetCharacterKillDetails(killDetails);
		}
	}
}