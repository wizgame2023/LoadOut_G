/*!
@file Sprite.h
@brief スプライト用のクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapItem :public GameObject
	{
	protected:
		//画像の表示サイズ
		float m_width;
		float m_heigth;
		int m_layer;
		Vec2 m_size;//画像の大きさ

		wstring m_textureName;//テクスチャの名前

		Vec3 m_pos;
		Vec3 m_rot;
		Col4 m_color;

		weak_ptr<Battery> m_parentObj;//元となるオブジェクトを保管する変数

	public:
		MiniMapItem(shared_ptr<Stage>& stagePtr,weak_ptr<Battery> parentObj, wstring textureName, Vec2 size,int layer = 1, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f));//コンストラクタ
		virtual ~MiniMapItem();//デストラクタ

		virtual void OnCreate()override;//作成
		virtual void OnUpdate()override;//更新

	};


}
//end basecross
