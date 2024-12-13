/*!
@file PillarEffect.cpp
@brief 柱上のエフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	PillarEffect::PillarEffect(const shared_ptr<Stage>& stagePtr,Vec3 pos, wstring textureName,Vec2 velocity, int square):
		GameObject(stagePtr),
		m_height(10.0f),
		m_topRadius(4.5f),
		m_bottomRadius(4.5f),
		m_square(square),
		m_loops(1.0f, 1.0f),
		m_topColor(1.0f, 1.0f, 1.0f, 1.0f),
		m_bottomColor(1.0f, 1.0f, 1.0f, 1.0f),
		m_textureName(textureName),
		m_scrollVelocity(velocity),
		m_pos(pos)
	{

	}
	//デストラクタ
	PillarEffect::~PillarEffect()
	{
	}

	void PillarEffect::InitializeVertices()
	{
		////ポリゴンの頂点データ
		m_vertices.clear();
		m_vertices.reserve((m_square+1)*2);
		for (int i = 0; i <= m_square; i++)
		{
			Vec3 pos;//頂点座標
			VertexPositionColorTexture vPCT; // 1頂点のデータ

			// 上下の頂点の共通データ
			float rad = XMConvertToRadians(360.0f * i / m_square);
			//uv座標
			float u = (m_loops.x * static_cast<float>(i) / static_cast<float>(m_square))+m_test.x;
			float v = m_loops.y+m_test.y;

			// 上の円の頂点
			pos = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_topRadius + Vec3(0.0f, m_height, 0.0f)+m_pos; // Y座標をm_height分ずらす
			vPCT = VertexPositionColorTexture(pos, m_topColor, Vec2(u, 0)); // V座標を最小値にする
			m_vertices.push_back(vPCT);

			// 下の円の頂点
			pos = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_bottomRadius+m_pos;
			vPCT = VertexPositionColorTexture(pos, m_bottomColor, Vec2(u, v)); // V座標を最大値にする
			m_vertices.push_back(vPCT);

		}

		// 頂点インデックス(頂点をつなげる順番)
		const vector<uint16_t> baseIndices = {
			 2, 1, 0,
			 3, 1, 2,
		};

		m_indices.clear();
		m_indices.reserve(m_square * baseIndices.size());//度数×頂点インデックス
		for (int i = 0; i < m_square; i++)
		{
			// baseIndicesの数だけループ
			for (auto baseIndex : baseIndices)
			{
				//頂点インデックスが１つの四角ごとに２ずれるためこうしている
				m_indices.push_back(baseIndex + (2 * i));
			}
		}

	}

	void PillarEffect::OnCreate()
	{
		m_pos.y = 0;
		InitializeVertices();

		m_drawComp = AddComponent<BcPCTStaticDraw>();//Bc付きでないといけない
		m_drawComp->SetOriginalMeshUse(true);
		m_drawComp->CreateOriginalMesh(m_vertices, m_indices);
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);//テクスチャをループさせる
		m_drawComp->SetDepthStencilState(DepthStencilState::Read);//自分のオブジェクト内のZバッファを無視
		m_drawComp->SetBlendState(BlendState::Additive);
		m_drawComp->SetTextureResource(m_textureName);

		SetAlphaActive(true);
		m_isUpdate = false;

	}

	void PillarEffect::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += m_scrollVelocity * delta;//uv座標をずらしている
			auto test = 0;
		}
		//m_test += m_scrollVelocity * delta;//uv座標をずらしている


		if (m_isUpdate)
		{
			m_isUpdate = false;	
			InitializeVertices();
		}

		m_drawComp->UpdateVertices(m_vertices);

	}

	void PillarEffect::UpdateTest(bool OnOff)
	{
		m_isUpdate = OnOff;
	}

	//void PillarEffect::SetScrollPerSecond()

}
//end basecross
