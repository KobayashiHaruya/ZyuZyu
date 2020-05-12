/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

#include "MyUI.h"
#include "Character.h"
#include "AIchan.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<UI_The_World> m_pause;
		shared_ptr<Player> m_player;
		shared_ptr<AIchan> m_enemy;
		shared_ptr<PinP> m_pinp;

		//ビューの作成
		void CreateViewLight();
		void CreateUI();

		void ShowPause();

		void CreateTime();

		void CreatePinP();

		float m_weaponTime;
		void WeaponUpdate();

		//トータル時間
		float m_TotalTime;

		//bool gather = false;
		void CreateAIchan();

	public:

		//構築と破棄
		GameStage() :
			Stage(),
			m_pause(NULL),
			m_player(NULL),
			m_enemy(NULL),
			m_pinp(NULL)
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

