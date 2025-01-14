/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	TrackingPillarEfect::TrackingPillarEfect(const shared_ptr<Stage>& stagePtr, Vec3 pos, wstring textureName, Vec2 velocity, int square) :
		PillarEffect(stagePtr,pos,textureName,velocity,square)
	{

	}
	//デストラクタ
	TrackingPillarEfect::~TrackingPillarEfect()
	{

	}

	//更新
	void TrackingPillarEfect::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();
		float delta = App::GetApp()->GetElapsedTime();

		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += m_scrollVelocity * delta;//uv座標をずらしている
			auto test = 0;
		}
		//m_test += m_scrollVelocity * delta;//uv座標をずらしている
		auto Trans = GetComponent<Transform>();
		auto pos = GetComponent<Transform>()->GetPosition();
		playerPos.y = pos.y;
		pos = playerPos;
		Trans->SetPosition(pos);

		if (m_isUpdate)
		{
			m_isUpdate = false;
			InitializeVertices();
		}

		m_drawComp->UpdateVertices(m_vertices);
	}


}
//end basecross
