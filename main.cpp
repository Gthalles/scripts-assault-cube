#include <iostream>
#include <windows.h>

HWND getGameWindow(const char *game = "AssaultCube")
{
    HWND window = FindWindow(NULL, game);

    if (!window)
    {
        std::cout << game << " window not found.\n";

        return window;
    }

    std::cout << game << " window captured!\n";

    return window;
}

HANDLE getGameProcessHandler()
{
    DWORD process;
    GetWindowThreadProcessId(getGameWindow(), &process);
    return OpenProcess(PROCESS_ALL_ACCESS, false, process);
}

void setBullet(int bullets, HANDLE handle)
{
    DWORD_PTR memory_address = 0x082F2A0;
    WriteProcessMemory(handle, (LPVOID)memory_address, &bullets, 4, 0);
}

void setGranades(int granades, HANDLE handle)
{
    DWORD_PTR memory_address = 0x082F2A4;
    WriteProcessMemory(handle, (LPVOID)memory_address, &granades, 4, 0);
}

void reload()
{
    HANDLE handle = getGameProcessHandler();

    // std::cout << "\nType the entity address memory: ";
    // std::cin >> memory_address;

    while (true)
    {
        if (GetAsyncKeyState(VK_TAB))
        {
            setBullet(500, handle);
            setGranades(5, handle);
        }
    }
}

int main()
{
    reload();

    return 0;
}