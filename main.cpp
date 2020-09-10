#include <iostream>
#include <windows.h>

SYSTEMTIME t;

DWORD WINAPI TreadTime(void* param) {

    for (;; Sleep(2000)) {
        GetSystemTime(&t);
        std::cout << "Time: " << t.wHour << ":" << t.wMinute << ":" << t.wSecond << std::endl;
    }

    return 0;
}

int main()
{
    char* pValue;
    size_t len;
    errno_t err = _dupenv_s(&pValue, &len, "MYTIME");

    int valueTime = 0;

    if (err == 0 && pValue != nullptr) {
        printf("MYTIME = %s\n", pValue);
        valueTime = atoi(pValue) * 1000;
    }

    std::cout << valueTime << std::endl;

    HANDLE thread = CreateThread(0, 0, TreadTime, 0, 0, 0);

    Sleep(valueTime);

    return 0;
}
