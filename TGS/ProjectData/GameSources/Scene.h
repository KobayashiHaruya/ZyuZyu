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
		game,
		result,
		Max
	};

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
