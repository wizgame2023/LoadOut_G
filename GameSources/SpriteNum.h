/*!
@file Sprite.h
@brief �X�v���C�g�p�̃N���X
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class SpriteNum :public Sprite
	{
	private:
		int m_num;//�\�����鐔�l

		shared_ptr<Transform> m_trans;

		vector<uint16_t> m_indices;
		vector<VertexPositionColorTexture> m_vertices;
	public:
		SpriteNum(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,int num,  Vec3 pos=Vec3(0.0f,0.0f,0.0f), Vec3 rot=Vec3(0.0f,0.0f,0.0f), Col4 color=Col4(1.0f,1.0f,1.0f,1.0f), int layer=1);//�R���X�g���N�^
		~SpriteNum();//�f�X�g���N�^

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void SetNum(int num);//�����̍X�V

	};


}
//end basecross
