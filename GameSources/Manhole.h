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

		int m_charen;//テクスチャを変えるフラグ

		float m_time;//時間を測るために必要

	public:
		Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos);
		~Manhole();

		void OnCreate()override;
		void OnUpdate()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;//当たった時に処理
	};

}
//end basecross
