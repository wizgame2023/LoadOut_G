/*!
@file Tracking.h
@brief 追跡
*/

#pragma once
#include "stdafx.h"
//#include"Ray.h"
namespace basecross {
	class Ray;
	class VecAStarIndex;
	class Node;
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

		int m_roodCount;//今A*の移動でどの段階にいるか決める変数

		bool m_rightFlag;
		bool m_leftFlag;
		bool m_upFlag;
		bool m_downFlag;


		shared_ptr<Transform> m_trans;

		weak_ptr<Ray>m_playerRay;

		vector<Vec3>m_posVec;
		vector<Vec3> m_tagetRootPos;//通る道の配列
		Vec3 m_tagetPos;//目的地のワールド座標


		//AStarMapの情報を入れる配列
		vector<vector<VecAStarIndex>> m_aStarMapDeta;

		//前のPlayerのAStar座標
		Vec2 m_beforPlayerAStar;

		vector<vector<shared_ptr<Node>>> m_unityMap;//マップのノード配列
		vector<vector<int>> m_aStarMapCSV;//AStarMapのCSVデータ

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
			m_directionCount(0),
			m_roodCount(0)
		{
		}

		virtual ~Tracking() {}
		void OnStart();
		void OnUpdate();
		void OnExit();

		void nextSelLook(int right,int left,int up, int down,Vec2 enemyAStarPos,Vec2 playerAStarPos);//隣に壁か上げているマンホールがあるか確認する

		vector<Vec3> AStar();

		bool LookAround(shared_ptr<Node> node, Vec2 goalPos);

	};


	//AStar管理用の専用配列
	class VecAStarIndex
	{
	public:
		int addLenght;//さしているマスに行くには現在地点からどのくらい進むのか
		int toTagetLenght;//その地点から目的地への距離
		int totalLenght;//そこを経由すると目的地に最短どれくらいで着くか
		bool use;//今まで通ったことのある所か

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
		int Status;//ステータス
		int Cost;//コスト
		int HeuristicCost;//ヒューリスティックコスト
		int Score;//スコア
		shared_ptr<AStarIndex> Parent;//親のポインタ

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
