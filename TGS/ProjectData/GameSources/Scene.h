/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	enum GameStageKey {
		copyright,
		title,
		charSelect,
		game,
		result,
		Max
	};


	//------------------------------------------------------------------------------------------------
	//�L�����N�^�[�^�C�v : enum
	//------------------------------------------------------------------------------------------------

	enum CharacterType {
		POTATO = 0,
		SHRIMP = 1,
		CHICKEN = 2,
		DOUGHNUT = 3
	};

	static wstring GetCharacterTypeToString(const CharacterType type) {
		switch (type)
		{
		case CharacterType::POTATO:
			return L"�|�e�g";
		case CharacterType::SHRIMP:
			return L"�G�r";
		case CharacterType::CHICKEN:
			return L"�`�L��";
		case CharacterType::DOUGHNUT:
			return L"�h�[�i�c";
		default:
			return L"";
		}
	}


	//------------------------------------------------------------------------------------------------
	//�L�����N�^�[�X�e�[�^�X : struct
	//------------------------------------------------------------------------------------------------

	typedef struct CharacterStatus {
		CharacterType type;
		unsigned int level;
		unsigned int kill;
		unsigned int death;
		unsigned int score;
		bool isPlayer;
		unsigned int unique;
	} CharacterStatus_s;


	//------------------------------------------------------------------------------------------------
	//�L���ڍ� : struct
	//------------------------------------------------------------------------------------------------

	typedef struct CharacterKillDetails {
		CharacterType type;
		unsigned int level;
	} CharacterKillDetails_s;

	typedef struct CharacterKillList {
		unsigned int killState;
	} CharacterKillList_s;

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
		vector<wstring> m_stageName;

		void CreateResourses();
		void FindFile(wstring dir);

		wstring m_stageKey[GameStageKey::Max];

		GameStageKey m_gameStageKey;

	public:
		Scene() {};
		virtual ~Scene() {};
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void SetGameStage(GameStageKey key) {
			m_gameStageKey = key;
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), m_stageKey[m_gameStageKey]);
		}

	};



}

//end basecross
