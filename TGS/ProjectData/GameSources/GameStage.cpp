/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, -6.0f, -6.0f);
		const Vec3 at(0.0f);

		//auto PtrView = CreateView<SingleView>();
		////�r���[�̃J�����̐ݒ�
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(eye);
		//PtrCamera->SetAt(at);
		////�}���`���C�g�̍쐬
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////�f�t�H���g�̃��C�e�B���O���w��
		//PtrMultiLight->SetDefaultLighting();

		auto& app = App::GetApp();
		Viewport view = { 0.0f, 0.0f, app->GetGameWidth(), app->GetGameHeight(), 0.0f, 1.0f };
		auto ptrView = CreateView<MultiView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		//ptrView->SetCamera(ptrMyCamera);
		//ptrView->SetViewport(view);
		//ptrMyCamera->SetViewPort(ptrView->GetViewport());
		//ptrView->SetViewport(ptrMyCamera->getv);
		ptrView->AddView(view, ptrMyCamera);
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateUI() {
		m_pause = AddGameObject<UI_The_World>(5);

	}

	void GameStage::CreateTime() {
		
		AddGameObject<Time01>(1,L"0_9.png",true,
			Vec2(25.0f, 25.0f),
			Vec3(900.0f, 500.0f, 0.0f));

		AddGameObject<Time10>(1, L"0_9.png", true,
			Vec2(25.0f, 25.0f),
			Vec3(850.0f, 500.0f, 0.0f));

		AddGameObject<Time100>(1, L"0_9.png", true,
			Vec2(25.0f, 25.0f),
			Vec3(750.0f, 500.0f, 0.0f));

		AddGameObject<Sprite>(L"Colon.png",
			Vec2(25.0f, 25.0f),
			Vec2(800.0f, 500.0f));


	}


	void GameStage::WeaponUpdate() {
		m_weaponTime -= App::GetApp()->GetElapsedTime();

		if (m_weaponTime <= 0.0f) {
			AddGameObject<Weapon>();
			m_weaponTime = 10.0f;
		}

	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateUI();
			CreateTime();
			AddGameObject<Object>(
				Vec3(0.0f, -10.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 60.0f, 60.0f)
				);
			AddGameObject<Oil>(
				Vec3(0.0f, -40.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 60.0f, 60.0f)
				);
			AddGameObject<Nabe>(
				Vec3(0.0f, -80.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 60.0f, 60.0f)
				);
			m_player = AddGameObject<Player>(
				CharacterType::SHRIMP,
				true,
				0, 0
				);
			SetSharedGameObject(L"Player", m_player);

			for (int i = 1; i < 8; i++) {

				CharacterType p;
				int Rand = rand() % 5;
				switch (Rand) {
				case 0:
					p = CharacterType::CHICKEN;
					break;
				case 1:
					p = CharacterType::DOUGHNUT;
					break;
				case 2:
					p = CharacterType::POTATO;
					break;
				case 3:
					p = CharacterType::SHRIMP;
					break;
				}

				m_enemy = AddGameObject<Enemy>(
					p,
					false,
					i, i
					);
			}

			for (int i = 0; i < 5; i++) {
				AddGameObject<Weapon>();
			}
			m_weaponTime = 10.0f;

			AddGameObject<GatlingGun>();


			CreatePinP();
		}

		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['Z']) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
		}

		float TimeEat = App::GetApp()->GetElapsedTime();
		float TimeEat2 = App::GetApp()->GetElapsedTime();
		float TimeEat3 = App::GetApp()->GetElapsedTime();

		m_TotalTime -= TimeEat;
		m_TotalTime2 -= TimeEat2;
		m_TotalTime3 -= TimeEat3;
		//if (m_TotalTime <= 000.0f) {
		//	m_TotalTime = 9.999f;
		//}
		//if (m_TotalTime2 <= 000.0f) {
		//	m_TotalTime2 = 5.999f;
		//}
		//if (m_TotalTime3 <= 000.0f) {
		//	m_TotalTime3 = 2.999f;
		//}
		//else if (m_TotalTime3 > 1.98f && m_TotalTime3 <= 0.98)
		//{
		//	m_TotalTime3 = 1.579f;
		//}

		//�X�R�A���X�V����
		auto ptrScor = GetSharedGameObject<Time01>(L"Time01");
		ptrScor->SetScore(m_TotalTime);

		//�X�R�A���X�V����
		auto ptrScor2 = GetSharedGameObject<Time10>(L"Time10");
		ptrScor2->SetScore(m_TotalTime2);

		//�X�R�A���X�V����
		auto ptrScor3 = GetSharedGameObject<Time100>(L"Time100");
		ptrScor3->SetScore(m_TotalTime3);

		WeaponUpdate();
		ShowPause();
	}

	void GameStage::ShowPause() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//R�L�[�������̓p�b�h�̃X�^�[�g�{�^������������|�[�Y��ʂ�\������
		if (KeyState.m_bPressedKeyTbl['P'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {

			m_pinp->Hidden(m_pinp->GetActive());

			//�����ł͖���z��𐶐����ăX�e�[�^�X��ݒ肵�Ă��邪���ۂɂ͂P�x������������ChangeStatus������
			vector<CharacterStatus_s> statuses;
			statuses.push_back(m_player->GetMyData());
			statuses.push_back(m_enemy->GetMyData());
			m_pause->SetCharacterStatuses(statuses);

			//�L���̏��ڍׂ�\��������Character��������擾���ă|�[�Y��ʂɒl��n��
			m_pause->SetCharacterKillDetails(m_player->GetKillCharacters());

			//���ۂɃ|�[�Y��ʂ�\������
			//�����͌��݃|�[�Y��ʂ��A�N�e�B�u���ǂ������擾���Ă��̃t���O�𔽓]�����邱�Ƃŕ\����\����؂�ւ��Ă���
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
		SetSharedGameObject(L"BlownPinP", m_pinp);  //shareObject�Ƃ���PinP��o�^
	}

}
//end basecross
