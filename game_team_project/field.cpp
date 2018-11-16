#include"field.h"
#include"texture.h"
#include"sprite.h"
#include"error.h"
#include"player.h"

// コンストラクタ
Field::Field()
{
    texture_ = NULL;
    parts_ = NULL;
    width_ = 0;
    height_ = 0;

}

// デストラクタ
Field::~Field()
{

}

// 初期化
bool Field::init()
{
    // テクスチャの読み込み
    if( !(texture_ = Texture::load( L"pokemon_rse.png" )) )
    {
        // エラー
        return false;
    }

    // FMFファイルを開く
    FILE*fp = fopen( "map_test.fmf", "rb" );

    if( !fp )
    {
        // エラー
        Error::showDialog( "map_test.fmfが開けませんでした。" );
        return false;
    }

    // 先頭8Byteをスキップ
    fseek( fp, 8L, SEEK_SET );

    // マップの横幅と縦幅を取得
    fread( &width_, sizeof( int ), 1, fp );
    fread( &height_, sizeof( int ), 1, fp );

    // parts構造体のメモリを確保
    parts_ = new Parts[ width_*height_ ];

    // NULLチェック
    if( !parts_ )
    {
        // エラー
        Error::showDialog( "パーツ構造体のメモリ確保に失敗しました。" );
        return false;
    }

    // FMFヘッダ部分をスキップ
    fseek( fp, 20L, SEEK_SET );

    // 全パーツデータ格納
    for( int i = 0; i < width_*height_; i++ )
    {
        // 番号の取得
        fread( &parts_[ i ].id, sizeof( char ), 1, fp );

        // 描画範囲の設定
        parts_[ i ].trim.left = parts_[ i ].id % 16 * 64L;
        parts_[ i ].trim.top = parts_[ i ].id / 16 * 64L;
        parts_[ i ].trim.right = parts_[ i ].trim.left + 64L;
        parts_[ i ].trim.bottom = parts_[ i ].trim.top + 64L;

        // 座標設定
        parts_[ i ].position.x = static_cast<float>(64.0F * (i % width_));
        parts_[ i ].position.y = static_cast<float>(64.0F * (i / width_));
    }

    // ファイルを閉じる
    fclose( fp );

    return true;
}


// 更新処理
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
// 描画
void Field::draw()
{
    for( int i = 0; i < width_*height_; i++ )
    {
        Sprite::draw( texture_, parts_[ i ].position, &parts_[ i ].trim );
    }

}

// 破棄
void Field::destroy()
{
    // テクスチャの開放
    SAFE_RELEASE( texture_ );

    // メモリの解放
    SAFE_DELETE_ARRAY( parts_ );
}