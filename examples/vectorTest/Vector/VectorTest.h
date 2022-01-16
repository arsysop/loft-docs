/*******************************************************************************
 * Copyright (c) 2022 ArSysOp.
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
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Contributors:
 *     (ArSysOp) - initial API and implementation
 *******************************************************************************/

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <typeinfo>

#define configFile "../vectorTypesConfig.txt"
using namespace std;

class ConfigReader {

    public:
        ConfigReader() {

        }

        list<string> typeNames(){
            ifstream inputStream(configFile);
            string configLine;
            list<string> typeNameList;
            while (getline(inputStream, configLine)) {
                int typenameStart = configLine.find("<") + 1;
                int typenameEnd = configLine.find(">") - 1;
                typeNameList.push_back(configLine.substr(typenameStart, typenameEnd - typenameStart + 1));
            }
            return typeNameList;
        }

        list<string> exampleStringValues(string typeName){
            ifstream inputStream(configFile);
            string configLine;
            list<string> valueList;
            while (getline(inputStream, configLine))
            {
                if(configLine.find("<" + typeName + ">") != -1) {
                    int valueListStart = configLine.find("{") + 1;
                    int valueListEnd = configLine.find("}") - 1;
                    istringstream valuesWithoutBraces(configLine.substr(valueListStart, valueListEnd - valueListStart + 1));
                    do {
                        string currentValue;
                        valuesWithoutBraces >> currentValue;
                        valueList.push_back(currentValue);
                    } while (valuesWithoutBraces);
                    break;
                }
            }
            return valueList;
        }
};

template <typename T>
class TestedVector : public std::vector<T> {
    public:
        TestedVector() { CreateTestedVector(); }
        std::vector<T> testedVect;
    private:
        void CreateTestedVector(){
            ConfigReader configReader;
            std::list<string> stringVectorValues = configReader.exampleStringValues(typeid(T).name());
            while (!stringVectorValues.empty())
            {
                string nextStringValue = stringVectorValues.front();
                stringVectorValues.pop_front();
                T nextValue;
                stringstream convertTypenameToType(nextStringValue);
                convertTypenameToType >> nextValue;
                testedVect.push_back(nextValue);
            }
        }
};