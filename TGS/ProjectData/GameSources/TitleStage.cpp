#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
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

	void TitleStage::CreateUI() {
		AddGameObject<Title_UI>(
			Vec2(1920.0f, 1080.0f),	//vertex
			Vec3(0.0f, 0.0f, 0.0f),	//pos
			Vec3(1.0f, 1.0f, 1.0f),	//scale
			1,	//layer
			Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
			//�W���̃^�C�g���摜
			L"NewTitle_ver2.png"	//file(texture)
			);

		//switch (RandGenerator()) {
		//case 0:	//�G�rver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Shrimp_Title	//file(texture)
		//		);
		//	break;

		//case 1:	//�`�L��ver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Chicken_Title	//file(texture)
		//		);
		//	break;

		//case 2:	//�|�e�gver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Potato_Title	//file(texture)
		//		);
		//	break;

		//case 3:	//�h�[�i�cver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Donut_Title	//file(texture)
		//		);
		//	break;
		//default:
		//	break;
		//}
	}

	void TitleStage::CreateOperationUI() {
		//��������摜
		AddGameObject<Operation_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			2,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			L"Operation_ver3.png"
			);
	}

	void TitleStage::OnCreate() {
		try {
			CreateViewLight();
			CreateUI();

			//SE���Đ�
			PlaySE(L"����_�F�X01.wav", 0.5f);
			//BGM���Đ�
			PlayBGM(L"title_bgm.wav", 0.5f);
			//BGM���~�߂�
			//StopBGM();

			//�^�C�g���Ŏg�����ōĐ���������
			//GetTypeStage<TitleStage>()->PlaySE(L"����_�F�X01.wav", 0.5f);

			//�L�����Z���N�g�Ŏg�����ōĐ���������
			//GetTypeStage<CharSelect>()->PlaySE(L"����_�F�X01.wav", 0.5f);

			//�Q�[���X�e�[�W�Ŏg�����ōĐ���������
			//GetTypeStage<GameStage>()->PlaySE(L"����_�F�X01.wav", 0.5f);

			//���U���g�Ŏg�����ōĐ���������
			//GetTypeStage<ResultStage>()->PlaySE(L"����_�F�X01.wav", 0.5f);


		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (KeyState.m_bUpKeyTbl[VK_LBUTTON] || KeyState.m_bPressedKeyTbl[VK_SPACE] || KeyState.m_bPushKeyTbl['W'] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)) {
			StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}


		//�}�E�X�E,B�{�^�����������Ƃ�����������o��,������x�����{�^������������charSelect�Ɉړ�
		if (KeyState.m_bUpKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			if (m_Update) {
				StopBGM();
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
			}
			CreateOperationUI();
			m_Update = true;
		}
	}

	int TitleStage::RandGenerator() {
		//srand((unsigned int)time(NULL));
		m_Rand = rand() % 4;
		return m_Rand;
	}
}