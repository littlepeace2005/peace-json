#ifndef JSON_NULL_H
#define JSON_NULL_H

#include "json.h"

namespace peace
{

class JsonNull: public peace::JsonBase
{
public:
    JsonNull(const JsonNull &) = delete;
    JsonNull(JsonNull &&) noexcept = delete;

    ~JsonNull() override;

    JsonNull &operator=(const JsonNull &) = delete;
    JsonNull &operator=(JsonNull &&) noexcept = delete;
    
    static const JsonNull &getInstance();

private:
    JsonNull();

    JsonBase *copySelf() const override;
    JsonBase *moveSelf() && override;
    void copyTo(JsonBase *) const override;
    void moveTo(JsonBase *) && noexcept override;
    bool isNull() const noexcept override;

    void serialize(std::ostream &) const override;
};
    
} // namespace peace

#endif // JSON_NULL_H
