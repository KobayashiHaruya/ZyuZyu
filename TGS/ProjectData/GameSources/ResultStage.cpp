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
		AddGameObject<Result_UI>(
			Vec2(1280.0f, 920.0f),	//vertex
			Vec3(0.0f, 0.0f, 0.0f),	//pos
			Vec3(1.0f, 1.0f, 1.0f),	//scale
			1,	//layer
			Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
			m_Curtain_Image	//file(texture)
			);

		//�X�R�A�g
		AddGameObject<Result_UI>(
			Vec2(500.0f, 100.0f),
			Vec3(0.0f, -200.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			2,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			m_Score_frame_Image
			);

		//�X�R�A
		for (int i = 0; i < 6; i++) {	//���[�v���Ō��ύX
			float n = static_cast<float>(i);
			auto Score = AddGameObject<Score_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(0.0f, -200.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				3,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				m_Score_Image,
				static_cast<int>((powf(10.0f, n))),	//��
				static_cast<int>(12345)	//�\������X�R�A
				);
			auto trans = Score->GetComponent<Transform>();
			trans->SetPosition(500.0f * 0.5f - n * 64.0f - 64.0f, -300.0f * 0.5f, 0.0f);
		}
	}

	void ResultStage::OnCreate() {
		try {
			CreateViewLight();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
	}


}