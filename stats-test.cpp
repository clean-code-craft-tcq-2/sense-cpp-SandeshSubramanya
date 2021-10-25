#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "stats.h"
#include <cmath>
#include <algorithm>
#include <vector>

TEST_CASE("reports average, minimum and maximum") {
    auto computedStats = Statistics::ComputeStatistics({1.5, 8.9, 3.2, 4.5});
    float epsilon = (float)0.001;
    REQUIRE(std::abs(computedStats.average - 4.525) < (double)epsilon);
    REQUIRE(std::abs(computedStats.max - 8.9) < (double)epsilon);
    REQUIRE(std::abs(computedStats.min - 1.5) < (double)epsilon);
}

TEST_CASE("average is NaN for empty array") {
    auto computedStats = Statistics::ComputeStatistics({});
    //All fields of computedStats (average, max, min) must be
    //NAN (not-a-number), as defined in math.h
    
    REQUIRE(std::isnan(computedStats.average) == true);
    REQUIRE(std::isnan(computedStats.max) == true);
    REQUIRE(std::isnan(computedStats.min) == true);
}

TEST_CASE("raises alerts when max is greater than threshold") {
    
    class IAlerter //abstract class
    {
      // do nothing;
      public:
         virtual void vSetAlert(bool bNewVal) = 0;
    };

    class EmailAlert:public IAlerter
    {
       public:
       EmailAlert()
       {
          emailSent = false;   // default
       }

       void vSetAlert(bool bNewVal)
       {
          emailSent = bNewVal;
       }

       bool emailSent;   // set to true, if maximum value crosses the threshold.
    };
    
    class LEDAlert :public IAlerter
    {
       public:
       LEDAlert()
       {
          ledGlows = false;
       }

       void vSetAlert(bool bNewVal)
       {
          ledGlows = bNewVal;
       }

       bool ledGlows; // set to true, if maximum value crosses the threshold.
    };
    
    class StatsAlerter
      {
      public:
         StatsAlerter(float maxThreshold, const std::vector<IAlerter*> vAlerters)
         {
            m_maxThreshold = maxThreshold;
            m_alerters = vAlerters;
         }

      void checkAndAlert(const std::vector<double>& rfVectorValues)
      {
            // get the maximum values from the list.
            if (!rfVectorValues.empty())
            {
               double maximum_value = *std::max_element(rfVectorValues.begin(), rfVectorValues.end());
               if (maximum_value > (double)m_maxThreshold)
               {
                  // threshold crossed, set the alerts
                  if (!m_alerters.empty())
                  {
                     for (int index = 0; index < (int)m_alerters.size(); ++index)
                     {
                        m_alerters[index]->vSetAlert(true);
                     }
                  }
               }
            }
      }

      private:
         float m_maxThreshold;
         std::vector<IAlerter*> m_alerters;
      };
    
    EmailAlert emailAlert;
    LEDAlert ledAlert;
    std::vector<IAlerter*> alerters = {&emailAlert, &ledAlert};
    
    const float maxThreshold = (float)10.2;
    StatsAlerter statsAlerter(maxThreshold, alerters);
    statsAlerter.checkAndAlert({99.8, 34.2, 4.5, 6.7});

    REQUIRE(emailAlert.emailSent == true);
    REQUIRE(ledAlert.ledGlows == true);
}
