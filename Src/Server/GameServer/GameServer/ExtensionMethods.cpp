#include <iostream>
#include <functional>
#include <WinSock2.h> // Windows下的Socket API头文件
#pragma comment(lib, "ws2_32.lib") // 链接ws2_32.lib库

using namespace std;

namespace Network {

    // 定义SocketAsyncMethod类型，使用std::function来模拟委托
    typedef std::function<bool(WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE)> SocketAsyncMethod;

    /**
     * @brief Socket类的扩展方法集合。
     */
    class ExtensionMethods {
    public:
        /**
         * @brief 扩展方法，简化Socket类中异步方法的调用模式。
         *
         * 此方法模拟扩展方法的调用，用于简化异步操作的模式。
         * 如果异步操作同步完成，则立即调用回调函数。
         *
         * @param socket 要操作的Socket。
         * @param method 要调用的异步方法。
         * @param callback 完成时的回调函数。
         * @param overlapped 用于异步操作的重叠结构。
         */
        static void InvokeAsyncMethod(SOCKET& socket,
            SocketAsyncMethod method,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE callback,
            WSAOVERLAPPED* overlapped) {
            // 调用指定的异步方法
            if (!method(overlapped, callback)) {
                // 如果方法同步执行完成，则调用回调
                callback(0, 0, overlapped, 0);
            }
        }
    };
}