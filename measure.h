#ifndef MEASURE_H_
#define MEASURE_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: <964398>

  This file contains the decalaration of the Measure class.

  TODO: Read the block comments with TODO in measure.cpp to know which 
  functions and member variables you need to declare in this class.
 */

#include <string>
#include <vector>
#include <map>

using MeasureContainer = std::vector<double>;
/*
  The Measure class contains a measure code, label, and a container for readings
  from across a number of years.

  TODO: Based on your implementation, there may be additional constructors
  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/
class Measure
{
private:
  std::string name;
  std::string codename;
  std::string label;
  std::map<int, double> values;

  double key; // the year
  double value;

public:
  Measure();
  Measure(std::string code, const std::string label);
  std::string getCodename() const;

  std::string getLabel() const;
  void setLabel(std::string label);

  double getValue(int year);
  void setValue(int key, double value);

  int size() const;

  friend bool operator==(const Measure &m1, const Measure &m2);
  friend std::ostream &operator<<(std::ostream &os, Measure measure);

  double getDifference() const;
  double getDifferenceAsPercentage() const;
  double getAverage() const;
};

#endif // MEASURE_H_