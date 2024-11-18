/*!
@file Sprite.h
@brief 動くオブジェクトをミニマップに表示
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class MiniMapActor :public Sprite
	{
	private:
		Vec3 m_miniMapStartPos;//ミニマップの初期位置
		float m_mapSize;//マップの大きさ(直径)
		float m_miniMapSize;//ミニマップの大きさ(直径)
		float m_mapMagnification;//ミニマップ用の倍率

		weak_ptr<Actor> m_parentObj;//親オブジェクト
		//Vec3 m_miniMapPos;
	public:
		MiniMapActor(shared_ptr<Stage>& stagePtr,weak_ptr<Actor> parentObj, wstring textureName, Vec2 size,
			Vec3 miniMapStartPos,float mapSize,float miniMapSize,
			Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f));//コンストラクタ
		~MiniMapActor();//デストラクタ

		//void OnCreate()override;//作成
		void OnUpdate()override;//更新
	};


}
//end basecross
