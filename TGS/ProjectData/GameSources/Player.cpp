/*!
@file Player.cpp
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«é¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void ResultScore::OnCreate() {
		ReadScore();
		auto string = AddComponent<StringSprite>();
		string->SetText(L"");
		string->SetTextRect(Rect2D<float>(960.0f, 540.0f, 1920.0f, 1080.0f));

		SetDrawLayer(100);

	}

	void ResultScore::OnUpdate() {
		//wstring str(L"");

		//str += test;
		//str += L"\n";

		//auto string = GetComponent<StringSprite>();
		//string->SetText(str);
	}


	void ResultScore::ReadScore() {
		wstring key;
		App::GetApp()->GetDataDirectory(key);

		unique_ptr<XmlDocReader> m_XmlDocReader;
		m_XmlDocReader.reset(new XmlDocReader(key + L"XML/" + L"ResultScore.xml"));

		wstring table = L"ScoreTable/Char";


		for (int i = 0; i < 8; i++) {
			CharacterStatus_s m_myData;
			vector<int> killList;

			wstring id = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/ID";
			wstring type = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Type";
			wstring kill = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Kill";
			wstring death = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Death";
			wstring score = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Score";
			wstring player = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Player";
			wstring list = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/List";

			m_myData.type = (CharacterType)std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(id.c_str())));
			m_myData.unique = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(type.c_str())));
			m_myData.kill = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(kill.c_str())));
			m_myData.death = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(death.c_str())));
			m_myData.score = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(score.c_str())));
			m_myData.isPlayer = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(player.c_str())));

			list = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(list.c_str()));

			//int killState = 0;
			//wstring num = L"";
			//for (int j = 0; j < list.size(); j++) {
			//	if (list[i] == L'|') {
			//		if (num != L"") {
			//			killState = std::stoi(num);
			//			killList.push_back(killState);
			//		}
			//		num = L"";
			//	}
			//	else {
			//		num += list[i];
			//	}
			//}
			//killState = std::stoi(num);
			//killList.push_back(killState);

			m_charState.push_back(m_myData);
			//m_KillList.push_back(killList);

		}
	}

}
//end basecross

