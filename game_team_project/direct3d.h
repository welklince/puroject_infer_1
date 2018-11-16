#pragma once

#include<d3d11.h>
#include"release.h"

// class
class Direct3D
{
private:
    static ID3D11Device*d3d_device_;              //D3Dデバイスインターフェイス
    static ID3D11DeviceContext* device_context_;  //デバイスコンテキストインターフェイス
    static IDXGISwapChain* swap_chain_;          //スワップチェーンインターフェイス
    static D3D_FEATURE_LEVEL feature_level_;       //機能レベル  
    static ID3D11RenderTargetView* render_target_view_;

public:
    static bool init( const HWND hwnd );  //初期化
    static void destroy();                //破棄
    static void clear();                  //画面クリア
    static void present();                //画面更新

    // インターフェイスの取得
    static ID3D11Device* getDevice() { return d3d_device_; }
    static ID3D11DeviceContext* getContext() { return device_context_; }
    static IDXGISwapChain* getChain() { return swap_chain_; }

};