#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    // Initialize window class
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const char *className = "SimpleAppClass";
    
    // Load the icon (check if it's loaded successfully)
    HICON hIcon = (HICON)LoadImage(NULL, "C:\\IBUILDtmp\\StudioX\\Studio_X desktop icon with alpha.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (!hIcon) {
        MessageBox(NULL, "Failed to load icon.", "Error", MB_OK | MB_ICONERROR);
        return 1; // Exit if icon loading fails
    }

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc; // Window procedure
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hIcon = hIcon;  // Set the icon for the window class

    // Register the window class and check for failure
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window class registration failed.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Create window
    HWND hwnd = CreateWindowEx(
        0, className, "Hello Ford - Tai Fong", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwnd == NULL) {
        MessageBox(NULL, "Window creation failed.", "Error", MB_OK | MB_ICONERROR);
        return 1; // Exit if window creation fails
    }

    // Show window
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up: Release the icon when the application exits
    DestroyIcon(hIcon);

    return 0;
}
