/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//�R���X�g���N�^�̐錾�E�f�X�g���N�^
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_speed(10)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(10,10,10);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());

		Mat4x4 spanMat;
		spanMat.affineTransformation
		(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		m_CurrentSt->OnStart();
	}

	void Enemy::OnUpdate()
	{
		auto trans = GetComponent<Transform>();

		m_CurrentSt->OnUpdate();//���݂̃X�e�[�g�X�V����

		//���̃X�e�[�g�p�ϐ��ɉ�������̃X�e�[�g��������ꂽ��
		if(m_NextSt)
		{
			m_CurrentSt->OnExit();// ���݂̃X�e�[�g���Ō�ɍs������
			
			m_CurrentSt.reset();// ���݂̃X�e�[�g�p�̕ϐ�����ɂ���
		
			m_CurrentSt = m_NextSt;// ���݂̃X�e�[�g�Ɏ��̃X�e�[�g����
			
			m_NextSt.reset();// ���̃X�e�[�g�p�̕ϐ�����ɂ���
		
			m_CurrentSt->OnExit();// �؂�ւ�����V�����X�e�[�g�̍ŏ��ɍs������
		}

		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//	wss << L"transform : "
		//	<< L"\n"
		//	<< L"postion : ("
		//	<< L"\nx."
		//	<< trans->GetPosition().x
		//	<< L","
		//	<< "\ny."
		//	<< trans->GetPosition().y
		//	<< L","
		//	<< "\nz."
		//	<< trans->GetPosition().z
		//	<< L")"
		//	<< L"\nRot:"
		//	<< L"\nx." << trans->GetRotation().x
		//	<< L"\ny." << XMConvertToDegrees(trans->GetRotation().y)
		//	<< L"\nz." << XMConvertToDegrees(trans->GetRotation().z)
		//	<< endl;
		//scene->SetDebugString(wss.str());
	}
	void Enemy::OnDestroy()
	{
		// �I�u�W�F�N�g���̂��j������鎞�Ɍ��݂Ǝ��̃X�e�[�g�p�̕ϐ�����ɂ���
		m_CurrentSt.reset();
		m_NextSt.reset();

	}

	float Enemy::GetSpeed()
	{
		return m_speed;
	}
}
//end basecross
