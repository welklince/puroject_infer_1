#include<WICTextureLoader.h>
#include<cstdio>
#include "texture.h"
#include"direct3d.h"
#include"error.h"

using namespace DirectX;

ID3D11ShaderResourceView* Texture::load( const wchar_t*FileName )
{

    ID3D11ShaderResourceView*texture;

    //テクスチャの読み込み
    if( FAILED( CreateWICTextureFromFileEx(
        Direct3D::getDevice(),                    //D3Dデバイスインターフェイス
        Direct3D::getContext(),                //デバイスコンテキストインターフェイス
        FileName,                 //ファイル名(ワイド文字で指定)
        0,                             //ミッドマップレベル
        D3D11_USAGE_DEFAULT,           //使用方法
        D3D11_BIND_SHADER_RESOURCE,    //バインドの種類
        0,                             //CPUアクセス方法
        0,                             //フラグオプション
        WIC_LOADER_DEFAULT,            //SRGBフラグ
        NULL,                          //リソースデータ受取先ポインタ
        &texture ) ) )                //シェーダーリソースビュー受取先ポインタ
    {
        //エラー
        char file_name[ 256 ], str[ 256 ];
        wcstombs( file_name, FileName, 256 );
        sprintf( str, "テクスチャの読み込みに失敗(%s)", file_name );
        Error::showDialog( str );
        return NULL;
    }

    return texture;
}