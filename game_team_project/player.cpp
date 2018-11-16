//********************************************************************
// Include
//********************************************************************
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "pad.h"

//********************************************************************
// Enum
//********************************************************************
enum
{
    pDown,
    pUp,     // 上向き
    pRight,  // 右向き
    pLeft,   // 左向き
};

//********************************************************************
// 定数
//********************************************************************
const int kPlayerSizeX = 64; // プレイヤー横幅
const int kPlayerSizeY = 96; // プレイヤー縦幅
const int kAnimationSpeed = 8;  // アニメーション速度
const int kAnimationSpeed2 = 4;  // アニメーション速度 (走行時)

//********************************************************************
// コンストラクタ
//********************************************************************
Player::Player()
{
    // メンバ変数の初期化
    position_ = Vector2( 576.0F, 288.0F );
    speed_ = 4;

    // アニメーション関係
    animation_no_ = 0;
    animation_counter_ = 0;
    animation_pattern_ = pUp,  // 下向き

    // キーボード関係
    pad_flag_ = false;

    // テクスチャ関係
    texture_ = NULL;
}

//********************************************************************
// デストラクタ
//********************************************************************
Player::~Player()
{
}

//********************************************************************
// 初期化
//********************************************************************
bool Player::init( const wchar_t* FileName )
{
    // テクスチャの読み込み
    texture_ = Texture::load( FileName );

    // NULLチェック
    if( texture_ == NULL )
    {
        // エラー
        return false;
    }

    return true;
}

//********************************************************************
// 更新処理
//********************************************************************
void Player::update( int* pad_ )
{
    // 実態の宣言

    // コントローラの入力の取得 
    const GamePad::State pad = Pad::getState();

    // 入力可能時
    if( pad_flag_ == false )
    {
        // コントローラが入力されたか
        // ←
        if( pad.dpad.left )
        {
            pad_flag_ = true;
            pad_no_ = pLeft;
            *pad_ = pLeft;
        }
        // →
        else if( pad.dpad.right )
        {
            pad_flag_ = true;
            pad_no_ = pRight;
            *pad_ = pRight;
        }
        // ↑
        else if( pad.dpad.up )
        {
            pad_flag_ = true;
            pad_no_ = pUp;
            *pad_ = pUp;
        }
        else
        {
            animation_no_ = 0;
        }
    }
    // 歩行時and走行時 
    else
    {
        if( pad_no_ == pLeft )
        {
            animation_pattern_ = pLeft;
            position_.x += speed_;
        }
        else if( pad_no_ == pRight )
        {
            animation_pattern_ = pRight;
            position_.x -= speed_;
        }
        else if( pad_no_ == pUp )
        {
            animation_pattern_ = pUp;
            position_.y += speed_;
        }
    }

    // 1マス進んだらフラグを下げる 
    if( static_cast<int>(position_.x) % 64 == 0 && static_cast<int>(position_.y) % 64 == 0 )
    {
        pad_flag_ = false;
    }

    // アニメーション更新
    animation();

}

//********************************************************************
//描画
//********************************************************************
void Player::draw( )
{
    // 描画範囲の設定
    RECT rect;
    rect.top = animation_pattern_ * kPlayerSizeY;
    rect.left = animation_no_ * kPlayerSizeX;
    rect.right = rect.left + kPlayerSizeX;
    rect.bottom = rect.top + kPlayerSizeY;

    // 描画
    Sprite::draw( texture_, position_, &rect );
}



//********************************************************************
// アニメーション処理
//********************************************************************
void Player::animation()
{
    // 歩行処理

        // カウントアップ
    if( ++animation_counter_ >= kAnimationSpeed )
    {
        // 終端まで進んだら戻す
        (animation_no_ == 3) ? animation_no_ = 0 : animation_no_++;

        // カウンター初期化
        animation_counter_ = 0;
    }
}

//********************************************************************
// 破棄
//********************************************************************
void Player::destroy()
{
    // テクスチャの解放
    SAFE_RELEASE( texture_ );
}