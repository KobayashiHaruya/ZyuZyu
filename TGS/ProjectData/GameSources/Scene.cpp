
/*!
@file Scene.cpp
@brief �V�[������
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

		////���b�V����o�^
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
			// ������FILE_ATTRIBUTE_DIRECTORY�Ȃ�
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// �f�B���N�g�������擾
				wstring ditectoryName = win32fd.cFileName;
				// �V�����t�H���_�̏ꏊ
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// ���̒�������
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//�摜�t�@�C���������ꍇ
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// �t�@�C���̏ꏊ
					wstring texture = dir + fileName;
					// �e�N�X�`���[��o�^
					App::GetApp()->RegisterTexture(fileName, texture);
				}

				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}

				if (exe == L".bmf") {
					// ��O�̓o�^,�{�[�����f��������
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
					// �^���W�F���g�t�����f���̓ǂݍ���
					auto modelMesh = MeshResource::CreateStaticModelMeshWithTangent(dir, fileName);
					App::GetApp()->RegisterResource(fileName, modelMesh);
				}
				if (exe == L".bbmf") {
					// �{�[�����f���̓ǂݍ���

				}

			}
		} while (FindNextFile(hFind, &win32fd));

		// �㏈��
		FindClose(hFind);

	}

	void Scene::OnCreate() {
		try {
			//���\�[�X�쐬
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
