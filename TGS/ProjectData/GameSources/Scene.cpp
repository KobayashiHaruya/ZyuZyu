
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{



	void Scene::CreateResourses() {

		wstring dataDir;
		//mediaディレクトリ取得用
		App::GetApp()->GetAssetsDirectory(dataDir);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		FindFile(mediaDir + L"Texters/");
		FindFile(mediaDir + L"Sound/SE/");
		FindFile(mediaDir + L"Sound/BGM/");
		FindFile(mediaDir + L"Model/");
		FindFile(mediaDir + L"Effect/");
	}

	void Scene::FindFile(wstring dir) {
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring newdir = dir + L"*.*";
		const wchar_t *dirExtension = newdir.c_str();

		hFind = FindFirstFile(dirExtension, &win32fd);

		do {
			// 属性がFILE_ATTRIBUTE_DIRECTORYなら
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// ディレクトリ名を取得
				wstring ditectoryName = win32fd.cFileName;
				// 新しいフォルダの場所
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// その中を検索
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//画像ファイルだった場合
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// ファイルの場所
					wstring texture = dir + fileName;
					// テクスチャーを登録
					App::GetApp()->RegisterTexture(fileName, texture);
				}

				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}

				if (exe == L".bmf") {
					// 例外の登録,ボーンモデルだから
					if ((fileName == L"Chara_R.bmf") ||
						(fileName == L"CornGatling_Animation.bmf") ||
						(fileName == L"TomatoCannon_Animation.bmf") ||
						(fileName == L"Shrimp_Animation_ver2.bmf") ||
						(fileName == L"0525_Animation_Shrimp_test4.bmf") ||
						(fileName == L"Chicken_Animation_test9.bmf") ||
						(fileName == L"Animation_Potato_test5.bmf") ||
						(fileName == L"Animation_Doughnut_test3.bmf")) {
						auto modelMesh = MeshResource::CreateBoneModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
					else
					{
						auto modelMesh = MeshResource::CreateStaticModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
				}

			}
		} while (FindNextFile(hFind, &win32fd));

		// 後処理
		FindClose(hFind);

	}

	void Scene::OnCreate() {
		try {
			//リソース作成
			CreateResourses();

			SetGameStage(GameStageKey::copyright);

			//App::GetApp()->GetStepTimer().GetFramesPerSecond();
			//App::GetApp()->
		}
		catch (...) {
			throw;
		}
	}


	void Scene::OnEvent(const shared_ptr<Event>& event) {

		switch (m_gameStageKey)
		{
		case GameStageKey::copyright:
			ResetActiveStage<CopyrightStage>();
			break;
		case GameStageKey::title:
			ResetActiveStage<TitleStage>();
			break;
		case GameStageKey::charSelect:
			ResetActiveStage<CharSelectStage>();
			break;
		case GameStageKey::game:
			ResetActiveStage<GameStage>();
			break;
		case GameStageKey::result:
			ResetActiveStage<ResultStage>();
			break;
		}
	}

}
//end basecross
