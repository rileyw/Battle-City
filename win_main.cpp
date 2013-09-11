#include <windows.h>
#include <SFML/Graphics.hpp>

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

    HWND hWnd = CreateWindowEx(
        WS_EX_TOPMOST,
        "Battle-City",
		"Battle City",
        WS_POPUP|WS_VISIBLE|WS_SYSMENU,
        0,
        0,
        640,
        480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    MSG message = {};
    message.message = static_cast<UINT>(~WM_QUIT);
    while(message.message != WM_QUIT)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            // If a message was waiting in the message queue, process it
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    DestroyWindow(hWnd);
    UnregisterClass("Battle City",hInstance);

    return EXIT_SUCCESS;
}