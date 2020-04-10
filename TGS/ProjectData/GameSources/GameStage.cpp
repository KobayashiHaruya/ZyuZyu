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


		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
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
		// HP�o�[
		AddGameObject<Time>(L"0.png",
			Vec2(250.0f, 250.0f),
			Vec2(0.0f, -400.0f));
	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateUI();
			CreateTime();
			AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(100.0f, 0.5f, 100.0f)
				);
			AddGameObject<Oil>(
				Vec3(0.0f, -10.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(150.0f, 0.1f, 150.0f)
				);
			m_player = AddGameObject<TestPlayer>(
				Vec3(0.0f, 3.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				0.15f, 10.0f, 5.0f,
				CharacterType::CHICKEN,
				true,
				0
				);
			m_enemy = AddGameObject<TestEnemy>(
				Vec3(0.0f, 3.0f, 50.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				0.15f, 10.0f, 5.0f,
				CharacterType::POTATO,
				false,
				1
				);

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['E']) {


		}

		ShowPause();
	}

	void GameStage::ShowPause() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//R�L�[�������̓p�b�h�̃X�^�[�g�{�^������������|�[�Y��ʂ�\������
		if (KeyState.m_bPressedKeyTbl['R'] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {

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

}
//end basecross
