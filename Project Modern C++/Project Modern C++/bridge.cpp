module bridge;

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

bool twixt::Bridge::intersectsWith(const twixt::Bridge& other) const {
	int x1 = m_start.getColumn();
	int y1 = m_start.getLine();
	int x2 = m_end.getColumn();
	int y2 = m_end.getLine();

	int x3 = other.getStart().getColumn();
	int y3 = other.getStart().getLine();
	int x4 = other.getEnd().getColumn();
	int y4 = other.getEnd().getLine();

	// Check if the bounding boxes of the line segments overlap
	if (std::max(x1, x2) < std::min(x3, x4) || std::min(x1, x2) > std::max(x3, x4) ||
		std::max(y1, y2) < std::min(y3, y4) || std::min(y1, y2) > std::max(y3, y4)) {
		return false; // Bounding boxes do not overlap, so line segments do not intersect
	}

	// Check for intersection using the cross product
	int crossProduct1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
	int crossProduct2 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
	int crossProduct3 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
	int crossProduct4 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);

	return (crossProduct1 * crossProduct2 <= 0) && (crossProduct3 * crossProduct4 <= 0);
}




