/*!
@file MyCamera.cpp
@brief プレイヤーを追尾するカメラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera(Vec3 pos):
		m_Pos(pos)
	{

	}

	MyCamera::~MyCamera()
	{

	}

	void MyCamera::OnCreate()
	{
	}

	void MyCamera::OnUpdate()
	{
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();//これでゲットステージ
		weak_ptr<Player> player = stage->GetSharedGameObject<Player>(L"Player");//プレイヤー取得

		auto posPlayer = player.lock()->GetComponent<Transform>()->GetPosition();//ポジション取得
		SetAt(posPlayer + Vec3(0.0f,4.5f,0.0f));//注視点を決定

		//カメラの座標を決める	
		SetEye(m_Pos+posPlayer);

	}

}
//end basecross
