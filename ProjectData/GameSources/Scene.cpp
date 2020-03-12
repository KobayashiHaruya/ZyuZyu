
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Scene::CreateResourses() {
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		FindFile(mediaDir + L"Sound/SE/");
		FindFile(mediaDir + L"Sound/BGM/");
		FindFile(mediaDir + L"Texters/");
		FindFile(mediaDir + L"Model/");

	}

	void Scene::FindMediaDirectoryFile(wstring dir) {
		//wstring folderDir = dir + L"Wall/";

		////メッシュを登録
		//auto wallMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_wall.bmf");
		//App::GetApp()->RegisterResource(L"m_wall.bmf", wallMesh);

		//folderDir = dir + L"Rock/";
		//auto rockMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_rock.bmf");
		//App::GetApp()->RegisterResource(L"m_rock.bmf", rockMesh);

		//folderDir = dir + L"GasTank/";
		//auto gasTankMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_GasTank.bmf");
		//App::GetApp()->RegisterResource(L"m_GasTank.bmf", gasTankMesh);

		//folderDir = dir + L"Buil_S/";
		//auto buil_sMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_Buil_s.bmf");
		//App::GetApp()->RegisterResource(L"m_Buil_s.bmf", buil_sMesh);

		//folderDir = dir + L"Buil_M/";
		//auto buil_mMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_buil.bmf");
		//App::GetApp()->RegisterResource(L"m_buil.bmf", buil_mMesh);

		//folderDir = dir + L"House/";
		//auto houseMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_House.bmf");
		//App::GetApp()->RegisterResource(L"m_House.bmf", houseMesh);

		//folderDir = dir + L"Wall_Corner/";
		//auto wall_cornerMesh = MeshResource::CreateStaticModelMesh(folderDir, L"m_wall_corner.bmf");
		//App::GetApp()->RegisterResource(L"m_wall_corner.bmf", wall_cornerMesh);


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
					if (!(fileName == L"Chara_R.bmf")) {
						auto modelMesh = MeshResource::CreateStaticModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
					else
					{
						auto modelMesh = MeshResource::CreateBoneModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
				}
				if (exe == L".tbmf") {
					// タンジェント付きモデルの読み込み
					auto modelMesh = MeshResource::CreateStaticModelMeshWithTangent(dir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".bbmf") {
					// ボーンモデルの読み込み

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
			SetGameStage(GameStageKey::result);
		}
		catch (...) {
			throw;
		}
	}


	void Scene::OnEvent(const shared_ptr<Event>& event) {

		switch (m_gameStageKey)
		{
		//case GameStageKey::copyright:
		//	ResetActiveStage<CopywriterStage>();
		//	break;
		case GameStageKey::title:
			ResetActiveStage<TitleStage>();
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
