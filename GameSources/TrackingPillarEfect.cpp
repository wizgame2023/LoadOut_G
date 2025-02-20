/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	TrackingPillarEfect::TrackingPillarEfect(shared_ptr<Stage>& stagePtr,weak_ptr<Actor> actor, Vec3 pos, wstring textureName, Vec2 velocity, int square) :
		PillarEffect(stagePtr,pos,textureName,velocity,square),
		m_actor(actor)
	{

	}
	//デストラクタ
	TrackingPillarEfect::~TrackingPillarEfect()
	{

	}

	//更新
	void TrackingPillarEfect::OnUpdate()
	{
		//フラグがオンになったらアップデートする
		if (!m_move) return;

		auto actor = m_actor.lock();
		//追尾する元がいなくなれば自分もいなくなる
		if (!actor)
		{
			GetStage()->RemoveGameObject<TrackingPillarEfect>(GetThis<TrackingPillarEfect>());
			return;
		}

		auto actorPos = actor->GetComponent<Transform>()->GetPosition();
		float delta = App::GetApp()->GetElapsedTime();

		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += m_scrollVelocity * delta;//uv座標をずらしている
			auto test = 0;
		}

		auto Trans = GetComponent<Transform>();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos = actorPos;
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
