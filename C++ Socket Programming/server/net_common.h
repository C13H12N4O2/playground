#pragma once

#include <iostream>
#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <sys/time.h>
#include <deque>

constexpr uintptr_t SERVER_MSG_EVENT_IDENT = 0xDEADBEEF;
