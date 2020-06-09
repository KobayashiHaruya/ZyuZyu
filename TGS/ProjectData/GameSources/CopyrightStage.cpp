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
		m_splash = AddGameObject<UI_Copyright_Splash>(mediaDir + L"Texters/CopyrightImagies/splash1024/", Vec3(0.0f, 30.0f, 0.0f), Vec3(20.0f), m_baseLayer + 1);
		m_splash->Play();
	}

	void CopyrightStage::CreateBanners() {
		Vec2 vertex(1024.0f, 512.0f);
		Vec3 pos(0.0f);
		Vec3 scale(0.5f);
		Col4 color(1.0f);

		vector<wstring> names({
			L"DovaSyndrome.png",
			L"FreeKoukaondeasobou.png",
			L"KoukaonLab.png",
			L"Maoudamashii.png"
			});

		for (auto name : names) {
			auto banner = AddGameObject<UI_Static_Image>(
				vertex,
				Vec3(0.0f, 30.0f, 0.0f),
				scale,
				m_baseLayer + 1,
				color,
				name
				);
			banner->Hidden(true);
			m_banners.push_back(banner);
		}
	}

	void CopyrightStage::UpdateBanners() {
		m_bannerCount += App::GetApp()->GetElapsedTime();
		if (m_bannerCount >= m_bannerChangeTime) {
			if(m_bannerIndex == m_banners.size()) App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
			if(m_bannerIndex > 0) m_banners[m_bannerIndex - 1]->Hidden(true);
			if(m_bannerIndex <= m_banners.size() - 1) m_banners[m_bannerIndex]->Hidden(false);
			m_bannerIndex++;
			m_bannerCount = 0.0f;
		}
	}

	void CopyrightStage::OnCreate() {
		try {
			StopBGM();
			CreateViewLight();
			CreateSplash();
			CreateBanners();
		}
		catch (...) {
			throw;
		}
	}

	void CopyrightStage::OnUpdate() {
		if (m_splash->IsAnimeEnd()) {
			m_splashCount += App::GetApp()->GetElapsedTime();
			if (m_splashCount >= m_splashTime) {
				m_splash->SetDrawActive(false);
				UpdateBanners();
			}
			//if(m_count >= m_titleTime) App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}
	}
}