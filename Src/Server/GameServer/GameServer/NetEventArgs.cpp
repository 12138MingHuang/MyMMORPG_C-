#include <vector>
#include <WinSock2.h> // Windows下的Socket API头文件
#include <WS2tcpip.h> // 提供sockaddr_in和inet_ntop等功能
#pragma comment(lib, "ws2_32.lib") // 链接ws2_32.lib库

namespace Network {

    /**
     * @brief 保存字节数组数据以及相关网络信息的类。
     */
    class DataEventArgs {
    public:
        // 远程端点地址
        sockaddr_in RemoteEndPoint;

        // 数据字节数组
        std::vector<uint8_t> Data;

        // 数据偏移量
        int Offset;

        // 数据长度
        int Length;

    };
}