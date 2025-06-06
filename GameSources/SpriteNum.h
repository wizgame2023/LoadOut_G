/*!
@file Sprite.h
@brief スプライト用のクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpriteNum :public GameObject
	{
	private:
		//画像の表示サイズ
		float m_width;
		float m_heigth;
		int m_layer;
		Vec2 m_size;//画像の大きさ

		int m_num;//表示する数値


		//vector<VertexPositionColorTexture> m_vertices;
		//vector<uint16_t> m_indices;
		//shared_ptr<PCTSpriteDraw> m_draw;
		wstring m_textureName;//テクスチャの名前

		shared_ptr<Transform> m_trans;

		Vec3 m_pos;
		Vec3 m_rot;
		Col4 m_color;

		shared_ptr<PCTSpriteDraw> m_drawComp;//ドローコンポーネント

		vector<uint16_t> m_indices;
		vector<VertexPositionColorTexture> m_vertices;


	public:
		SpriteNum(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,int num,Vec3 pos=Vec3(0.0f,0.0f,0.0f), Vec3 rot=Vec3(0.0f,0.0f,0.0f));//コンストラクタ
		~SpriteNum();//デストラクタ

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void SetNum(int num);//数字の更新

	};


}
//end basecross
