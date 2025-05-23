/*!
@file SpriteNum.cpp
@brief 数字を出すスプライト 作成途中
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpriteNum::SpriteNum(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,int num,Vec3 pos, Vec3 rot):
		GameObject(stagePtr),
		m_textureName(textureName),
		m_size(size),
		m_pos(pos),
		m_rot(rot),
		m_num(num)
	{

	}

	SpriteNum::~SpriteNum()
	{

	}

	void SpriteNum::OnCreate()
	{
		// ポリゴンの自作
		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 200.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ
		m_vertices = { // 頂点データ

			//             座標                          ,頂点色,     UV座標
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f*(m_num-1), 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f*m_num, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f*(m_num-1), 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f*m_num, 1.0f)}, // 3
		};

		m_indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2, // ←これで一つのポリゴン(三角形)
			2, 1, 3  // ←こっちも
		};

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // スプライト用のドローコンポーネント
		m_drawComp->SetTextureResource(m_textureName);//テクスチャの名前指定
		m_drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);


		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

		//m_vertices[0].textureCoordinate = Vec2(0.0f, 0.0f);

		////時間経過で数値が変わるようにする
		//for (auto num : m_vertices)
		//{

		//}

	}

	void SpriteNum::OnUpdate()
	{
		Col4 color(1, 1, 1, 1); // ポリゴンの色

		m_vertices = { // 頂点データ

			//             座標                          ,頂点色,     UV座標
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f * (m_num - 1), 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f * m_num, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f * (m_num - 1), 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f * m_num, 1.0f)}, // 3
		};

		GetComponent<PCTSpriteDraw>()->UpdateVertices(m_vertices);//頂点データ更新

	}

	void SpriteNum::SetNum(int num)
	{
		m_num = num;
	}

}
//end basecross
