#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ResultStage::CreateViewLight() {
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


	void ResultStage::CreateUI() {
		//スコア枠
		//AddGameObject<Result_UI>(
		//	Vec2(500.0f, 100.0f),
		//	Vec3(0.0f, -200.0f, 0.0f),
		//	Vec3(1.0f, 1.0f, 1.0f),
		//	2,
		//	Col4(1.0f, 1.0f, 1.0f, 1.0f),
		//	m_Score_frame_Image
		//	);

		//スコア
		for (int i = 0; i < 6; i++) {	//ループ数で桁変更
			float n = static_cast<float>(i);
			int score = 0;
			auto Score = AddGameObject<Score_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(0.0f, -200.0f, 0.0f),
				Vec3(1.0f, 1.0f, 1.0f),
				3,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				m_Score_Image,
				static_cast<int>((powf(10.0f, n))),
				static_cast<int>(123456)	//表示するスコア
				);
			auto trans = Score->GetComponent<Transform>();
			trans->SetPosition(300.0f * 0.5f - n * 64.0f - 64.0f, -500.0f * 0.5f, 0.0f);
		}


		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		m_Cartain = AddGameObject<Result_Curtain>(mediaDir + L"Texters/ResultImagis/ResultAnimation/SpriteStadio/", Vec3(0.0f, 0.0f, 0.0f), Vec3(32.0f), m_layer);
	}

	void ResultStage::CreateIcon(CharacterType type, int level) {
		m_ResultIcon = AddGameObject<Result_Icon_UI>(
			Vec3(0.0f, 500.0f, 0.0f),
			Vec3(0.3f, 0.3f, 0.3f),
			0,
			type,
			level
			);

	}

	void ResultStage::OnCreate() {
		try {
			CreateViewLight();
			//SetPhysicsActive(true);
			CreateUI();
			CreateIcon(m_type, m_level);
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto Trans = m_ResultIcon->GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		if (Pos.y > -10.0f) {
			Trans->SetPosition(0.0f, m_Move, 0.0f);
			m_Move -= 10.0f;
		}
	}



}