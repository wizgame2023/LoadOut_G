/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	NumberSquare::NumberSquare(const shared_ptr<Stage>& StagePtr,
		 shared_ptr<Enemy>& enemyPtr, size_t Number) :
		GameObject(StagePtr),
		m_enemy(enemyPtr),
		m_Number(Number)
	{}
	NumberSquare::~NumberSquare() {}

	//初期化
	void NumberSquare::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_enemy.expired()) {
			auto SeekPtr = m_enemy.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(5.0f, 5.0f, 5.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV値の変更
			float from = ((float)m_Number) / 10.0f;
			float to = from + (1.0f / 10.0f);
			//左上頂点
			vertices[0].textureCoordinate = Vec2(from, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vec2(to, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vec2(from, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vec2(to, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Battery1");
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}
	void NumberSquare::OnUpdate() {

		if (!m_enemy.expired()) {
			auto SeekPtr = m_enemy.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

	}

}
//end basecross
