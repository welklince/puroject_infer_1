#pragma once

// 関数形式マクロ

// インターフェイス解放
#define SAFE_RELEASE(x)   {if(x){x->Release();x = NULL;}}

// メモリ解放
#define SAFE_DELETE(x)         {delete x;x=NULL;}      // 一つ
#define SAFE_DELETE_ARRAY(x)   {delete[] x;x = NULL; } // 配列