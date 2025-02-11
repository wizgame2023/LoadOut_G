/*!
@file Actor.h
@brief PlayerやEnemyなど動くオブジェクトの親クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomItem :public Actor
	{
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転度
		//const int m_oneBlock;//このゲームの単位(この数値をセル座標では１とする)
	public:

		RandomItem(shared_ptr<Stage>& StagePtr, Vec3 pos);//コンストラクタ
		~RandomItem();//デストラクタ

		virtual void OnCreate() override;//開始する際に呼び出す関数
		virtual void OnUpdate() override;

		void OnCollisionEnter(shared_ptr<GameObject>& obj)override;

	};
}
