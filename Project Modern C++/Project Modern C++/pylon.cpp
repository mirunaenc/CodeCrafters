
module pylon;

twixt::Pylon::Pylon(uint16_t line, uint16_t column) : m_line{ line }, m_column{ column }
{
    m_color = EColor::NONE;
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

bool twixt::Pylon::operator==(const Pylon& other) const
{
    return this->m_line == other.m_line && this->m_column == other.m_column && this->m_color == other.m_color;
}

void twixt::Pylon::setColor(twixt::EColor color)
{
    m_color = color;
}

twixt::EColor twixt::Pylon::getColor() const
{
    return m_color;
}

twixt::Pylon::~Pylon()
{
}


