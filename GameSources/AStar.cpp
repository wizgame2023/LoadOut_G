/*!
@file AStar.cpp
@brief �o�H�T������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�R���X�g���N�^
	AStar::AStar(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	//�f�X�g���N�^
	AStar::~AStar()
	{

	}

	//�쐬
	void AStar::OnCreate()
	{

	}

	//�X�V
	void AStar::OnUpdate()
	{

	}


	//�o�H�T������
	vector<Vec3> AStar::RouteSearch(Vec3 startWPos,Vec3 goalWPos)
	{
		//������������
		m_unityMap.clear();

		vector<Vec2> aStarRood;//�ړ��J��

		auto mapManager = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");


		m_unityMapCSV = mapManager->GetUnityMap();//AStar�}�b�v�擾
		//vector<vector<shared_ptr<Node>>> aStarMap;//�}�b�v�̃m�[�h�z��
		vector<shared_ptr<Node>> aStarMapline;
		//AStar�}�b�v�̔z��Ɠ����z��̑傫���̃m�[�h�����
		for (int y = 0; y < m_unityMapCSV.size(); y++)
		{
			for (int x = 0; x < m_unityMapCSV[0].size(); x++)
			{
				aStarMapline.push_back(make_shared<Node>(Node(x, y, Status_None, 999, 999, 999, NULL)));
			}
			m_unityMap.push_back(aStarMapline);
			aStarMapline.clear();//���Z�b�g
		}
		auto test = 0;

		//�����ʒu�����߂鎩�����g(Enemy)�̌��ݒn�_
		auto enemySelPos = mapManager->ConvertSelMap(startWPos);//�Z���ɕς���
		auto enemyAStarPos = mapManager->ConvertUnityMap(enemySelPos);
		auto originPos = enemyAStarPos;
		m_unityMap[originPos.y][originPos.x]->Status = Status_Open;
		auto cost = 0;
		//�S�[���n�_(Player)	
		auto playerSelPos = mapManager->ConvertSelMap(goalWPos);
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
			root = LookAround(m_unityMap[originPos.y][originPos.x], goalPos);

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
		rootVec.push_back(goalWPos);
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
		for (int i = rootVec.size() - 1; i >= 0(); i--)
		{
			rootReverse.push_back(rootVec[i]);
		}
		auto a = mapManager->ConvertUnityMap(Vec2(6, 6));
		return rootReverse;
	}


	//�T���Ă���Z�����S�[������ǂꂭ�炢�������m�F����
	bool AStar::LookAround(shared_ptr<Node> parent, Vec2 goalPos)
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

				//�ǂݍ��񂾃}�b�v�̏ꏊ���ǂ������邩�Ȃ����݂Ď��͒T���ς݂�����
				if (m_unityMapCSV[lookY][lookX] == 3)
				{
					//���}���u�@�ړI�n���}���z�[���Ȃ疳������
					if (goalPos != Vec2(lookX, lookY))
					{
						continue;
					}
				}


				if (lookX < 0 || lookX>m_unityMap.size() - 1)
				{
					auto test = 0;
				}
				if (lookY < 0 || lookY>m_unityMap.size() - 1)
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

	//AStar�p�̈ړ�����
	void AStar::MoveActor(shared_ptr<Actor> actor, vector<Vec3> routePos,int& routeCount,float speed)
	{
		auto trans = actor->GetComponent<Transform>();
		auto pos = trans->GetPosition();

		if (routePos.size() > 2&&routeCount == 0)
		{
			auto one = routePos[0];
			auto two = routePos[1];
			//���ݒn���P�Ԗڂ����A�Q�Ԗڂ̋����ɋ߂�������P�Ԗڂ̈ړ������𖳎�����
			if (abs(two.x - pos.x) + abs(two.z - pos.z) <= abs(two.x - one.x) + abs(two.z - one.z))
			{
				routeCount++;
			}

		}

		//�ړI�n�Ɉړ������Ƃ݂Ȃ�
		if (abs(pos.x - routePos[routeCount].x) <= 1.0f && abs(pos.z - routePos[routeCount].z) <= 1.0f)
		{
			pos = routePos[routeCount];
			trans->SetPosition(pos);//���L��(Enemy)�̃|�W�V�����̍X�V
			if (routeCount < routePos.size() - 1)//���̐�ɐi�܂Ȃ��Ƃ����Ȃ��悪����ꍇ
			{
				routeCount++;//�ړI�n��ς���
			}
		}
		auto delta = App::GetApp()->GetElapsedTime();
		Math math;	
		auto angle = math.GetAngle(pos, routePos[routeCount]);

		//�ړ�����
		pos.x += -sin(angle) * speed * delta;
		pos.z += -cos(angle) * speed * delta;
		trans->SetPosition(pos);		
		
		//��]��i�ޕ����ɍ��킹��
		auto quat = trans->GetQuaternion();
		quat = Quat(0.0f, sin((angle) / 2.0f), 0.0f, cos((angle) / 2.0f));
		trans->SetQuaternion(quat);

		//�p�x��n��
		actor->SetAngle(angle + XMConvertToRadians(90.0f));

	}

}
//end basecross
