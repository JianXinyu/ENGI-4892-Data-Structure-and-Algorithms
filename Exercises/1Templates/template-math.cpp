/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include "templates.h"
using namespace std;

int main()
{
    double x = 1, y = 1;
    vector<int> vi = {1, 2 ,3, 4};
    vector<double> vd = {1.1, 2.2 };
    vector<string> vs = {"me", "you"};
    cout << "x + y = " << add(x, y) << "\n";
    cout << "average int:" << average(vi) << endl;
    cout << "average int(modified):" << average<double>({1, 2 ,3, 4}) << endl;
    cout << "average double:" << average(vd) << endl;
//    cout << "average string:" << average(vs);


    //Class templates problems
//    GrowableArray<int> ga_int;
//    ga_int << 1;
//    cout << ga_int[0] << endl;
//
//    GrowableArray<std::string> ga_str;
//    ga_str << "me";
//    cout << ga_str[0] << endl;

/* Not work
    GrowableArray<double> ga_d;
    ga_d << 1.2;
    vector<GrowableArray<double>> vec;
    vec.push_back(ga_d);
    GrowableArray<vector<GrowableArray<double>>> ga_vec;
    ga_vec << vec;
    cout << ga_vec[0] << endl;
*/

    //Extra (optional) exercises
    GrowableArray<int, 2> ga_int;
    ga_int << 1 << 2;
    cout << "GrowableArray Int average:" << ga_int.average() << endl;

    GrowableArray<double, 2> ga_d;
    ga_d << 1.2 << 2.3;
    cout << "GrowableArray double average:" << ga_d.average() << endl;

    GrowableArray<std::string, 2> ga_str;
    ga_str << "me" << "you";
//    cout << "GrowableArray String average:" <<ga_str.average() << endl;



    return 0;
}