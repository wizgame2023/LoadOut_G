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
		m_speed(15)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(2.5f,2.5f,2.5f);
		GetComponent<Transform>()->SetPosition(0, 2.0f, 0);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		m_CurrentSt = make_shared<Tracking>(GetThis<Enemy>());

		Mat4x4 spanMat;
		spanMat.affineTransformation
		(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 5.0f, 0.0f)
		);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���
		ptrDraw->SetMeshToTransformMatrix(spanMat);

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

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾

		if (mapManager->SelMapNow(trans->GetPosition())==2)
		{
			GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
		}

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

	float Enemy::GetAngle()
	{
		return  GetComponent<Transform>()->GetRotation().y;
	}
}
//end basecross
