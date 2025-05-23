/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprite::Sprite(shared_ptr<Stage>& stagePtr,wstring textureName,Vec2 size,Vec3 pos,Vec3 rot, Col4 color,int layer) :
		GameObject(stagePtr),
		m_textureName(textureName),
		m_size(size),
		m_pos(pos),
		m_rot(rot),
		m_color(color),
		m_layer(layer)
	{

	}

	Sprite::~Sprite()
	{
	}

	void Sprite::OnCreate()
	{
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 200.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ
		vector<VertexPositionColorTexture> m_vertices = { // 頂点データ
			//             座標                          ,頂点色,     UV座標
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> m_indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2, // ←これで一つのポリゴン(三角形)
			2, 1, 3  // ←こっちも
		};

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // スプライト用のドローコンポーネント
		m_drawComp->SetTextureResource(m_textureName);//テクスチャの名前指定
		m_drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_drawComp->SetDiffuse(m_color); // ポリゴンを色を設定する

		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
		m_trans->SetRotation(m_rot);


		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

		SetDrawLayer(m_layer);

	}

	void Sprite::OnUpdate()
	{
		
	}

	//カラーの数値を変更する
	void Sprite::SetTexture(wstring texture)
	{
		m_drawComp->SetTextureResource(texture);//テクスチャの名前指定
	}

	//カラーの数値を変更する
	void Sprite::SetColor(Col4 color)
	{
		m_color = color;
		m_drawComp->SetDiffuse(m_color);
	}
	//カラーの数値を取得させる
	Col4 Sprite::GetColor()
	{
		return m_color;
	}

	//自分自身を消去する
	void Sprite::MyDestroy()
	{
		GetStage()->RemoveGameObject<Sprite>(GetThis<Sprite>());
	}

}
//end basecross
