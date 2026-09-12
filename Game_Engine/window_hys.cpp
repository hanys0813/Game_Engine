#include <windows.h>

LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}

int main()
{
    HINSTANCE instance = GetModuleHandleW(nullptr);
    const wchar_t* className = L"HysWindowClass";

    // Register the window class.
    WNDCLASSW windowClass{};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = className;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground =
        reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

    if (!RegisterClassW(&windowClass))
        return 1;

    // Create the window.
    HWND window = CreateWindowExW(
        0,
        className,
        L"Game Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        nullptr,
        nullptr,
        instance,
        nullptr
    );

    if (!window)
        return 1;

    ShowWindow(window, SW_SHOW);

    // Process window messages.
    MSG message{};
    BOOL result;

    while ((result = GetMessageW(&message, nullptr, 0, 0)) > 0)
    {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    return result == -1 ? 1 : static_cast<int>(message.wParam);
}