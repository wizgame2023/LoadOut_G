/*!
@file PillarEffect.h
@brief ����̃G�t�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PillarEffect : public Actor
	{
	private:

	protected:
		void InitializeVertices();

		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		std::shared_ptr<BcPCTStaticDraw> m_drawComp;

		Vec3 m_pos;//�|�W�V����
		float m_height;//����
		float m_topRadius;//��̉~�̑傫��
		float m_bottomRadius;//���̉~�̑傫��
		int m_square;//�p��
		Vec2 m_loops;//�摜���ǂ����[�v�����邩
		Col4 m_topColor;//��̒��_�̐F
		Col4 m_bottomColor;//���̒��_�̐F
		wstring m_textureName;
		Vec2 m_scrollVelocity;//XY�����̑��x

		bool m_isUpdate = false;

		Vec2 m_test;

	public:
		PillarEffect(shared_ptr<Stage>& stagePtr,Vec3 pos, wstring textureName,Vec2 velovity, int square = 36);
		~PillarEffect();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetScrollPerSecond(Vec2 velocity);
		void SetVelocity(Vec2 velocity);
		void SetTexture(wstring textureName);
		virtual void UpdateTest(bool OnOff);

	};

}
//end basecross
