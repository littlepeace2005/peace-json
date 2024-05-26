#ifndef JSON_BASE_H
#define JSON_BASE_H

#include <iostream>

namespace peace
{

class Json;

class JsonBase
{
public:
    JsonBase();
    JsonBase(const JsonBase &);
    JsonBase(JsonBase &&) noexcept;

    virtual ~JsonBase() = 0;

    JsonBase &operator=(const JsonBase &);
    JsonBase &operator=(JsonBase &&) noexcept;

private:
    virtual JsonBase *copySelf() const = 0;
    virtual JsonBase *moveSelf() && = 0;
    virtual void copyTo(JsonBase *) const = 0;
    virtual void moveTo(JsonBase *) && noexcept = 0;

    virtual bool isArray() const noexcept;
    virtual bool isBoolean() const noexcept;
    virtual bool isNull() const noexcept;
    virtual bool isNumeric() const noexcept;
    virtual bool isObject() const noexcept;
    virtual bool isString() const noexcept;

protected:
    virtual void serialize(std::ostream &) const = 0;
    
    friend class Json;
    friend std::ostream &operator<<(std::ostream &, const Json &);
    friend std::istream &operator>>(std::istream &, Json &);
};
    
} // namespace peace

#endif // JSON_BASE_H