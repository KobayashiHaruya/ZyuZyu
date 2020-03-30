
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
		FindFile(mediaDir + L"Texters/");
		//FindFile(mediaDir + L"Sound/SE/");
		//FindFile(mediaDir + L"Sound/BGM/");
		//FindFile(mediaDir + L"Model/");

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
<<<<<<< HEAD
			SetGameStage(GameStageKey::charSelect);
			SetGameStage(GameStageKey::title);
=======
			SetGameStage(GameStageKey::game);
>>>>>>> Kobayashi
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
