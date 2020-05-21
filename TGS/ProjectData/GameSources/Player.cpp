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
		wstring str(L"");

		str += test;
		str += L"\n";

		//str += Util::FloatToWStr(t);
		//str += L"\n";


		auto string = GetComponent<StringSprite>();
		string->SetText(str);
	}

	void ResultScore::ReadScore() {
		wstring key;
		App::GetApp()->GetDataDirectory(key);

		unique_ptr<XmlDocReader> m_XmlDocReader;
		m_XmlDocReader.reset(new XmlDocReader(key + L"XML/" + L"ResultScore.xml"));

		wstring table = L"ScoreTable/Char";


		for (int i = 0; i < 8; i++) {
			CharacterStatus_s m_myData;

			wstring id = Util::IntToWStr(i);
			wstring data = L"/Type";
			wstring a = table + id + data;
			a = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(a.c_str()));

			switch (std::stoi(a))
			{
			case 0:
				m_myData.type = CharacterType::POTATO;
				break;
			case 1:
				m_myData.type = CharacterType::SHRIMP;
				break;
			case 2:
				m_myData.type = CharacterType::CHICKEN;
				break;
			case 3:
				m_myData.type = CharacterType::DOUGHNUT;
				break;
			default:
				m_myData.type = CharacterType::SHRIMP;
				break;
			}

			data = L"/ID";
			a = table + id + data;
			a = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(a.c_str()));

			m_myData.unique = std::stoi(a);

			data = L"/Kill";
			a = table + id + data;
			a = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(a.c_str()));

			m_myData.kill = std::stoi(a);

			data = L"/Death";
			a = table + id + data;
			a = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(a.c_str()));

			m_myData.death = std::stoi(a);

			data = L"/Score";
			a = table + id + data;
			a = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(a.c_str()));

			m_myData.score = std::stoi(a);

			data = L"/Player";
			a = table + id + data;
			a = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(a.c_str()));

			m_myData.isPlayer = std::stoi(a);

			//vector<IXMLDOMNodePtr> GameDataNode = {
			//	key->GetSelectSingleNode(id.c_str()),
			//	key->GetSelectSingleNode(type.c_str()),
			//	key->GetSelectSingleNode(kill.c_str()),
			//	key->GetSelectSingleNode(death.c_str()),
			//	key->GetSelectSingleNode(score.c_str()),
			//	key->GetSelectSingleNode(player.c_str())
			//};

			//GameDataNode[0];

			m_charState.push_back(m_myData);
		}

	}

}
//end basecross

