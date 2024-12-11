/*!
@file Ground.cpp
@brief ブロックのオブジェクトの実装
担当：三瓶
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ground::Ground(const shared_ptr<Stage>& StagePtr,vector<vector<int>> map,float push) :
		GameObject(StagePtr),
		m_map(map),
		m_push(push)
	{
	}
	Ground::Ground(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_pos(Vec3(0.0f, 0.0f, 0.0f)),
		m_rot(Vec3(200.0f, 0.1f, 200.0f))
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::OnCreate()
	{
		//Transform作成
		auto ptr = GetComponent<Transform>();//Transform取得
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f,0.0f,0.0f);
		ptr->SetScale(Vec3(10.0f,0.1f,10.0f));

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTStaticInstanceDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Road");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		////csvファイルから読み取って床関係のオブジェクトの生成する
		for (int i = 0; i < m_map.size(); i++)
		{
			for (int j = 0; j < m_map[0].size(); j++)
			{
				//ブロックの位置を取得
				float x = (j * 10.0f) - m_push;
				float z = m_push - (i * 10.0f);

				//インスタンス用の行列を作成する
				Mat4x4 matrix;
				//matrix.translation(Vec3(x, 0.0f, z));
				//matrix.scale(Vec3(10.0f, 0.1f, 10.0f));
				matrix.affineTransformation(
					Vec3(10.0f, 0.1f, 10.0f),
					Vec3(),
					Vec3(),
					Vec3(x, 0.0f, z)
				);
				ptrDraw->AddMatrix(matrix);//ブロックを表示

			}
		}


		//コリジョン生成 コリジョンいらなくなった
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(false);
		//ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる
		//ptrColl->SetDrawActive(true);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Ground");//地面用のタグ

	}

}