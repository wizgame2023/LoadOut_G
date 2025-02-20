/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "BillBoard.h"

namespace basecross {

	enum ABILITY
	{
		normal,
		perspective,
		rush,
	};

	enum ANGER
	{
		ANGER_NONE,
		ANGER_LOW,
		ANGER_MIDDLE,
		ANGER_HI
	};

	class Enemy :public Actor
	{
	private:
		Vec3 m_pos;
		const Vec3 m_startPos;
		Vec3 m_playerPos;
		Vec3 m_scale;

		float m_speed;
		float m_angle;

		int m_ability;
		int m_anger;//どれくらい怒っているのかを表す変数(ステータスが上がる)

		bool m_startPop;//最初のスポーンかリポップかを表す変数


		//シャドウマップ
		shared_ptr<Shadowmap> m_ptrShadow;
		//メッシュデータ
		shared_ptr<PNTBoneModelDraw> m_ptrDraw;

		// 現在のステートを入れておく
		shared_ptr<StateBase> m_CurrentSt;

		// 次のステートを入れておく、ステートが入ると即座に切り替わる
		shared_ptr<StateBase> m_NextSt;

		shared_ptr<Ray>m_forwardRay;
		shared_ptr<Ray>m_leftRay;
		shared_ptr<Ray>m_playerRay;

		shared_ptr<BillBoard> m_billBoard;
		shared_ptr<MapManager> m_mapMgr;

	public:
		//コンストラクタ・デストラクタ
		Enemy(shared_ptr<Stage>& StagePtr);
		Enemy(shared_ptr<Stage>& StagePtr, Vec3 pos, bool startpop = true, int ability = normal,int anger = 0);

		~Enemy();
		//生成・更新・削除
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		// m_NextStateに代入する
		template <typename NextState>
		void ChangeState()
		{
			m_NextSt.reset();

			m_NextSt = make_shared<NextState>(GetThis<Enemy>());
		}
		void ChangeAbility(int state);//ステートを変更する処理
		float GetSpeed();
		void SetSpeed(float speed);
		float GetAngle();
		int GetAbility();
		int GetAnger();//怒り値を渡す
		float GetDistance(Vec3 a, Vec3 b);
		void SetAngle(float angle);
		void GetGameOverScene();
		Vec3 GetPlayerPos();
		Vec3 GetStartPos();
		shared_ptr<Ray> GetForwardRay();
		shared_ptr<Ray> GetPlayerRay();
		shared_ptr<StateBase> GetNowState();
		shared_ptr<MapManager> GetMapMgr();
	};


}
//end basecross
