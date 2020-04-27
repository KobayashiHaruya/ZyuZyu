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
		const Vec3 eye(0.0f, -10.0f, -15.0f);
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
		
		//AddGameObject<Time01>(L"0.png",
		//	Vec2(200.0f, 200.0f),
		//	Vec2(0.0f, -300.0f));

		//AddGameObject<Time10>(L"0.png",
		//    Vec2(200.0f, 200.0f),
		//	Vec2(-30.0f, -300.0f));

		//AddGameObject<Time100>(L"0.png",
		//    Vec2(200.0f, 200.0f),
		//	Vec2(-60.0f, -300.0f));

	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateUI();
			CreateTime();
			AddGameObject<Object>(
				Vec3(0.0f, -25.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(50.0f, 50.0f, 50.0f)
				);
			AddGameObject<Oil>(
				Vec3(0.0f, -60.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(50.0f, 50.0f, 50.0f)
				);
			AddGameObject<Nabe>(
				Vec3(0.0f, -60.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(50.0f, 50.0f, 50.0f)
				);
			m_player = AddGameObject<TestPlayer>(
				Vec3(0.0f, 3.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				10.0f, 10.0f, 5.0f,
				CharacterType::CHICKEN,
				true,
				10,1
				);
			m_enemy = AddGameObject<TestEnemy>(
				Vec3(0.0f, 3.0f, 10.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				5.0f, 10.0f, 5.0f,
				CharacterType::POTATO,
				false,
				1,
				0
				);
			CreatePinP();

			AddGameObject<UI_TestTimeTime>(180, Vec2(870.0f, 500.0f), Vec2(0.5f), Col4(1.0f), 5);
		}
		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['E']) {
			Vec3 rot;
			rot.y = (180.0f * 3.14f) / 180.0f;
			AddGameObject<Bullet>(
				Vec3(0.0f, 2.0f, 15.0f),
				rot,
				Vec3(1.0f, 1.0f, 1.0f),
				50.0f, 10.0f,
				0,
				0,
				CharacterStatus_s({})
				);
		}

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
