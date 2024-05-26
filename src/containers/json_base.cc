#include <iomanip>
#include "json_base.h"

namespace peace
{
    
JsonBase::JsonBase() = default;
JsonBase::JsonBase(const JsonBase &) = default;
JsonBase::JsonBase(JsonBase &&) noexcept = default;

JsonBase::~JsonBase() = default;

JsonBase &JsonBase::operator=(const JsonBase &) = default;
JsonBase &JsonBase::operator=(JsonBase &&) noexcept = default;

bool JsonBase::isArray() const noexcept
{ return false; }

bool JsonBase::isBoolean() const noexcept
{ return false; }

bool JsonBase::isNull() const noexcept
{ return false; }

bool JsonBase::isNumeric() const noexcept
{ return false; }

bool JsonBase::isObject() const noexcept
{ return false; }

bool JsonBase::isString() const noexcept
{ return false; }

} // namespace peace