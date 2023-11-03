module bridge;
import pylon;
import <regex>;

twixt::Bridge::Bridge(Pylon& start, Pylon& end) : m_start{ start }, m_end{ end }
{
}

twixt::Bridge::Bridge(const Bridge& otherBridge) : m_start{ otherBridge.m_start }, m_end{ otherBridge.m_end }
{
	
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

std::pair<uint16_t, uint16_t> twixt::Bridge::getStart() const
{
	return std::make_pair(m_start.getLine(), m_start.getColumn());
}

std::pair<uint16_t, uint16_t> twixt::Bridge::getEnd() const
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
