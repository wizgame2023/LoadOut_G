/*!
@file AStar.cpp
@brief �o�H�T������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�R���X�g���N�^
	AStar::AStar(shared_ptr<Stage>& stagePtr,Vec3 startPos,Vec3 goalPos) :
		GameObject(stagePtr),
		m_startPos(startPos),
		m_goalPos(goalPos)
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


}
//end basecross
