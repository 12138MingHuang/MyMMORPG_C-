# MyMMORPG

## 项目简介
MyMMORPG 是一个自建的简单服务器框架，采用原生 C++ 实现。该项目旨在提供一个基础的 MMORPG（大型多人在线角色扮演游戏）服务器框架，支持高效的通信和日志记录，方便开发者进行游戏服务器的开发和维护。

## 项目特点
- **原生 C++ 实现**：提供高性能和灵活性。
- **日志记录**：使用 `log4cplus` 库进行日志记录，方便调试和错误追踪。
- **通信协议**：采用 Google 的 `Protobuf`（Protocol Buffers）进行通信协议的序列化和反序列化，保证高效的数据传输和兼容性。
- **客户端**：使用 Unity 引擎开发游戏客户端，提供跨平台支持和高效的渲染能力。

## 依赖库
- **log4cplus**：一个 C++ 的日志库，用于日志记录。
- **Protobuf**：Google 提供的序列化库，用于通信协议的实现。

## 项目结构
```plaintext
MyMMORPG/
│
├── src/                # 源代码目录
│   ├── server/         # 服务器相关代码
│   ├── client/         # 客户端相关代码
│   └── common/         # 公共模块
│
├── logs/               # 日志文件目录
│
├── protos/             # Protobuf 文件目录
│
├── UnityClient/        # Unity 客户端项目
│
├── README.md           # 项目介绍文件
│
└── CMakeLists.txt      # CMake 构建脚本

安装与使用
前置条件
安装 C++ 编译器（如 VS2022 或 Rider）
安装 CMake
安装 Unity 引擎
安装 log4cplus 库
安装 Protobuf 库

贡献指南
欢迎任何形式的贡献！请提交 Pull Request 或者提交 Issue 来帮助改进该项目。

许可证
该项目基于 MIT 许可证进行开源，详情请参见 LICENSE 文件。

联系方式
如有任何问题或建议，请联系：1799385440@qq.com
