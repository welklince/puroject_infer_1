#include"field.h"
#include"texture.h"
#include"sprite.h"
#include"error.h"
#include"player.h"

// �R���X�g���N�^
Field::Field()
{
    texture_ = NULL;
    parts_ = NULL;
    width_ = 0;
    height_ = 0;

}

// �f�X�g���N�^
Field::~Field()
{

}

// ������
bool Field::init()
{
    // �e�N�X�`���̓ǂݍ���
    if( !(texture_ = Texture::load( L"pokemon_rse.png" )) )
    {
        // �G���[
        return false;
    }

    // FMF�t�@�C�����J��
    FILE*fp = fopen( "map_test.fmf", "rb" );

    if( !fp )
    {
        // �G���[
        Error::showDialog( "map_test.fmf���J���܂���ł����B" );
        return false;
    }

    // �擪8Byte���X�L�b�v
    fseek( fp, 8L, SEEK_SET );

    // �}�b�v�̉����Əc�����擾
    fread( &width_, sizeof( int ), 1, fp );
    fread( &height_, sizeof( int ), 1, fp );

    // parts�\���̂̃��������m��
    parts_ = new Parts[ width_*height_ ];

    // NULL�`�F�b�N
    if( !parts_ )
    {
        // �G���[
        Error::showDialog( "�p�[�c�\���̂̃������m�ۂɎ��s���܂����B" );
        return false;
    }

    // FMF�w�b�_�������X�L�b�v
    fseek( fp, 20L, SEEK_SET );

    // �S�p�[�c�f�[�^�i�[
    for( int i = 0; i < width_*height_; i++ )
    {
        // �ԍ��̎擾
        fread( &parts_[ i ].id, sizeof( char ), 1, fp );

        // �`��͈͂̐ݒ�
        parts_[ i ].trim.left = parts_[ i ].id % 16 * 64L;
        parts_[ i ].trim.top = parts_[ i ].id / 16 * 64L;
        parts_[ i ].trim.right = parts_[ i ].trim.left + 64L;
        parts_[ i ].trim.bottom = parts_[ i ].trim.top + 64L;

        // ���W�ݒ�
        parts_[ i ].position.x = static_cast<float>(64.0F * (i % width_));
        parts_[ i ].position.y = static_cast<float>(64.0F * (i / width_));
    }

    // �t�@�C�������
    fclose( fp );

    return true;
}


// �X�V����
void Field::update( int pad )
{
    /*if( pad == 0 )
    {
        for( int i = 0; i < width_*height_; i++ )
        {
            parts_[ i ].position.y -= 4;
        }
    }

    if( pad == 1 )
    {
        for( int i = 0; i < width_*height_; i++ )
        {
            parts_[ i ].position.y += 4;
        }
    }
    if( pad == 2 )
    {
        for( int i = 0; i < width_*height_; i++ )
        {
            parts_[ i ].position.x -= 4;
        }
    }
    if( pad == 3 )
    {
        for( int i = 0; i < width_*height_; i++ )
        {
            parts_[ i ].position.x += 4;
        }
    }*/
}
// �`��
void Field::draw()
{
    for( int i = 0; i < width_*height_; i++ )
    {
        Sprite::draw( texture_, parts_[ i ].position, &parts_[ i ].trim );
    }

}

// �j��
void Field::destroy()
{
    // �e�N�X�`���̊J��
    SAFE_RELEASE( texture_ );

    // �������̉��
    SAFE_DELETE_ARRAY( parts_ );
}