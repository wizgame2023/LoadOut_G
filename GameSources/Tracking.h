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
	class Tracking :public StateBase
	{
	private:
		Vec3 m_ownerPos;
		Vec3 m_ownerRot;
		Vec3 m_playerPos;
		Vec3 m_forward;
		Vec3 m_right;
		float m_time;
		float m_directionRad;

		
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

		bool m_rightFlag;
		bool m_leftFlag;
		bool m_upFlag;
		bool m_downFlag;


		shared_ptr<Transform> m_trans;

		weak_ptr<Ray>m_playerRay;

		vector<Vec3>m_posVec;
		vector<Vec3> m_tagetRootPos;//�ʂ铹�̔z��
		Vec3 m_tagetPos;//�ړI�n�̃��[���h���W


		//AStarMap�̏�������z��
		vector<vector<VecAStarIndex>> m_aStarMapDeta;

	public:
		Tracking(const shared_ptr<Enemy> ptrOwner) :
			StateBase(ptrOwner),
			m_ownerPos(0, 0, 0),
			m_ownerRot(0, 0, 0),
			m_playerPos(0, 0, 0),
			m_forward(0, 0, 1),
			m_right(1, 0, 0),
			m_time(0),
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
			m_directionCount(0)
		{
		}

		virtual ~Tracking() {}
		void OnStart();
		void OnUpdate();
		void OnExit();

		Vec3 MoveCost();
		void nextSelLook(int right,int left,int up, int down,Vec2 enemyAStarPos,Vec2 playerAStarPos);//�ׂɕǂ��グ�Ă���}���z�[�������邩�m�F����

		void Navi();
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


}
//end basecross
