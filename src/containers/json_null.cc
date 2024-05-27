#include "json_null.h"

namespace peace
{

JsonNull::JsonNull() = default;

JsonNull::~JsonNull() = default;

JsonBase *JsonNull::copySelf() const
{ return Json::getNull(); }

JsonBase *JsonNull::moveSelf() &&
{ return Json::getNull(); }

void JsonNull::copyTo(JsonBase *) const {}
void JsonNull::moveTo(JsonBase *) && noexcept {}

bool JsonNull::isNull() const noexcept
{ return true; }
    
} // namespace peace
