#ifndef JSON_H
#define JSON_H

#include "json_base.h"
#include "json_array.h"
#include "json_boolean.h"
#include "json_null.h"
#include "json_number.h"
#include "json_object.h"
#include "json_string.h"

#define JSON_NULL ::peace::JsonNull::getInstance()

namespace peace
{

class JsonArray;
class JsonBoolean;
class JsonNull;
class JsonNumber;
class JsonObject;
class JsonString;

class Json
{
public:
    Json();
    Json(const Json &);
    Json(Json &&) noexcept;
    Json(const JsonBase &);
    Json(JsonBase &&);
    template <typename Bool, typename std::enable_if<
        std::is_same<Bool, bool>::value, int>::type = 0>
    Json(Bool);
    Json(double);
    template <typename Str, typename std::enable_if<
        std::is_same<Str, std::string>::value, int>::type = 0>
    Json(const Str &);
    template <typename Str, typename std::enable_if<
        std::is_same<Str, std::string>::value, int>::type = 0> 
    Json(Str &&);
    Json(const char *);

    ~Json();

    Json &operator=(const Json &);
    Json &operator=(Json &&) noexcept;
    Json &operator=(const JsonBase &);
    Json &operator=(JsonBase &&);
    template <typename Bool, typename std::enable_if<
        std::is_same<Bool, bool>::value, int>::type = 0> 
    Json &operator=(Bool);
    Json &operator=(double);
    template <typename Str, typename std::enable_if<
        std::is_same<Str, std::string>::value, int>::type = 0>
    Json &operator=(const Str &);
    template <typename Str, typename std::enable_if<
        std::is_same<Str, std::string>::value, int>::type = 0>
    Json &operator=(Str &&);
    Json &operator=(const char *);

    Json &at(size_t);
    const Json &at(size_t) const;
    Json &at(const std::string &);
    const Json &at(const std::string &) const;

    Json &operator[](size_t);
    const Json &operator[](size_t) const;
    Json &operator[](const std::string &);
    Json &operator[](std::string &&);

    JsonArray &asArray();
    JsonBoolean &asBoolean();
    JsonNumber &asNumber();
    JsonObject &asObject();
    JsonString &asString();
    const JsonArray &asArray() const;
    const JsonBoolean &asBoolean() const;
    const JsonNumber &asNumber() const;
    const JsonObject &asObject() const;
    const JsonString &asString() const;

    bool isArray() const noexcept;
    bool isBoolean() const noexcept;
    bool isNull() const noexcept;
    bool isNumeric() const noexcept;
    bool isObject() const noexcept;
    bool isString() const noexcept;

    static std::string stringify(const Json &);
    static Json parse(const std::string &);

private:
    JsonBase *p_data;
    static const JsonNull m_null;
    static JsonBase *getNull() noexcept;
    
    friend class JsonNull;
    friend std::ostream &operator<<(std::ostream &, const Json &);
    friend std::istream &operator>>(std::istream &, Json &);
};

template <typename Bool, typename std::enable_if<
    std::is_same<Bool, bool>::value, int>::type>
Json::Json(Bool n)
: Json((JsonBase &&)JsonBoolean(n)) {}
    
template <typename Str, typename std::enable_if<
    std::is_same<Str, std::string>::value, int>::type> 
Json::Json(const Str &str)
: Json((JsonBase &&)JsonString(str)) {}

template <typename Str, typename std::enable_if<
    std::is_same<Str, std::string>::value, int>::type>
Json::Json(Str &&str)
: Json((JsonBase &&)JsonString(std::move(str))) {}

} // namespace peace

#endif // JSON_H
