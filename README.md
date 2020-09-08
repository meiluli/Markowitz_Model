# Markowitz_Model
"assets_returns.csv"包含了700天FTSE 100中83个公司的收益信息

# Csv
csv.hpp和csv.cpp两个文件主要实现了读取csv格式文件的功能。

# read_data
read_data.hpp和read_data.cpp两个文件包含将数据保存到2D vector中的函数。

# Matrix
Matrix.hpp和Matrix.cpp两个文件包含运算符重载函数，以定义与vector<double>和vector<vector<double>>相关的操作。

# assetsReturns
assetReturns.hpp和assetReturns.cpp两个文件包含4个类，用于执行样本内和样本外计算及回测。

## class AR
- 保存通用信息，例如样本内窗口，样本外窗口，滚动窗口，滚动次数窗口，700x83收益矩阵等。

## class IS: public virtual AR
- 计算样本内均值和协方差

## class OOS: : public virtual AR
- 计算样本外均值和协方差

## class FTSE: public OOS, public IS
- 回测
