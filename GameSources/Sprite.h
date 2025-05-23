/*!
@file Sprite.h
@brief スプライト用のクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite :public GameObject
	{
	protected:
		//画像の表示サイズ
		float m_width;
		float m_heigth;
		int m_layer;
		Vec2 m_size;//画像の大きさ
		shared_ptr<PCTSpriteDraw> m_drawComp;//ドローコンポーネント

		//vector<VertexPositionColorTexture> m_vertices;
		//vector<uint16_t> m_indices;
		//shared_ptr<PCTSpriteDraw> m_draw;
		wstring m_textureName;//テクスチャの名前

		shared_ptr<Transform> m_trans;

		Vec3 m_pos;
		Vec3 m_rot;
		Col4 m_color;


	public:
		Sprite(shared_ptr<Stage>& stagePtr,wstring textureName,Vec2 size,Vec3 pos = Vec3(0.0f,0.0f,0.0f), Vec3 rot = Vec3(0.0f,0.0f,0.0f),Col4 color = Col4(1.0f,1.0f,1.0f,1.0f), int layer = 1);//コンストラクタ
		virtual ~Sprite();//デストラクタ

		virtual void OnCreate()override;//作成
		virtual void OnUpdate()override;//更新

		void SetColor(Col4 coler);//セッター
		void SetTexture(wstring Texture);//セッター
		void MyDestroy();//自分自身を消す
		Col4 GetColor();//ゲッター

	};


}
//end basecross
