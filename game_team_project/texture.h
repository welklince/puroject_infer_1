#pragma once

#include<d3d11.h>

class Texture
{
public:

    static ID3D11ShaderResourceView* load( const wchar_t*FileName );
};