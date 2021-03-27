#ifndef AREA_H_
#define AREA_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: <964398>

  This file contains the Area class declaration. Area objects contain all the
  Measure objects for a given local area, along with names for that area and a
  unique authority code.

  TODO: Read the block comments with TODO in area.cpp to know which 
  functions and member variables you need to declare in this class.
 */

#include <string.h>
#include <stdio.h>

#include "measure.h"

/*
  An Area object consists of a unique authority code, a container for names
  for the area in any number of different languages, and a container for the
  Measures objects.

  TODO: Based on your implementation, there may be additional constructors
  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/

class Area
{
private:
  std::string langCodeWelsh;
  std::string langCodeEnglish;
  std::string langValueWelsh;
  std::string langValueEnglish;

  std::string localAuthorityCode;
  std::string langCode;
  std::string langValue;

  std::string codename;
  Measure measure;

  //allows for find() to be case insensitive
  struct comp
  {
    bool operator()(const std::string &lhs, const std::string &rhs) const
    {
      return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
    }
  };

public:
  Area();
  Area(const std::string &localAuthorityCode);
  std::string getLocalAuthorityCode();
  std::string getName(std::string) const;
  void setName(std::string lang, std::string name);

  void setMeasure(std::string codename, Measure measure);
  Measure &getMeasure(std::string key);
  int size() const;
  std::map<std::string, Measure, comp> measures;

  bool compareChar(char &c1, char &c2);
  bool caseInSensStringCompare(std::string &str1, std::string &str2);

  friend bool operator==(const Area &a1, const Area &a2);
};

#endif // AREA_H_