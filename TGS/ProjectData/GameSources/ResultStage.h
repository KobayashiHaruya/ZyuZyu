#pragma once
#include "stdafx.h"

namespace basecross {

	class ResultStage : public Stage {
		int m_layer;
		float m_PosY;
		float m_Move;
		float m_Second;
		float m_Second2;
		float m_randpos;
		int m_Value;
		bool m_Onoff;

		Vec3 m_position = Vec3(0.0f, 5.0f, 5.0f);
		int m_Score;
		int m_TrueScore;

		CharacterType m_type;
		int m_level;

		int m_state;

		wstring m_Stage_Image;
		wstring m_Score_Image;
		wstring m_Score_frame_Image;

		shared_ptr<Result_Curtain> m_Cartain;
		shared_ptr<SoundItem> m_bgm;

		shared_ptr<Result_Icon_UI> m_ResultIcon;

		shared_ptr<UI_Curtain> m_curtain;
		shared_ptr<UI_Result_Three> m_resultThree;
		shared_ptr<UI_Result_Two> m_resultTwo;

		shared_ptr<Score_UI> m_Score_UI[5];
		//shared_ptr<Object> m_Object;

		//エフェクトの再生
		shared_ptr<EfkEffect> m_efkEffect;
		shared_ptr<EfkPlay> m_efkPlay;

		//Score
		vector<CharacterStatus_s> m_charState;
		vector<vector<int>> m_KillList;

		wstring m_resultFont;

		shared_ptr<UI_Static_Image> m_scoreTableBack;
		shared_ptr<UI_Score_Table> m_scoreTable;
		bool m_isScoreTableShow;

		void CreateSplash();

		void CreateScoreTable();
		void ShowScoreTable(const bool e);

		float m_effectWaitTimaer;
		void UpdateEffectWaitTimert();

		shared_ptr<EfkEffect> m_starEffect;
		shared_ptr<EfkPlay> m_starEffectPlay;
		void PlayStarEffect();
		shared_ptr<EfkEffect> m_crackerEffect;
		shared_ptr<EfkPlay> m_crackerEffectPlay;
		void PlayCrackerEffect();

	public:
		//エフェクトの生成
		shared_ptr<EfkInterface> m_efkInterface;
		shared_ptr<EfkEffect> m_effect;

		ResultStage() :Stage(),
			m_layer(5),
			m_Score_Image(L"Number_695_Gold.png"),
			m_Stage_Image(L"ScoreBoard_Sample.png"),
			m_Cartain(NULL),
			m_Onoff(true),
			m_PosY(1500.0f),
			m_Value(1),
			m_Second(0.0f),
			m_Second2(0.0f),
			m_Move(500.0f),
			m_Score(000000),
			m_TrueScore(0),
			m_type(SHRIMP),
			m_level(0),
			m_curtain(NULL),
			m_resultThree(NULL),
			m_resultTwo(NULL),
			m_state(NULL),
			m_scoreTableBack(NULL),
			m_scoreTable(NULL),
			m_isScoreTableShow(NULL),
			m_resultFont(L"ResultFont.png"),
			m_effectWaitTimaer(NULL),
			m_starEffect(NULL),
			m_starEffectPlay(NULL),
			m_crackerEffect(NULL),
			m_crackerEffectPlay(NULL)
		{}
		virtual ~ResultStage() {}

		void CreateViewLight();
		void CreateUI();
		void CreateIcon(CharacterType type);
		void ScoreMove();
		void CreateWall();
		void ReadScore();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2() override;
		virtual void OnDraw() override;

		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		void StopBGM() {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Stop(m_bgm);
		}

		int GetScore() const {
			return m_Score;
		}

		void SetScore(int value) {
			m_Score = value;
		}

		shared_ptr<EfkEffect> GetEffect(wstring name) {
			wstring dir;
			App::GetApp()->GetDataDirectory(dir);
			wstring effectStr = dir + L"Effect\\";
			m_effect = ObjectFactory::Create<EfkEffect>(m_efkInterface, (effectStr + name));

			return m_effect;

		}

	};

}