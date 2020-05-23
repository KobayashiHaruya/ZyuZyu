/*!
@file UI.h
@brief UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	����
	//--------------------------------------------------------------------------------------
	class Time01 : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Time = 5.9f;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	NumberOfDigits	����
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		Time01(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~Time01() {}
		void SetTime(float f) {
			m_Time = f;
		}

		//�g�[�^������
		float m_TotalTime = 5.9f;
		float m_Count = 0;

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
	};



//--------------------------------------------------------------------------------------
///	�X�^�[�g�X�C�b�`
//--------------------------------------------------------------------------------------

	class Time_Start : public Sprite {

	public:
		Time_Start(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~Time_Start() {}

		float time_ON = 0;
		//�g�[�^������
		float m_TotalTime;

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		

	};

	//--------------------------------------------------------------------------------------
	///	����
	//--------------------------------------------------------------------------------------
	class EndTime : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Time;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	NumberOfDigits	����
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		EndTime(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~EndTime() {}
		void SetTime(float f) {
			m_Time = f;
		}

		//�g�[�^������
		float m_TotalTime;
		float m_Count = 0;

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
	};

//--------------------------------------------------------------------------------------
///	�G���h�X�C�b�`
//--------------------------------------------------------------------------------------

	class End : public Sprite {

	public:
		End(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~End() {}

		float time_ON = 0;
		//�g�[�^������
		float m_TotalTime;

		//������
		virtual void OnCreate() override;
		virtual void OnUpdate()override;


	};

}
