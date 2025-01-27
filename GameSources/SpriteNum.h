/*!
@file Sprite.h
@brief スプライト用のクラス
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class SpriteNum :public Sprite
	{
	private:
		int m_num;//表示する数値

		shared_ptr<Transform> m_trans;

		vector<uint16_t> m_indices;
		vector<VertexPositionColorTexture> m_vertices;
	public:
		SpriteNum(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,int num,  Vec3 pos=Vec3(0.0f,0.0f,0.0f), Vec3 rot=Vec3(0.0f,0.0f,0.0f), Col4 color=Col4(1.0f,1.0f,1.0f,1.0f), int layer=1);//コンストラクタ
		~SpriteNum();//デストラクタ

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void SetNum(int num);//数字の更新

	};


}
//end basecross
