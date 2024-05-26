#include "json_string.h"

namespace peace
{
    
JsonString::JsonString() = default;
JsonString::JsonString(const JsonString &) = default;
JsonString::JsonString(JsonString &&) noexcept = default;

JsonString::JsonString(const std::string &str)
: basic_string(str) {}

JsonString::JsonString(std::string &&str)
: basic_string(std::move(str)) {}

JsonString::~JsonString() = default;

JsonString &JsonString::operator=(const JsonString &) = default;
JsonString &JsonString::operator=(JsonString &&) noexcept = default;

JsonString &JsonString::operator=(const std::string &str)
{ basic_string::operator=(str); return *this; }

JsonString &JsonString::operator=(std::string &&str) noexcept
{ basic_string::operator=(std::move(str)); return *this; }

JsonBase *JsonString::copySelf() const
{ return new JsonString(*this); }

JsonBase *JsonString::moveSelf() &&
{ return new JsonString(std::move(*this)); }

void JsonString::copyTo(JsonBase *ptr) const
{ *(JsonString *)ptr = *this; }

void JsonString::moveTo(JsonBase *ptr) && noexcept
{ *(JsonString *)ptr = std::move(*this); }

bool JsonString::isString() const noexcept
{ return true; }

} // namespace peace