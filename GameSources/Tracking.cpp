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
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		m_ownerRot.y = rad;//player�̕����Ɍ���

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		//Player�̈ʒu��AStar�̍��W�ɂ���
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);//���[���h���W����Z�����W�ɂ��Ă���
		auto playerAStarPos = mapManager->ConvertAStarMap(playerSelPos);//A*�̍��W�ɕς���

		//A*�̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//�v���C���[��A*���W�����ς���Ă�����A*������������x���
		if (playerAStarPos != m_beforPlayerAStar)
		{
			m_ownerPos;

			m_aStarMap.clear();
			m_roodCount = 0;
			m_beforPlayerAStar = playerAStarPos;
			//MoveCost();
			m_tagetRootPos = AStar();
		}
		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);
		//�ړI�n�Ɉړ������Ƃ݂Ȃ�
		if (abs(m_ownerPos.x - m_tagetRootPos[m_roodCount].x) <= 0.5f && abs(m_ownerPos.z - m_tagetRootPos[m_roodCount].z) <= 0.5f)
		{
			m_ownerPos = m_tagetRootPos[m_roodCount];
			m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
			if (m_roodCount < m_tagetRootPos.size())//���̐�ɐi�܂Ȃ��Ƃ����Ȃ��悪����ꍇ
			{
				m_roodCount++;//�ړI�n��ς���
			}
		}
		m_directionRad = math.GetAngle(m_ownerPos,m_tagetRootPos[m_roodCount]);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
			m_time += app()->GetElapsedTime();
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
		auto scene = App::GetApp()->GetScene<Scene>();
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

		//�f�o�b�N�p/////////////////////////////////////////////////////////////
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̎擾
		auto m_controler = inputDevice.GetControlerVec()[0];
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)//B�{�^�����������Ƃ�
		{
			mapManager->MapDataUpdate(pos, 5);//�E�o��Ԃɂ���

		}
		////////////////////////////////////////////////////////////////////////

	}
	//�ǐՃX�e�[�g�̍Ō�̏���
	void Tracking::OnExit()
	{

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

	vector<Vec3> Tracking::AStar()
	{		
		vector<Vec2> aStarRood;//�ړ��J��

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		m_aStarMapCSV = mapManager->GetAStarMap();//AStar�}�b�v�擾
		//vector<vector<shared_ptr<Node>>> aStarMap;//�}�b�v�̃m�[�h�z��
		vector<shared_ptr<Node>> aStarMapline;
		//AStar�}�b�v�̔z��Ɠ����z��̑傫���̃m�[�h�����
		for (int y=0; y < m_aStarMapCSV.size(); y++)
		{
			for (int x=0; x < m_aStarMapCSV[0].size(); x++)
			{
				aStarMapline.push_back(make_shared<Node>(Node(x, y, Status_None, 999, 999, 999, NULL)));
			}
			m_aStarMap.push_back(aStarMapline);
			aStarMapline.clear();//���Z�b�g
		}
		auto test=0;
		
		//�����ʒu�����߂鎩�����g(Enemy)�̌��ݒn�_
		auto enemySelPos = mapManager->ConvertSelMap(m_ownerPos);//�Z���ɕς���
		auto enemyAStarPos = mapManager->ConvertAStarMap(enemySelPos);
		auto originPos = enemyAStarPos;
		m_aStarMap[originPos.y][originPos.x]->Status = Status_Open;
		auto cost = 1;
		//�S�[���n�_(Player)
		auto playerSelPos = mapManager->ConvertSelMap(m_playerPos);
		auto playerASterPos = mapManager->ConvertAStarMap(playerSelPos);
		auto goalPos = playerASterPos;
		bool root = false;//�o�H�������������ǂ���

		//�o�H��������܂Ń��[�v����
		while (!root)
		{				
			//����ɉ������邩�m�F���� //�E���㉺�̏��̃Z���Ɍo�H�̕]�����鏈�����o���Ă܂��� ���A�]�����Ă���ꏊ���ǂ̃Z���ɂȂ��Ă��܂�
			root = LookAround(m_aStarMap[originPos.y][originPos.x],goalPos);
	
			//�����̒��S�_��T��
			auto openScore = 0;
			auto minScore = 999;
			for (auto map : m_aStarMap)
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


			auto a = 0;
			//m_aStarMap[originPos.y][originPos.x]->Status = Status_Closed;//����
			//cost++;
		}

		//���[�g������������ǂ��i�߂΂�������`����
		vector<Vec3> rootVec;
		//�܂��AAStar�̍��W�����[���h���W�ɖ߂���Ƃ�����
		rootVec.push_back(m_playerPos);
		auto parentSel = m_aStarMap[goalPos.y][goalPos.x]->Parent;
		while (parentSel != NULL)
		{
			Vec2 AStarPos = Vec2(parentSel->x, parentSel->y);
			Vec2 SelPos = mapManager->ConvertA_S(AStarPos);
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

				//�m�F������W���e���W���猩�č��E�㉺�ȊO�Ȃ�m�F���Ȃ�
				if (pushy == 0 && pushx == 0 || pushy != 0 && pushx != 0) continue;	
				//�ǂݍ��񂾃}�b�v�̏ꏊ���ǂ������邩�Ȃ����݂Ď��͒T���ς݂�����
				if (m_aStarMapCSV[lookY][lookX] == 1 || m_aStarMap[lookY][lookX]->Status == Status_Closed) continue;
				//�ǂ��m�F�����̂ŏ��̃}�X�ɑ΂��ĕ]������
				lookX = (pushx * 2) + originPos.x;
				lookY = (pushy * 2) + originPos.y;	
				//�z��͈̔͊O�Ȃ�m�F���Ȃ�	
				if ((lookY <= 0 || lookY >= (m_aStarMap.size() - 1)) || (lookX <= 0 || lookX >= (m_aStarMap.size() - 1))) continue;

				if (lookX < 0||lookX>m_aStarMap.size()-1)
				{
					auto test=0;
				}
				if (lookY < 0||lookY>m_aStarMap.size()-1)
				{
					auto test = 0;
				}

				if (m_aStarMap[lookY][lookX]->Status == Status_None)//�T���������Ƃ��Ȃ��Ȃ�
				{
					m_aStarMap[lookY][lookX]->Status = Status_Open;
					auto lookCost = m_aStarMap[lookY][lookX]->Cost = cost;//�R�X�g�̕ϐ��܂�����ĂȂ�
					auto lookHCost = m_aStarMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - lookX) + abs(goalPos.y - lookY);
					m_aStarMap[lookY][lookX]->Score = lookCost + lookHCost;
					m_aStarMap[lookY][lookX]->Parent = m_aStarMap[originPos.y][originPos.x];
				}
				if (m_aStarMap[lookY][lookX]->Status == Status_Open)//�T���ς݂Ȃ�
				{
					auto Cost = m_aStarMap[lookY][lookX]->Cost = cost;
					m_aStarMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
					auto score = m_aStarMap[lookY][lookX]->Score = m_aStarMap[lookY][lookX]->Cost + m_aStarMap[lookY][lookX]->HeuristicCost;

					if (m_aStarMap[lookY][lookX]->Score > score)//�X�R�A���O�������Ȃ�������
					{
						m_aStarMap[lookY][lookX]->Status = Status_Open;
						m_aStarMap[lookY][lookX]->Cost = cost;
						m_aStarMap[lookY][lookX]->HeuristicCost = abs(goalPos.x - (lookX)) + abs(goalPos.y - (lookY));
						m_aStarMap[lookY][lookX]->Score = score;
						m_aStarMap[lookY][lookX]->Parent = m_aStarMap[originPos.y][originPos.x];
					}
				}

				if (m_aStarMap[lookY][lookX]->HeuristicCost == 0)
				{
					return true;
				}
			}
		}

		//���͒T�����I������Ȃ�X�e�[�^�X��Open����Closed�֕ς��
		m_aStarMap[originPos.y][originPos.x]->Status = Status_Closed;

		return false;
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
