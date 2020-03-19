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

	}


	void GameStage::OnCreate() {
		try {
			//SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateUI();
			AddGameObject<Object>(
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(50.0f, 0.5f, 10.0f)
				);
			AddGameObject<Object>(
				Vec3(0.0f, 4.0f, 20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(5.0f, 10.0f, 5.0f)
				);
			AddGameObject<TestPlayer>(
				Vec3(0.0f, 3.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				0.15f, 10.0f, 5.0f
				);


			AddGameObject<Bullet>(
				Vec3(-10.0f, 3.0f, 1.0f),
				Vec3(0.0f, 90.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				10.0f, 80.0f
				);
			AddGameObject<Bullet>(
				Vec3(-5.0f, 3.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				10.0f, 80.0f
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

	}

}
//end basecross
