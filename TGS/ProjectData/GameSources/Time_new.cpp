/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	����
	//--------------------------------------------------------------------------------------
	Time01::Time01(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		GameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void Time01::OnCreate() {
		float helfSize = 0.5f;

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 1 + X), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, -8 + Y), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 1 + X), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, -8 + Y), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//AddTag(L"Time01");
	}

	void Time01::OnUpdate() {

		auto transComp = GetComponent<Transform>();
		//auto scale = transComp->GetScale();
		////������scale - Player_HP
		//scale.x = scale.x;
		//���ߏ���
		SetAlphaActive(true);

		float helfSize = 0.5f;

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, X), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize,  Y), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, X), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize,  Y), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);


		//auto GM = GameManager::getInstance();

		//auto Maxtime2 = GM->GetMaxtime();

		//auto Mintime2 = GM->GetMintime();

		//auto Notime2 = GM->GetNotime();

		//auto time01_2 = GM->Gettime01();

		//auto time02_2 = GM->Gettime02();

		//auto time03_2 = GM->Gettime03();

		//auto time01 = time01_2;

		//auto time02 = time02_2;

		//auto time03 = time03_2;

		//auto Maxtime = Maxtime2;

		//auto Mintime = Mintime2;



		if (time01 == Maxtime)
		{
			time02 += Mintime;
			time01 -= Maxtime;
		}

		if (time02 == Maxtime)
		{
			time03 += Mintime;
			time02 -= Maxtime;
		}

		if (time03 == Maxtime)
		{
			time03 -= Maxtime;
		}

		if (time03 == 0)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 1)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 2)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 3)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 4)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 5)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 6)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0_9.png");
		}

		if (time03 == 7)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"2.png");
		}

		if (time03 == 8)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"1.png");
		}

		if (time03 == 9)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0.png");
		}

		time01 += Mintime;
	}

	//--------------------------------------------------------------------------------------
	///	����
	//--------------------------------------------------------------------------------------
	Time10::Time10(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		GameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void Time10::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}

	void Time10::OnUpdate() {

		auto transComp = GetComponent<Transform>();
		auto scale = transComp->GetScale();
		//������scale - Player_HP
		scale.x = scale.x;
		//���ߏ���
		SetAlphaActive(true);

		float helfSize = 1.0f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);


		if (time01 == -Maxtime)
		{
			time02 -= Mintime;
			time01 += Maxtime;
		}

		if (time02 == -Maxtime)
		{
			time03 -= Mintime;
			time02 += Maxtime;
		}

		if (time03 == -Maxtime)
		{
			time04 -= Mintime;
			time03 += Maxtime;
		}

		if (time04 == -6)
		{
			time04 += 6;
		}

		if (time04 == 0)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"5.png");
		}

		if (time04 == -1)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"4.png");
		}

		if (time04 == -2)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"3.png");
		}

		if (time04 == -3)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"2.png");
		}

		if (time04 == -4)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"1.png");
		}

		if (time04 == -5)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0.png");
		}

		if (time04 == -6)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0.png");
		}

		time01 -= Mintime;

	}

	//--------------------------------------------------------------------------------------
	///	����
	//--------------------------------------------------------------------------------------
	Time100::Time100(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		GameObject(stagePtr),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void Time100::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}

	void Time100::OnUpdate() {

		auto transComp = GetComponent<Transform>();
		auto scale = transComp->GetScale();
		//������scale - Player_HP
		scale.x = scale.x;
		//���ߏ���
		SetAlphaActive(true);

		float helfSize = 1.0f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);


		if (time01 == Maxtime)
		{
			time02 += Mintime;
			time01 -= Maxtime;
		}

		if (time02 == Maxtime)
		{
			time03 += Mintime;
			time02 -= Maxtime;
		}

		if (time03 == Maxtime)
		{
			time04 += Mintime;
			time03 -= Maxtime;
		}

		if (time04 == 6)
		{
			time05 += 1;
			time04 -= 6;

		}

		if (time05 == 3)
		{

		}

		if (time05 == 0)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"2.png");
		}

		if (time05 == 1)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"1.png");
		}

		if (time05 == 2)
		{
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(L"0.png");
		}

		time01 += Mintime;
	}

}