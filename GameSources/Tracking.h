/*!
@file Tracking.h
@brief �ǐ�
*/

#pragma once
#include "stdafx.h"
//#include"Ray.h"
namespace basecross {
	class Ray;
	class VecAStarIndex;
	class Node;

	enum MoveXorZ
	{
		move_X,
		move_Z
	};

	class Tracking :public StateBase,public AStar
	{
	private:
		Vec3 m_ownerPos;
		Vec3 m_ownerRot;
		Vec3 m_playerPos;
		Vec3 m_forward;
		Vec3 m_right;

		Vec2 m_moveSelPos;//�ǂ��ړ����Ă��邩�ۑ�����ϐ�

		float m_time;
		float m_directionRad;
		float m_aStarTime;//AStar�X�V���܂ł̃^�C���v���p�ϐ�
		float m_waitTime;
		float m_delta;

		
		int m_costRWall;
		int m_costLWall;
		int m_costFWall;
		int m_costDWall;

		int m_costRight;
		int m_costLeft;
		int m_costFod;
		int m_costDown;
		int m_count;
		int m_directionCount;

		int m_anger;//�{��l

		int m_roodCount;//��A*�̈ړ��łǂ̒i�K�ɂ��邩���߂�ϐ�
		//int m_moveXorZ;//x�����Ɉړ����Ă��邩z�����Ɉړ����Ă��邩�ۑ�����ϐ�
		//Vec3 m_targetPos;////���݂̖ړI�n��ۑ�����ϐ�
		Vec3 m_movePos;//�ǂ��ړ����邩�o����ϐ�(���̕ϐ���-1��1,0�̂ݓ���ėǂ����̂Ƃ���)

		bool m_rightFlag;
		bool m_leftFlag;
		bool m_upFlag;
		bool m_downFlag;

		//���b�V���֌W

		enum RUSH_FLOW//���b�V���̏�ԑJ��
		{
			Rush_Start,
			Rush_SetSpeed,
			Rush_Continue
		};

		bool m_rushMoveFlag;//���b�V����Ԃɂ��Ă������̃t���O
		bool m_XorZBefor;//�O�ǂ̕����ɐi��ł������ۑ�����ϐ�
		int m_rushFlow;//���b�V����Ԃ̃t���[��Ԃ�ۑ�����
		float m_rushSetSpeedCountTime;//�X�s�[�h�����鎞�Ԃ��v������ϐ�
		//

		shared_ptr<Transform> m_trans;

		weak_ptr<Ray>m_playerRay;

		vector<Vec3>m_posVec;
		vector<Vec3> m_tagetRootPos;//�ʂ铹�̔z��
		Vec3 m_tagetPos;//�ړI�n�̃��[���h���W(�g�p���Ă��Ȃ�)


		//AStarMap�̏�������z��
		vector<vector<VecAStarIndex>> m_unityMapDeta;

		//�O��Player��AStar���W
		Vec2 m_beforPlayerUnity;

		vector<vector<shared_ptr<Node>>> m_unityMap;//�}�b�v�̃m�[�h�z��
		vector<vector<int>> m_unityMapCSV;//AStarMap��CSV�f�[�^

		shared_ptr<AStar> m_aStar;//�o�H�T���̏������������|�C���^

	public:
		Tracking(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner),
			AStar(),
			m_ownerPos(0, 0, 0),
			m_ownerRot(0, 0, 0),
			m_playerPos(0, 0, 0),
			m_forward(0, 0, 1),
			m_right(1, 0, 0),
			m_time(0),
			m_waitTime(0.0f),
			m_directionRad(0),
			m_costRWall(0),
			m_costLWall(0),
			m_costFWall(0),
			m_costDWall(0),
			m_costRight(0),
			m_costLeft(0),
			m_costFod(0),
			m_costDown(0),
			m_count(0),
			m_directionCount(0),
			m_roodCount(0),
			m_aStarTime(0.0f),
			//m_moveXorZ(move_X),
			m_XorZBefor(false),
			m_rushFlow(Rush_Start),
			m_rushMoveFlag(false),
			m_rushSetSpeedCountTime(0.0f)
		{
		}

		virtual ~Tracking() {}
		void OnStart();
		void OnUpdate();
		void OnExit();

		void AStarMove();//A�X�^�[�̈ړ�����
		void nextSelLook(int right,int left,int up, int down,Vec2 enemyAStarPos,Vec2 playerAStarPos);//�ׂɕǂ��グ�Ă���}���z�[�������邩�m�F����

		void AngerSpeed(int anger);//�{��l�ɂ���ăX�s�[�h��ύX���鏈��

		vector<Vec3> RouteSearchNotA();

		bool LookAround(shared_ptr<Node> node, Vec2 goalPos);
		bool RushMoveChack(Vec3 pos, int vision);//�ːi���Ă������m�F����֐�
		void RushMove(bool onOff);


	};



	//AStar�Ǘ��p�̐�p�z��
	class VecAStarIndex
	{
	public:
		int addLenght;//�����Ă���}�X�ɍs���ɂ͌��ݒn�_����ǂ̂��炢�i�ނ̂�
		int toTagetLenght;//���̒n�_����ړI�n�ւ̋���
		int totalLenght;//�������o�R����ƖړI�n�ɍŒZ�ǂꂭ�炢�Œ�����
		bool use;//���܂Œʂ������Ƃ̂��鏊��

		VecAStarIndex(int addLenght, int toTagetLenght, int totalLenght, bool use) :
			addLenght(addLenght),
			toTagetLenght(toTagetLenght),
			totalLenght(totalLenght),
			use(use)
		{
		}
		~VecAStarIndex()
		{
		}
	};

	class AStarIndex
	{
	public:
		int x;
		int y;
		int Status;//�X�e�[�^�X
		int Cost;//�R�X�g
		int HeuristicCost;//�q���[���X�e�B�b�N�R�X�g
		int Score;//�X�R�A
		shared_ptr<AStarIndex> Parent;//�e�̃|�C���^


		AStarIndex(int x, int y, int Status, int Cost, int HeuristicCost, int Score, shared_ptr<AStarIndex> parent) :
			x(x),
			y(y),
			Status(Status),
			Cost(Cost),
			HeuristicCost(HeuristicCost),
			Score(Score),
			Parent(parent)
		{
			
		}
		~AStarIndex()
		{
		}


	};
}
//end basecross
