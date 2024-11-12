/*!
@file Ray.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Ray :public GameObject
	{
	private:
		vector<weak_ptr<GameObject>> m_discoveryObj;//ぶつかったオブジェクトのアドレスを取る

		float m_countTime;//レイスフィアを生成するクールタイムを測る変数
		float m_range;//レイの射程

		//weak_ptr<Enemy> m_parentObj;//親オブジェクト
		weak_ptr<Enemy> m_parentObj;

	public:
		Ray(shared_ptr<Stage>& stagePtr,shared_ptr<Enemy> parentObj,float range);
		~Ray();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void SetDisObj(vector<weak_ptr<GameObject>> discoveryObj);//レイスフィアが取得したオブジェクトを受け取るセッター
		vector<weak_ptr<GameObject>> GetDisObj();//取得したオブジェクトを渡す

	};

}
//end basecross
