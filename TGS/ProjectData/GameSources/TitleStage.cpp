#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
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

	void TitleStage::CreateUI() {
		AddGameObject<Title_UI>(
			Vec2(1920.0f, 1080.0f),	//vertex
			Vec3(0.0f, 0.0f, 0.0f),	//pos
			Vec3(1.0f, 1.0f, 1.0f),	//scale
			1,	//layer
			Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
			//標準のタイトル画像
			L"NewTitle_ver2.png"	//file(texture)
			);

		//switch (RandGenerator()) {
		//case 0:	//エビver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Shrimp_Title	//file(texture)
		//		);
		//	break;

		//case 1:	//チキンver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Chicken_Title	//file(texture)
		//		);
		//	break;

		//case 2:	//ポテトver
		//	AddGameObject<Title_UI>(
		//		Vec2(1920.0f, 1080.0f),	//vertex
		//		Vec3(0.0f, 0.0f, 0.0f),	//pos
		//		Vec3(1.0f, 1.0f, 1.0f),	//scale
		//		1,	//layer
		//		Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
		//		m_Potato_Title	//file(texture)
		//		);
		//	break;

		//case 3:	//ドーナツver
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
		//操作説明画像
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

			//SEを再生
			PlaySE(L"爆発_色々01.wav", 0.5f);
			//BGMを再生
			PlayBGM(L"title_bgm.wav", 0.5f);
			//BGMを止める
			//StopBGM();

			//タイトルで使う物で再生させるやつ
			//GetTypeStage<TitleStage>()->PlaySE(L"爆発_色々01.wav", 0.5f);

			//キャラセレクトで使う物で再生させるやつ
			//GetTypeStage<CharSelect>()->PlaySE(L"爆発_色々01.wav", 0.5f);

			//ゲームステージで使う物で再生させるやつ
			//GetTypeStage<GameStage>()->PlaySE(L"爆発_色々01.wav", 0.5f);

			//リザルトで使う物で再生させるやつ
			//GetTypeStage<ResultStage>()->PlaySE(L"爆発_色々01.wav", 0.5f);


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


		//マウス右,Bボタンを押したとき操作説明を出す,もう一度同じボタンを押したらcharSelectに移動
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