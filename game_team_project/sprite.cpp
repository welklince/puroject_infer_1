#include"sprite.h"
#include"direct3d.h"
#include"common.h"

SpriteBatch* Sprite::sprite_;

bool Sprite::init()
{
    // SpriteBatchクラスのメモリを確保
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    // メモリ確保チェック
    if( !sprite_ )
    {
        // エラー
        return false;
    }
    return true;
}

// スプライトの描画開始
void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getState()->NonPremultiplied() );

}

// 
void Sprite::end()
{
    sprite_->End();
}

// 描画
void Sprite::draw( ID3D11ShaderResourceView* Texture, const Vector2& Position, const RECT* Rect,
    const float Rocation, const Vector2& Scale, const Vector2& Origin, const SpriteEffects Effect, const float Depth )
{
    sprite_->Draw(
        Texture,       //テクスチャ
        Position,     //座標
        Rect,          //描画範囲
        Colors::White, //カラー
        Rocation,      //回転
        Origin,       //アンカーポイント（原点）
        Scale,        //拡縮
        Effect,        //エフェクト
        Depth          //深度
    );
}
// 破棄
void Sprite::destroy()
{
    // メモリ解放
    SAFE_DELETE( sprite_ );

}