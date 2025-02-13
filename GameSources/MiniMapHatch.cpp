/*!
@file MiniMapHatch.cpp
@brief  �~�j�}�b�v�p�̃n�b�`
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

	//�X�V
	void MiniMapHatch::OnUpdate()
	{
		//�t���O���I���ɂȂ�����A�b�v�f�[�g����������
		if (!m_updateFlag) return;

		float delta = App::GetApp()->GetElapsedTime();
		//�����łȂ��ꍇ
		if (m_color.w >= 1.0f)
		{
			m_plusColorFlag = false;
		}
		//�����̏ꍇ
		if (m_color.w <= 0.0f)
		{
			m_plusColorFlag = true;
		}

		//�t���O�ɂ���ē����ɂ��Ă����̂��F��t���Ă����̂����߂�
		switch (m_plusColorFlag)
		{
		case true://�F��t����
			m_color.w += delta;
			break;
		case false://�����ɂ���
			m_color.w -= delta;
			break;
		default:
			break;
		}
		SetColor(m_color);//�F���Z�b�g����
	}

	void MiniMapHatch::OnClear(bool onOff)
	{
		Sprite::OnClear(onOff);
		//�����ɂ��邩���Ȃ����ŃA�b�v�f�[�g���������邩���߂�
		if (onOff)
		{
			m_updateFlag = false;//�A�b�v�f�[�g���Ȃ�
		}
		if (!onOff)
		{
			m_updateFlag = true;//�A�b�v�f�[�g����
		}
	}
}
//end basecross
