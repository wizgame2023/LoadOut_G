/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//�R���X�g���N�^�̐錾�E�f�X�g���N�^
	Enemy::Enemy(shared_ptr<Stage>& StagePtr) :
		Actor(StagePtr),
		m_pos(-95.0f,2.5f,95.0f),
		m_startPos(-95.0f, 2.5f, 95.0f),
		m_scale(5.0f),
		m_playerPos(0,0,0),
		m_speed(10),
		m_angle(0),
		m_startPop(true)//���߂ẴX�|�[�����ǂ���
	{
	}
	Enemy::Enemy(shared_ptr<Stage>& StagePtr,Vec3 pos,bool startPop) :
		Actor(StagePtr),
		m_pos(pos),
		m_startPos(pos),
		m_scale(5.0f),
		m_playerPos(0, 0, 0),
		m_speed(10),
		m_angle(0),
		m_startPop(startPop)//���߂ẴX�|�[�����ǂ���
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(m_scale);
		GetComponent<Transform>()->SetPosition(m_pos);
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		ptrDraw->AddAnimation(L"Default", 6, 10, true, 20.0f);
		ptrDraw->AddAnimation(L"Ran", 6, 20, true, 20.0f);

		m_mapMgr = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");

		//�����z�u�Ȃ�p�g���[����ԍĔz�u�Ȃ�ォ��~���Ă��鉉�o�t��
		if (m_startPop)
		{
			m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());
		}
		if (!m_startPop)
		{
			m_CurrentSt = make_shared<RepopEnemy>(GetThis<Enemy>(),0.0f);
		}

		Mat4x4 spanMat;
		spanMat.affineTransformation
		(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�e��t����
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"Boss_Mesh_Kari");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Enemy");

		m_CurrentSt->OnStart();

		//m_forwardRay = GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 15.0f);
		//m_playerRay= GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 60.0f);

		MoveSwitch(true);//������悤�ɂ���

		//�r���{�[�h�̐���
		m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(),0);
	}

	void Enemy::OnUpdate()
	{
		if (!m_move)//�t���O���I���ɂȂ����瓮����
		{
			return;
		}

		auto trans = GetComponent<Transform>();
		auto app = App::GetApp;
		m_CurrentSt->OnUpdate();//���݂̃X�e�[�g�X�V����
		m_pos = trans->GetPosition();
		//���̃X�e�[�g�p�ϐ��ɉ�������̃X�e�[�g��������ꂽ��
		if(m_NextSt)
		{
			m_CurrentSt->OnExit();// ���݂̃X�e�[�g���Ō�ɍs������
			
			m_CurrentSt.reset();// ���݂̃X�e�[�g�p�̕ϐ�����ɂ���
		
			m_CurrentSt = m_NextSt;// ���݂̃X�e�[�g�Ɏ��̃X�e�[�g����
			
			m_NextSt.reset();// ���̃X�e�[�g�p�̕ϐ�����ɂ���
		
			m_CurrentSt->OnStart();// �؂�ւ�����V�����X�e�[�g�̍ŏ��ɍs������
		}

		//auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾

		//if (mapManager->SelMapNow(trans->GetPosition())==2)
		//{
		//	GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
		//}
		auto rot = GetComponent<Transform>()->GetRotation();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		float playerVec = atan2f((m_pos.x - m_playerPos.x), (m_pos.z - m_playerPos.z)) + XM_PI * 0.5;//���L��(Enemy)�𒆐S��player�̕������v�Z


		auto state = GetNowState();
		//auto castEnemy = dynamic_pointer_cast<Enemy>(manhole);
		if (!dynamic_pointer_cast<Tracking>(state))
		{
			m_billBoard->ChangeTexture(L"search");
			m_speed = 10.0f;
		}
		if (dynamic_pointer_cast<Tracking>(state))
		{
			m_billBoard->ChangeTexture(L"Wow");
			m_speed = 20.0f;
		}

		//float angle = playerVec - m_angle;
		//���E�̍쐬
		//if (angle > m_angle + XM_PI * 0.25 || angle < m_angle-XM_PI*0.25)
		//{
		//	angle = m_angle;
		//}
		//m_forwardRay->SetAngle(m_angle);
		//m_leftRay->SetAngle(m_angle - XM_PI * 0.5f);
		//m_playerRay->SetAngle(angle);
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"\n�G�̉�].x : " << rot.x
		//	<< L"\n�G�̉�].y : " << rot.y
		//	<< L"\n�G�̉�].z : " << rot.z
		//	<< L"\nplayerPos.x : " << m_playerPos.x
		//	<< L"\nplayerPos.z : " << m_playerPos.z
		//	<< L"\n�A���O�� : " << m_angle
		//	<< L"\nplayerRay : " << XMConvertToDegrees(playerVec)
		//	<< L"\nangle : " << XMConvertToDegrees(angle)
		//<< endl;

		//scene->SetDebugString(wss.str());

		//�A�j���[�V�����̍X�V
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto delta = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(delta);

	}
	void Enemy::OnDestroy()
	{
		// �I�u�W�F�N�g���̂��j������鎞�Ɍ��݂Ǝ��̃X�e�[�g�p�̕ϐ�����ɂ���
		m_CurrentSt.reset();
		m_NextSt.reset();
		////SE���� �G�̋��ѐ�
		//auto SEManager = App::GetApp()->GetXAudio2Manager();
		//auto SE = SEManager->Start(L"Scream", 0, 0.9f);
		auto stage = GetStage();
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		//���������������Ă���Ƃ�
		if (this->FindTag(L"Key"))
		{	
			//����Player�ɓn��
			//GetStage()->GetSharedGameObject<Player>(L"Player")->SetKey(true);
			stageManager->SetPlayerKeyFlag(1);
		}
		stageManager->AddUpEnemyCount(1);//�G���P�̑ł������������Ƃ�m�点��

	}

	float Enemy::GetSpeed()
	{
		return m_speed;
	}

	float Enemy::GetAngle()
	{
		return  m_angle;
	}

	void Enemy::SetAngle(float angle)
	{
		m_angle = angle;
	}

	float Enemy::GetDistance(Vec3 a, Vec3 b)
	{ 
		float numX = a.x - b.x;
		float numY = a.y - b.y;
		float numZ = a.z - b.z;

		return  sqrtf(numX * numX + numY * numY + numZ * numZ);
	}

	Vec3 Enemy::GetPlayerPos()
	{
		return m_playerPos;
	}
	Vec3 Enemy::GetStartPos()
	{
		return m_startPos;
	}
	shared_ptr<Ray> Enemy::GetForwardRay()
	{
		return m_forwardRay;
	}

	shared_ptr<Ray> Enemy::GetPlayerRay()
	{
		return m_playerRay;
	}

	shared_ptr<StateBase> Enemy::GetNowState()
	{
		return m_CurrentSt;
	}

	shared_ptr<MapManager> Enemy::GetMapMgr()
	{
		return m_mapMgr;
	}

	void Enemy::GetGameOverScene()
	{
		GetStage()->AddGameObject<MovieGameOver>();
	}


}
//end basecross
