#include "json.h"

namespace peace
{

Json::Json()
: p_data(getNull()) {}

Json::Json(const Json &other)
: p_data(other.p_data->copySelf()) {}

Json::Json(Json &&other) noexcept
: p_data(other.p_data) { other.p_data = getNull(); }

Json::Json(const JsonBase &val)
: p_data(val.copySelf()) {}

Json::Json(JsonBase &&val)
: p_data(std::move(val).moveSelf()) {}

Json::Json(double n): Json(JsonNumber(n)) {}

Json::Json(const char *str): Json(JsonString(str)) {}

Json::~Json()
{ if (!isNull()) delete p_data; }

Json &Json::operator=(const Json &other)
{ return *this = *other.p_data; }

Json &Json::operator=(Json &&other) noexcept
{
    if (this != &other) {
        if (!isNull()) delete p_data;
        p_data = other.p_data;
        other.p_data = getNull();
    }
    return *this;
}

Json &Json::operator=(const JsonBase &val)
{
    if (p_data != &val) {
        if (typeid(*p_data) == typeid(val))
            val.copyTo(p_data);
        else {
            JsonBase *ptr = val.copySelf();
            if (!isNull()) delete p_data;
            p_data = ptr;
        }
    }
    return *this;
}

Json &Json::operator=(JsonBase &&val)
{
    if (p_data != &val) {
        if (typeid(*p_data) == typeid(val))
            std::move(val).moveTo(p_data);
        else {
            JsonBase *ptr = std::move(val).moveSelf();
            if (!isNull()) delete p_data;
            p_data = ptr;
        }
    }
    return *this;
}

template <typename Bool, typename std::enable_if<
    std::is_same<Bool, bool>::value, int>::type>
Json &Json::operator=(Bool n)
{ *this = JsonBoolean(n); return *this; }
template Json &Json::operator=<bool>(bool);

Json &Json::operator=(double n)
{ *this = JsonNumber(n); return *this; }

template <typename Str, typename std::enable_if<
    std::is_same<Str, std::string>::value, int>::type>
Json &Json::operator=(const Str &str)
{ *this = JsonString(str); return *this; }
template Json &Json::operator=<std::string>(const std::string &);

template <typename Str, typename std::enable_if<
    std::is_same<Str, std::string>::value, int>::type>
Json &Json::operator=(Str &&str)
{ *this = JsonString(std::move(str)); return *this; }
template Json &Json::operator=<std::string>(std::string &&);

Json &Json::operator=(const char *str)
{ *this = JsonString(str); return *this; }

Json &Json::at(size_t pos)
{ return asArray().at(pos); }

const Json &Json::at(size_t pos) const
{ return asArray().at(pos); }

Json &Json::at(const std::string &key)
{ return asObject().at(key); }

const Json &Json::at(const std::string &key) const
{ return asObject().at(key); }

Json &Json::operator[](size_t pos)
{ return asArray()[pos]; }

const Json &Json::operator[](size_t pos) const
{ return asArray()[pos]; }

Json &Json::operator[](const std::string &key)
{ return asObject()[key]; }

Json &Json::operator[](std::string &&key)
{ return asObject()[std::move(key)]; }

JsonArray &Json::asArray()
{ return dynamic_cast<JsonArray &>(*p_data); }

JsonBoolean &Json::asBoolean()
{ return dynamic_cast<JsonBoolean &>(*p_data); }

JsonNumber &Json::asNumber()
{ return dynamic_cast<JsonNumber &>(*p_data); }

JsonObject &Json::asObject()
{ return dynamic_cast<JsonObject &>(*p_data); }

JsonString &Json::asString()
{ return dynamic_cast<JsonString &>(*p_data); }

const JsonArray &Json::asArray() const
{ return dynamic_cast<JsonArray &>(*p_data); }

const JsonBoolean &Json::asBoolean() const
{ return dynamic_cast<JsonBoolean &>(*p_data); }

const JsonNumber &Json::asNumber() const
{ return dynamic_cast<JsonNumber &>(*p_data); }

const JsonObject &Json::asObject() const
{ return dynamic_cast<JsonObject &>(*p_data); }

const JsonString &Json::asString() const
{ return dynamic_cast<JsonString &>(*p_data); }

bool Json::isArray() const noexcept
{ return p_data->isArray(); }

bool Json::isBoolean() const noexcept
{ return p_data->isBoolean(); }

bool Json::isNull() const noexcept
{ return p_data->isNull(); }

bool Json::isNumeric() const noexcept
{ return p_data->isNumeric(); }

bool Json::isObject() const noexcept
{ return p_data->isObject(); }

bool Json::isString() const noexcept
{ return p_data->isString(); }

const JsonNull Json::m_null;

JsonBase *Json::getNull() noexcept
{ return (JsonBase *)&m_null; }

} // namespace peace
