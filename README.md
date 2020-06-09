# Markowitz_Model
Given a file "assets_returns.csv" containing returns from 83 of the FTSE 100 companies

# Csv
Two files csv.hpp and csv.cpp contain a function that read files in the csv format.

# read_data
Two files read_data.hpp and read_data.cpp contain a function that saves data into a 2D vector.

# Matrix
Two files Matrix.hpp and Matrix.cpp contain operator overloading functions to define operations related to vector<double> and vector<vector<double>>.

# assetsReturns
Two files assetsReturns.hpp and assetsReturns.cpp contain 4 classes to perform in-sample out-of-sample calculations and backtesting.
## class AR
- Save common information like isWindow, oosWindow, rollingWindow, rollingTimes, assetsReturns, etc..

## class IS: public virtual AR
- Calculate in-sample mean and covariance

## class OOS: : public virtual AR
- Calculate out-og-sample mean and covariance

## class FTSE: public OOS, public IS
- Backtesting
