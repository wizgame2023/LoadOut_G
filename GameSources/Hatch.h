/*!
@file Hatch.h
@brief ハッチ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Hatch :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		//weak_ptr<MapManager> m_mapManager;//マップマネージャー

		//shared_ptr<ClearObject> m_clearObject;//透明な壁
		//shared_ptr<WaterPillar> m_waterPillar;//水柱

		int m_charen;//テクスチャを変えるフラグ

		float m_time;//時間を測るために必要

	public:
		Hatch(shared_ptr<Stage>& stagePtr);
		~Hatch();

		void OnCreate()override;
		void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;//当たった時に処理
	};


}
//end basecross
