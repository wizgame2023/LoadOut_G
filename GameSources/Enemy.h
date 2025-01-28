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

		bool m_startPop;//最初のスポーンかリポップかを表す変数



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
		Enemy(shared_ptr<Stage>& StagePtr, Vec3 pos, bool startpop = true, int ability = normal);

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
		float GetSpeed();
		float GetAngle();
		int GetAbility();
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
