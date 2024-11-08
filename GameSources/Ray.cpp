/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr, shared_ptr<Enemy> parentObj) :
		GameObject(stagePtr),
		m_parentObj(parentObj)
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
		//もし、レイスフィアがが前受け取ったオブジェクトを取得していなかったらそのオブジェクトは配列から消す
		if (m_countTime >= 0.5f)
		{
			//GetStage()->AddGameObject<RaySphere>()
			//GetStage()->AddGameObject<RaySphere>(GetComponent<Transform>()->GetPosition(), atan2(m_controler.fThumbLY, m_controler.fThumbLX),GetThis<Ray>());

		}
	}

	//レイスフィアが取得したオブジェクトを受け取るセッター
	void Ray::SetDisObj(vector<weak_ptr<GameObject>> discoveryObj)
	{
		m_discoveryObj.clear();//前の配列全削除
		m_discoveryObj.swap(discoveryObj);//新しい配列の中身にする
		
		//for (auto test : m_discoveryObj)
		//{
		//	
		//}
		//m_discoveryObj[0].lock();
		////m_discoveryObj = discoveryObj;//受け取る
	}

}
//end basecross
