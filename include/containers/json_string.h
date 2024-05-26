#ifndef JSON_STRING_H
#define JSON_STRING_H

#include <string>
#include "json.h"

namespace peace
{

class JsonString: public JsonBase, public std::string
{
public:
    JsonString();
    JsonString(const JsonString &);
    JsonString(JsonString &&) noexcept;
    JsonString(const std::string &);
    JsonString(std::string &&);
    using basic_string::basic_string;

    ~JsonString() override;

    JsonString &operator=(const JsonString &);
    JsonString &operator=(JsonString &&) noexcept;
    JsonString &operator=(const std::string &);
    JsonString &operator=(std::string &&) noexcept;
    using basic_string::operator=;

private:
    JsonBase *copySelf() const override;
    JsonBase *moveSelf() && override;
    void copyTo(JsonBase *) const override;
    void moveTo(JsonBase *) && noexcept override;
    bool isString() const noexcept override;

    void serialize(std::ostream &) const override;
};
    
} // namespace peace

#endif // JSON_STRING_H