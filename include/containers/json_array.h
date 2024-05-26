#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <vector>
#include "json.h"

namespace peace
{

class JsonArray: public JsonBase, public std::vector<Json>
{
public:
    JsonArray();
    JsonArray(const JsonArray &);
    JsonArray(JsonArray &&) noexcept;
    JsonArray(const std::vector<value_type> &);
    JsonArray(std::vector<value_type> &&);
    using vector::vector;

    ~JsonArray() override;

    JsonArray &operator=(const JsonArray &);
    JsonArray &operator=(JsonArray &&) noexcept;
    JsonArray &operator=(const std::vector<value_type> &);
    JsonArray &operator=(std::vector<value_type> &&) noexcept;

private:
    JsonBase *copySelf() const override;
    JsonBase *moveSelf() && override;
    void copyTo(JsonBase *) const override;
    void moveTo(JsonBase *) && noexcept override;
    bool isArray() const noexcept override;

    void serialize(std::ostream &) const override;
};
    
} // namespace peace

#endif // JSON_ARRAY_H