module;

export module bridge;
import pylon;
import <regex>;

namespace twixt {
	export class Bridge {

	private:
		twixt::Pylon* m_start;
		twixt::Pylon* m_end;
	public:
		Bridge(twixt::Pylon* m_start = nullptr, twixt::Pylon* m_end = nullptr);
		Bridge(const Bridge& otherBridge);
		Bridge& operator=(const Bridge& otherBridge);
		std::pair<uint16_t, uint16_t>  getStart() const;
		std::pair<uint16_t, uint16_t> getEnd() const;
		void setStart(const twixt::Pylon*& start);
		void setEnd(const twixt::Pylon*& end);
		~Bridge();
	};
}