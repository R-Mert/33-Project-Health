#include <QDebug>
#include <vector>
#include <utility>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

class RecommendationCalculator {
private:
    float calculateRate(tuple<pair<float, float>, pair<float, float>, pair<float, float> > formerDiet,
                        tuple<pair<float, float>, pair<float, float>, pair<float, float> > formerExercise) {

        int rateBreDiet = get<0>(formerDiet).second / get<0>(formerDiet).first;
        int rateLunDiet = get<1>(formerDiet).second / get<1>(formerDiet).first;
        int rateDinDiet = get<2>(formerDiet).second / get<2>(formerDiet).first;

        int rateMorExercise = get<0>(formerExercise).first / get<0>(formerExercise).second;
        int rateAftExercise = get<1>(formerExercise).first / get<1>(formerExercise).second;
        int rateEveExercise = get<2>(formerExercise).first / get<2>(formerExercise).second;

        int rate = (0.3 * rateBreDiet + 0.4 * rateLunDiet + 0.3 * rateDinDiet) * 0.7 +
                   (0.2 * rateMorExercise + 0.4 * rateAftExercise + 0.4 * rateEveExercise) * 0.3;

        return rate;
    }

    float calculateDecrease(float weight, float goal, int time) {
        return (weight - goal) / time;
    }

    float calculateSeggestion(float formerSeggestion, float decrease, float rate) {
        return formerSeggestion / (1+rate) + rate * decrease / (1+rate);
    }

    float calculateCaloryIntake(float height, float weight, float seggestion) {
        return 10 * weight + 6.25 * height - 5 * seggestion;
    }

    tuple<float, float, float> calculateRecommendationDiet(float caloryIntake, tuple<float, float, float> diet) {
        float breakfirst = caloryIntake * 0.3 / get<0>(diet);
        float lunch = caloryIntake * 0.4 / get<1>(diet);
        float dinner = caloryIntake * 0.3 / get<2>(diet);

        return make_tuple(breakfirst, lunch, dinner);
    }

    tuple<float, float, float> calculateRecommendationExercise(tuple<float, float, float> exercise) {
        float morning = 2 * get<0>(exercise);
        float afternoon = 4 * get<1>(exercise);
        float evening = 4 * get<2>(exercise);

        return make_tuple(morning, afternoon, evening);
    }

    tuple<float, int, float> updateParams(float goal, int time, float seggestion) {
        return make_tuple(goal, time - 1, seggestion);
    }

public:
    RecommendationCalculator() {}
    tuple<tuple<float, float, float>, tuple<float,float,float>, tuple<float, int, float> > getRecommendationAndUpdatedParams(
        float height,
        float weight,
        tuple<pair<float, float>, pair<float, float>, pair<float, float> > formerDiet, // <actual, seggest>
        tuple<pair<float, float>, pair<float, float>, pair<float, float> > formerExercise,
        tuple<float, float, float> diet, // <breakfirst, lunch, dinner>
        tuple<float, float, float> exercise, // <morning, afternoon, evening>
        tuple<float, int, float> params) { // <goal, time, seggestion>

        float goal = get<0>(params);
        int time = get<1>(params);
        float formerSeggestion = get<2>(params);

        float decrease = calculateDecrease(weight, goal, time);
        float rate = calculateRate(formerDiet, formerExercise);
        float seggestion = calculateSeggestion(formerSeggestion, decrease, rate);
        float caloryIntake = calculateCaloryIntake(height, weight, seggestion);

        tuple<float, float, float> recommendationdiet = calculateRecommendationDiet(caloryIntake, diet);
        tuple<float, float, float> recommendationexercise = calculateRecommendationExercise(exercise);
        tuple<float, int, float> updatedParams = updateParams(goal, time, seggestion);

        return make_tuple(recommendationdiet, recommendationexercise, updatedParams);
    }
};

class TestAlgorithm {
private:
    float testLine(pair<float, float> function, pair<float, float> data) { // <k, b> <time, seggest>
        return abs(data.second -(function.first * data.first + function.second));
    }

    float testInverse(pair<float, float> function, pair<float, float> data) { // <a, b> <y = a / x + b>
        return abs(data.second - (get<0>(function) / (data.first) + get<1>(function)));
    }

    float test3Times(pair<float, float> function, pair<float, float> point, pair<float, float> data) { // <a, b> <c, d> <y = (a * x + b) * (x - c) ^ 2 + d>
        return abs(data.second - (function.first * point.first + function.second) * pow(point.first - data.first, 2) + data.second);
    }

    float testSigma(float function, pair<float, float> data) { // y = a / ( 1 + e ^ - x)
        return abs(data.second - function / (1 + exp(-data.first)));
    }

    float countVariance(vector<float> data) {
        float sum = 0;

        for (int i = 0; i < data.size(); i++) {
            sum += data[i];
        }
        float average = sum / data.size();
        float variance = 0;

        for (int i = 0; i < data.size(); i++) {
            variance += pow(data[i] - average, 2);
        }

        return variance / data.size();
    }

    pair<float, float> lineGet(vector<float> time, vector<float> weight) {
        float sumX = 0;
        float sumY = 0;
        float sumXY = 0;
        float sumX2 = 0;

        for (int i = 0; i < time.size(); i++) {
            sumX += time[i];
            sumY += weight[i];
            sumXY += time[i] * weight[i];
            sumX2 += pow(time[i], 2);
        }
        float k = (time.size() * sumXY - sumX * sumY) / (time.size() * sumX2 - pow(sumX, 2));
        float b = (sumY - k * sumX) / time.size();

        return make_pair(k, b);
    }

    pair<float, float> inverseGet(vector<float> time, vector<float> weight) {
        float sumX = 0;
        float sumY = 0;
        float sumX2 = 0;
        float sumXY = 0;

        for (int i = 0; i < time.size(); i++) {
            sumX += 1 / time[i];
            sumY += weight[i];
            sumX2 += 1 / pow(time[i], 2);
            sumXY += weight[i] / time[i];
        }
        float a = (time.size() * sumXY - sumX * sumY) / (time.size() * sumX2 - pow(sumX, 2));
        float b = (sumY - a * sumX) / time.size();

        return make_pair(a, b);
    }

    pair<float, float> pointGet(vector<float> time, vector<float> weight) {
        float c = time.front() / 2;
        float d = (weight.front() + weight.back()) / 2;

        return make_pair(c, d);
    }

    pair<float, float> threeTimesGet(vector<float> time, vector<float> weight) {
        float sumX = 0;
        float sumY = 0;
        float sumX2 = 0;
        float sumXY = 0;
        float sumX3 = 0;
        float sumX2Y = 0;

        for (int i = 0; i < time.size(); i++) {
            sumX += time[i];
            sumY += weight[i];
            sumX2 += pow(time[i], 2);
            sumXY += time[i] * weight[i];
            sumX3 += pow(time[i], 3);
            sumX2Y += pow(time[i], 2) * weight[i];
        }
        float a = (sumX2Y * sumX2 - sumXY * sumX3) / (sumX2 * sumX2 - sumX * sumX3);
        float b = (sumXY * sumX2 - sumX * sumX2Y) / (sumX2 * sumX2 - sumX * sumX3);

        return make_pair(a, b);
    }

    float sigmaGet(vector<float> time, vector<float> weight) {
        float sumX = 0;
        float sumY = 0;
        float sumX2 = 0;
        float sumXY = 0;

        for (int i = 0; i < time.size(); i++) {
            sumX += time[i];
            sumY += weight[i];
            sumX2 += pow(time[i], 2);
            sumXY += time[i] * weight[i];
        }
        float a = (time.size() * sumXY - sumX * sumY) / (time.size() * sumX2 - pow(sumX, 2));

        return a;
    }

    float lineVarianceget(pair<float, float> function, vector<float> time, vector<float> weight) {
        vector<float> data;

        for (int i = 0; i < time.size(); i++) {
            data.push_back(testLine(function, make_pair(time[i], weight[i])));
        }

        return countVariance(data);
    }

    float inverseVarianceget(pair<float, float> function, vector<float> time, vector<float> weight) {
        vector<float> data;

        for (int i = 0; i < time.size(); i++) {
            data.push_back(testInverse(function, make_pair(time[i], weight[i])));
        }

        return countVariance(data);
    }

    float threeTimesVarianceget(pair<float, float> function, pair<float, float> point, vector<float> time, vector<float> weight) {
        vector<float> data;

        for (int i = 0; i < time.size(); i++) {
            data.push_back(test3Times(function, point, make_pair(time[i], weight[i])));
        }

        return countVariance(data);
    }

    float sigmaVarianceget(float function, vector<float> time, vector<float> weight) {
        vector<float> data;

        for (int i = 0; i < time.size(); i++) {
            data.push_back(testSigma(function, make_pair(time[i], weight[i])));
        }

        return countVariance(data);
    }

    float testLineAlgorithm(vector<float> time, vector<float> weight) {
        pair<float, float> function = lineGet(time, weight);
        qDebug()<<"line"<<function;
        return lineVarianceget(function, time, weight);
    }

    float testInverseAlgorithm(vector<float> time, vector<float> weight) {
        pair<float, float> function = inverseGet(time, weight);
        qDebug()<<"inverse"<<function;
        return inverseVarianceget(function, time, weight);
    }

    float testThreeTimesAlgorithm(vector<float> time, vector<float> weight) {
        pair<float, float> function = threeTimesGet(time, weight);
        pair<float, float> point = pointGet(time, weight);
        qDebug()<<"threetimes"<<function<<" "<<point;
        return threeTimesVarianceget(function, point, time, weight);
    }

    float testSigmaAlgorithm(vector<float> time, vector<float> weight) {
        float function = sigmaGet(time, weight);
        qDebug()<<"sigmoid"<<function;
        return sigmaVarianceget(function, time, weight);
    }

public:

    string getBestFittingAlgorithm(vector<float> time, vector<float> weight) {
        pair<string, float> algorithms[] = {
            {"line", testLineAlgorithm(time, weight)},
            {"inverse", testInverseAlgorithm(time, weight)},
            {"threeTimes", testThreeTimesAlgorithm(time, weight)},
            {"sigma", testSigmaAlgorithm(time, weight)}
        };
        qDebug()<<algorithms[0];
        qDebug()<<algorithms[1];
        qDebug()<<algorithms[2];
        qDebug()<<algorithms[3];
        sort(std::begin(algorithms), std::end(algorithms), [](auto &a, auto &b) {
            return a.second < b.second;
        });

        return algorithms[0].first;
    }

    pair<float, float> getLineParams(vector<float> time, vector<float> weight) {
        return lineGet(time, weight);
    }

    pair<float, float> getInverseParams(vector<float> time, vector<float> weight) {
        return inverseGet(time, weight);
    }

    tuple<float, float, float, float> getThreeTimesParams(vector<float> time, vector<float> weight) {
        pair<float, float> function = threeTimesGet(time, weight);
        pair<float, float> point = pointGet(time, weight);

        return make_tuple(function.first, function.second, point.first, point.second);
    }

    float getSigmaParams(vector<float> time, vector<float> weight) {
        return sigmaGet(time, weight);
    }

    pair<float, float> refreshLineParams(pair<float, float> originalParams, vector<float> newTime, vector<float> newWeight) {
        float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
        for (int i = 0; i < newTime.size(); i++) {
            sumX += newTime[i];
            sumY += newWeight[i];
            sumXY += newTime[i] * newWeight[i];
            sumX2 += pow(newTime[i], 2);
        }
        float newK = (newTime.size() * sumXY - sumX * sumY) / (newTime.size() * sumX2 - pow(sumX, 2));
        float newB = (sumY - newK * sumX) / newTime.size();
        float updatedK = 0.9 * originalParams.first + 0.1 * newK;
        float updatedB = 0.9 * originalParams.second + 0.1 * newB;
        return make_pair(updatedK, updatedB);
    }

    pair<float, float> refreshInverseParams(pair<float, float> originalParams, vector<float> newTime, vector<float> newWeight) {
        float sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;
        for (int i = 0; i < newTime.size(); i++) {
            sumX += 1 / newTime[i];
            sumY += newWeight[i];
            sumX2 += 1 / pow(newTime[i], 2);
            sumXY += newWeight[i] / newTime[i];
        }
        float newA = (newTime.size() * sumXY - sumX * sumY) / (newTime.size() * sumX2 - pow(sumX, 2));
        float newB = (sumY - newA * sumX) / newTime.size();
        float updatedA = 0.9 * originalParams.first + 0.1 * newA;
        float updatedB = 0.9 * originalParams.second + 0.1 * newB;
        return make_pair(updatedA, updatedB);
    }

    tuple<float, float, float, float> refreshThreeTimesParams(tuple<float, float, float, float> originalParams, vector<float> newTime, vector<float> newWeight) {
        float sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0, sumX3 = 0, sumX2Y = 0;
        for (int i = 0; i < newTime.size(); i++) {
            sumX += newTime[i];
            sumY += newWeight[i];
            sumX2 += pow(newTime[i], 2);
            sumXY += newTime[i] * newWeight[i];
            sumX3 += pow(newTime[i], 3);
            sumX2Y += pow(newTime[i], 2) * newWeight[i];
        }
        float newA = (sumX2Y * sumX2 - sumXY * sumX3) / (sumX2 * sumX2 - sumX * sumX3);
        float newB = (sumXY * sumX2 - sumX * sumX2Y) / (sumX2 * sumX2 - sumX * sumX3);
        float updatedA = 0.9 * get<0>(originalParams) + 0.1 * newA;
        float updatedB = 0.9 * get<1>(originalParams) + 0.1 * newB;
        float updatedC = 0.9 * get<2>(originalParams) + 0.1 * newTime.front() / 2;
        float updatedD = 0.9 * get<3>(originalParams) + 0.1 * (newWeight.front() + newWeight.back()) / 2;
        return make_tuple(updatedA, updatedB, updatedC, updatedD);
    }

    float refreshSigmaParams(float originalParams, vector<float> newTime, vector<float> newWeight) {
        float sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;
        for (int i = 0; i < newTime.size(); i++) {
            sumX += newTime[i];
            sumY += newWeight[i];
            sumX2 += pow(newTime[i], 2);
            sumXY += newTime[i] * newWeight[i];
        }
        float newA = (newTime.size() * sumXY - sumX * sumY) / (newTime.size() * sumX2 - pow(sumX, 2));
        float updatedA = 0.9 * originalParams + 0.1 * newA;
        return updatedA;
    }

};
/*
getBestFittingAlgorithm输入两个vector<float> time和weight，返回一个string，表示最佳拟合算法。

getLineParams输入两个vector<float> time和weight，返回一个pair<float, float>，表示线性拟合的参数。
getInverseParams输入两个vector<float> time和weight，返回一个pair<float, float>，表示反比例拟合的参数。
getThreeTimesParams输入两个vector<float> time和weight，返回一个tuple<float, float, float, float>，表示三次拟合的参数。
getSigmaParams输入两个vector<float> time和weight，返回一个float，表示sigmoid拟合的参数。

originalParams表示原始参数，newTime和newWeight表示新的时间和体重数据。

refreshLineParams输入一个pair<float, float> originalParams和两个vector<float> newTime和newWeight，返回一个pair<float, float>，表示线性拟合的参数。
refreshInverseParams输入一个pair<float, float> originalParams和两个vector<float> newTime和newWeight，返回一个pair<float, float>，表示反比例拟合的参数。
refreshThreeTimesParams输入一个tuple<float, float, float, float> originalParams和两个vector<float> newTime和newWeight，返回一个tuple<float, float, float, float>，表示三次拟合的参数。
refreshSigmaParams输入一个float originalParams和两个vector<float> newTime和newWeight，返回一个float，表示sigmoid拟合的参数。
*/
