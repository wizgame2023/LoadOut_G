/*!
@file TilteStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "BlackOut.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SpriteNum>m_sprite;

		shared_ptr<Sprite> m_StagePhoto;
		shared_ptr<Sprite> m_StageText;
		shared_ptr<Sprite> m_StageText1;
		shared_ptr<Sprite> m_StageText2;
		shared_ptr<NuberManager> m_NumberSprite;
		shared_ptr<BlackOut> m_blackOut;//暗転処理
		shared_ptr<Sprite>m_spriteMozi;
		shared_ptr<Sprite>m_spriteB;

		shared_ptr<Sprite> m_LStick1;
		shared_ptr<Sprite> m_LStick2;
		shared_ptr<Sprite> m_LStickLeft;
		shared_ptr<Sprite> m_LStickRight;

		float m_time = 0;
		float m_controllerTime = 0;
		float m_countTime = 0;


		int m_count = 0;
		int m_controllerCount = 0;
		int m_SelectStage;//選択しているステージ

		const int m_allStage = 20;
		
		bool m_decisionFlag;//選択したかどうかのフラグ
		bool m_stickCheck;//スティックの傾けた処理を受け取るかのフラグ
		bool m_stickLongCheck;//長く傾けているかのフラグ

		bool m_updateFlag;//アップデートのフラグ


		CONTROLER_STATE m_controler;//コントローラー

	public:
		//構築と破棄
		SelectStage() :
			Stage(),
			m_stickCheck(true),
			m_updateFlag(true)
		{}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SelectionStage();//どのステージにするかの選択処理

		void OnDestroy()override;
		void SetUpdateFlag(bool onOff);//アップデートするかのセッター

	};


}
//end basecross

