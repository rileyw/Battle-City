#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "map/tile_loader.h"
#include "map/static_tiled_map.h"
#include "map/map_loader.h"

//  Handles messaging for WinMain
//  http://msdn.microsoft.com/en-us/library/ms633569(v=vs.85).aspx
LONG WINAPI MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    //  Observe uMsg and perform logic on its value
    switch(uMsg)
    {
        //  Handle window closing
        case WM_CLOSE :
        {
            //  Indicate to the system that this thread is closing; otherwise, clean up tasks may not execute
            //  http://msdn.microsoft.com/en-us/library/windows/desktop/ms644945(v=vs.85).aspx
            PostQuitMessage(0);
            return 0;
        }
    }
    //  Calls the default window procedure to provide default processing
    //  for any window messages
    //  http://msdn.microsoft.com/en-us/library/ms633572.aspx
    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

/// <summary>
/// Windows 32 main entry point
/// </summary>
/// <param name="hInstance">Window instance</param>
/// <param name="hPreviousInstance">Previous window instance</param>
/// <param name="lpCmdLine">Command line arguments</param>
/// <param name="nCmdShow">The asynchronous command show.</param>
/// <returns>0</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC) MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = NULL;
	wc.hCursor       = LoadCursor (NULL,IDC_ARROW);
	wc.hbrBackground = (struct HBRUSH__ *)COLOR_GRAYTEXT;
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Battle-City";
    
    if(!RegisterClass(&wc))
    {
        MessageBox(NULL,"Could not register window class","Window class registration failed",MB_ICONEXCLAMATION | MB_OK);
    }
    //  Initialize the display window
    HWND hWnd = CreateWindowEx(
        WS_EX_TOPMOST,
        "Battle-City",
		"Battle City",
        WS_POPUP|WS_VISIBLE|WS_SYSMENU,
        GetSystemMetrics(SM_CXSCREEN)/2-320,
        GetSystemMetrics(SM_CYSCREEN)/2-240,
        640,
        480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    HWND Scene = CreateWindow(
        "STATIC",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
        0,
        0,
        640,
        480,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    sf::RenderWindow SceneWindow(Scene);
    sf::View SceneCamera = SceneWindow.getDefaultView();
    
    StaticTiledMap map;
    MapLoader mapLoader;
    map.LoadFrom(&mapLoader);

    sf::Clock clock;

    MSG message = {};
    message.message = static_cast<UINT>(~WM_QUIT);
    while(message.message != WM_QUIT)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        } else {
            float time = clock.getElapsedTime().asSeconds();
		        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			        SceneCamera.zoom(1.05f);

		        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			        SceneCamera.move(0.f,-10.f);

		        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			        SceneCamera.zoom(0.95f);

		        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			        SceneCamera.move(-10.f,0.f);

		        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			        SceneCamera.move(0.f,10.f);

		        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			        SceneCamera.move(10.f,0.f);
            SceneWindow.setView(SceneCamera);
            SceneWindow.clear();
            SceneWindow.draw(map);
            SceneWindow.display();
        }
    }

    DestroyWindow(hWnd);
    UnregisterClass("Battle City",hInstance);

    return EXIT_SUCCESS;
}