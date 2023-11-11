
export module bridge;
import pylon;
import <regex>;

namespace twixt {
	export class Bridge {

	private:
		 Pylon& m_start; 
		 Pylon& m_end; 
	public:
		Bridge(Pylon& m_start,Pylon& m_end);
		Bridge(const Bridge& otherBridge);
		Bridge(Bridge&& otherBridge) noexcept;
		Bridge& operator=(Bridge&& otherBridge) noexcept;
		Bridge& operator=(const Bridge& otherBridge);
		std::pair<uint16_t, uint16_t>  getStart() const;
		std::pair<uint16_t, uint16_t> getEnd() const;
		void setStart(const Pylon& start); 
		void setEnd(const Pylon& end);
		~Bridge();
		bool isConnectedTo(const Pylon& pylon);
		bool operator==(const Bridge& other) const;
	};
}