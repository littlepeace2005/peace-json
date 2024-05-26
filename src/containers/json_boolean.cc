#include "json_boolean.h"

namespace peace
{

JsonBoolean::JsonBoolean() = default;
JsonBoolean::JsonBoolean(bool n): m_value(n) {} 

JsonBoolean::~JsonBoolean() = default;

JsonBoolean &JsonBoolean::operator=(bool n) noexcept
{ m_value = n; return *this; }

JsonBoolean &JsonBoolean::operator&=(bool n) noexcept
{ m_value &= n; return *this; }

JsonBoolean &JsonBoolean::operator|=(bool n) noexcept
{ m_value |= n; return *this; }

JsonBoolean &JsonBoolean::operator^=(bool n) noexcept
{ m_value ^= n; return *this; }

JsonBoolean::operator bool() const noexcept
{ return m_value; }

JsonBase *JsonBoolean::copySelf() const
{ return new JsonBoolean(m_value); }

JsonBase *JsonBoolean::moveSelf() &&
{ return new JsonBoolean(m_value); }

void JsonBoolean::copyTo(JsonBase *ptr) const
{ ((JsonBoolean *)ptr)->m_value = m_value; }

void JsonBoolean::moveTo(JsonBase *ptr) && noexcept
{ ((JsonBoolean *)ptr)->m_value = m_value; }

bool JsonBoolean::isBoolean() const noexcept
{ return true; }

} // namespace peace
