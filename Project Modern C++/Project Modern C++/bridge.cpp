module bridge;
import pylon;
import <regex>;

twixt::Bridge::Bridge(Pylon& start, Pylon& end) : m_start{ start }, m_end{ end }
{
}

twixt::Bridge::Bridge(const Bridge& otherBridge) : m_start{ otherBridge.m_start }, m_end{ otherBridge.m_end }
{
	
}

twixt::Bridge::Bridge(Bridge&& otherBridge) noexcept : m_start{ otherBridge.m_start }, m_end{ otherBridge.m_end }
{
}

twixt::Bridge& twixt::Bridge::operator=(Bridge&& otherBridge) noexcept
{
	if (this != &otherBridge)
	{
		m_start = otherBridge.m_start;
		m_end = otherBridge.m_end;
	}
	return *this;
}

twixt::Bridge& twixt::Bridge::operator=(const Bridge& otherBridge)
{
	if (this != &otherBridge)
	{
		m_start = otherBridge.m_start;
		m_end = otherBridge.m_end;
	}
	return *this;
}

twixt::Pylon& twixt::Bridge::getStart() const
{
	return m_start;
}

twixt::Pylon& twixt::Bridge::getEnd() const
{
	return m_end;
}

std::pair<uint16_t, uint16_t> twixt::Bridge::getCoordStart() const
{
	return std::make_pair(m_start.getLine(), m_start.getColumn());
}

std::pair<uint16_t, uint16_t> twixt::Bridge::getCoordEnd() const
{
	return std::make_pair(m_end.getLine(), m_end.getColumn());
}

void twixt::Bridge::setStart(const Pylon& start)
{
	m_start = start;
}

void twixt::Bridge::setEnd(const Pylon& end)
{
	m_end = end;
}

twixt::Bridge::~Bridge()
{
	
}

bool twixt::Bridge::isConnectedTo(const Pylon& pylon)
{
	if (this->m_start == pylon || this->m_end == pylon) {
		return true;
	}
	return false;
}

bool twixt::Bridge::operator==(const Bridge& other) const
{
	return this->m_start == other.m_start && this->m_end == other.m_end;
}




