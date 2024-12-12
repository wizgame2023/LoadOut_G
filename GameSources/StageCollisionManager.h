/*!
@file StageCollisionManager.h
@brief コリジョンの管理
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollisionManager :public GameObject
	{
	private:
		bool m_CollisionSwhich;

		void CollisionActive(bool On);//ステージ上の有効なコリジョン範囲を決める

	public:
		StageCollisionManager(shared_ptr<Stage>& stagePtr);
		~StageCollisionManager();

		void OnCreate()override;
		void OnUpdate()override;
		void SetCollisionSwhich(bool On);//コリジョン範囲を決めるためのフラグを取得する関数

	};
}