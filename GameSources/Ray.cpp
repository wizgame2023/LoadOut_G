/*!
@file Ray.cpp
@brief レイ
*/
//現在の処理だと重い状態になる可能性がとても高いので修正必須だと思います
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr,Vec3 pos,float angle,weak_ptr<GameObject> parentObj) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rad(angle),
		m_parentObj(parentObj),
		m_discoveryObj(NULL)
	{

	}

	Ray::~Ray()
	{
	}

	void Ray::OnCreate()
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

	}

	void Ray::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム取得
		auto ptr = GetComponent<Transform>();//Transform取得
		auto pos = ptr->GetPosition();
		float speed = 100;
		pos.x += cos(m_rad) * speed * delta;
		pos.z += sin(m_rad) * speed * delta;
		ptr->SetPosition(pos);
	}

	void Ray::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//ぶつかったオブジェクトが今までぶつかったことのないオブジェクトなら配列に入れる
		for (auto a : m_discoveryObj)
		{
			if (a.lock() != other)//オブジェクトが前覚えている物でないとき
			{
				m_discoveryObj.push_back(other);//記憶する
			}
			GetDisObj();//取得したオブジェクトを渡したい
		}
		
		auto enemy = dynamic_pointer_cast<Wall>(other);
		if (enemy)
		{
			GetStage()->RemoveGameObject<Ray>(GetThis<Ray>());//自分自身を消す
		}
	}

	//取得したオブジェクトを渡す
	vector<weak_ptr<GameObject>> Ray::GetDisObj()
	{
		return m_discoveryObj;
	}

}
//end basecross
