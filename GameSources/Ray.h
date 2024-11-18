/*!
@file Ray.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RaySphere;//プロトタイプ宣言みたいなもの応急処置みたいなものだからあまり多用したくない

	class Ray :public GameObject
	{
	private:
		vector<weak_ptr<GameObject>> m_discoveryObj;//ぶつかったオブジェクトのアドレスを取る

		float m_countTime;//レイスフィアを生成するクールタイムを測る変数
		float m_range;//レイの射程
		float m_angle;//角度

		weak_ptr<Actor> m_parentObj;//親オブジェクト

		vector<weak_ptr<RaySphere>> m_raySphere;//ぶつかったオブジェクトのアドレスを取る

	public:
		Ray(shared_ptr<Stage>& stagePtr,shared_ptr<Actor> parentObj,float range);
		~Ray();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void ResetDisObj();//レイスフィアの当たったオブジェクトのポインタ配列のリセット
		void ResetRaySphere();//出ているレイスフィアを全て削除



		void SetAngle(float angle);//角度を入れるセッター
		float GetAngle();//角度を渡すゲッター
		void SetDisObj(vector<weak_ptr<GameObject>> discoveryObj);//レイスフィアが取得したオブジェクトを受け取るセッター
		vector<weak_ptr<GameObject>> GetDisObj();//取得したオブジェクトを渡す

	};

}
//end basecross
