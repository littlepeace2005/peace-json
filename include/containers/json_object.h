#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <unordered_map>
#include <string>
#include "json.h"

namespace peace
{

class JsonObject: public JsonBase, public std::unordered_map<std::string, Json>
{
public:
    JsonObject();
    JsonObject(const JsonObject &);
    JsonObject(JsonObject &&) noexcept;
    JsonObject(const std::unordered_map<std::string, Json> &);
    JsonObject(std::unordered_map<std::string, Json> &&);
    using unordered_map::unordered_map;

    ~JsonObject() override;

    JsonObject &operator=(const JsonObject &);
    JsonObject &operator=(JsonObject &&) noexcept;
    JsonObject &operator=(const std::unordered_map<std::string, Json> &);
    JsonObject &operator=(std::unordered_map<std::string, Json> &&) noexcept;
    using unordered_map::operator=;

private:
    JsonBase *copySelf() const override;
    JsonBase *moveSelf() && override;
    void copyTo(JsonBase *) const override;
    void moveTo(JsonBase *) && noexcept override;
    bool isObject() const noexcept override;

    void serialize(std::ostream &) const override;
};
    
} // namespace peace

#endif // JSON_OBJECT_H