module bridge;

twixt::Bridge::Bridge(twixt::Pylon* start, twixt::Pylon* end) : m_start{ start }, m_end{ end }
{
}

twixt::Bridge::Bridge(const Bridge& otherBridge)
{
	m_start = otherBridge.m_start;
	m_end = otherBridge.m_end;
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
