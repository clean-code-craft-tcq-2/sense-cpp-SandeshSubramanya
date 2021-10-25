#include <vector>

namespace Statistics {
   struct Stats
   {
      double average;
      double max;
      double min;
   };
   Stats ComputeStatistics(const std::vector<double>&);
}
