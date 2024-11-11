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
		m_pos(0,2.0f,0),
		m_speed(15)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(2.5f,2.5f,2.5f);
		GetComponent<Transform>()->SetPosition(m_pos);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());

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

		AddTag(L"Enemy");

		m_CurrentSt->OnStart();
	}

	void Enemy::OnUpdate()
	{
		auto trans = GetComponent<Transform>();
		auto app = App::GetApp;
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

		//auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾

		//if (mapManager->SelMapNow(trans->GetPosition())==2)
		//{
		//	GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
		//}
		auto rot = GetComponent<Transform>()->GetRotation();
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		auto playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		float PlayerVec = atan2f((m_pos.x - playerPos.x), (m_pos.z - playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		m_forwardRay = GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 100.0f);
		//m_leftRay = GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 10.0f);
		//m_playerRay= GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 10.0f);
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
