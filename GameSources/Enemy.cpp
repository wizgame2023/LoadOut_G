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
		m_scale(3.5f),
		m_playerPos(0,0,0),
		m_speed(10),
		m_angle(0),
		m_startPop(true),//���߂ẴX�|�[�����ǂ���
		m_anger(ANGER_NONE),
		m_ability(normal)//Enemy�̔\�͂̐錾�p
	{
	}
	Enemy::Enemy(shared_ptr<Stage>& StagePtr, Vec3 pos, bool startPop, int ability,int anger) :
		Actor(StagePtr),
		m_pos(pos),
		m_startPos(pos),
		m_scale(3.5f),
		m_playerPos(0, 0, 0),
		m_speed(10),
		m_angle(0),
		m_startPop(startPop),//���߂ẴX�|�[�����ǂ���
		m_ability(ability),//Enemy�̔\�͂̐錾�p
		m_anger(anger)//�ǂꂭ�炢�{���Ă��邩(�X�e�[�^�X���ǂ̈ʏグ�邩)
	{
		//�����{��l�����������Ȃ����l�ɖ߂�
		if (m_anger > ANGER_HI)
		{
			m_anger = ANGER_HI;
		}
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(m_scale);
		GetComponent<Transform>()->SetPosition(m_pos);
		m_ptrDraw = AddComponent<PNTBoneModelDraw>();
		m_ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		m_ptrDraw->AddAnimation(L"Default", 6, 10, true, 20.0f);
		m_ptrDraw->AddAnimation(L"Ran", 6, 20, true, 20.0f);
		m_ptrDraw->AddAnimation(L"All", 0, 100, true, 10.0f);

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

		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���
		ptrColl->SetAfterCollision(AfterCollision::None);

		//�e��t����
		m_ptrShadow = AddComponent<Shadowmap>();
		m_ptrShadow->SetMeshResource(L"Boss_Mesh_Kari");
		m_ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Enemy");

		m_CurrentSt->OnStart();

		//m_forwardRay = GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 15.0f);
		//m_playerRay= GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 60.0f);

		MoveSwitch(true);//������悤�ɂ���

		//�r���{�[�h�̐���
		m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(),L"Clear",2,13.0f);

		//�{��l���P�ȏォ���킩��₷�����邽�߂̃G�t�F�N�g
		switch (m_anger)
		{
		case ANGER_LOW:
			GetStage()->AddGameObject<TrackingPillarEfect>(GetThis<Actor>(), Vec3(0.0f, 0.0f, 0.0f), L"AngerEffectLow", Vec2(0.0f, +1.0f));
			break;
		case ANGER_MIDDLE:
			GetStage()->AddGameObject<TrackingPillarEfect>(GetThis<Actor>(), Vec3(0.0f, 0.0f, 0.0f), L"AngerEffectMiddle", Vec2(0.0f, +1.0f));
			break;
		case ANGER_HI:
			GetStage()->AddGameObject<TrackingPillarEfect>(GetThis<Actor>(), Vec3(0.0f, 0.0f, 0.0f), L"AngerEffectHi", Vec2(0.0f, +1.0f));
			break;
		default:
			break;
		}

	}

	void Enemy::OnUpdate()
	{
		if (!m_move)//�t���O���I���ɂȂ����瓮����
		{
			return;
		}

		Actor::OnUpdate();//�e�N���X�̃A�b�v�f�[�g����

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

		//�r���{�[�g�̌����ڕύX�ǂ̂��炢�{���Ă��邩�ŕύX����
		switch (m_anger)
		{
		case ANGER_NONE://�{���ĂȂ���
			if (!dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"search");
			}
			if (dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"Wow");
			}
			break;
		case ANGER_LOW://�{���Ă��鎞(��)
			if (!dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"search_AngerLow");
			}
			if (dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"Wow_AngerLow");
			}
			break;
		case ANGER_MIDDLE://�{���Ă��鎞(��)
			if (!dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"search_AngerMiddle");
			}
			if (dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"Wow_AngerMiddle");
			}
			break;
		case ANGER_HI://�{���Ă���Ƃ�(��)
			if (!dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"search_AngerHi");
			}
			if (dynamic_pointer_cast<Tracking>(state))
			{
				m_billBoard->ChangeTexture(L"Wow_AngerHi");
			}
			break;
		default:
			break;
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
		//�A�j���[�V�����ύX
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
		
		//���|�b�v�����̗\��
		stageManager->SetRepopEnemyPos(m_startPos);//��̏����ʒu��StageManager�ɓn��
		stageManager->SetRepopEnemyAnger(++m_anger);//�{��l���v���X���ēn��
		stageManager->AddUpEnemyCount(1);//�G���P�̑ł������������Ƃ�m�点��

	}

	float Enemy::GetSpeed()
	{
		return m_speed;
	}

	void Enemy::SetSpeed(float speed)
	{
		m_speed = speed;
	}
	float Enemy::GetAngle()
	{
		return  m_angle;
	}

	int Enemy::GetAbility()
	{
		return m_ability;
	}

	//�{��l��n��
	int Enemy::GetAnger()
	{
		return m_anger;
	}

	//�A�r���e�B��ύX����
	void Enemy::ChangeAbility(int ability)
	{
		//�m�[�}���ɕύX
		if (ability == normal)
		{
			//�����ڂ�ς���
			m_ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		}

		//���b�V����ԂɕύX
		if (ability == rush)
		{
			//�����ڂ�ς���
			m_ptrDraw->SetMeshResource(L"Boss_Mesh_Spec");//���œ����̓G�̃��b�V���ɂ��Ă��܂�
		}
		m_ability = ability;
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
