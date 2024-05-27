#ifndef JSON_NUMBER_H
#define JSON_NUMBER_H

#include "json.h"

namespace peace
{

class JsonNumber: public JsonBase
{
public:
    JsonNumber();
    JsonNumber(double);

    ~JsonNumber() override;

    JsonNumber &operator=(double) noexcept;
    JsonNumber &operator+=(double) noexcept;
    JsonNumber &operator-=(double) noexcept;
    JsonNumber &operator*=(double) noexcept;
    JsonNumber &operator/=(double) noexcept;
    JsonNumber &operator++() noexcept;
    JsonNumber &operator--() noexcept;
    JsonNumber operator++(int) noexcept;
    JsonNumber operator--(int) noexcept;

    operator double() const noexcept;

private:
    double m_value;

    JsonBase *copySelf() const override;
    JsonBase *moveSelf() && override;
    void copyTo(JsonBase *) const override;
    void moveTo(JsonBase *) && noexcept override;
    bool isNumeric() const noexcept override;

    void serialize(std::ostream &) const override;

    friend std::ostream &operator<<(std::ostream &, const JsonNumber &);
    friend std::istream &operator>>(std::istream &, JsonNumber &);
};
    
} // namespace peace

#endif // JSON_NUMBER_H
