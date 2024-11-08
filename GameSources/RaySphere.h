/*!
@file RaySphere.h
@brief レイ　視界
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RaySphere :public GameObject
	{
	private:
		vector<weak_ptr<GameObject>> m_discoveryObj;//ぶつかったオブジェクトのアドレスを取る 出来れば静的変数にしたい

		float m_range;//視界の射程
		float m_move;//元居た地点からどれくらい移動したか測る変数
		weak_ptr<GameObject> m_parentObj;//親オブジェクト

		Vec3 m_pos;//位置
		float m_rad;//角度

	public:
		RaySphere(shared_ptr<Stage>& stagePtr, Vec3 pos, float angle,weak_ptr<GameObject> parentObj);//コンストラクタ
		~RaySphere();//デストラクタ

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		vector<weak_ptr<GameObject>> GetDisObj();//取得したオブジェクトを渡す

	};

}
//end basecross
