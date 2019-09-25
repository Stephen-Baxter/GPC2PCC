#pragma once
#include <fstream>
#include <sstream>
#include <vector>

#define JSON_FILE_NOT_FOUND "JSONFNF"
#define OBJECT_NOT_FOUND "ONF"
#define ITME_IS_NULL "null"

namespace json
{
	inline std::string GetJSONData(std::string fileName)
	{
		std::ifstream inFile;

		inFile.open(fileName);

		if (!inFile)
		{
			inFile.close();


			return "JSONFNF";
		}

		std::vector<std::string> vectorFromFile;

		while (inFile)
		{
			std::string fileData;
			inFile >> fileData;
			vectorFromFile.push_back(fileData);
		}

		inFile.close();

		std::string parsedFile = "";

		for (size_t i = 0; i < vectorFromFile.size(); i++) parsedFile += vectorFromFile[i];


		return parsedFile;
	}
	inline void SetJSONData(std::string fileName, std::vector<std::string> jsonData)
	{
		std::ofstream outFile;

		outFile.open(fileName, std::ios::app);

		for (size_t i = 0; i < jsonData.size(); i++) outFile << jsonData[i] << std::endl;

		outFile.close();
	}
	inline void SetJSONData(std::string fileName, std::string jsonData)
	{
		std::ofstream outFile;

		outFile.open(fileName, std::ios::app);

		outFile << jsonData << std::endl;

		outFile.close();
	}

	inline std::vector<std::string> GetArray(std::string arrayData)
	{
		std::string arrayElement = "";
		int bracketCheck = 0;
		std::vector<std::string> returnArray;

		for (size_t i = 1; i < arrayData.length() - 1; i++)
		{
			if (arrayData[i] == '{' || arrayData[i] == '[') bracketCheck++;
			if ((arrayData[i] == '}' || arrayData[i] == ']') && bracketCheck != 0) bracketCheck--;

			if (arrayData[i] == ',' && bracketCheck == 0)
			{
				returnArray.push_back(arrayElement);
				arrayElement = "";
			}
			else arrayElement += arrayData[i];
		}

		returnArray.push_back(arrayElement);

		return returnArray;
	}
	inline std::string SetArray(std::vector<std::string> array)
	{
		std::string arrayAsString = "[";

		for (size_t i = 0; i < array.size(); i++)
		{
			arrayAsString += array[i];

			if (i < array.size() - 1) arrayAsString += ",";
		}


		return arrayAsString + "]";
	}

	inline std::string Getobject(std::string objectName, std::string objectData)
	{
		for (size_t i = 0; i < objectData.length(); i++)
		{
			if (objectData[i] == ':')
			{
				bool quoteCheck = false;
				int j = i - 2;

				while (!quoteCheck)
				{
					if (objectData[j] == '"') quoteCheck = true; else j--;
				}

				std::string testName = "";

				for (int k = j + 1; k < i - 1; k++)
				{
					testName = testName + objectData[k];
				}

				if (testName == objectName)
				{
					int j = i;
					std::string returnObjectData = "";
					int bracketCheck = 0;

					while (true)
					{
						if ((objectData[j + 1] == ',' || objectData[j + 1] == '}') && bracketCheck == 0) break; else
						{
							j++;
							if (objectData[j] == '{' || objectData[j] == '[') bracketCheck++;
							if ((objectData[j] == '}' || objectData[j] == ']') && bracketCheck != 0) bracketCheck--;
							returnObjectData += objectData[j];
						}
					}


					return returnObjectData;
				}
			}
		}


		return "ONF";
	}
	inline std::string SetObject(std::vector<std::pair<std::string, std::string>> object)
	{
		std::string objectAsString = "{";

		for (size_t i = 0; i < object.size(); i++)
		{
			objectAsString += "\"" + object[i].first + "\":" + object[i].second;

			if (i < object.size() - 1) objectAsString += ",";
		}


		return objectAsString + "}";
	}
	inline std::string SetObject(std::string objectName, std::string objectData)
	{
		return "{\"" + objectName + "\":" + objectData + "}";
	}

	inline double GetNumber(std::string numberData)
	{
		return std::stod(numberData);
	}
	inline std::string SetNumber(double number)
	{
		return std::to_string(number);
	}

	inline bool GetBoolean(std::string booleanData)
	{
		return booleanData == "true";
	}
	inline std::string SetBoolean(bool boolean)
	{
		return (boolean) ? "true" : "false";
	}

	inline std::string GetString(std::string stringData)
	{
		std::string returnString = "";

		for (size_t i = 1; i < stringData.length() - 1; i++) returnString += stringData[i];

		return returnString;
	}
	inline std::string SetString(std::string string)
	{
		return "\"" + string + "\"";
	}
}

//******************************************************************************************************
//Author: Stephen Baxter
//Development Tools Used: Visual Studeo 2019
//Name: getsetjson
//Language: c++11
//
//Description: getsetjson is a small library for C++11, that can be used to retrieve json data from
//a json file, convert json data into C++ values, convert C++ values into json data, and store json
//data to a json file
//******************************************************************************************************
