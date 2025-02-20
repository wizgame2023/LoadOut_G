/*!
@file Manhole.h
@brief マンホール
*/

#pragma once
#include "stdafx.h"
#include "ClearObject.h"
#include "WaterPillar.h"
#include "BillBoardGauge.h"

namespace basecross {
	class Manhole :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		weak_ptr<MapManager> m_mapManager;//マップマネージャー
		shared_ptr<MapManager> m_lockMapManager;//マップマネージャー

		shared_ptr<ClearObject> m_clearObject;//透明な壁
		shared_ptr<WaterPillar> m_waterPillar;//水柱
		shared_ptr<BillBoard> m_billBoard;//ビルボード
		shared_ptr<BillBoardGauge> m_billBoardSecond;//2つめのビルボード

		shared_ptr<Stage> m_stage;//今いるステージ

		vector<weak_ptr<Enemy>> m_upEnemyVec;//打ち上げる敵ポインタの配列

		int m_charen;//進行度

		float m_coolTime;//時間を測るために必要
		float m_stanbyTime;//時間を測るために必要
		float m_blinkingTime;//点滅する時間を測る
		float m_billBoardTime;//ビルボードが出ている時間を測る
		float m_playerUpTime;//マンホールから出てプレイヤーが踏むと上がる時間計測

		bool m_playerStanbyFlag;//プレイヤーが踏むかまつフラグ
		bool m_UpdateFlag;//アップデートするかのフラグ

	public:
		//マンホールの状態遷移
		enum STATE
		{
			Manhole_None,
			Manhole_Start,
			Manhole_SoonUp,
			Manhole_Up,
			Manhole_Used
		};

		Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos);
		~Manhole();

		void OnCreate()override;
		void OnUpdate()override;

		void ManholeTransition();

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;//当たった時に処理
		void OnCollisionExcute(shared_ptr<GameObject>& other)override;//入り続けているときに処理
		void OnCollisionExit(shared_ptr<GameObject>& other)override;//離れたときに処理

		//コリジョンによって敵やプレイヤーが当たった時の処理
		void CollisionUpManhole(shared_ptr<Enemy> enemy,shared_ptr<Player> player);

		int GetState();//ゲッター
		void SetUpdateSwitch(bool onOff);//アップデートするかのセッター
	};

}
//end basecross
