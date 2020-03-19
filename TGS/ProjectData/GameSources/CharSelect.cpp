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

	}

}