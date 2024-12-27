/*!
@file Sprite.h
@brief �X�v���C�g�p�̃N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapItem :public GameObject
	{
	protected:
		//�摜�̕\���T�C�Y
		float m_width;
		float m_heigth;
		int m_layer;
		Vec2 m_size;//�摜�̑傫��

		wstring m_textureName;//�e�N�X�`���̖��O

		Vec3 m_pos;
		Vec3 m_rot;
		Col4 m_color;

		weak_ptr<Battery> m_parentObj;//���ƂȂ�I�u�W�F�N�g��ۊǂ���ϐ�

	public:
		MiniMapItem(shared_ptr<Stage>& stagePtr,weak_ptr<Battery> parentObj, wstring textureName, Vec2 size,int layer = 1, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f));//�R���X�g���N�^
		virtual ~MiniMapItem();//�f�X�g���N�^

		virtual void OnCreate()override;//�쐬
		virtual void OnUpdate()override;//�X�V

	};


}
//end basecross
