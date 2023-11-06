#include <cstdint>
module pylon;

twixt::Pylon::Pylon(uint16_t line, uint16_t column) : m_line{ line }, m_column{ column }
{
}

void twixt::Pylon::setLine(uint16_t line) {
    m_line = line;
}

void twixt::Pylon::setColumn(uint16_t column) {
    m_column = column;
}

uint16_t twixt::Pylon::getLine() const {
    return m_line;
}

uint16_t twixt::Pylon::getColumn() const {
    return m_column;
}

twixt::Pylon::Pylon(const Pylon& pylon) : m_line{ pylon.m_line }, m_column{ pylon.m_column }/*, owner{ pylon.owner }*/ {}

twixt::Pylon& twixt::Pylon::operator=(const Pylon& pylon)
{
    if (this != &pylon) { 
        m_line = pylon.m_line;
        m_column = pylon.m_column;
       
    }
    return *this;
}

bool twixt::Pylon::operator==(const Pylon& other) const
{
    return this->m_line == other.m_line && this->m_column == other.m_column;
}

