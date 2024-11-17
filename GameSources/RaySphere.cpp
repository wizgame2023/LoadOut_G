/*!
@file RaySphere.cpp
@brief レイ
*/
//現在の処理だと重い状態になる可能性がとても高いので修正必須だと思います
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RaySphere::RaySphere(shared_ptr<Stage>& stagePtr,Vec3 pos,float angle,weak_ptr<Ray> parentObj,float range) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rad(angle),
		m_parentObj(parentObj),
		m_range(range),
		m_originPos(pos),
		m_discoveryObj(NULL)
	{

	}

	RaySphere::~RaySphere()
	{
	}

	void RaySphere::OnCreate()
	{
		//Transform作成
		auto ptr = GetComponent<Transform>();//Transform取得
		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptr->SetScale(Vec3(3.0f,3.0f,3.0f));

		//Transformに対しての等差数列
		//Mat4x4 spanMat;
		//spanMat.affineTransformation(
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);

		//メッシュ生成
		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetFixed(true);
		//ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"RaySphere");//レイスフィア用のタグ

	}

	void RaySphere::OnUpdate()
	{
		//元となるオブジェクトが消えた場合、自分も消える
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<RaySphere>(GetThis<RaySphere>());
			return;

		}


		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム取得
		auto ptr = GetComponent<Transform>();//Transform取得
		auto pos = ptr->GetPosition();
		float speed = 100;
		pos.x += cos(m_rad) * speed * delta;
		pos.z += sin(m_rad) * speed * delta;
		ptr->SetPosition(pos);

		m_moveVec = Vec3((m_originPos.x - pos.x), (m_originPos.y - pos.y), (m_originPos.z - pos.z));
		float move = RemoveMinus(m_moveVec.x) + RemoveMinus(m_moveVec.y) + RemoveMinus(m_moveVec.z);
		
		//原点から一定距離離れた場合自分が消える
		if (move >= m_range)
		{
			GetStage()->RemoveGameObject<RaySphere>(GetThis<RaySphere>());//自分自身が消える
			m_parentObj.lock()->SetDisObj(m_discoveryObj);//取得したオブジェクトを渡す

		}


		
	}

	void RaySphere::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//ぶつかったオブジェクトが今までぶつかったことのないオブジェクトなら配列に入れる
		//for (auto a : m_discoveryObj)
		//{
		//	if (a.lock() != other)//オブジェクトが前覚えている物でないとき
		//	{
				//m_discoveryObj.push_back(other);//記憶する
			//}
			//m_parentObj.lock()->SetDisObj(m_discoveryObj);//取得したオブジェクトを渡す
		//}
		
		auto wall = dynamic_pointer_cast<Wall>(other);
		auto player = dynamic_pointer_cast<Player>(other);
		if (wall||player)
		{
			m_discoveryObj.push_back(other);//記憶する
			m_parentObj.lock()->SetDisObj(m_discoveryObj);//取得したオブジェクトを渡す

			GetStage()->RemoveGameObject<RaySphere>(GetThis<RaySphere>());//自分自身を消す
		}
	}

	//取得したオブジェクトを渡す
	vector<weak_ptr<GameObject>> RaySphere::GetDisObj()
	{
		return m_discoveryObj;
	}

	float RaySphere::RemoveMinus(float num)
	{
		//numが0より小さかったら0よりも大きくする
		if (num <= 0)
		{
			num = -num;
		}

		return num;
	}

}
//end basecross
