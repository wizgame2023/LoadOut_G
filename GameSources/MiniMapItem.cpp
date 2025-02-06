/*!
@file MiniMapItem.cpp
@brief ミニマップ用のアイテム
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapItem::MiniMapItem(shared_ptr<Stage>& stagePtr,weak_ptr<Battery> parentObj, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, int layer) :
		Sprite(stagePtr,textureName,size,pos,rot,color,layer),
		m_parentObj(parentObj)
	{

	}

	MiniMapItem::~MiniMapItem()
	{
	}

	void MiniMapItem::OnUpdate()
	{
		//元となるオブジェクトが消えた場合、自分も消える
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<MiniMapItem>(GetThis<MiniMapItem>());
		}
	}

}
//end basecross
