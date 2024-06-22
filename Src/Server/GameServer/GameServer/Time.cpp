#include <iostream>
#include <windows.h>
#include <limits.h>

/**
 * @brief Time 类用于精确计时和跟踪帧率，特别适用于需要高精度计时的场景，如游戏开发。
 */
class Time {
public:
    /**
     * @brief 获取已经过的帧数（只读）。
     *
     * @return long long 已经过的帧数。
     */
    static long long getFrameCount() {
        return frameCount;
    }

    /**
     * @brief 获取上一帧完成所用的时间（秒）（只读）。
     *
     * @return float 上一帧完成所用的时间（秒）。
     */
    static float getDeltaTime() {
        return deltaTime;
    }

    /**
     * @brief 获取当前帧开始时的时间（秒）（只读）。这是自游戏开始以来的时间。
     *
     * @return float 当前帧开始时的时间（秒）。
     */
    static float getTime() {
        return time;
    }

    /**
     * @brief 获取自启动以来的实际时间（秒）（只读）。
     *
     * @return float 自启动以来的实际时间（秒）。
     */
    static float getRealtimeSinceStartup() {
        long long currentTicks = ticks();
        return (currentTicks - startupTicks) / 10000000.0f;
    }

    /**
     * @brief 更新计时信息，应在每帧调用。
     */
    static void Tick();

private:
    /**
     * @brief 记录应用程序启动时的计数器值。
     */
    static long long startupTicks;

    /**
     * @brief 记录高精度计数器的频率。
     */
    static long long freq;

    /**
     * @brief 记录上一帧的计数器值。
     */
    static long long lastTick;

    static long long frameCount;
    static float deltaTime;
    static float time;

    /**
     * @brief 调用 Windows API 函数，用于获取高精度计数器的值。
     *
     * @param lpPerformanceCount 高精度计数器的值。
     * @return true 获取成功。
     * @return false 获取失败。
     */
    static bool QueryPerformanceCounter(long long* lpPerformanceCount);

    /**
     * @brief 调用 Windows API 函数，用于获取高精度计数器的频率。
     *
     * @param lpFrequency 高精度计数器的频率。
     * @return true 获取成功。
     * @return false 获取失败。
     */
    static bool QueryPerformanceFrequency(long long* lpFrequency);

    /**
     * @brief 获取当前的计数器值（Tick）。
     *
     * 该属性首先检查 freq 是否已初始化，如果没有，它会调用 QueryPerformanceFrequency 初始化。
     * 如果高精度计时器不可用，它会使用系统时钟的 GetTickCount 进行模拟。
     * 然后，它调用 QueryPerformanceCounter 获取当前计数器值，并将其转换为 100 纳秒（1/10,000,000 秒）为单位的时间。
     *
     * @return long long 当前的计数器值（Tick）。
     */
    static long long ticks();
};

long long Time::frameCount = 0;
float Time::deltaTime = 0;
float Time::time = 0;
long long Time::startupTicks = 0;
long long Time::freq = 0;
long long Time::lastTick = 0;

bool Time::QueryPerformanceCounter(long long* lpPerformanceCount) {
    LARGE_INTEGER count;
    bool result = ::QueryPerformanceCounter(&count);
    *lpPerformanceCount = count.QuadPart;
    return result;
}

bool Time::QueryPerformanceFrequency(long long* lpFrequency) {
    LARGE_INTEGER frequency;
    bool result = ::QueryPerformanceFrequency(&frequency);
    *lpFrequency = frequency.QuadPart;
    return result;
}

long long Time::ticks() {
    if (freq == 0) {
        if (QueryPerformanceFrequency(&freq)) {
            freq = freq;
        }
        else {
            freq = -1;
        }
    }

    if (freq == -1) {
        return static_cast<long long>(GetTickCount()) * 10000;
    }

    long long count = 0;
    QueryPerformanceCounter(&count);
    return static_cast<long long>((static_cast<double>(count) * 1000 * 10000) / static_cast<double>(freq));
}

void Time::Tick() {
    long long currentTicks = ticks();

    frameCount++;
    if (frameCount == LLONG_MAX)
        frameCount = 0;

    if (lastTick == 0) lastTick = currentTicks;
    deltaTime = (currentTicks - lastTick) / 10000000.0f;
    time = (currentTicks - startupTicks) / 10000000.0f;
    lastTick = currentTicks;
}
