/*!
@file MiniMapItem.cpp
@brief �~�j�}�b�v�p�̃A�C�e��
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
		//���ƂȂ�I�u�W�F�N�g���������ꍇ�A������������
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<MiniMapItem>(GetThis<MiniMapItem>());
		}
	}

}
//end basecross
