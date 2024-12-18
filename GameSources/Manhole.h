/*!
@file Manhole.h
@brief マンホール
*/

#pragma once
#include "stdafx.h"
#include "ClearObject.h"
#include "WaterPillar.h"

namespace basecross {
	class Manhole :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		weak_ptr<MapManager> m_mapManager;//マップマネージャー

		shared_ptr<ClearObject> m_clearObject;//透明な壁
		shared_ptr<WaterPillar> m_waterPillar;//水柱

		int m_charen;//進行度

		float m_coolTime;//時間を測るために必要
		float m_stanbyTime;//時間を測るために必要
		float m_blinkingTime;//点滅する時間を測る

		bool m_playerStanbyFlag;//プレイヤーが踏むかまつフラグ

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
		void OnCollisionExit(shared_ptr<GameObject>& other)override;//離れたときに処理

		int GetState();//ゲッター
	};

}
//end basecross
