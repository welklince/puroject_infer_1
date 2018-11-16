#include"sprite.h"
#include"direct3d.h"
#include"common.h"

SpriteBatch* Sprite::sprite_;

bool Sprite::init()
{
    // SpriteBatch�N���X�̃��������m��
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    // �������m�ۃ`�F�b�N
    if( !sprite_ )
    {
        // �G���[
        return false;
    }
    return true;
}

// �X�v���C�g�̕`��J�n
void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getState()->NonPremultiplied() );

}

// 
void Sprite::end()
{
    sprite_->End();
}

// �`��
void Sprite::draw( ID3D11ShaderResourceView* Texture, const Vector2& Position, const RECT* Rect,
    const float Rocation, const Vector2& Scale, const Vector2& Origin, const SpriteEffects Effect, const float Depth )
{
    sprite_->Draw(
        Texture,       //�e�N�X�`��
        Position,     //���W
        Rect,          //�`��͈�
        Colors::White, //�J���[
        Rocation,      //��]
        Origin,       //�A���J�[�|�C���g�i���_�j
        Scale,        //�g�k
        Effect,        //�G�t�F�N�g
        Depth          //�[�x
    );
}
// �j��
void Sprite::destroy()
{
    // ���������
    SAFE_DELETE( sprite_ );

}