namespace Network {

	/**
	 * @brief 定义了一个接口，用于处理网络响应消息。
	 */
	class IPostResponser {
	public:
		/**
		 * @brief 处理网络响应消息的纯虚方法。
		 *
		 * @param message 网络响应消息对象。
		 */
		virtual void PostProcess(const NetMessageResponse& message) = 0;
	};
}