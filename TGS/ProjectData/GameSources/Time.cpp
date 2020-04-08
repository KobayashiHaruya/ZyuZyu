/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///����
	//--------------------------------------------------------------------------------------

	Time::Time(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void Time::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		// �s�{�b�g���E�[�ɂ���
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"Light_on.png");


		AddTag(L"UI_Time");



		SetDrawLayer(11);
		SetAlphaActive(true);

		//�X�v���C�g�̌���		
		ptrDraw->SetDiffuse(Col4(1, 1, 1, 11.1f));
	}


	void Time::OnUpdate() {

		// �h���[�R���|�[�l���g���擾
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		//// Spotlight.cpp�̂������Ă���
		//auto on = GetStage()->GetSharedGameObject<Spotlight>(L"Spotlight")->GetOn();
		//if (on) {
		//	// ���C�g�����Ă�����ON.jpg�ɒ���ւ���
		//	ptrDraw->SetTextureResource(L"Light_on.png");
		//}
		//else {
		//	// ���̑���OFF.jpg�ɒ���ւ���
		//	ptrDraw->SetTextureResource(L"Light_off.png");
		//}


	}

}