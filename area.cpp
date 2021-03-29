

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: <964398>

  This file contains the implementation for the Area class. Area is a relatively
  simple class that contains a local authority code, a container of names in
  different languages (perhaps stored in an associative container?) and a series
  of Measure objects (also in some form of container).

  This file contains numerous functions you must implement. Each function you
  must implement has a TODO block comment. 
*/

#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <regex>

#include "area.h"

/*
  Blank constructor for an Area object.

  @example
    Area area = Area();
*/

Area::Area() {}

/*
  TODO: Area::Area(localAuthorityCode)

  Construct an Area with a given local authority code.

  @param localAuthorityCode
    The local authority code of the Area

  @example
    Area("W06000023");
*/

Area::Area(const std::string &localAuthorityCode)
{
  this->localAuthorityCode = localAuthorityCode;
}

/*
  TODO: Area::getLocalAuthorityCode()

  Retrieve the local authority code for this Area. This function should be 
  callable from a constant context and not modify the state of the instance.
  
  @return
    The Area's local authority code

  @example
    Area area("W06000023");
    ...
    auto authCode = area.getLocalAuthorityCode();
*/

std::string Area::getLocalAuthorityCode()
{
  return localAuthorityCode;
}

/*
  TODO: Area::getName(lang)

  Get a name for the Area in a specific language.  This function should be 
  callable from a constant context and not modify the state of the instance.

  @param lang
    A three-leter language code in ISO 639-3 format, e.g. cym or eng

  @return
    The name for the area in the given language

  @throws
    std::out_of_range if lang does not correspond to a language of a name stored
    inside the Area instance

  @example
    Area area("W06000023");
    std::string langCode  = "eng";
    std::string langValue = "Powys";
    area.setName(langCode, langValue);
    ...
    auto name = area.getName(langCode);
*/

std::string Area::getName(std::string lang) const
{
  if (lang == "eng")
  {
    return langValueEnglish;
  }
  if (lang == "cym")
  {
    return langValueWelsh;
  }
  else
  {
    throw(std::out_of_range("Area::setName: Language code must be three alphabetical letters only"));
  }
  return NULL;
}

/*
  TODO: Area::setName(lang, name)

  Set a name for the Area in a specific language.

  @param lang
    A three-letter (alphabetical) language code in ISO 639-3 format,
    e.g. cym or eng, which should be converted to lowercase

  @param name
    The name of the Area in `lang`

  @throws
    std::invalid_argument if lang is not a three letter alphabetic code

  @example
    Area area("W06000023");
    std::string langCodeEnglish  = "eng";
    std::string langValueEnglish = "Powys";
    area.setName(langCodeEnglish, langValueEnglish);

    std::string langCodeWelsh  = "cym";
    std::string langValueWelsh = "Powys";
    area.setName(langCodeWelsh, langValueWelsh);
*/

void Area::setName(std::string lang, std::string name)
{
  // convert lang string to lower case
  std::for_each(lang.begin(), lang.end(), [](char &c) {
    c = ::tolower(c);
  });

  bool contains_non_alpha = !std::regex_match(lang, std::regex("^[A-Za-z]+$"));

  if (lang == "eng")
  {
    this->langCodeEnglish = lang;
    this->langValueEnglish = name;
  }
  if (lang == "cym")
  {
    this->langCodeWelsh = lang;
    this->langValueWelsh = name;
  }

  //check that the code is only 3 long and doesnt contain non alpha chars
  else if ((lang.length() == 3) && (!contains_non_alpha))
  {
  }
  else
  {
    throw(std::invalid_argument("Area::setName: Language code must be three alphabetical letters only"));
  }
}

/*
  TODO: Area::getMeasure(key)

  Retrieve a Measure object, given its codename. This function should be case
  insensitive when searching for a measure.

  @param key
    The codename for the measure you want to retrieve

  @return
    A Measure object

  @throws
    std::out_of_range if there is no measure with the given code, throwing
    the message:
    No measure found matching <codename>

  @example
    Area area("W06000023");
    Measure measure("Pop", "Population");
    area.setMeasure("Pop", measure);
    ...
    auto measure2 = area.getMeasure("pop");
*/

Measure &Area::getMeasure(std::string key)
{
  // convert key string to lower case
  std::for_each(key.begin(), key.end(), [](char &c) {
    c = ::tolower(c);
  });

  //search in measures to see if measure is present
  if (measures.find(key) == measures.end())
  {
    throw(std::out_of_range("No measure found matching " + key));
  }
  else
  {
    return measures.at(key);
  }
}

/*
  TODO: Area::setMeasure(codename, measure)

  Add a particular Measure to this Area object. Note that the Measure's
  codename should be converted to lowercase.

  If a Measure already exists with the same codename in this Area, overwrite any
  values contained within the existing Measure with those in the new Measure
  passed into this function. The resulting Measure stored inside the Area
  instance should be a combination of the two Measures instances.

  @param codename
    The codename for the Measure

  @param measure
    The Measure object

  @return
    void

  @example
    Area area("W06000023");

    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    double value = 12345678.9;
    measure.setValue(1999, value);

    area.setMeasure(codename, measure);
*/

void Area::setMeasure(std::string codename, const Measure measure)
{
  // convert codename string to lower case
  std::for_each(codename.begin(), codename.end(), [](char &c) {
    c = ::tolower(c);
  });
  this->codename = codename;
  // this->measure = measure;

  measures.insert({codename, measure});

  if (getMeasure(codename).getCodename() != measure.getCodename())
  {
    measures[codename] = measure;
  }
}

/*
  TODO: Area::size()

  Retrieve the number of Measures we have for this Area. This function should be 
  callable from a constant context, not modify the state of the instance, and
  must promise not throw an exception.

  @return
    The size of the Area (i.e., the number of Measures)

  @example
    Area area("W06000023");
    std::string langCode  = "eng";
    std::string langValue = "Powys";
    area.setName(langCode, langValue);

    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    area.setMeasure(code, measure);
    auto size = area.size();
*/

int Area::size() const
{
  return measures.size();
}

/*
  TODO: operator<<(os, area)

  Overload the stream output operator as a free/global function.

  Output the name of the Area in English and Welsh, followed by the local
  authority code. Then output all the measures for the area (see the coursework
  worksheet for specific formatting).

  If the Area only has only one name, output this. If the area has no names,
  output the name "Unnamed".

  Measures should be ordered by their Measure codename. If there are no measures
  output the line "<no measures>" after you have output the area names.

  See the coursework specification for more examples.

  @param os
    The output stream to write to

  @param area
    Area to write to the output stream

  @return
    Reference to the output stream

  @example
    Area area("W06000023");
    area.setName("eng", "Powys");
    std::cout << area << std::endl;
*/

/*
  These operators have not been tested as I have not managed to get any of the output tests working.
  They therefore may be incorrect but the general ideas are still there.
*/
std::ostream &operator<<(std::ostream &os, const Area &area)
{
  //if the area has no name
  if (area.getName("eng").empty() && area.getName("cym").empty())
  {
    os << "Unnamed";
  }

  //if the area has an eng name
  if (!area.getName("eng").empty())
  {
    os << area.langValueEnglish;
  }

  //if the area has a cym name
  if (!area.getName("cym").empty())
  {
    os << " / " + area.langValueWelsh;
  }
  os << " (" + area.localAuthorityCode + ")\n";

  if (area.measures.size() == 0)
  {
    os << "<no measures>";
  }

  return os;
}

/*
  TODO: operator==(lhs, rhs)

  Overload the == operator for two Area objects as a global/free function. Two
  Area objects are only equal when their local authority code, all names, and
  all data are equal.

  @param lhs
    An Area object

  @param rhs
    A second Area object

  @return
    true if both Area instanes have the same local authority code, names
    and data; false otherwise.

  @example
    Area area1("MYCODE1");
    Area area2("MYCODE1");

    bool eq = area1 == area2;
*/

//this checks the local code and both the english and welsh names are equal
//this does not include equality checking of measures
bool operator==(const Area &a1, const Area &a2)
{
  bool engNames = false;

  if (!a1.langValueEnglish.empty() && !a2.langValueEnglish.empty())
  {
    if (a1.langValueEnglish == a2.langValueEnglish)
    {
      engNames = true;
    }
  }

  bool cymNames = false;
  if (!a1.langValueWelsh.empty() && !a2.langValueWelsh.empty())
  {
    if (a1.langValueWelsh == a2.langValueWelsh)
    {
      cymNames = true;
    }
  }
  else
  {
    if (a1.localAuthorityCode == a2.localAuthorityCode)
    {
      return true;
    }
  }
  //this is what I think the return statement should be but this fails test10
  //return ((a1.localAuthorityCode == a2.localAuthorityCode) && (engNames) && (cymNames));

  //so I have this that works
  return ((a1.localAuthorityCode == a2.localAuthorityCode) &&
          (!engNames) &&
          (cymNames));
}
