#include "json_object.h"

namespace peace
{
    
JsonObject::JsonObject() = default;
JsonObject::JsonObject(const JsonObject &) = default;
JsonObject::JsonObject(JsonObject &&) noexcept = default;

JsonObject::JsonObject(const std::unordered_map<std::string, Json> &obj)
: unordered_map(obj) {}

JsonObject::JsonObject(std::unordered_map<std::string, Json> &&obj)
: unordered_map(std::move(obj)) {}

JsonObject::~JsonObject() = default;

JsonObject &JsonObject::operator=(const JsonObject &) = default;
JsonObject &JsonObject::operator=(JsonObject &&) noexcept = default;

JsonObject &JsonObject::operator=(const std::unordered_map<std::string, Json> &obj)
{ unordered_map::operator=(obj); return *this; }

JsonObject &JsonObject::operator=(std::unordered_map<std::string, Json> &&obj) noexcept
{ unordered_map::operator=(std::move(obj)); return *this; }

JsonBase *JsonObject::copySelf() const
{ return new JsonObject(*this); }

JsonBase *JsonObject::moveSelf() &&
{ return new JsonObject(std::move(*this)); }

void JsonObject::copyTo(JsonBase *ptr) const
{ *(JsonObject *)ptr = *this; }

void JsonObject::moveTo(JsonBase *ptr) && noexcept
{ *(JsonObject *)ptr = std::move(*this); }

bool JsonObject::isObject() const noexcept
{ return true; }

} // namespace peace