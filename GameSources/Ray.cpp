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

		//レイの判定となるレイスフィアを生成する
		if (m_countTime >= 0.1f)
		{	
			m_countTime = 0;//リセット
			auto raySphere = GetStage()->AddGameObject<RaySphere>(m_parentObj.lock()->GetComponent<Transform>()->GetPosition(), -m_angle, GetThis<Ray>(),m_range);//レイスフィア生成
			//m_raySphere.push_back(raySphere);
			//auto a = 0;//デバック用
		}

		////デバック用
		//// インプットデバイスオブジェクト
		//auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		////コントローラーの取得
		//auto m_controler = inputDevice.GetControlerVec()[0];

		////生成したレイスフィアを削除する 作成途中
		//if (m_controler.wPressedButtons & XINPUT_GAMEPAD_X)
		//{
		//	//for (auto a : m_raySphere)
		//	//{
		//	//	GetStage()->RemoveGameObject<RaySphere>(a.lock());
		//	//	auto test = m_raySphere;
		//	//}
		//	//ステージ上のオブジェクトをすべて見て特定のタグのオブジェクトを取得する
		//	//GetStage()->GetUsedTagObjectVec(L"RaySphere", shared_ptr<RaySphere>)
		//	//weak_ptr<RaySphere> obj[] = 

		//}

		
		

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

	}

	//当たったオブジェクトのポインター配列を削除する
	void Ray::ResetDisObj()
	{
		//使わない配列を削除
		m_discoveryObj.clear();//前の配列全削除

	}

	//角度のセッター
	void Ray::SetAngle(float angle)
	{
		m_angle = angle;
	}

	//角度のゲッター
	float Ray::GetAngle()
	{
		return m_angle;
	}



}
//end basecross
