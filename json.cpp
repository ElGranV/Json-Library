#include "json.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
using namespace std;

void checkObjectSyntax(string& s)
{
    int accolade = 0, parenthese = 0, crochet = 0;
    bool quote = false, doubleQuote = false;
    removeSpaces(s);
    for (auto& c: s)
    {
        if (c=='{') accolade++;
        if (c=='}')accolade--;
        if (c=='(') parenthese++;
        if (c==')') parenthese--;
        if (c=='[') crochet++;
        if (c==']') crochet--;
        if (c=='"' && !quote) doubleQuote = !doubleQuote;
        if (c=="'"[0] && !doubleQuote) quote = !quote;
        if (accolade < 0 || crochet < 0 || parenthese < 0) throw invalid_argument(s);
    }

    if (accolade!=0 || parenthese!=0 || crochet!=0)
    {
        throw invalid_argument("Une parenthese, un crochet ou une accolade est manquant dans l'objet :\n"+s);
    }
    if (quote || doubleQuote) throw invalid_argument(s);

    for (auto& paire : split(s, ','))
    {

        auto tab = split(paire, ':');
        if (tab.size()!=2) throw invalid_argument(paire);
        if ((tab[0][0]!='"' && tab[0][0]!="'"[0]) || (tab[0].back()!='"' && tab[0].back()!="'"[0])) throw invalid_argument("Guillemet invalide : "+paire);
        if (tab[1][0]!='"')
            {
                if (tab[1]!="null" && tab[1]!="true" && tab[1]!="false" && tab[1][0]!='{' && tab[1][0]!='[' && !isNumber(tab[1]))
                {
                    throw invalid_argument("Argument invalide : ("+paire+") -> "+tab[1]);
                }
            }
    }

}

bool checkObject(string& s)
{
    int accolade = 0, parenthese = 0, crochet = 0;
    bool quote = false, doubleQuote = false;
    removeSpaces(s);
    for (auto& c: s)
    {
        if (c=='{') accolade++;
        if (c=='}')accolade--;
        if (c=='(') parenthese++;
        if (c==')') parenthese--;
        if (c=='[') crochet++;
        if (c==']') crochet--;
        if (c=='"' && !quote) doubleQuote = !doubleQuote;
        if (c=="'"[0] && !doubleQuote) quote = !quote;
        if (accolade < 0 || crochet < 0 || parenthese < 0) return false;
    }

    if (accolade!=0 || parenthese!=0 || crochet!=0)
    {
        return false;
    }
    if (quote || doubleQuote) return false;

    for (auto& paire : split(s, ','))
    {

        auto tab = split(paire, ':');
        if (tab.size()!=2) return false;
        if ((tab[0][0]!='"' && tab[0][0]!="'"[0]) || (tab[0].back()!='"' && tab[0].back()!="'"[0])) return false;
        if (tab[1][0]!='"')
            {
                if (tab[1]!="null" && tab[1]!="true" && tab[1]!="false" && tab[1][0]!='{' && tab[1][0]!='[' && !isNumber(tab[1]))
                {
                    return false;
                }
            }
    }
    return true;

}

bool checkJsonValue(string &s)
{
    if (s.size()==0) return false;
    if (s=="true"||s=="false"||s=="null"||isNumber(s)||(s[0]=='"'&&s.back()=='"'&&s.size()>=2)) return true;
    if (s[0]=='['&&s.back()==']')
       {
            string content = s.substr(1, s.size()-2);
            for (auto& value : split(content, ','))
            {
                if (!checkJsonValue(value)) return false;
            }
            return true;
        }
    if (s[0]=='{' && s.back()=='}')
        {

            string content = s.substr(1, s.size()-2);
            if (!checkObject(content)) return false;
            for (auto& paire: split(content, ','))
            {
                auto tab = split(paire, ':');
                if (!checkJsonValue(tab[1]))  return false;
            }
            return true;
        }
    return false;
}

namespace Json
{
JsonValue::JsonValue()
{
    type = JSON_NULL;
    value = "null";
}



JsonValue::JsonValue(string val)
{

    removeSpaces(val);
    if (!checkJsonValue(val)) throw invalid_argument("Invalid value for json construction : "+val);
    if (val=="true" || val=="false")
    {
        type = BOOLEAN;
        boolean = (val=="true");
        value = val;
    }
    if (val=="null")
    {
        type = JSON_NULL;
        value = val;
    }
    if (isNumber(val))
    {
        number = strtod(val.c_str(), nullptr);
        value =  val;
        type = NUMBER;
    }
    if (val.size()>1)
    {
        if (val[0]=='"' && val.back()=='"')
        {
            type = STRING;
            value = val.substr(1,val.size()-2);

        }
            removeSpaces(val);
            removeEndl(val);
        if (val[0]=='[' && val.back()==']')
        {
            type = ARRAY;
            value = val;

        }
        if (val[0]=='{' && val.back()=='}')
            {

            }

    }


}
JsonValue::JsonValue(const char* c)
{
    string val = c;

    removeSpaces(val);
    if (!checkJsonValue(val)) throw invalid_argument("Invalid value for json construction : "+val);
    if (val=="true" || val=="false")
    {
        type = BOOLEAN;
        boolean = (val=="true");
        value = val;
    }
    if (val=="null")
    {
        type = JSON_NULL;
        value = val;
    }
    if (isNumber(val))
    {
        number = strtod(val.c_str(), nullptr);
        value =  val;
        type = NUMBER;
    }
    if (val.size()>1)
    {
        if (val[0]=='"' && val.back()=='"')
        {
            type = STRING;
            value = val.substr(1,val.size()-2);

        }
            removeSpaces(val);
            removeEndl(val);
        if (val[0]=='[' && val.back()==']')
        {
            type = ARRAY;
            value = val;

        }
        if (val[0]=='{' && val.back()=='}')
            {

            }

    }
}


JsonValue::JsonValue(double val)
{
    number = val;
    value = std::to_string(val);
    type = NUMBER;
}

JsonValue::JsonValue(bool truth)
{
    type = BOOLEAN;
    value = (truth)?"true":"false";
    boolean = truth;
}


const int JsonValue::get_type() const
{
    return type;
}
const string JsonValue::to_string() const
{
    switch (type)
    {
    case NUMBER:
    case STRING:
    case JSON_NULL:
        return value;
    case BOOLEAN:
        return (boolean)?"true":"false";
    case ARRAY:
        {
        string s;
        for (auto& c : value)
        {
            s+=c;
            if (c==',') s+= " ";
        }
        return s;
        }
    case OBJECT:
        return value;

    }
    return "";
}

ostream& operator << (ostream& flux, JsonValue& jsval)
{
    if (jsval.get_type()==STRING) flux<<'"';
    flux << jsval.to_string();
    if (jsval.get_type()==STRING) flux << '"';
    return flux;
}


JsonValue::operator double() const
{
    if (type!=NUMBER) throw TypeError(type, NUMBER);
    return number;
}



JsonValue::operator bool() const
{
    if (type!=BOOLEAN && type!=JSON_NULL) throw TypeError(type, BOOLEAN);
    if (type==JSON_NULL) return false;
    return boolean;
}

JsonValue::operator vector<JsonValue>()
{
    if (type!=ARRAY) throw TypeError(type, ARRAY);
    vector<JsonValue> v;
    string content = value.substr(1, value.size()-2);
    for (auto& s : split(content, ',')) v.push_back(JsonValue(s));
    return v;
}



//------------------------------------------
//TypeError


TypeError::TypeError(int from, int to)
{
    if (0<=from && from <= 5 && 0<= to && to <= 5)
    {
    vector<string> types = {"NUMBER", "STRING", "BOOLEAN", "Null", "ARRAY", "OBJECT"};
    message = "TypeError : invalid cast from type "+types[from]+" to type "+types[to];
    }else
    {
        message = "Type error : invalid cast";
    }
    typeFrom = from;
    typeTo = to;
}

const char* TypeError::what() const noexcept
{
    return message.c_str();
}

}
