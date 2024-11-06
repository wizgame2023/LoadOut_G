/*!
@file Ray.cpp
@brief レイ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	Ray::~Ray()
	{
	}

	void Ray::OnCreate()
	{
		//Transform作成
		auto ptr = GetComponent<Transform>();//Transform取得
		ptr->SetPosition(Vec3(0.0f,0.0f,0.0f));
		ptr->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptr->SetScale(Vec3(10.0f,10.0f,10.0f));

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
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

	void Ray::OnUpdate()
	{
		auto ptr = GetComponent<Transform>();//Transform取得
		auto pos = ptr->GetPosition();
		pos.x += 1;
		ptr->SetPosition(pos);
	}

	void Ray::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		
	}

}
//end basecross
