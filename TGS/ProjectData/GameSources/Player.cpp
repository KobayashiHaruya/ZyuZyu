/*!
@file Player.cpp
@brief プレイヤーなど実体
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

		auto string = GetComponent<StringSprite>();
		string->SetText(str);
	}


	void ResultScore::ReadScore() {
		wstring key;
		App::GetApp()->GetDataDirectory(key);

		unique_ptr<XmlDocReader> m_XmlDocReader;
		m_XmlDocReader.reset(new XmlDocReader(key + L"XML/" + L"ResultScore.xml"));

		wstring table = L"ScoreTable/Char";


		//for (int i = 0; i < 8; i++) {
			//CharacterStatus_s m_myData;

			//wstring id = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/ID";
			//wstring type = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Type";
			//wstring kill = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Kill";
			//wstring death = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Death";
			//wstring score = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Score";
			//wstring player = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/Player";
			//wstring list = L"ScoreTable/Char" + Util::IntToWStr(i) + L"/List";

			//switch (std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(id.c_str()))))
			//{
			//case 0:
			//	m_myData.type = CharacterType::POTATO;
			//	break;
			//case 1:
			//	m_myData.type = CharacterType::SHRIMP;
			//	break;
			//case 2:
			//	m_myData.type = CharacterType::CHICKEN;
			//	break;
			//case 3:
			//	m_myData.type = CharacterType::DOUGHNUT;
			//	break;
			//default:
			//	m_myData.type = CharacterType::SHRIMP;
			//	break;
			//}

			//m_myData.unique = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(type.c_str())));
			//m_myData.kill = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(kill.c_str())));
			//m_myData.death = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(death.c_str())));
			//m_myData.score = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(score.c_str())));
			//m_myData.isPlayer = std::stoi(XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(player.c_str())));
			//list = XmlDocReader::GetText(m_XmlDocReader->GetSelectSingleNode(list.c_str()));


			//vector<wstring> LineVec;
			//Util::WStrToTokenVector(LineVec, list, L'\\');

			//int count = 0;
			//vector<int> m_list;
			//int m_kills;
			//for (size_t i = 0; i < LineVec.size(); i++) {
			//	vector<wstring> Tokens;
			//	Util::WStrToTokenVector(Tokens, LineVec[i], L'\\');
				//for (size_t j = 0; j < Tokens.size(); j++)
				//{
				//	if (Tokens[j] != L",") {
				//		m_kills.killState = std::stoi(Tokens[j]);
				//		m_list.push_back(m_kills);
				//		count++;
				//	}
				//}

				//m_charState.push_back(m_myData);
				//m_KillList.push_back(m_list[0]);
			//}

		//}
	}


	////XML読み込み
	//void MapCreator::ReadXML() {
	//	wstring DataDir;
	//	auto stageKey = App::GetApp()->GetScene<Scene>()->GetStageKey();
	//	wstring stageNode = L"MapData/" + stageKey;

	//	App::GetApp()->GetDataDirectory(DataDir);
	//	m_XmlDocReader.reset(new XmlDocReader(DataDir + L"XML/" + L"MapData.xml"));

	//	auto mapNode = m_XmlDocReader->GetSelectSingleNode(stageNode.c_str());
	//	wstring SetMapStr = XmlDocReader::GetText(mapNode);

	//	vector<wstring> LineVec;
	//	Util::WStrToTokenVector(LineVec, SetMapStr, L'\\');
	//	m_maxMapPos = { 0,0 };

	//	int count = 0;
	//	for (size_t i = 0; i < LineVec.size(); i++) {
	//		vector<wstring> Tokens;
	//		Util::WStrToTokenVector(Tokens, LineVec[i], L',');
	//		for (size_t j = 0; j < Tokens.size(); j++)
	//		{
	//			if (Tokens[j] != L"|") {
	//				int num = stoi(Tokens[j]);
	//				m_mapData.push_back(num);
	//				count++;
	//			}
	//			else {
	//				m_maxMapPos[1]++;
	//			}
	//		}
	//	}
	//	m_maxMapPos[0] = count / m_maxMapPos[1];
	//}

	////マップをもとに生成
	//void MapCreator::CreateObject() {
	//	for (int i = 0; i < m_positionData.size(); i++) {
	//		m_objectState.Position = m_positionData[i];
	//		m_objectState.WaterPosition = Vec3(m_positionData[i].x, m_waterHeight, m_positionData[i].z);

	//		switch (m_mapData[i])
	//		{
	//		case on_Wall:
	//			ChooseWall(i);
	//			break;

	//		case on_House:
	//			GetStage()->AddGameObject<House>(
	//				m_objectState.Scale,
	//				m_objectState.Roteton,
	//				m_positionData[i],
	//				m_objectState.ModelScale,
	//				m_objectState.ModelPosition);
	//			AddMaxBreakObjectCount();
	//			break;

	//		case on_BuildingS:
	//			m_builPos = Vec3(m_positionData[i].x, m_builPos.y, m_positionData[i].z);
	//			GetStage()->AddGameObject<Building>(
	//				m_objectState.Scale,
	//				m_objectState.Roteton,
	//				m_builPos,
	//				m_objectState.ModelScale,
	//				m_builModelPos,
	//				100.0f);
	//			AddMaxBreakObjectCount();
	//			break;

	//		case on_GasTank:
	//			GetStage()->AddGameObject<GasTank>(
	//				m_objectState.Scale,
	//				m_objectState.Roteton,
	//				m_positionData[i],
	//				m_objectState.ModelScale,
	//				m_objectState.ModelPosition);
	//			AddMaxBreakObjectCount();
	//			break;

	//		case on_Slop:
	//			GetStage()->AddGameObject<Slop>(
	//				m_objectState.Scale,
	//				m_objectState.Roteton,
	//				Vec3(m_positionData[i].x, m_positionData[i].y - m_slopOfset, m_positionData[i].z),
	//				m_objectState.ModelScale,
	//				m_builModelPos);
	//			break;

	//		case on_Bridge:
	//			GetStage()->AddGameObject<Bridge>(
	//				m_objectState.Scale,
	//				Vec3(0.0f, 0.0f, 1.55f),
	//				m_positionData[i],
	//				m_objectState.ModelScale,
	//				m_builModelPos);
	//			break;

	//		case on_Block:
	//			GetStage()->AddGameObject<Block>(
	//				Vec3(m_cellSize),
	//				m_objectState.Roteton,
	//				m_objectState.Position
	//				);
	//			break;

	//		case on_WallCornerRightUp:
	//			GetStage()->AddGameObject<Wall_Corner>(
	//				m_wallScale,
	//				m_wallRotetonVec[0],
	//				m_objectState.Position,
	//				m_objectState.ModelScale,
	//				m_objectState.ModelPosition
	//				);
	//			break;

	//		case on_WallCornerLeftUp:
	//			GetStage()->AddGameObject<Wall_Corner>(
	//				m_wallScale,
	//				m_wallRotetonVec[1],
	//				m_objectState.Position,
	//				m_objectState.ModelScale,
	//				m_objectState.ModelPosition
	//				);
	//			break;

	//		case on_WallCornerRightDown:
	//			GetStage()->AddGameObject<Wall_Corner>(
	//				m_wallScale,
	//				m_wallRotetonVec[2],
	//				m_objectState.Position,
	//				m_objectState.ModelScale,
	//				m_objectState.ModelPosition
	//				);
	//			break;

	//		case on_WallCornerLeftDown:
	//			GetStage()->AddGameObject<Wall_Corner>(
	//				m_wallScale,
	//				m_wallRotetonVec[3],
	//				m_objectState.Position,
	//				m_objectState.ModelScale,
	//				m_objectState.ModelPosition
	//				);
	//			break;

	//		case on_Water:
	//			GetStage()->AddGameObject<Water>(
	//				Vec3(m_cellSize, 0.5f, m_cellSize),
	//				m_objectState.Roteton,
	//				m_objectState.WaterPosition
	//				);
	//			break;

	//		case on_Restriction:
	//			GetStage()->AddGameObject<Restriction>(
	//				Vec3(m_cellSize),
	//				m_objectState.Roteton,
	//				m_objectState.Position
	//				);
	//			break;

	//		case on_FreeHouse:

	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void MapCreator::CreateTile(int itr) {

	//	for (int i = 0; i < m_positionData.size(); i++) {
	//		m_objectTile = {
	//			nullptr,

	//			nullptr,

	//			GetStage()->AddGameObject<House>(
	//				m_objectState.Scale,m_objectState.Roteton,m_positionData[i],
	//				m_objectState.ModelScale,m_objectState.ModelPosition),

	//			GetStage()->AddGameObject<Building>(
	//				m_objectState.Scale,m_objectState.Roteton,m_builPos,
	//				m_objectState.ModelScale,m_builModelPos,
	//				100.0f),

	//			nullptr,

	//			nullptr,

	//			GetStage()->AddGameObject<GasTank>(
	//				m_objectState.Scale,m_objectState.Roteton,m_positionData[i],
	//				m_objectState.ModelScale,m_objectState.ModelPosition),

	//			GetStage()->AddGameObject<Slop>(
	//				m_objectState.Scale,Vec3(-0.8f, 0.0f, 0.0f),
	//				Vec3(m_positionData[i].x, m_positionData[i].y - m_slopOfset, m_positionData[i].z),
	//				m_objectState.ModelScale,m_builModelPos),

	//			GetStage()->AddGameObject<Bridge>(
	//				m_objectState.Scale,Vec3(0.0f,0.0f,1.55f),m_positionData[i],
	//				m_objectState.ModelScale,m_builModelPos)
	//		};

	//		//m_objectTile[i];
	//	}
	//}

	//void MapCreator::ChooseWall(int num) {
	//	int itrUp = num - m_maxMapPos[0];
	//	int itrRight = num + 1;
	//	int itrLeft = num - 1;

	//	bool wall = m_mapData[itrUp] == on_Wall;
	//	bool wallCorner_Up =
	//		m_mapData[itrUp] == on_WallCornerRightUp ||
	//		m_mapData[itrUp] == on_WallCornerRightDown ||
	//		m_mapData[itrUp] == on_WallCornerLeftUp ||
	//		m_mapData[itrUp] == on_WallCornerLeftDown;

	//	bool wallCorner_Right =
	//		m_mapData[itrRight] == on_WallCornerRightUp ||
	//		m_mapData[itrRight] == on_WallCornerRightDown ||
	//		m_mapData[itrRight] == on_WallCornerLeftUp ||
	//		m_mapData[itrRight] == on_WallCornerLeftDown;

	//	bool wallCorner_Left =
	//		m_mapData[itrLeft] == on_WallCornerRightUp ||
	//		m_mapData[itrLeft] == on_WallCornerRightDown ||
	//		m_mapData[itrLeft] == on_WallCornerLeftUp ||
	//		m_mapData[itrLeft] == on_WallCornerLeftDown;

	//	if (itrUp < 0) {
	//		CreateWall(w_Up);
	//	}
	//	else if (m_mapData[itrUp] == on_Wall || wallCorner_Up) {
	//		if (itrRight < m_mapData.size()) {
	//			if (m_mapData[itrRight] == on_Wall || wallCorner_Right) {
	//				CreateWall(w_Right);
	//			}
	//		}
	//		if (itrLeft > 0) {
	//			if (m_mapData[itrLeft] == on_Wall || wallCorner_Left) {
	//				CreateWall(w_Left);
	//			}
	//		}
	//	}
	//	else {
	//		CreateWall(w_Down);
	//	}
	//}

	//void MapCreator::CreateWall(int num) {
	//	GetStage()->AddGameObject<Wall>(
	//		m_wallScale,
	//		m_wallRotetonVec[num],
	//		m_objectState.Position,
	//		m_objectState.ModelScale,
	//		m_objectState.ModelPosition
	//		);
	//}

}
//end basecross

