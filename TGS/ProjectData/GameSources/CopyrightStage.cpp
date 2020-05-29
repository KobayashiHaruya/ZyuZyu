#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CopyrightStage::CreateViewLight() {
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

	void CopyrightStage::CreateSplash() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		m_splash = AddGameObject<UI_Copyright_Splash>(mediaDir + L"Texters/CopyrightImagies/splash1024/", Vec3(0.0f, 30.0f, 0.0f), Vec3(30.0f), m_baseLayer + 1);
		m_splash->Play();
	}

	void CopyrightStage::OnCreate() {
		try {
			StopBGM();
			CreateViewLight();
			CreateSplash();
		}
		catch (...) {
			throw;
		}
	}

	void CopyrightStage::OnUpdate() {
		if (m_splash->IsAnimeEnd()) {
			m_count += App::GetApp()->GetElapsedTime();
			if(m_count >= m_titleTime) App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}
	}
}