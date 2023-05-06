#include "Application.hpp"

#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow) {
#else
int main() {
#endif
    auto application = Application();
    application.Run();
    return EXIT_SUCCESS;
}