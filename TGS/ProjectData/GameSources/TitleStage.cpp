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
			Vec2(500.0f, 500.0f),	//vertex
			Vec3(0.0f, 0.0f, 0.0f),	//pos
			Vec3(1.0f, 1.0f, 1.0f),	//scale
			1,	//layer
			Col4(1.0f, 1.0f, 1.0f, 1.0f),	//color
			//タイトル画像
			L"Blue.png"	//file(texture)
			);
	}

	void TitleStage::CreateOperationUI() {
		AddGameObject<Operation_UI>(
			Vec2(500.0f, 500.0f),
			Vec3(100.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			2,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			//操作説明画像
			L"Blue.png"
			);
	}


	void TitleStage::OnCreate() {
		try {
			CreateViewLight();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//マウス左,Aボタンを押したときcharSelectに移動
		if (KeyState.m_bPressedKeyTbl[VK_LBUTTON] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
		}

		//マウス右,Bボタンを押したとき操作説明を出す,もう一度同じボタンを押したらcharSelectに移動
		if (KeyState.m_bPressedKeyTbl[VK_RBUTTON] || (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)) {
			CreateOperationUI();
			if (m_Update) {
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::charSelect);
			}
			m_Update = true;
		}
	}
}