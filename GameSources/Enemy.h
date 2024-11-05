/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Enemy :public GameObject
	{
	private:
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		float m_speed;
		// 現在のステートを入れておく
		shared_ptr<StateBase> m_CurrentSt;

		// 次のステートを入れておく、ステートが入ると即座に切り替わる
		shared_ptr<StateBase> m_NextSt;

	public:
		//コンストラクタ・デストラクタ
		Enemy(const shared_ptr<Stage>& StagePtr);
		~Enemy();

		//生成・更新・削除
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		// m_NextStateに代入する
		template <typename NextState>
		void ChangeState()
		{
			m_NextSt.reset();

			m_NextSt = makeShared<NextState>(GetThis<Enemy>());
		}
		float GetSpeed();
	};

}
//end basecross
