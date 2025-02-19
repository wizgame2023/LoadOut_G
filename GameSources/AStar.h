/*!
@file AStar.h
@brief �o�H�T������
*/

#pragma once
#include "stdafx.h"
#include "MapManager.h"

namespace basecross {
	class Node;
	class AStar
	{
	private:
		bool m_aStarFirst;//AStar�̈ړ��������n�߂Ă��ۑ�����ϐ�
		bool m_XorZ;//X(false)�����ɐi��ł��邩Z(true)�����ɐi��ł��邩�̕ϐ�

		int m_roopCount;//�o�H�T�������񐔂𐔂���ϐ�

		Vec3 m_targetPos;//�ړI�n�̃��[���h���W
		Vec3 m_movePos;//�ǂ��ړ����邩�o����ϐ�(���̕ϐ���-1��1,0�̂ݓ���ėǂ����̂Ƃ���)

		vector<vector<shared_ptr<Node>>> m_unityMap;//�}�b�v�̃m�[�h�z��
		vector<vector<int>> m_unityMapCSV;//AStarMap��CSV�f�[�^
		vector<Vec3> m_tagetRootPos;//�ʂ铹�̔z��

		weak_ptr<MapManager> m_mapManager;//�}�b�v�}�l�[�W���[

	public:
		AStar();//�R���X�g���N�^
		~AStar();//�f�X�g���N�^

		vector<Vec3> RouteSearch(Vec3 startPos,Vec3 goalPos);//�o�H�T��
		bool MoveActor(shared_ptr<Actor> actor,vector<Vec3> routePos,int& routeCount,float speed);//�ړ�����
		bool LookAround(shared_ptr<Node> parent, Vec2& goalPos);//������m�F���鏈��
		bool GetMoveXorZ();//��X,Z�̂ǂ����̕����ɐi��ł��邩�n���֐�
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
