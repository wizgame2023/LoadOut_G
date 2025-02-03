/*!
@file Actor.h
@brief PlayerやEnemyなど動くオブジェクトの親クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Actor :public GameObject
	{
	private:
		float m_angle;//角度

	protected:
		bool m_move;//動くか動かないかのフラグ
		Vec2 m_selPosNow;//現在のセル座標を保存する変数
		Vec2 m_selPosBefor;//前いたセル座標を保存する変数

	public:
		Actor(shared_ptr<Stage>& stagePtr);
		~Actor();

		virtual void OnUpdate()override;

		virtual float GetAngle();
		Vec2 GetSelPosNow();//現在のセル座標のゲッター
		Vec2 GetSelPosBefor();//前にいたセル座標のゲッター

		virtual void SetAngle(float angle);

		void MoveSwitch(bool onOff);//動いていいかのフラグ

		//void OnCreate()override;
		//void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
//end basecross
