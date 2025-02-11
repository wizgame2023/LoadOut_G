/*!
@file PillarEffect.h
@brief 柱上のエフェクト
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

		Vec3 m_pos;//ポジション
		float m_height;//高さ
		float m_topRadius;//上の円の大きさ
		float m_bottomRadius;//下の円の大きさ
		int m_square;//角数
		Vec2 m_loops;//画像をどうループさせるか
		Col4 m_topColor;//上の頂点の色
		Col4 m_bottomColor;//下の頂点の色
		wstring m_textureName;
		Vec2 m_scrollVelocity;//XY方向の速度

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
