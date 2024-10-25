/*!
@file State.h
@brief ステートマシン
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//Enemyクラスの前方宣言
	class Enemy;

	//ステートの基底クラス
	class StateBase
	{
	protected:
		// ステートの所有者用
		shared_ptr<Enemy> m_Owner;
	public:
		//StateBaseのコンストラクタ・デストラクタの宣言
		StateBase(const shared_ptr<Enemy> OwnerPtr) :
			m_Owner(OwnerPtr)
		{

		}
		virtual ~StateBase() {}

		virtual void OnStart() = 0;//ステートを実行するとき最初の一回だけ行う
		virtual void OnUpdate() = 0;//ステートを実行するとき毎フレーム行う
		virtual void OnExit() = 0;//ステートが切り替わる時に行う
	};

}
//end basecross
