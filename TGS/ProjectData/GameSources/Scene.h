/*!
@file Scene.h
@brief シーン
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
	//キャラクタータイプ : enum
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
			return L"ポテト";
		case CharacterType::SHRIMP:
			return L"エビ";
		case CharacterType::CHICKEN:
			return L"チキン";
		case CharacterType::DOUGHNUT:
			return L"ドーナツ";
		default:
			return L"";
		}
	}


	//------------------------------------------------------------------------------------------------
	//キャラクターステータス : struct
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
	//キル詳細 : struct
	//------------------------------------------------------------------------------------------------

	typedef struct CharacterKillDetails {
		CharacterType type;
		unsigned int level;
	} CharacterKillDetails_s;

	typedef struct CharacterKillList {
		unsigned int killState;
	} CharacterKillList_s;

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
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
