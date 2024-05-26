#include "json_number.h"

namespace peace
{

JsonNumber::JsonNumber() = default;
JsonNumber::JsonNumber(double n): m_value(n) {}

JsonNumber::~JsonNumber() = default;

JsonNumber &JsonNumber::operator=(double n) noexcept
{ m_value = n; return *this; }

JsonNumber::operator double() const noexcept
{ return m_value; }

JsonBase *JsonNumber::copySelf() const
{ return new JsonNumber(m_value); }

JsonBase *JsonNumber::moveSelf() &&
{ return new JsonNumber(m_value); }

void JsonNumber::copyTo(JsonBase *ptr) const
{ ((JsonNumber *)ptr)->m_value = m_value; }

void JsonNumber::moveTo(JsonBase *ptr) && noexcept
{ ((JsonNumber *)ptr)->m_value = m_value; }

bool JsonNumber::isNumeric() const noexcept
{ return true; }

} // namespace peace