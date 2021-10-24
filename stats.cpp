#include "stats.h"
#include <algorithm>
#include <cmath>

Statistics::Stats Statistics::ComputeStatistics(const std::vector<double>& rfVectorValues) 
{
   Statistics::Stats oTempStatistics;
   double sum = 0.0;
   if (!rfVectorValues.empty())
   {
      // compute statistics with the input vector values.
      std::vector<double>::const_iterator vectorValuesItr = rfVectorValues.begin();
      for (; vectorValuesItr != rfVectorValues.end(); ++vectorValuesItr)
      {
         sum += *vectorValuesItr;
      }

      oTempStatistics.average = (double) (sum / (double)rfVectorValues.size());
      oTempStatistics.max = *std::max_element(rfVectorValues.begin(), rfVectorValues.end());
      oTempStatistics.min = *std::min_element(rfVectorValues.begin(), rfVectorValues.end());
   }
   else
   {
      // vector is empty. Assign "nan" to all the values.
      oTempStatistics.average = (double)std::nan("1");
      oTempStatistics.max = (double)std::nan("1");
      oTempStatistics.min = (double)std::nan("1");
   }
    
   return oTempStatistics;
}
