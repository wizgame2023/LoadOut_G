/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapItem::MiniMapItem(shared_ptr<Stage>& stagePtr,weak_ptr<Item> parentObj, wstring textureName, Vec2 size,int layer, Vec3 pos,  Vec3 rot) :
		GameObject(stagePtr),
		m_textureName(textureName),
		m_parentObj(parentObj),
		m_size(size),
		m_pos(pos),
		m_layer(layer)
	{

	}

	MiniMapItem::~MiniMapItem()
	{
	}

	void MiniMapItem::OnCreate()
	{
		// ポリゴンの自作
		m_color = Col4(1, 1, 1, 1); // ポリゴンの色
		const float w = 200.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ
		vector<VertexPositionColorTexture> m_vertices = { // 頂点データ
			//             座標                          ,頂点色,     UV座標
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), m_color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), m_color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), m_color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), m_color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> m_indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2, // ←これで一つのポリゴン(三角形)
			2, 1, 3  // ←こっちも
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // スプライト用のドローコンポーネント
		drawComp->SetTextureResource(m_textureName);//テクスチャの名前指定
		drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);


		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

		SetDrawLayer(m_layer);

	}

	void MiniMapItem::OnUpdate()
	{
		//元となるオブジェクトが消えた場合、自分も消える
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<MiniMapItem>(GetThis<MiniMapItem>());
		}
	}

}
//end basecross
