/*!
@file AStar.h
@brief �o�H�T������
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Node;
	class AStar :GameObject
	{
	private:
		Vec3 m_startPos;//�ŏ��̃|�W�V����
		Vec3 m_goalPos;//�S�[������|�W�V����

		//�O��Player��AStar���W
		Vec2 m_beforPlayerUnity;

		vector<vector<shared_ptr<Node>>> m_unityMap;//�}�b�v�̃m�[�h�z��
		vector<vector<int>> m_unityMapCSV;//AStarMap��CSV�f�[�^

	public:
		AStar(shared_ptr<Stage>& stagePtr,Vec3 startPos,Vec3 goalPos);//�R���X�g���N�^
		~AStar();//�f�X�g���N�^

		void OnCreate() override;//�쐬
		void OnUpdate() override;//�X�V

		bool LookAround(shared_ptr<Node> parent, Vec2 goalPos);//������m�F���鏈��
	};

	enum STATUS//�X�e�[�^�X
	{
		Status_None,
		Status_Open,
		Status_Closed
	};

	//�m�[�h�f�[�^
	class Node
	{
	public:
		int x;
		int y;
		int Status;//�X�e�[�^�X
		int Cost;//�R�X�g
		int HeuristicCost;//�q���[���X�e�B�b�N�R�X�g
		int Score;//�X�R�A
		shared_ptr<Node> Parent;//�e�̃|�C���^

		Node(int x, int y, int Status, int Cost, int HeuristicCost, int Score, shared_ptr<Node> parent) :
			x(x),
			y(y),
			Status(Status),
			Cost(Cost),
			HeuristicCost(HeuristicCost),
			Score(Score),
			Parent(parent)
		{

		}
		~Node()
		{
		}
	};

}
//end basecross
