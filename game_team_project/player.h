#pragma once

//********************************************************************
// Include
//********************************************************************
#include <d3d11.h>
#include <SimpleMath.h>
#include <Windows.h>
#include "release.h"

//********************************************************************
//  Namespace
//********************************************************************
using namespace DirectX;
using namespace SimpleMath;

//********************************************************************
// Class
//********************************************************************
class Player
{
private:
    ID3D11ShaderResourceView* texture_; // テクスチャ
    Vector2 position_;                  // 座標
    Vector2 offset_;                    // 補正値

    // アニメーション関係
    int  animation_no_;      // アニメーション番号
    int  animation_pattern_; // アニメーションパターン
    int  animation_counter_; // アニメーションカウンタ
    void animation();        // アニメーション処理
    int  speed_;             // 移動速度

    // キーボード関係
    bool pad_flag_;       // パッドのフラグ
    int  pad_no_;         // パッドの入力番号

public:
    Player();  //コントラスタ
    ~Player(); //デストラクタ

    //初期化
    bool init( const wchar_t* FileName ); // 初期化
    void update( int* pad_ );                        // 更新
    void draw( );                          // 描画
    void destroy();                       // 破棄
};