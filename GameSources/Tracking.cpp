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
	}

	//�ǐՃX�e�[�g�̍X�V����
	void Tracking::OnUpdate()
	{
		//player��ǂ������鏈��
		auto app = App::GetApp;
		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)�̃|�W�V�������擾
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		m_playerRay = m_Owner->GetPlayerRay();
		//float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		//m_ownerRot.y = rad;//player�̕����Ɍ���


		MoveCost();
		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);
		m_directionRad = math.GetAngle(m_ownerPos,m_tagetPos);

		//m_ownerRot.y = m_directionRad;

		m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//player�Ɍ������Ĉړ�
		m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos.y = 2.5f;
		
		auto CircleRange = math.GetCircleRange(60, m_ownerPos, m_playerPos);
		if (CircleRange)
		{
			m_time = 0;
		}
		else
		{
			//m_time += app()->GetElapsedTime();
		}


		if (m_time >= 3)
		{
			m_Owner->ChangeState<Patrol>();
		}

		if (m_Owner->GetDistance(m_ownerPos, m_playerPos) < 7)
		{
			m_Owner->ChangeState<Attack>();
		}
		//auto a = m_posVec[m_count-1];

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		auto AStar = mapMgr->GetAStarMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertAStarMap(sellPos);

		m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);

		float deg = m_directionRad * 180 / XM_PI;//���W�A�����f�B�O���[�ɕϊ��i�f�o�b�N�p�j

		//�f�o�b�N���O
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss /*<< L"�v���C���[Pos.x : " << m_playerPos.x
			//<< L"\n�v���C���[Pos.z : " << m_playerPos.z*/
			//<< L"\n�G�̉�].y : " << m_ownerRot.y
			//<< L"\n�G�̉�]�ideg�j" << deg
			//<< L"\n�G��Pos.x : " << m_ownerPos.x
			//<< L"\n�G��Pos.z : " << m_ownerPos.z
			//<< L"\n�E�R�X�g : " << m_costRight
			//<< L"\n���R�X�g : " << m_costLeft
			//<< L"\n�O�R�X�g : " << m_costFod
			//<< L"\n��R�X�g : " << m_costDown
			//<< L"\nAStarPos.x : " << AStarPos.x
			//<< L"\nAStarPos.y : " << AStarPos.y
			//<< L"\na.x : " << a.x
			//<< L"\na.y : "<<a.y
			//<<L"\na.z : "<<a.z
			//<< endl;
		//scene->SetDebugString(wss.str());
	}
	//�ǐՃX�e�[�g�̍Ō�̏���
	void Tracking::OnExit()
	{

	}

	////������A*�̏��������܂�  �܂��ׂ̃}�X(�ǂ̃}�X)�������Đi�ނ��i�܂Ȃ������f���Ă܂�
	Vec3 Tracking::MoveCost()
	{
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;

		auto aStarMap = mapManager->GetAStarMap();//A�X�^�[�擾

		//m_AStarMapDeta�̔z��̒�����aStarMap�ƂƓ����ɂ���
		vector<VecAStarIndex> lineAStarMapDeta;//��s�z��
		for (int i = 0; i < aStarMap.size(); i++)
		{
			for (int j = 0; j < aStarMap[0].size(); j++)
			{
				lineAStarMapDeta.push_back(VecAStarIndex(0, 0, 0, false));
			}
			m_aStarMapDeta.push_back(lineAStarMapDeta);
			lineAStarMapDeta.clear();
		}

		//�������g�̈ʒu��AStar�̍��W�ɂ���
		auto EnemySelPos = mapManager->ConvertSelMap(m_ownerPos);
		auto EnemyAStarPos = mapManager->ConvertAStarMap(EnemySelPos);

		auto test = mapManager->ConvertA_S(EnemyAStarPos);
		auto test2 = mapManager->ConvertWorldMap(test);

		//Player�̈ʒu��AStar�̍��W�ɂ���
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//���[���h���W����Z�����W�ɂ��Ă���
		auto playerAStarPos = mapManager->ConvertAStarMap(playerSelPos);//A*�̍��W�ɕς���

		aStarMap[playerAStarPos.y][playerAStarPos.x] = 2;//AMap�ɂ������ړI�n�Ɠ`����
		auto a = 0;

		auto kyori = 999;
		Vec2 searchAStar = EnemyAStarPos;//���W�̃f�[�^���擾���邽�߂̒��S�̃Z�����W
		while (kyori > 0)//�ǂ��s���΂��������܂����炪���܂����烋�[�v���I���
		{
			////�E�̍��W
			auto right = aStarMap[EnemyAStarPos.y][EnemyAStarPos.x + 1];//��X�A�X�̈�����EnemyStarPos�ł͂Ȃ����ׂ������W�̕ϐ��ɕς���
			////���̍��W
			auto left = aStarMap[EnemyAStarPos.y][EnemyAStarPos.x - 1];
			////���̍��W
			auto down = aStarMap[EnemyAStarPos.y + 1][EnemyAStarPos.x];
			////��̍��W
			auto up = aStarMap[EnemyAStarPos.y - 1][EnemyAStarPos.x];

			//auto m_rightWall = false;
			//auto m_leftWall = false;
			//auto m_downWall = false;
			//auto m_upWall = false;

			//�ׂ̍��W��1(�܂�ǂ�����Βʂ�Ȃ�)����������
			nextSelLook(right, left, up, down, EnemyAStarPos, playerAStarPos);

			//�R�X�g�̏�����
			m_costLWall = 999;
			m_costRWall = 999;
			m_costFWall = 999;
			m_costDWall = 999;

			//���̌�Ɉ�ԒႢ�R�X�g�̕����ɐi�ޏ����������A������ԒႢ�R�X�g�̕�����������������Γ����ɂ��
			//�܂��͈�ԒႢ�R�X�g�̕������P�����̏����������A���̌�Ɋ֐��������ĕ������������� ���������ł�����
			// �ׂ̃}�X�ɏ�������
			//���ɕǂ��Ȃ�������Ƃ��̍��W���g���Ă��Ȃ��Ȃ�
			if (m_leftFlag && m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x - 2].use == false)
			{
				auto distance = abs((EnemyAStarPos.x - 2) - playerAStarPos.x) + abs(EnemyAStarPos.y - playerAStarPos.y);
				m_costLWall = distance;//�R�X�g������

				auto addLenght = m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x - 2].addLenght = 2;//�ǂꂭ�炢���̃}�X�ɍs�����߂Ɍ��ݒn����ړ����Ă��邩
				kyori=m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x - 2].toTagetLenght = distance;//���̒n�_����ړI�n�ւ̋���
				m_costLWall = m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x - 2].totalLenght = distance+addLenght;//�������o�R����ƖړI�n�ɍŒZ�ǂꂭ�炢�Œ�����
				m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x - 2].use = true;//���̃}�X���g������



				auto a = 0;
			}
			//�E�ɕǂ��Ȃ�������Ƃ��̍��W���g���Ă��Ȃ��Ȃ�
			if (m_rightFlag&& m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x + 2].use==false)
			{
				auto distance = abs((EnemyAStarPos.x + 2) - playerAStarPos.x) + abs(EnemyAStarPos.y - playerAStarPos.y);
				m_costRWall = distance;//�R�X�g������

				auto addLenght = m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x + 2].addLenght = 2;//�ǂꂭ�炢���̃}�X�ɍs�����߂Ɍ��ݒn����ړ����Ă��邩
				kyori = m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x + 2].toTagetLenght = distance;//���̒n�_����ړI�n�ւ̋���
				m_costRWall = m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x + 2].totalLenght = distance + addLenght;//�������o�R����ƖړI�n�ɍŒZ�ǂꂭ�炢�Œ�����
				m_aStarMapDeta[EnemyAStarPos.y][EnemyAStarPos.x + 2].use = true;//���̃}�X���g������

				auto a = 0;
			}
			//��ɕǂ��Ȃ�������Ƃ��̍��W���g���Ă��Ȃ��Ȃ�
			if (m_upFlag&& m_aStarMapDeta[EnemyAStarPos.y - 2][EnemyAStarPos.x].use==false)
			{
				auto distance = abs(EnemyAStarPos.x - playerAStarPos.x) + abs((EnemyAStarPos.y-2) - playerAStarPos.y);
				m_costFWall = distance;//�R�X�g������

				auto addLenght = m_aStarMapDeta[EnemyAStarPos.y-2][EnemyAStarPos.x].addLenght = 2;//�ǂꂭ�炢���̃}�X�ɍs�����߂Ɍ��ݒn����ړ����Ă��邩
				kyori = m_aStarMapDeta[EnemyAStarPos.y-2][EnemyAStarPos.x].toTagetLenght = distance;//���̒n�_����ړI�n�ւ̋���
				m_costFWall = m_aStarMapDeta[EnemyAStarPos.y-2][EnemyAStarPos.x].totalLenght = distance + addLenght;//�������o�R����ƖړI�n�ɍŒZ�ǂꂭ�炢�Œ�����
				m_aStarMapDeta[EnemyAStarPos.y-2][EnemyAStarPos.x].use = true;//���̃}�X���g������

				auto a = 0;

			}
			//���ɕǂ��Ȃ�������Ƃ��̍��W���g���Ă��Ȃ��Ȃ�
			if (m_downFlag&& m_aStarMapDeta[EnemyAStarPos.y + 2][EnemyAStarPos.x].use==false)
			{
				auto distance = abs(EnemyAStarPos.x - playerAStarPos.x) + abs((EnemyAStarPos.y + 2) - playerAStarPos.y);
				m_costDWall = distance;//�R�X�g������

				auto addLenght = m_aStarMapDeta[EnemyAStarPos.y + 2][EnemyAStarPos.x].addLenght = 2;//�ǂꂭ�炢���̃}�X�ɍs�����߂Ɍ��ݒn����ړ����Ă��邩
				kyori = m_aStarMapDeta[EnemyAStarPos.y + 2][EnemyAStarPos.x].toTagetLenght = distance;//���̒n�_����ړI�n�ւ̋���
				m_costDWall = m_aStarMapDeta[EnemyAStarPos.y + 2][EnemyAStarPos.x].totalLenght = distance + addLenght;//�������o�R����ƖړI�n�ɍŒZ�ǂꂭ�炢�Œ�����
				m_aStarMapDeta[EnemyAStarPos.y + 2][EnemyAStarPos.x].use = true;//���̃}�X���g������

				auto a = 0;
			}

			vector<int> cost =
			{
				m_costLWall,//��
				m_costRWall,//�E
				m_costFWall,//��
				m_costDWall//��
			};

			auto minCost = 999;//��ԒႢ�R�X�g��ۊǂ���
			vector<int> minDirection;//�������Ǘ�����ϐ�
			//�R�X�g����ԒႢ�����𒲂ׂ�
			for (int i = 0; i < cost.size(); i++)
			{
				auto nowCost = cost[i];//���݂̃R�X�g
				if (minCost > nowCost)//���̃R�X�g���ŏ��̃R�X�g�����Ⴂ�Ƃ�
				{
					minCost = nowCost;//�ŏ��R�X�g���X�V����
					minDirection.clear();//�ŏ��R�X�g���X�V���ꂽ�̂Ŕz�񃊃Z�b�g
					minDirection.push_back(i);//����ň�ԒႢ�R�X�g�̕������m�F����
				}
				else if (minCost == nowCost)//���̃R�X�g���ŏ��̃R�X�g�Ɠ�����
				{
					minDirection.push_back(i);//��ԒႢ�R�X�g�̕�����ǉ�����
				}
			}

			for (int i = 0; i < minDirection.size(); i++)
			{
				if (minDirection[i] ==0)
				{
					auto AStarPos(Vec2(EnemyAStarPos.x - 2, EnemyAStarPos.y));//AStar�̍��W���擾
					auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel���W�ɕϊ�
					m_tagetPos = mapManager->ConvertWorldMap(SelPos);//���[���h���W�ɕϊ�
					auto a = 0;
				}
				//�E�ɕǂ��Ȃ�������
				if (minDirection[i] == 1)
				{
					auto AStarPos(Vec2(EnemyAStarPos.x + 2, EnemyAStarPos.y));//AStar�̍��W���擾
					auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel���W�ɕϊ�
					m_tagetPos = mapManager->ConvertWorldMap(SelPos);//���[���h���W�ɕϊ�
					auto a = 0;
				}
				//��ɕǂ��Ȃ�������
				if (minDirection[i] == 2)
				{
					auto AStarPos(Vec2(EnemyAStarPos.x, EnemyAStarPos.y - 2));//AStar�̍��W���擾
					auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel���W�ɕϊ�
					m_tagetPos = mapManager->ConvertWorldMap(SelPos);//���[���h���W�ɕϊ�
					auto a = 0;

				}
				//���ɕǂ��Ȃ�������
				if (minDirection[i] == 3)
				{
					auto AStarPos(Vec2(EnemyAStarPos.x, EnemyAStarPos.y + 2));//AStar�̍��W���擾
					auto SelPos = mapManager->ConvertA_S(AStarPos);//Sel���W�ɕϊ�
					m_tagetPos = mapManager->ConvertWorldMap(SelPos);//���[���h���W�ɕϊ�
					auto a = 0;
				}

			}

			m_tagetRootPos.push_back(m_tagetPos);//��ԒႢ�R�X�g�̏ꏊ�Ɉړ����邱�Ƃɂ���

		}



		return Vec3(0,0,0);
	}

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

	//Vec3 Tracking::MoveCost()
	//{
	//	Math math;
	//	auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
	//	Vec3 pos = m_ownerPos;
	//	Vec3 playerPos = m_playerPos;
	//	Vec3 direction;
	//	auto AStar = mapMgr->GetAStarMap();//A*�̃}�b�v�z��擾
	//	auto sellPos = mapMgr->ConvertSelMap(pos);//Enemy�̈ʒu���Z�����W�ɕύX
	//	auto AStarPos = mapMgr->ConvertAStarMap(sellPos);//�Z�����W����AStar���W�ɕύX

	//	auto rightAStar = AStar[AStarPos.y][AStarPos.x + 1];
	//	auto leftAStar = AStar[AStarPos.y][AStarPos.x - 1];
	//	auto fodAStar = AStar[AStarPos.y - 1][AStarPos.x];
	//	auto downAStar = AStar[AStarPos.y + 1][AStarPos.x];


	//	auto rightASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x + 2, AStarPos.y));
	//	auto leftASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x - 2, AStarPos.y));
	//	auto fodASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y - 2));
	//	auto downASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y + 2));


	//	auto rightWPos = mapMgr->ConvertWorldMap(rightASPos);
	//	auto leftWPos = mapMgr->ConvertWorldMap(leftASPos);
	//	auto fodWPos = mapMgr->ConvertWorldMap(fodASPos);
	//	auto downWPos = mapMgr->ConvertWorldMap(downASPos);


	//	auto rightVec = math.GetDistance(rightWPos, m_playerPos);
	//	auto liftVec = math.GetDistance(leftWPos, m_playerPos);
	//	auto fodVec = math.GetDistance(fodWPos, m_playerPos);
	//	auto downVec = math.GetDistance(downWPos, m_playerPos);


	//	if (rightAStar == 1)
	//	{
	//		m_costRWall += 1000;
	//	}
	//	else if(rightAStar == 0)
	//	{
	//		m_costRWall = 0;
	//	}
	//	if (leftAStar == 1)
	//	{
	//		m_costLWall = 1000;
	//	}
	//	else if (leftAStar == 0)
	//	{
	//		m_costLWall = 0;
	//	}
	//	if (fodAStar == 1)
	//	{
	//		m_costFWall += 1000;
	//	}
	//	else if (fodAStar == 0)
	//	{
	//		m_costFWall = 0;
	//	}
	//	if (downAStar == 1)
	//	{
	//		m_costDWall += 1000;
	//	}
	//	else if (downAStar == 0)
	//	{
	//		m_costDWall = 0;
	//	}



	//	int min_value[] =
	//	{
	//		{rightVec + m_costRight+m_costRWall},
	//		{liftVec + m_costLeft+m_costLWall},
	//		{fodVec + m_costFod+m_costFWall},
	//		{downVec + m_costDown+m_costDWall},
	//	};
	//	int min = min_value[0];
	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (min_value[i] < min)
	//		{
	//			min = min_value[i];
	//		}
	//	}

	//	if (min == min_value[0])
	//	{
	//		direction = rightWPos;
	//	}
	//	if (min == min_value[1])
	//	{
	//		direction = leftWPos;
	//	}
	//	if (min == min_value[2])
	//	{
	//		direction = fodWPos;
	//	}
	//	if (min == min_value[3])
	//	{
	//		direction = downWPos;
	//	}
	//	while (direction != m_playerPos)
	//	{
	//		if (m_count >= 0)
	//		{
	//			//m_posVec[m_count] = direction;
	//			m_posVec.push_back(direction);

	//		}

	//		if (m_count > 0)
	//		{
	//			if (playerPos==m_playerPos)
	//			{
	//				if (rightWPos == m_posVec[m_count - 1])
	//				{
	//					m_costLeft += 100;
	//					m_costRight = 0;
	//				}
	//				if (leftWPos == m_posVec[m_count - 1])
	//				{
	//					m_costRight += 100;
	//					m_costLeft = 0;
	//				}
	//				if (fodWPos == m_posVec[m_count - 1])
	//				{
	//					m_costDown += 1;
	//					m_costFod = 0;
	//				}
	//				if (downWPos == m_posVec[m_count - 1])
	//				{
	//					m_costFod += 1;
	//					m_costDown = 0;
	//				}
	//			}
	//		}
	//		if (m_costRight < 0)
	//		{
	//			m_costRight = 0;
	//		}
	//		if (m_costRight > 100)
	//		{
	//			m_costRight = 100;
	//		}
	//		if (m_costLeft < 0)
	//		{
	//			m_costLeft = 0;
	//		}
	//		if (m_costLeft > 100)
	//		{
	//			m_costLeft = 100;
	//		}
	//		if(m_costFod < 0)
	//		{
	//			m_costFod = 0;
	//		}
	//		if (m_costFod > 100)
	//		{
	//			m_costFod = 100;
	//		}
	//		if (m_costDown < 0)
	//		{
	//			m_costDown = 0;
	//		}
	//		if (m_costDown > 100)
	//		{
	//			m_costDown = 100;
	//		}
	//		m_count++;
	//		
	//		return m_posVec[m_count - 1];
	//	}

	//}

	

}

//end basecross
