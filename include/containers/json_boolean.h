#ifndef JSON_BOOLEAN_H
#define JSON_BOOLEAN_H

#include "json.h"

namespace peace
{

class JsonBoolean: public JsonBase
{
public:
    JsonBoolean();
    JsonBoolean(bool);

    ~JsonBoolean() override;

    JsonBoolean &operator=(bool) noexcept;

    operator bool () const noexcept;

private:
    bool m_value;

    JsonBase *copySelf() const override;
    JsonBase *moveSelf() && override;
    void copyTo(JsonBase *) const override;
    void moveTo(JsonBase *) && noexcept override;
    bool isBoolean() const noexcept override;

    void serialize(std::ostream &) const override;

    friend std::ostream &operator<<(std::ostream &, const JsonBoolean &);
    friend std::istream &operator<<(std::istream &, JsonBoolean &);
};
    
} // namespace peace

#endif // JSON_BOOLEAN_H