/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BillBoardGauge::BillBoardGauge(const shared_ptr<Stage>& StagePtr,
		shared_ptr<GameObject>& actorPtr, wstring spriteName,int layer, float pushY, Vec3 scale) :
		BillBoard(StagePtr, actorPtr, spriteName,layer, pushY, scale)
	{

	}

	BillBoardGauge::~BillBoardGauge()
	{

	}

	void BillBoardGauge::OnCreate()
	{
		m_parsecond = 0;//全体の何パーセント出すか決める
		auto PtrTransform = GetComponent<Transform>();
		if (!m_actor.expired()) {
			auto SeekPtr = m_actor.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += m_pushY;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(m_scale);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			//vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, m_vertices, indices);

			//UV値の変更
			//左上頂点
			m_vertices[0].textureCoordinate = Vec2(0.0f, 0.0f);
			//右上頂点
			m_vertices[1].textureCoordinate = Vec2(1.0f * m_parsecond, 0.0f);
			//左下頂点
			m_vertices[2].textureCoordinate = Vec2(0.0f, 1.0f);
			//右下頂点
			m_vertices[3].textureCoordinate = Vec2(1.0f * m_parsecond, 1.0f);

			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : m_vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 0.0f, 0.0f, 1.0f);//赤
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_textureName);
			SetAlphaActive(true);
			SetDrawLayer(m_layer);
		}

	}

	void BillBoardGauge::OnUpdate()
	{
		if (m_actor.expired())
		{
			GetStage()->RemoveGameObject<BillBoard>(GetThis<BillBoard>());
		}
		if (!m_actor.expired()) {
			auto SeekPtr = m_actor.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, m_vertices, indices);

			//アニメーション処理/////////////////////////////////////////
			auto test = m_vertices[1].position;
			m_vertices[1].position.x = -0.5f + (1.0f * m_parsecond);
			m_vertices[3].position.x = -0.5f + (1.0f * m_parsecond);
			m_vertices[1].position.y = 0.5f;
			m_vertices[3].position.y = -0.5f;
			//UV座標の設定		
			auto move = (1.0f * m_parsecond);
			m_vertices[1].textureCoordinate.x = move;
			m_vertices[3].textureCoordinate.x = move;
			////////////////////////////////////////////////////////////

			//新しい頂点に更新
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : m_vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 0.0f, 0.0f, 1.0f);//赤
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);


			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += m_pushY;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(m_scale);

			//メッシュの更新
			auto DrawComp = GetComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_textureName);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをカメラ目線にする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}
		//auto verticesVec = m_SquareMeshResource->GetBackupVerteces<VertexPositionColorTexture>();
		////verticesVec[1].position
		//
		////ワールドマトリックス取得
		//auto world = GetComponent<Transform>()->GetWorldMatrix();
		//world.transpose();//ワールド座標できるように変換
		
	}

	//何パーセントテクスチャを出すか決める
	void BillBoardGauge::SetPercent(float parcent)
	{
		m_parsecond = parcent;
	}

}
//end basecross
