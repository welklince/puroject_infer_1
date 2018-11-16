#include<Windows.h>
#include<d3d11.h>
#include<cstdio>
#include<ctime>
#include<Keyboard.h>

#include"common.h"
#include"game.h"
#include"pad.h"
#include"direct3d.h"
#include"sprite.h"

//// 列挙体
//enum
//{
//    kTitleinit,   // タイトル画面初期化
//    kTitleUpdate, // タイトル画面更新(描画)
//    kGameInit,    // ゲーム画面初期化
//    kGameUpdate   // ゲーム画面更新(描画)
//};

//プロトタイプ宣言
LRESULT CALLBACK WinProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow )
{
    srand( time( NULL ) );

    //ウィンドウクラスの作成
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );    //構造体サイズ
    wnd.style = CS_HREDRAW | CS_VREDRAW; //スタイル
    wnd.hInstance = hInstance;               //アプリケーションインストール
    wnd.lpszClassName = "ClassName";             //クラス名
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW ); //カーソル形状
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;                 //ウィンドウプロシージャへの関数ポインタ

    //登録
    if( !RegisterClassEx( &wnd ) )
    {
        //エラー
        return 0;
    }

    //ウィンドウサイズを決定
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;
    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );

    //ウィンドウの作成
    const HWND hwnd = CreateWindowEx(
        ex_style,               //拡張ウィンドウスタイル
        "ClassName",            //クラス名
        "Title",                //ウィンドウスタイル
        style,                  //ウィンドウスタイル
        CW_USEDEFAULT,          //表示座標X
        CW_USEDEFAULT,          //表示座標Y
        rect.right - rect.left, //ウィンドウ横幅
        rect.bottom - rect.top, //ウィンドウ縦幅
        NULL,                   //親ウィンドウへのハンドル
        NULL,                   //メニューハンドル
        hInstance,              //アプリケーションインスタンス
        NULL                    //ウィンドウ作成データ
    );

    //NULLチェック
    if( hwnd == NULL )
    {
        //エラー
        return 0;
    }

    //Direct3D初期化
    if( !Direct3D::init( hwnd ) )
    {
        // エラー 
        return 0;
    }

    //COMライブラリの初期化
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        //エラー
        return 0;
    }

    // spriteクラス初期化
    if( !Sprite::init() )
    {
        // エラー
        return 0;
    }

    // Commonクラスの作成
    if( !Common::init() )
    {
        // エラー
        return 0;
    }

    // シーンクラス変数
    Game game;

    game.init();

    //ウィンドウの表示
    ShowWindow( hwnd, SW_SHOWNORMAL );

    //メインループ
    MSG msg = { NULL };

    // 時間計測
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    //// 現在の作業番号
    //int work_no = kTitleinit;

    while( msg.message != WM_QUIT )
    {
        //メッセージ処理
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // フレームレート制御
            t1 = timeGetTime();   // 現在の時間
            dt = (t1 - t2) + t3;  //前回の更新からの差分を計算

            // 約16ミリ秒経過していたら処理を行う
            if( dt > 16 )
            {
                t2 = t1;       // 今の時間を前回の時間にする
                t3 = dt % 16;  // 誤差分を吸収

                //// 更新処理
                // コントローラクラスの更新 
                Pad::update();

                game.update();


                //// 描画処理
                // 画面クリア
                Direct3D::clear();

                //スプライト描画開始
                Sprite::begin();

                game.draw();

                //スプライトの描画終了
                Sprite::end();

                //画面更新
                Direct3D::present();
            }
        }
    }

    //COMライブラリの解放
    CoUninitialize();

    // インターフェイスの解放
    game.destroy();
    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();

    return 0;
}

LRESULT CALLBACK WinProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hwnd, &ps );
        EndPaint( hwnd, &ps );
        break;
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

    case WM_KEYDOWN:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        switch( wParam )
        {
        case VK_ESCAPE:
            //ESCが押されたらループを終了する
            PostMessage( hwnd, WM_CLOSE, 0, 0 );
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hwnd, Msg, wParam, lParam );
}
