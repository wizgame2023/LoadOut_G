/*!
@file Sprite.h
@brief �X�v���C�g�p�̃N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite :public GameObject
	{
	protected:
		//�摜�̕\���T�C�Y
		float m_width;
		float m_heigth;
		int m_layer;
		Vec2 m_size;//�摜�̑傫��

		//vector<VertexPositionColorTexture> m_vertices;
		//vector<uint16_t> m_indices;
		//shared_ptr<PCTSpriteDraw> m_draw;
		wstring m_textureName;//�e�N�X�`���̖��O

		shared_ptr<Transform> m_trans;

		Vec3 m_pos;
		Vec3 m_rot;
		Col4 m_color;


	public:
		Sprite(shared_ptr<Stage>& stagePtr,wstring textureName,Vec2 size,Vec3 pos = Vec3(0.0f,0.0f,0.0f), Vec3 rot = Vec3(0.0f,0.0f,0.0f),Col4 color = Col4(1.0f,1.0f,1.0f,1.0f), int layer = 1);//�R���X�g���N�^
		virtual ~Sprite();//�f�X�g���N�^

		virtual void OnCreate()override;//�쐬
		virtual void OnUpdate()override;//�X�V

	};


}
//end basecross
