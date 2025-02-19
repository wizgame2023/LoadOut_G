/*!
@file MiniMapHatch.cpp
@brief  ミニマップ用のハッチ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapHatch::MiniMapHatch(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, int layer) :
		Sprite(stagePtr, textureName, size, pos, rot, color, layer),
		m_plusColorFlag(false)
	{

	}

	MiniMapHatch::~MiniMapHatch()
	{

	}

	//更新
	void MiniMapHatch::OnUpdate()
	{
		//フラグがオンになったらアップデート処理をする
		if (!m_updateFlag) return;

		float delta = App::GetApp()->GetElapsedTime();
		//透明でない場合
		if (m_color.w >= 1.0f)
		{
			m_plusColorFlag = false;
		}
		//透明の場合
		if (m_color.w <= 0.0f)
		{
			m_plusColorFlag = true;
		}

		//フラグによって透明にしていくのか色を付けていくのか決める
		switch (m_plusColorFlag)
		{
		case true://色を付ける
			m_color.w += delta;
			break;
		case false://透明にする
			m_color.w -= delta;
			break;
		default:
			break;
		}
		SetColor(m_color);//色をセットする
	}

	void MiniMapHatch::OnClear(bool onOff)
	{
		Sprite::OnClear(onOff);
		//透明にするかしないかでアップデート処理をするか決める
		if (onOff)
		{
			m_updateFlag = false;//アップデートしない
		}
		if (!onOff)
		{
			m_updateFlag = true;//アップデートする
		}
	}
}
//end basecross
