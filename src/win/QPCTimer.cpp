/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Microsoft
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file
 *
 * @brief Header file for the QPCTimer class.
 */

#ifdef _WIN32

//Headers
#include <win/QPCTimer.h>

//Libraries
#include <windows.h>

using namespace xmem;

QPCTimer::QPCTimer() :
	Timer(),
	__start_tick(),
	__stop_tick()
{	
	//Override default Timer constructor initialization of __ticks_per_sec and __ns_per_tick using the OS-derived values
	LARGE_INTEGER tmp;
	QueryPerformanceFrequency(&tmp);
	_ticks_per_sec = tmp.QuadPart;
	_ns_per_tick = (1/(double)(_ticks_per_sec)) * 1e9;
}

void QPCTimer::start() {
	QueryPerformanceCounter(&__start_tick);
}

uint64_t QPCTimer::stop() {
	QueryPerformanceCounter(&__stop_tick);
	return (__stop_tick.QuadPart - __start_tick.QuadPart); 
}

uint64_t get_qpc_time() {
	LARGE_INTEGER tmp;
	QueryPerformanceCounter(&tmp);
	return static_cast<uint64_t>(tmp.QuadPart);
}

#else
#error This file should only be used in Windows builds.
#endif
