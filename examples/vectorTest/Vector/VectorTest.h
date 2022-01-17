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

    private:

        list<string> readConfigFile() {
            list<string> lines;
            ifstream inputStream(configFile);
            string configLine;
            while (getline(inputStream, configLine))
            {
                lines.push_back(configLine);
            }
            return lines;
        }

        string findTypeNameInLine(string line) {
            int typenameStart = line.find("<") + 1;
            int typenameEnd = line.find(">") - 1;
            string _typename = line.substr(typenameStart, typenameEnd - typenameStart + 1);
            return _typename;
        }

        list<string> findValueListInLine(string line) {
            list<string> valueList;
            int typenameStart = line.find("{") + 1;
            int typenameEnd = line.find("}") - 1;
            istringstream valuesWithoutBraces(line.substr(typenameStart, typenameEnd - typenameStart + 1));
            do {
                    string currentValue;
                    valuesWithoutBraces >> currentValue;
                    valueList.push_back(currentValue);
                } while (valuesWithoutBraces);
                    
            return valueList;
        }

    public:
        ConfigReader() {

        }

        list<string> typeNames() {
            list<string> typeNameList;
            for(string configLine : readConfigFile()) {
                typeNameList.push_back(findTypeNameInLine(configLine));
            }
            return typeNameList;
        }

        list<string> exampleStringValues(string typeName) {
            list<string> valueList;
            for(string configLine : readConfigFile())
            {
                if(configLine.find("<" + typeName + ">") != -1) {
                    valueList = findValueListInLine(configLine);
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
            // there is a place where typenames should
            // be provided on the compile time
        }
};