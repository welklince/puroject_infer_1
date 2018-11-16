#pragma once

#include"direct3d.h"
#include"sprite.h"
#include"release.h"

// 構造体
struct Parts
{
    Vector2 position;  // 座標
    RECT trim;         // 描画範囲
    int id;            // パーツ番号

    // コンストラクタ
    Parts()
    {
        position = Vector2( 0.0F, 0.0F );
        trim = RECT();
        id = 0;
    }
};

// クラス
class Field
{
private:
    ID3D11ShaderResourceView* texture_; // テクスチャ
    int width_, height_;                // マップ横幅縦幅
    Parts* parts_;                      // パーツ構造体ポインタ

public:
    Field();       // コンストラクタ
    ~Field();      // デストラクタ
    bool init();   // 初期化
    void update( int pad ); // 更新
    void draw();   // 描画
    void destroy();// 破棄 
};