#include <vector>

namespace Network {

	/**
	 * @brief 网络会话接口，定义了获取响应数据的方法。
	 */
	class INetSession {
	public:
		/**
		 * @brief 获取响应数据的虚方法，需要子类实现具体逻辑。
		 *
		 * @return 响应数据的字节数组。
		 */
		virtual std::vector<uint8_t> GetResponse() = 0;
	};
}