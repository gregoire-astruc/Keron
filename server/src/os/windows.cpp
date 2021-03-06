#include "signal_handlers.h"

#include <cstring>

#include <iostream>
#include <system_error>

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#include <spdlog/spdlog.h>


namespace keron {
namespace server {
std::atomic_int stop{0};

static BOOL handler(DWORD fdwCtrlType)
{

	switch (fdwCtrlType) {
		case CTRL_C_EVENT:
		case CTRL_CLOSE_EVENT:
			spdlog::get("log")->info() << "The server is going DOWN!";
			stop.store(1);
			return TRUE;
		case CTRL_BREAK_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			spdlog::get("log")->info() << "The server is going DOWN!";
			stop.store(1);
			// Same return as the default case.
		default:
			return FALSE;
	}
}

void register_signal_handlers()
{
	spdlog::get("log")->info() << "Registering signal handlers.";
    // We use posix-like retcode, 0 means success.
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)handler, TRUE) != TRUE) {
		auto errcode = static_cast<int>(GetLastError());
		throw std::system_error({errcode, std::system_category()}, "Cannot register signal handler");
	}
}

} // namespace server
} // namespace keron
