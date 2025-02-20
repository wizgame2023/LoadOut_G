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

		Vec2 m_moveSelPos;//どう移動しているか保存する変数

		float m_time;
		float m_directionRad;
		float m_aStarTime;//AStar更新時までのタイム計測用変数
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

		int m_anger;//怒り値

		int m_roodCount;//今A*の移動でどの段階にいるか決める変数
		//int m_moveXorZ;//x方向に移動しているかz方向に移動しているか保存する変数
		//Vec3 m_targetPos;////現在の目的地を保存する変数
		Vec3 m_movePos;//どう移動するか覚える変数(中の変数は-1か1,0のみ入れて良いものとする)

		bool m_rightFlag;
		bool m_leftFlag;
		bool m_upFlag;
		bool m_downFlag;

		//ラッシュ関係

		enum RUSH_FLOW//ラッシュの状態遷移
		{
			Rush_Start,
			Rush_SetSpeed,
			Rush_Continue
		};

		bool m_rushMoveFlag;//ラッシュ状態にしていいかのフラグ
		bool m_XorZBefor;//前どの方向に進んでいたか保存する変数
		int m_rushFlow;//ラッシュ状態のフロー状態を保存する
		float m_rushSetSpeedCountTime;//スピードを入れる時間を計測する変数
		//

		shared_ptr<Transform> m_trans;

		weak_ptr<Ray>m_playerRay;

		vector<Vec3>m_posVec;
		vector<Vec3> m_tagetRootPos;//通る道の配列
		Vec3 m_tagetPos;//目的地のワールド座標(使用していない)


		//AStarMapの情報を入れる配列
		vector<vector<VecAStarIndex>> m_unityMapDeta;

		//前のPlayerのAStar座標
		Vec2 m_beforPlayerUnity;

		vector<vector<shared_ptr<Node>>> m_unityMap;//マップのノード配列
		vector<vector<int>> m_unityMapCSV;//AStarMapのCSVデータ

		shared_ptr<AStar> m_aStar;//経路探査の処理が入ったポインタ

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

		void AStarMove();//Aスターの移動処理
		void nextSelLook(int right,int left,int up, int down,Vec2 enemyAStarPos,Vec2 playerAStarPos);//隣に壁か上げているマンホールがあるか確認する

		void AngerSpeed(int anger);//怒り値によってスピードを変更する処理

		vector<Vec3> RouteSearchNotA();

		bool LookAround(shared_ptr<Node> node, Vec2 goalPos);
		bool RushMoveChack(Vec3 pos, int vision);//突進していいか確認する関数
		void RushMove(bool onOff);


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
