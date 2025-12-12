/*!
@file Actor.h
@brief PlayerやEnemyなど動くオブジェクトの親クラス
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Actor :public GameObject
	{
	private:
		float m_angle; // 角度

	protected:
		bool m_move;		// 動くか動かないかのフラグ
		Vec2 m_selPosNow;   // 現在のセル座標を保存する変数
		Vec2 m_selPosBefor; // 前いたセル座標を保存する変数

	public:
		Actor(const shared_ptr<Stage>& stagePtr);
		~Actor();

		virtual void OnUpdate()override;

		virtual float GetAngle(); // 向いている方向のゲッタ
		Vec2 GetSelPosNow();	  // 現在のセル座標のゲッタ
		Vec2 GetSelPosBefor();    // 前にいたセル座標のゲッタ

		virtual void SetAngle(float angle); // 向いている方向のセッタ

		void MoveSwitch(bool onOff); // 動いていいかのフラグ

	};

}
//end basecross
