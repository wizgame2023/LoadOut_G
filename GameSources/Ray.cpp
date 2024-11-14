/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr, shared_ptr<Actor> parentObj,float range) :
		GameObject(stagePtr),
		m_parentObj(parentObj),
		m_range(range)
	{

	}

	Ray::~Ray()
	{
	}

	void Ray::OnCreate()
	{

	}

	void Ray::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		m_countTime += delta;
		auto angle = m_parentObj.lock()->GetAngle();//角度を取得

		//レイの判定となるレイスフィアを生成する
		if (m_countTime >= 0.5f)
		{	
			m_countTime = 0;//リセット
			GetStage()->AddGameObject<RaySphere>(m_parentObj.lock()->GetComponent<Transform>()->GetPosition(), -angle, GetThis<Ray>(),m_range);//レイスフィア生成
		}

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		////auto gameStage = scene->GetGameStage();

		//wss /* << L"デバッグ用文字列 "*/
		//	<< L"\n傾き " << XMConvertToDegrees(-angle)
		//	<< endl;

		//scene->SetDebugString(wss.str());

	}

	//レイスフィアが取得したオブジェクトを受け取るセッター
	void Ray::SetDisObj(vector<weak_ptr<GameObject>> discoveryObj)
	{
		m_discoveryObj.clear();//前の配列全削除
		m_discoveryObj.swap(discoveryObj);//新しい配列の中身にする
		auto a = 0;//デバック用
	}

	vector<weak_ptr<GameObject>> Ray::GetDisObj()
	{
		//当たったオブジェクトの情報の配列を渡す
		return m_discoveryObj;

		//情報の配列を渡したのでいらなくなった配列を削除
		m_discoveryObj.clear();//前の配列全削除
		vector<weak_ptr<GameObject>> discoveryObj;//新しい空の配列を生成
		m_discoveryObj.swap(discoveryObj);//新しい配列の中身にする

	}



}
//end basecross
