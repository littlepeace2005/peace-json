#include "json_array.h"

namespace peace
{

JsonArray::JsonArray() = default;
JsonArray::JsonArray(const JsonArray &) = default;
JsonArray::JsonArray(JsonArray &&) noexcept = default;

JsonArray::JsonArray(const std::vector<value_type> &arr)
: vector(arr) {}

JsonArray::JsonArray(std::vector<value_type> &&arr)
: vector(std::move(arr)) {}

JsonArray::~JsonArray() = default;

JsonArray &JsonArray::operator=(const JsonArray &) = default;
JsonArray &JsonArray::operator=(JsonArray &&) noexcept = default;

JsonArray &JsonArray::operator=(const std::vector<value_type> &arr)
{ vector::operator=(arr); return *this; }

JsonArray &JsonArray::operator=(std::vector<value_type> &&arr) noexcept
{ vector::operator=(std::move(arr)); return *this; }

JsonBase *JsonArray::copySelf() const
{ return new JsonArray(*this); }

JsonBase *JsonArray::moveSelf() &&
{ return new JsonArray(std::move(*this)); }

void JsonArray::copyTo(JsonBase *ptr) const
{ *(JsonArray *)ptr = *this; }

void JsonArray::moveTo(JsonBase *ptr) && noexcept
{ *(JsonArray *)ptr = std::move(*this); }

bool JsonArray::isArray() const noexcept
{ return true; }
    
} // namespace peace