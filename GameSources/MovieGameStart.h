/*!
@file MovieGameStart.h
@brief ゲーム開始時のムービ用
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include"Movie.h"

namespace basecross {
	class MovieGameStart :public Movie
	{
	private:
		int m_count;					// ムービーの進行度
		weak_ptr<ViewBase> m_StageView; // ステージのビュー(ゲームプレイ用)
		float m_mapSize;				// マップのサイズ
		float m_speed;

	public:
		MovieGameStart(shared_ptr<Stage>& stagePtr,float mapSize,float speed = 50.0f);
		~MovieGameStart();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override; // 削除時処理

		void CameraChange()override; // ムービー用のカメラに変更させる処理
	};

}
//end basecross
