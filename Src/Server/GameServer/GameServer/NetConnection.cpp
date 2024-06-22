//#include <iostream>
//#include <vector>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <mswsock.h>
//#include <functional>
//#include <cassert>
//
//#pragma comment(lib, "ws2_32.lib")
//
//namespace Network {
//
//	/**
//	 * @brief 表示连接到服务器的连接类。
//	 *
//	 * @tparam T 必须继承自 INetSession。
//	 */
//	template <typename T>
//	class NetConnection {
//		static_assert(std::is_base_of<INetSession, T>::value, "T 必须继承自 INetSession");
//
//	public:
//		/**
//		 * @brief 表示用于通知监听器 ServerConnection 已接收到数据的回调。
//		 *
//		 * @param sender 回调的发送者。
//		 * @param e 包含接收数据的 DataEventArgs 对象。
//		 */
//		using DataReceivedCallback = std::function<void(NetConnection<T>& sender, DataEventArgs& e)>;
//
//		/**
//		 * @brief 表示用于通知监听器 ServerConnection 已断开连接的回调。
//		 *
//		 * @param sender 回调的发送者。
//		 * @param e ServerConnection 使用的 SocketAsyncEventArgs 对象。
//		 */
//		using DisconnectedCallback = std::function<void(NetConnection<T>& sender, LPWSAOVERLAPPED e)>;
//
//	private:
//
//#pragma region 类内部的类(嵌套类)
//
//		/**
//		 * @brief 内部状态类。
//		 */
//		class State {
//		public:
//			DataReceivedCallback dataReceived;
//			DisconnectedCallback disconnectedCallback;
//			SOCKET socket;
//		};
//
//#pragma endregion
//
//#pragma region 字段
//
//		LPWSAOVERLAPPED eventArgs;
//		PackageHandler<NetConnection<T>> packageHandler;
//		T session;
//
//#pragma endregion
//
//
//	public:
//		/**
//		 * @brief 构造一个连接到服务器的连接对象，始终异步监听。
//		 *
//		 * @param socket 连接使用的 Socket。
//		 * @param args 异步接收使用的 SocketAsyncEventArgs。
//		 * @param dataReceived 接收到数据时调用的回调。
//		 * @param disconnectedCallback 断开连接时调用的回调。
//		 * @param session 会话对象。
//		 */
//		NetConnection(SOCKET socket, LPWSAOVERLAPPED args, DataReceivedCallback dataReceived,
//			DisconnectedCallback disconnectedCallback, T session)
//			: session(session), packageHandler(*this) {
//			auto state = new State{ dataReceived, disconnectedCallback, socket };
//			eventArgs = args;
//			eventArgs->hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
//			eventArgs->Pointer = state;
//
//			BeginReceive();
//		}
//
//		/**
//		 * @brief 断开客户端连接。
//		 */
//		void Disconnect() {
//			CloseConnection();
//		}
//
//		/**
//		 * @brief 发送数据到客户端。
//		 *
//		 * @param data 要发送的数据。
//		 */
//		void SendData(const std::vector<uint8_t>& data) {
//			auto state = static_cast<State*>(eventArgs->Pointer);
//			SOCKET socket = state->socket;
//			if (socket != INVALID_SOCKET) {
//				WSABUF buffer;
//				buffer.buf = reinterpret_cast<CHAR*>(const_cast<uint8_t*>(data.data()));
//				buffer.len = data.size();
//
//				DWORD bytesSent;
//				int result = WSASend(socket, &buffer, 1, &bytesSent, 0, nullptr, nullptr);
//				if (result == SOCKET_ERROR) {
//					std::cerr << "WSASend failed: " << WSAGetLastError() << std::endl;
//				}
//			}
//		}
//
//		/**
//		 * @brief 发送响应数据到客户端。
//		 */
//		void SendResponse() {
//			std::vector<uint8_t> data = session.GetResponse();
//			SendData(data);
//		}
//
//	private:
//		/**
//		 * @brief 开始异步接收。
//		 */
//		void BeginReceive() {
//			auto state = static_cast<State*>(eventArgs->Pointer);
//			SOCKET socket = state->socket;
//
//			if (socket != INVALID_SOCKET) {
//				WSABUF buffer;
//				buffer.buf = new CHAR[64 * 1024];
//				buffer.len = 64 * 1024;
//
//				DWORD flags = 0;
//				DWORD bytesReceived;
//
//				int result = WSARecv(socket, &buffer, 1, &bytesReceived, &flags, eventArgs, nullptr);
//				if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) {
//					std::cerr << "WSARecv failed: " << WSAGetLastError() << std::endl;
//					CloseConnection();
//				}
//			}
//		}
//
//		/**
//		 * @brief 异步接收完成后的回调。
//		 *
//		 * @param error 错误码。
//		 * @param bytesTransferred 传输的字节数。
//		 * @param overlapped 异步操作的重叠结构。
//		 */
//		static void ReceivedCompleted(DWORD error, DWORD bytesTransferred, LPWSAOVERLAPPED overlapped, DWORD flags) {
//			auto state = static_cast<State*>(overlapped->Pointer);
//
//			if (bytesTransferred == 0 || error != NO_ERROR) {
//				state->disconnectedCallback(*static_cast<NetConnection*>(state), overlapped);
//				return;
//			}
//
//			std::vector<uint8_t> data(overlapped->Pointer, overlapped->Pointer + bytesTransferred);
//			DataEventArgs eventArgs{/* RemoteEndPoint */nullptr, data, 0, static_cast<int>(bytesTransferred) };
//			state->dataReceived(*static_cast<NetConnection*>(state), eventArgs);
//
//			static_cast<NetConnection*>(state)->BeginReceive();
//		}
//
//		/**
//		 * @brief 关闭连接。
//		 */
//		void CloseConnection() {
//			auto state = static_cast<State*>(eventArgs->Pointer);
//			SOCKET socket = state->socket;
//			if (socket != INVALID_SOCKET) {
//				shutdown(socket, SD_BOTH);
//				closesocket(socket);
//				state->socket = INVALID_SOCKET;
//			}
//
//			CloseHandle(eventArgs->hEvent);
//			delete state;
//		}
//	};
//}
