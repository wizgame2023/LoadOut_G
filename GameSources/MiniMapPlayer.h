/*!
@file Sprite.h
@brief スプライト用のクラス
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class MiniMapPlayer :public Sprite
	{
	private:
		Vec3 m_miniMapStartPos;//ミニマップの初期位置
		float m_mapSize;//マップの大きさ(直径)
		float m_miniMapSize;//ミニマップの大きさ(直径)
		float m_mapMagnification;//ミニマップ用の倍率
		//Vec3 m_miniMapPos;
	public:
		MiniMapPlayer(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,
			Vec3 miniMapStartPos,float mapSize,float miniMapSize,
			Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f));//コンストラクタ
		~MiniMapPlayer();//デストラクタ

		//void OnCreate()override;//作成
		void OnUpdate()override;//更新
	};


}
//end basecross
