#pragma once
#include <regex>
#include <algorithm>
#include "pylon.h"

namespace twixt {
	 class Bridge {

	private:
		Pylon& m_start;
		Pylon& m_end;
	public:
		Bridge();
		Bridge(Pylon& m_start, Pylon& m_end);
		Bridge(const Bridge& otherBridge);
		Bridge(Bridge&& otherBridge) noexcept;
		Bridge& operator=(Bridge&& otherBridge) noexcept;
		Bridge& operator=(const Bridge& otherBridge);
		Pylon& getStart() const;
		Pylon& getEnd() const;
		std::pair<uint16_t, uint16_t>  getCoordStart() const;
		std::pair<uint16_t, uint16_t> getCoordEnd() const;
		void setStart(const Pylon& start);
		void setEnd(const Pylon& end);
		~Bridge();
		bool isConnectedTo(const Pylon& pylon);
		bool operator==(const Bridge& other) const;
		bool intersectsWith(const Bridge& other) const;
	};
}