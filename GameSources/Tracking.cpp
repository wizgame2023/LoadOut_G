/*!
@file Tracking.cpp
@brief �ǐ�
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�ǐՃX�e�[�g�̍ŏ��̏���
	void Tracking::OnStart()
	{
		auto app = App::GetApp;
		float delta = App::GetApp()->GetElapsedTime();
		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)�̃|�W�V�������擾

		m_anger = m_Owner->GetAnger();//�{��l���擾
		//�{��l�ɂ���ăg���b�L���O���̃X�s�[�h��ύX����
		AngerSpeed(m_anger);

		AStarMove();//A�X�^�[����

		//m_targetPos = m_tagetRootPos[m_roodCount];//���݂̖ړI�n

		//�ړ�����
		m_directionRad = math.GetAngle(m_ownerPos, m_tagetRootPos[m_roodCount]);

		m_ownerRot.y = m_directionRad;

		m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//player�Ɍ������Ĉړ�
		m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		
		//�ړ��X�V
		m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);
	}

	//�ǐՃX�e�[�g�̍X�V����
	void Tracking::OnUpdate()
	{	
		//player��ǂ������鏈��
		auto app = App::GetApp;
		float delta = App::GetApp()->GetElapsedTime();
		m_delta = App::GetApp()->GetElapsedTime();

		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)�̃|�W�V�������擾
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		m_playerRay = m_Owner->GetPlayerRay();
		//float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		//m_ownerRot.y = rad;//player�̕����Ɍ���

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		//Player�̈ʒu��AStar�̍��W�ɂ���
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//���[���h���W����Z�����W�ɂ��Ă���
		auto playerAStarPos = mapManager->ConvertUnityMap(playerSelPos);//A*�̍��W�ɕς���
		//A*�̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//m_aStar = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<AStar>(L"AStar");//AStar�����擾
		//�v���C���[��A*���W�����ς���Ă�����A*������������x���
		bool aStarStart = false;//AStar�̍Čv�Z����������Ă��邩����ϐ�
		if (playerAStarPos != m_beforPlayerUnity)
		{
			aStarStart = true;//AStar�̍Čv�Z������Ă���
			AStarMove();
		}
		//��莞�Ԃ�������A*����������
		m_aStarTime += delta;
		if (m_aStarTime >= 0.3f)
		{
			m_aStarTime = 0.0f;//�^�C�����Z�b�g
			aStarStart = true;//AStar�̍Čv�Z������Ă���
			AStarMove();
		}
		
		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);
		//�ړI�n�Ɉړ������Ƃ݂Ȃ�
		//if (abs(m_ownerPos.x - m_tagetRootPos[m_roodCount].x) <= 1.0f && abs(m_ownerPos.z - m_tagetRootPos[m_roodCount].z) <= 1.0f)
		//{
		//	m_ownerPos = m_tagetRootPos[m_roodCount];
		//	m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V 
		//	if (m_roodCount < m_tagetRootPos.size()-1)//���̐�ɐi�܂Ȃ��Ƃ����Ȃ��悪����ꍇ
		//	{
		//		m_roodCount++;//�ړI�n��ς���
		//	}
		//}
		
		////�ړI�n�Ɉړ������Ƃ݂Ȃ������Q
		//if (m_tagetRootPos.size() - 1 >= m_roodCount + 1)//�w�肷��z�񐔂��z��͈͓��ł��邩�m�F����
		//{
		//	//���[�g�T�[�`���ŏ��ɂ����ꍇ�̈ړ����@�̌�������
		//	if (aStarStart)
		//	{
		//		m_movePos = m_tagetRootPos[m_roodCount] - m_ownerPos;//���݂̍��W�ƖړI�n�̍����m�F����
		//		aStarStart = false;//���[�g�T�[�`�̈�ԍŏ��̏�Ԃł͂Ȃ��Ȃ���
		//	}

		//	//���l���P��[�P�ɌŒ艻���� �O�����Z�q�͂O�̏ꍇ���Ɩ��ɂȂ邽�ߎg��Ȃ�
		//	if (m_movePos.x > 0)//���̐��Ȃ�
		//	{
		//		m_movePos.x = 1;//�P�ɂ���
		//	}
		//	if (m_movePos.x < 0)//���̐��Ȃ�
		//	{
		//		m_movePos.x = -1;//-�P�ɂ���
		//	}
		//	if (m_movePos.z > 0)//���̐��Ȃ�
		//	{
		//		m_movePos.z = 1;//�P�ɂ���
		//	}
		//	if (m_movePos.z < 0)//���̐��Ȃ�
		//	{
		//		m_movePos.z = -1;//-�P�ɂ���
		//	}

		//	//���ړ�����̂�x�ړ��̏ꍇ
		//	if (m_tagetRootPos[m_roodCount].x - m_tagetRootPos[m_roodCount + 1].x != 0)
		//	{
		//		//��x�ړ����Ȃ�
		//		switch ((int)m_movePos.x)
		//		{
		//		case 1://�E�����ɐi��ł���Ȃ�
		//			//������ʒu���ړI�n��ʂ�߂����ꍇ�ړI�n�Ɉړ������Ƃ݂Ȃ����̖ړI�n�ɕύX����
		//			if (m_ownerPos.x >= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		case -1://�������ɐi��ł���Ȃ�
		//			//������ʒu���ړI�n��ʂ�߂����ꍇ�ړI�n�Ɉړ������Ƃ݂Ȃ����̖ړI�n�ɕύX����
		//			if (m_ownerPos.x <= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//		//��z�ړ����Ȃ�
		//		switch ((int)m_movePos.z)
		//		{
		//		case 1://��ɐi��ł���Ȃ�
		//			if (m_ownerPos.z >= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//�u�Ԉړ�

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		case -1://���ɐi��ł���Ȃ�
		//			if (m_ownerPos.z <= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//�u�Ԉړ�

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//	else if (m_tagetRootPos[m_roodCount].z - m_tagetRootPos[m_roodCount + 1].z != 0)//���ړ�����̂�z�ړ��̏ꍇ
		//	{
		//		//��x�ړ����Ȃ�
		//		switch ((int)m_movePos.x)//x���ǂ̕����Ɉړ����Ă��邩�m�F����
		//		{
		//		case 1://�E�����ɐi��ł���Ȃ�

		//			//������ʒu���ړI�n��ʂ�߂����ꍇ�ړI�n�Ɉړ������Ƃ݂Ȃ����̖ړI�n�ɕύX����
		//			if (m_ownerPos.x >= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//�u�Ԉړ�

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		case -1://�������ɐi��ł���Ȃ�

		//			//������ʒu���ړI�n��ʂ�߂����ꍇ�ړI�n�Ɉړ������Ƃ݂Ȃ����̖ړI�n�ɕύX����
		//			if (m_ownerPos.x <= m_tagetRootPos[m_roodCount].x)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_ownerPos = m_tagetRootPos[m_roodCount];//�u�Ԉړ�

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//		//��z�ړ����Ȃ�
		//		switch ((int)m_movePos.z)
		//		{
		//		case 1://��ɐi��ł���Ȃ�
		//			if (m_ownerPos.z >= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		case -1://���ɐi��ł���Ȃ�
		//			if (m_ownerPos.z <= m_tagetRootPos[m_roodCount].z)
		//			{
		//				m_movePos = m_tagetRootPos[m_roodCount + 1] - m_tagetRootPos[m_roodCount];//�V���ɂǂ��ړ�����΂������v�Z����

		//				m_roodCount++;//�ړI�n��ς���
		//				m_targetPos = m_tagetRootPos[m_roodCount];//�ړI�n���X�V
		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//}

		//m_directionRad = math.GetAngle(m_ownerPos,m_tagetRootPos[m_roodCount]);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//m_ownerRot.y = m_directionRad;
		//auto speedtest = m_Owner->GetSpeed();
		//m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//player�Ɍ������Ĉړ�
		//m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		
		//AStar���g�����ړ�����
		MoveActor(m_Owner, m_tagetRootPos, m_roodCount, m_Owner->GetSpeed());
		
		auto CircleRange = math.GetCircleRange(40, m_ownerPos, m_playerPos);
		if (CircleRange)
		{
			m_time = 0;
		}
		else
		{
			m_time += app()->GetElapsedTime();
		}


		if (m_time >= 1)
		{
			//Player���������������ɕύX
			m_Owner->ChangeState<TargetLost>();
		}

		if (m_Owner->GetDistance(m_ownerPos, m_playerPos) < 7)
		{
			m_Owner->ChangeState<Attack>();
		}
		//auto a = m_posVec[m_count-1];

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		auto RouteSearch = mapMgr->GetUnityMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertUnityMap(sellPos);

		//m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		//m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		//m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);

		float deg = m_directionRad * 180 / XM_PI;//���W�A�����f�B�O���[�ɕϊ��i�f�o�b�N�p�j

		//���b�V���̏���
		auto ability = m_Owner->GetAbility();

		if (ability==rush)
		{			
			if (m_rushMoveFlag == false)
			{
				m_rushMoveFlag = RushMoveChack(m_ownerPos, 2);
			}

			m_waitTime+= app()->GetElapsedTime();
			RushMove(m_rushMoveFlag);

		}

		////�f�o�b�N���O
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss /*<< L"�v���C���[Pos.x : " << m_playerPos.x
		//	<< L"\n�v���C���[Pos.z : " << m_playerPos.z*/
		//	<< L"\n�G�̉�].y : " << m_ownerRot.y
		//	<< L"\n�G�̉�]�ideg�j" << deg
		//	<< L"\n�G��Pos.x : " << m_ownerPos.x
		//	<< L"\n�G��Pos.z : " << m_ownerPos.z
		//	<< L"\n�E�R�X�g : " << m_costRight
		//	<< L"\n���R�X�g : " << m_costLeft
		//	<< L"\n�O�R�X�g : " << m_costFod
		//	<< L"\n��R�X�g : " << m_costDown
		//	<< L"\nAStarPos.x : " << AStarPos.x
		//	<< L"\nAStarPos.y : " << AStarPos.y
		//	//<< L"\na.x : " << a.x
		//	//<< L"\na.y : "<<a.y
		//	//<<L"\na.z : "<<a.z
		//	<< endl;
		//scene->SetDebugString(wss.str());


	}
	//�ǐՃX�e�[�g�̍Ō�̏���
	void Tracking::OnExit()
	{

	}

	//AStar���g���ړ�����
	void Tracking::AStarMove()
	{
		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		//Player�̈ʒu��AStar�̍��W�ɂ���
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//���[���h���W����Z�����W�ɂ��Ă���
		auto playerAStarPos = mapManager->ConvertUnityMap(playerSelPos);//A*�̍��W�ɕς���
		m_unityMap.clear();
		m_roodCount = 0;
		m_beforPlayerUnity = playerAStarPos;
		m_tagetRootPos = RouteSearch(m_ownerPos, m_playerPos);//�o�H�T��
		if (m_tagetRootPos.size() >= 2)
		{
			auto one = m_tagetRootPos[0];
			auto two = m_tagetRootPos[1];
			//���ݒn���P�Ԗڂ����A�Q�Ԗڂ̋����ɋ߂�������P�Ԗڂ̈ړ������𖳎�����
			if (abs(two.x - m_ownerPos.x) + abs(two.z - m_ownerPos.z) <= abs(two.x - one.x) + abs(two.z - one.z))
			{
				m_roodCount++;
			}
		}

	}

	//�g��Ȃ������ł������܂�
	void Tracking::nextSelLook(int right,int left,int up,int down,Vec2 enemyAStarPos,Vec2 playerAStarPos)
	{

		//�ׂ̍��W��1(�܂�ǂ�����Βʂ�Ȃ�)����������
		if (right == 1)
		{
			m_rightFlag = false;
			m_costRWall = 999;
		}
		//�ǂ��Ȃ���Ώ���������
		if (right == 0)
		{
			m_rightFlag = true;
			//�E�ɍs���Ă����Enemy��Player�̋����𑪂�
			auto distance = abs((enemyAStarPos.x + 1) - playerAStarPos.x) + abs(enemyAStarPos.y - playerAStarPos.y);
			auto addDistance = 1;//�i�񂾋���
			m_costRWall = distance;//�R�X�g������

		}

		if (left == 1)
		{
			m_leftFlag = false;
			m_costLWall = 999;
		}
		if (left == 0)
		{
			m_leftFlag = true;
			//���ɍs���Ă����Enemy��Player�̋����𑪂�
			auto distance = abs((enemyAStarPos.x - 1) - playerAStarPos.x) + abs(enemyAStarPos.y - playerAStarPos.y);
			auto addDistance = 1;//�i�񂾋���
			m_costLWall = distance;//�R�X�g������
		}

		if (up == 1)
		{
			m_upFlag = false;
			m_costFWall = 999;//�R�X�g������
		}
		if (up == 0)
		{
			m_upFlag = true;
			//��ɍs���Ă����Enemy��Player�̋����𑪂�
			auto distance = abs(enemyAStarPos.x - playerAStarPos.x) + abs((enemyAStarPos.y - 1) - playerAStarPos.y);
			auto addDistance = 1;//�i�񂾋���
			m_costFWall = distance;//�R�X�g������
		}

		if (down == 1)
		{
			m_downFlag = false;
			m_costDWall = 999;//�R�X�g������
		}
		if (down == 0)
		{
			m_downFlag = true;
			//��ɍs���Ă����Enemy��Player�̋����𑪂�
			auto distance = abs(enemyAStarPos.x - playerAStarPos.x) + abs((enemyAStarPos.y + 1) - playerAStarPos.y);
			auto addDistance = 1;//�i�񂾋���
			m_costDWall = distance;//�R�X�g������
		}
	}

	//�����g��Ȃ�
	vector<Vec3> Tracking::RouteSearchNotA()
	{		
		vector<Vec2> aStarRood;//�ړ��J��

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		

		m_unityMapCSV = mapManager->GetUnityMap();//AStar�}�b�v�擾
		//vector<vector<shared_ptr<Node>>> aStarMap;//�}�b�v�̃m�[�h�z��
		vector<shared_ptr<Node>> aStarMapline;
		//AStar�}�b�v�̔z��Ɠ����z��̑傫���̃m�[�h�����
		for (int y=0; y < m_unityMapCSV.size(); y++)
		{
			for (int x=0; x < m_unityMapCSV[0].size(); x++)
			{
				aStarMapline.push_back(make_shared<Node>(Node(x, y, Status_None, 999, 999, 999, NULL)));
			}
			m_unityMap.push_back(aStarMapline);
			aStarMapline.clear();//���Z�b�g
		}
		auto test=0;
		
		//�����ʒu�����߂鎩�����g(Enemy)�̌��ݒn�_
		auto enemySelPos = mapManager->ConvertSelMap(m_ownerPos);//�Z���ɕς���
		auto enemyAStarPos = mapManager->ConvertUnityMap(enemySelPos);
		auto originPos = enemyAStarPos;
		m_unityMap[originPos.y][originPos.x]->Status = Status_Open;
		auto cost = 0;
		//�S�[���n�_(Player)	
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);
		auto playerASterPos = mapManager->ConvertUnityMap(playerSelPos);
		auto goalPos = playerASterPos;
		bool root = false;//�o�H�������������ǂ���
		
		//��ԍŏ���Player�Ƃ̋������m�F����
		m_unityMap[originPos.y][originPos.x]->Status = Status_Open;
		auto lookCost = m_unityMap[originPos.y][originPos.x]->Cost = cost++;//�R�X�g�̕ϐ��܂�����ĂȂ�
		auto lookHCost = m_unityMap[originPos.y][originPos.x]->HeuristicCost = abs(goalPos.x - originPos.x) + abs(goalPos.y - originPos.y);
		m_unityMap[originPos.y][originPos.x]->Score = lookCost + lookHCost;

		//�o�H��������܂Ń��[�v����
		while (!root)
		{				
			//����ɉ������邩�m�F���� //�E���㉺�̏��̃Z���Ɍo�H�̕]�����鏈�����o���Ă܂��� ���A�]�����Ă���ꏊ���ǂ̃Z���ɂȂ��Ă��܂�
			root = LookAround(m_unityMap[originPos.y][originPos.x],goalPos);
	
			//�����̒��S�_��T��
			auto openScore = 0;
			auto minScore = 999;
			for (auto map : m_unityMap)
			{
				for (auto mapline : map)
				{
					if (mapline->Status == Status_Open)//Open��Ԃ̃X�R�A���擾����
					{
						openScore = mapline->Score;//�X�R�A���擾
						if (openScore <= minScore)//�ŐV�̍ŏ��X�R�A�������̃X�R�A�̕����Ⴏ��Γn��
						{
							minScore = openScore;
							originPos.x = mapline->x;//�����̒��S�_��ύX����
							originPos.y = mapline->y;//�����̒��S�_��ύX����
						
						}
					}
				}
			}

		}

		//���[�g������������ǂ��i�߂΂�������`����
		vector<Vec3> rootVec;
		//�܂��AAStar�̍��W�����[���h���W�ɖ߂���Ƃ�����
		rootVec.push_back(m_playerPos);
		auto parentSel = m_unityMap[goalPos.y][goalPos.x]->Parent;
		while (parentSel != NULL)
		{
			Vec2 AStarPos = Vec2(parentSel->x, parentSel->y);
			Vec2 SelPos = mapManager->ConvertU_S(AStarPos);
			Vec3 worldPos = mapManager->ConvertWorldMap(SelPos);
			rootVec.push_back(worldPos);
			parentSel = parentSel->Parent;
		}
		vector<Vec3> rootReverse;
		for (int i = rootVec.size()-1; i >= 0(); i--)
		{
			rootReverse.push_back(rootVec[i]);
		}
		m_ownerPos;
		return rootReverse;

	}

	bool Tracking::LookAround(shared_ptr<Node> parent,Vec2 goalPos)
	{
		Vec2 originPos = Vec2(parent->x, parent->y);
		auto cost = parent->Parent ? parent->Cost + 1 : 1;//�R�X�g�̌v�Z

		//�E���㉺�ɕǂ����邩�ǂ���������
		for (int pushy = -1; pushy < 2; pushy++)
		{
			for (int pushx = -1; pushx < 2; pushx++)
			{
				int lookX = pushx + originPos.x;
				int lookY = pushy + originPos.y;
				auto test = m_unityMap.size();

				//�m�F������W���e���W���猩�č��E�㉺�ȊO�Ȃ�m�F���Ȃ�
				if (pushy == 0 && pushx == 0 || pushy != 0 && pushx != 0) continue;	
				//�z��͈̔͊O�Ȃ�m�F���Ȃ�
				if ((lookY < 0 || lookY >= (m_unityMap.size())) || (lookX < 0 || lookX >= (m_unityMap.size()))) continue;
				//�ǂݍ��񂾃}�b�v�̏ꏊ���ǂ������邩�Ȃ����݂Ď��͒T���ς݂�����
				if (m_unityMapCSV[lookY][lookX] == 1 || m_unityMap[lookY][lookX]->Status == Status_Closed) continue;

				//�ǂ��m�F�����̂ŏ��̃}�X�ɑ΂��ĕ]������//////////////////////////////////////////////////////////////////////
				lookX = (pushx * 2) + originPos.x;
				lookY = (pushy * 2) + originPos.y;	

				if (lookX < 0||lookX>m_unityMap.size()-1)
				{
					auto test=0;
				}
				if (lookY < 0||lookY>m_unityMap.size()-1)
				{
					auto test = 0;
				}

				if (m_unityMap[lookY][lookX]->Status == Status_None)//�T���������Ƃ��Ȃ��Ȃ�
				{
					
					m_unityMap[lookY][lookX]->Status = Status_Open;
					auto lookCost = m_unityMap[lookY][lookX]->Cost = cost;//�R�X�g�̕ϐ��܂�����ĂȂ�
					auto lookHCost = m_unityMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - lookX) + abs(goalPos.y - lookY);
					m_unityMap[lookY][lookX]->Score = lookCost + lookHCost;
					m_unityMap[lookY][lookX]->Parent = m_unityMap[originPos.y][originPos.x];
				}
				if (m_unityMap[lookY][lookX]->Status == Status_Open)//�T���ς݂Ȃ�
				{
					auto Cost = m_unityMap[lookY][lookX]->Cost = cost;
					m_unityMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
					auto score = m_unityMap[lookY][lookX]->Score = m_unityMap[lookY][lookX]->Cost + m_unityMap[lookY][lookX]->HeuristicCost;

					if (m_unityMap[lookY][lookX]->Score > score)//�X�R�A���O�������Ȃ�������
					{
						m_unityMap[lookY][lookX]->Status = Status_Open;
						m_unityMap[lookY][lookX]->Cost = cost;
						m_unityMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
						m_unityMap[lookY][lookX]->Score = score;
						m_unityMap[lookY][lookX]->Parent = m_unityMap[originPos.y][originPos.x];
					}
				}



			}
		}

		//�}�b�v�̂��ׂĂ�����Player�̋������O�ȂƂ��낪���邩�m�F����
		for (auto map : m_unityMap)
		{
			for (auto mapline : map)
			{
				if (mapline->HeuristicCost == 0)
				{
					return true;
				}
			}
		}

		//���͒T�����I������Ȃ�X�e�[�^�X��Open����Closed�֕ς��
		m_unityMap[originPos.y][originPos.x]->Status = Status_Closed;

		return false;
	}

	//RushMove�̏���
	void Tracking::RushMove(bool onOff)
	{
		//RushMove���Ă����ꍇ�̏���(�Q��ڈȍ~�̏���)
		if (onOff && m_rushFlow == Rush_Continue)
		{
			//�i�ޕ������ʂɂȂ��Ă����烉�b�V����Ԃ���߂�
			if (m_XorZBefor != GetMoveXorZ())
			{
				m_rushMoveFlag = false;//���b�V����Ԃ���߂�
				AngerSpeed(m_anger);
				m_rushFlow = Rush_Start;//���Z�b�g����
				m_rushSetSpeedCountTime = 0.0f;//���b�V����Ԃ̑ҋ@���Ԃ����Z�b�g
			}
		}
		else if (onOff && m_rushFlow == Rush_SetSpeed)//��������(��ԍŏ��̏���)
		{
			m_rushSetSpeedCountTime += m_delta;

			if(m_rushSetSpeedCountTime >= 0.15f)
			{
				AngerSpeed(m_anger);
				m_Owner->SetSpeed(m_Owner->GetSpeed() * 2.0f);//���b�V����Ԃ̑ҋ@��Ԃɂ���
				m_rushFlow = Rush_Continue;//���̏������I��点����p�������ɑJ�ڂ���
			}
		}
		else if (onOff && m_rushFlow == Rush_Start)//RushMove���Ă����ꍇ�̏���(��ԍŏ��̏���)
		{
			//���ܑ����Ă���������o����
			m_XorZBefor = GetMoveXorZ();
			m_Owner->SetSpeed(0.0f);//���b�V����Ԃ̑ҋ@��Ԃɂ���
			
			m_rushFlow = Rush_SetSpeed;//���̏������I��点����������鏈���ɑJ�ڂ���
		}

		//RushMove�o���Ȃ��Ȃ����Ƃ�
		if (!onOff && m_rushFlow == Rush_Continue)
		{
			m_Owner->SetSpeed(21.0f);
			m_rushFlow = Rush_Start;//���Z�b�g����
			m_rushSetSpeedCountTime = 0.0f;//���b�V����Ԃ̑ҋ@���Ԃ����Z�b�g
		}
	}

	//RushMove���Ă������m�F����֐�
	bool Tracking::RushMoveChack(Vec3 pos, int vision)
	{
		Vec3 n_pos = pos;

		int n_vision = vision;
		int lineRootCount = 0;//�����̓����ǂ̂��炢�����Ă��邩�L�^����ϐ�

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		auto angle = m_Owner->GetAngle();

		//x�����ɐi��ł��邩z�����ɐi��ł��邩�m�F���� false��x,true��z
		bool XorZ=false;
		//�O���x�����ɐi��ł��邩z�����ɐi��ł��邩�m�F���� false��x,true��z
		bool XorZBetor = false;
		//�܂������i��ł���o�H���m�F����ϐ�
		bool straightLine = true;


		//�ːi����̂Ɍ��݂̐i�ތo�H������������Ă��邩
		if (m_roodCount + vision < m_tagetRootPos.size())
		{		
			//�o�H�T���̕����ƍ��i��ł���������������m�F����
			bool XorZ = GetMoveXorZ();
			Vec3 rootVec = m_tagetRootPos[0] - m_tagetRootPos[1];
			if (!XorZ)//x�����ɐi��ł���Ȃ�
			{
				//�o�H�T���ł͎��ǂ̕����ɐi�ނ��m�F����
				if (rootVec.x == 0) return false;
			}
			if (XorZ)//z�����ɐi��ł���Ȃ�
			{
				//�o�H�T���ł͎��ǂ̕����ɐi�ނ��m�F����
				if (rootVec.z == 0) return false;
			}

			//���i�ތo�H��vision�̐��l�������������Ă��邩�m�F����
			for (int i = 0; i <= vision; i++)
			{
				//���̍��W�ƖڕW�n�_�̍��W�̍��𑪂�ϐ�
				Vec3 distance = Vec3(0.0f, 0.0f, 0.0f);
				if (i == 0)
				{
					distance = m_tagetRootPos[m_roodCount+i] - m_ownerPos;
				}
				if (i > 0)
				{
					distance = m_tagetRootPos[m_roodCount + i] - m_tagetRootPos[m_roodCount + lineRootCount];
				}

				//x��z�����ǂ����ɐi��ł��邩����
				if (distance.x != 0.0f)
				{
					XorZ = true;
				}
				if (distance.z != 0.0f)
				{
					XorZ = false;
				}

				//�P��ڂȂ�X����Z�����ǂ����ɐi��ł��邩�ۑ�����
				if (i == 0)
				{
					XorZBetor = XorZ;
				}
				//2��ڈȍ~��X��Z�̐i�ޕ������Ⴄ�Ȃ�ːi�����Ȃ�
				if (i > 0)
				{
					if (XorZBetor != XorZ)//�Ⴄ�̂ł���Γːi���Ȃ�
					{
						return false;//�ːi�ł��Ȃ�
					}
				}

				lineRootCount = i;
			}

			//�����̓����Œ�����b�V�������邽�߂ɕK�v�ȋ���������΂��
			if (lineRootCount == vision)
			{
				return true;//�ːi���ėǂ�
			}
		}

		return false;//�Ⴄ�̂ł���Γːi���Ȃ�
	}

	//�{��l�ɂ���ăX�s�[�h�����߂鏈��
	void Tracking::AngerSpeed(int anger)
	{
		switch (anger)
		{
		case ANGER_NONE://�{���ĂȂ�
			m_Owner->SetSpeed(21.0f);
			break;
		case ANGER_LOW://�{���Ă�(��)
			m_Owner->SetSpeed(21.0f * 1.065f);
			break;
		case ANGER_MIDDLE://�{���Ă�(��)
			m_Owner->SetSpeed(21.0f * 1.25f);
			break;
		case ANGER_HI://�{���Ă�(��)
			m_Owner->SetSpeed(21.0f * 1.5f);
			break;
		default:
			break;
		}
	}

}

//end basecross
