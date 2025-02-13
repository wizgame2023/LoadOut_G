/*!
@file WaterPillar.cpp
@brief ブロックのオブジェクトの実装
担当：三瓶
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	WaterPillar::WaterPillar(shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot,Vec3 scale) :
		Actor(StagePtr),
		m_pos(pos),
		m_originPos(pos),
		m_rot(rot),
		m_scale(scale),
		m_oneBlock(10),
		m_count(0)
	{
	}
	WaterPillar::~WaterPillar()
	{
	}

	void WaterPillar::OnCreate()
	{
		//ピポットを真ん中ではなくオブジェクトの下にさせる
		m_pos.y = m_originPos.y - (m_scale.y / 2);//オブジェクトの半分ずらすことで

		//Transform作成
		auto ptr = GetComponent<Transform>();//Transform取得
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 0.28f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.5f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"WaterPillerMesh");
		ptrDraw->AddAnimation(L"Defalt", 0, 30, true, 30.0f);//アニメーション追加

		//ptrDraw->SetTextureResource(L"Water");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる
		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"WaterPillar");//ブロック用のタグこれが基礎のオブジェクト

		//吹っ飛ぶマンホール作成
		//m_manhole =  GetStage()->AddGameObject<Block>(m_pos-Vec3(0.0f,-m_pos.y,0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//m_manhole->GetComponent<CollisionObb>()->SetAfterCollision(AfterCollision::None);
		//m_manhole->GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//マンホールテクスチャに変更
		//m_manhole->GetComponent<Transform>()->SetScale(10.0f, 1.0f, 10.0f);//サイズ変更

	}

	void WaterPillar::OnUpdate()
	{
		//フラグがオンになったらアップデートする
		if (!m_move) return;

		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto ptr = GetComponent<Transform>();//Transform取得

		//アニメーション再生
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);

		//ptr->SetScale()
		//Transform作成

		//吹っ飛び用のマンホールのTransformとPos取得
		//auto manholeTrans = m_manhole->GetComponent<Transform>();
		//auto manholePos = manholeTrans->GetPosition();

		//吹っ飛び用のマンホールが一定の高さまで行ったら削除する
		//if (manholePos.y >= 300.0f && m_manhole)
		//{
		//	stage->RemoveGameObject<Block>(m_manhole);
		//}
		//else if(m_manhole)
		//{
		//	//吹っ飛び用のマンホールを上に上げる
		//	//manholePos.y += 300 * delta;
		//	//manholeTrans->SetPosition(manholePos);
		//}

		//高さが一定になるまで伸ばす
		if (m_count == 0)
		{
			if (m_count == 0)
			{
				m_scale.y += 110*delta;//大きさをyを１づつ増やす
				ptr->SetScale(m_scale);
				m_pos.y = m_originPos.y + (m_scale.y / 2);//オブジェクトの半分ずらすことで
				ptr->SetPosition(m_pos);
			}

			if (m_scale.y >= 30)
			{
				m_count = 1;//柱を伸ばす段階を終了

				//伸ばしたい長さぴったりにする
				m_scale.y = 30.0f;
				ptr->SetScale(m_scale);
				m_pos.y = m_originPos.y + (m_scale.y / 2);//オブジェクトの半分ずらすことで
				ptr->SetPosition(m_pos);

			}

		}

		//一定の長さになるまで縮ませる
		if (m_count == 1)
		{
			m_scale.y -= 100 * delta;//大きさをyを１づつ増やす
			ptr->SetScale(m_scale);
			m_pos.y = m_originPos.y + (m_scale.y / 2);//オブジェクトの半分ずらすことで
			ptr->SetPosition(m_pos);

			if (m_scale.y <= 15.0f)
			{
				m_count = 2;//柱を縮ませる段階を終了

				//伸ばしたい長さぴったりにする
				m_scale.y = 15.0f;
				ptr->SetScale(m_scale);
				m_pos.y = m_originPos.y + (m_scale.y / 2);//オブジェクトの半分ずらすことで
				ptr->SetPosition(m_pos);

			}


		}


	}

}



