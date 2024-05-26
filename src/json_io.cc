#include <iomanip>
#include <sstream>
#include "json_base.h"
#include "json_array.h"
#include "json_boolean.h"
#include "json_null.h"
#include "json_number.h"
#include "json_object.h"
#include "json_string.h"

namespace peace
{
// serialization
std::ostream &printStr(std::ostream &os, const std::string &str)
{
    os << std::hex << '"';
    for (std::string::const_iterator i = str.begin(); i != str.end(); i++) {
        switch (*i){
          case '\"': case '\\': case '\b':
          case '\f': case '\n': case '\r': 
          case '\t': os << '\\'; // fall through
          default:
            if (*i < 0x20 || *i > 0x7f)
                os << "\\u" << std::setw(4)
                    << std::setfill('0') << (int)*i;
            else os << *i;
        }
    }
    os << '"' << std::dec;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Json &n)
{ n.p_data->serialize(os); return os; }

void JsonArray::serialize(std::ostream &os) const
{
    os << '[';
    for (const_iterator i = begin(); i != end(); i++)
        os << *i << (std::next(i) == end() ? "" : ", ");
    os << ']';
}

void JsonBoolean::serialize(std::ostream &os) const
{ os << (m_value ? "true" : "false"); }

void JsonNull::serialize(std::ostream &os) const
{ os << "null"; }

void JsonNumber::serialize(std::ostream &os) const
{ os << m_value; }

void JsonObject::serialize(std::ostream &os) const
{
    os << '{';
    for (const_iterator i = begin(); i != end(); i++)
        printStr(os, i->first) << ": "
            << i->second << (std::next(i) == end() ? "" : ", ");
    os << '}';
}

void JsonString::serialize(std::ostream &os) const
{ printStr(os, *this); }


std::string Json::stringify(const Json &v)
{
    std::ostringstream ss;
    ss << v;
    return ss.str();
}

// deserialization
std::istream &consumeWhilteSpace(std::istream &is)
{
    char ch;
    while (is >> ch) {
        if (std::isspace(ch)) continue;
        is.putback(ch);
        break;
    }
    return is;
}

std::string scanLiteral(std::istream &is)
{
    std::string str;
    char ch;
    std::ios_base::fmtflags flags = is.flags();
    consumeWhilteSpace(is) >> std::noskipws;
    while (is >> ch) {
        if (ch != ',' && ch != '}' &&
            ch != ']' && !std::isspace(ch))
        { str.push_back(ch); continue; }
        is.putback(ch);
        break;
    }
    is.flags(flags);
    return str;
}

std::vector<Json> scanArray(std::istream &);
double scanNumber(std::istream &);
std::unordered_map<std::string, Json> scanObject(std::istream &);
std::string scanString(std::istream &);

Json deserialize(std::istream &is)
{
    char ch;
    is >> ch;
    is.putback(ch);
    if (ch == '[')
        return JsonArray(scanArray(is));
    else if (ch == '{')
        return JsonObject(scanObject(is));
    else if (std::isdigit(ch) || ch == '+' || ch == '-' )
        return scanNumber(is);
    else if (ch == '"')
        return scanString(is);
    else {
        std::string str = scanLiteral(is);
        if (str == "true") return true;
        else if (str == "false") return false;
        else if (str == "null") return Json();
    }
    throw std::runtime_error("Unexpected character");
}

std::istream &operator>>(std::istream &is, Json &n)
{ n = deserialize(is); return is; }

std::vector<Json> scanArray(std::istream &is)
{
    std::vector<Json> arr;
    char ch;
    consumeWhilteSpace(is) >> ch;
    if (ch != '[')
        throw std::runtime_error("Expected '['");
    do {
        if (consumeWhilteSpace(is).peek() == ']')
        { is.get(); break; }
        arr.push_back(deserialize(is));
        consumeWhilteSpace(is) >> ch;
        if (ch == ']') break;
        if (ch == ',') continue;
        throw std::runtime_error("Expected ',' or ']'");
    } while(true);
    return arr;
}

double scanNumber(std::istream &is)
{
    try { return std::stod(scanLiteral(is)); }
    catch (const std::invalid_argument &)
    { throw std::runtime_error("Expected a number literal"); }
}

std::unordered_map<std::string, Json> scanObject(std::istream &is)
{
    std::unordered_map<std::string, Json> obj;
    char ch;
    consumeWhilteSpace(is) >> ch;
    if (ch != '{')
        throw std::runtime_error("Expected '{'");
    do {
        if (consumeWhilteSpace(is).peek() == '}')
        { is.get(); break; }
        std::string key = scanString(is);
        consumeWhilteSpace(is) >> ch;
        if (ch != ':')
            throw std::runtime_error("Expected ':'");
        obj[std::move(key)] = deserialize(is);
        consumeWhilteSpace(is) >> ch;
        if (ch == '}') break;
        if (ch == ',') continue;
        throw std::runtime_error("Expected ',' or '}'");
    } while (true);
    return obj;
}

std::string scanString(std::istream &is)
{
    std::string str;
    char ch;
    consumeWhilteSpace(is) >> ch;
    if (ch != '"')
        throw std::runtime_error("Expected '\"'");
    std::ios_base::fmtflags flags = is.flags();
    is >> std::noskipws;
    while (is >> ch) {
        if (ch == '\\') {
            is >> ch;
            switch (ch) {
              case '\"': str.push_back('\"'); break;
              case '\\': str.push_back('\\'); break;
              case '/':  str.push_back('/'); break;
              case 'b':  str.push_back('\b'); break;
              case 'f':  str.push_back('\f'); break;
              case 'n':  str.push_back('\n'); break;
              case 'r':  str.push_back('\r'); break;
              case 't':  str.push_back('\t'); break;
              default: throw std::runtime_error("Invalid escape sequence");
            }
        } else if (ch == '"')
            break;
        else
            str.push_back(ch);
    }
    is.flags(flags);
    return str;
}

Json Json::parse(const std::string &s)
{
    std::istringstream ss(s);
    Json n;
    ss >> n;
    return n;
}

// JsonBoolean & JsonNumber
std::ostream &operator<<(std::ostream &os, const JsonBoolean &n)
{ os << (bool)n; return os; }

std::istream &operator<<(std::istream &is, JsonBoolean &n)
{ is >> n.m_value; return is; }

std::ostream &operator<<(std::ostream &os, const JsonNumber &n)
{ os << (double)n; return os; }

std::istream &operator<<(std::istream &is, JsonNumber &n)
{ is >> n.m_value; return is; }
    
} // namespace peace
