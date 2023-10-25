module pylon;

twixt::Pylon::Pylon(uint16_t line, uint16_t column) : m_line{ line }, m_column{ column }
{
}

void twixt::Pylon::setLine(const uint16_t& line) {
    m_line = line;
}

void twixt::Pylon::setColumn(const uint16_t& column) {
    m_column = column;
}

uint16_t twixt::Pylon::getLine() const {
    return m_line;
}

uint16_t twixt::Pylon::getColumn() const {
    return m_column;
}

