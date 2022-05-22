#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>

#include "Common.hpp"

namespace ImBridge {

	class Parameter;

	class Bridge
	{
	public:
		Bridge();

		void addFloat(const std::string& label, float& value, float min, float max, const std::string& desc = "");
		
		void addInt(const std::string& label, int& value, int min, int max, const std::string& desc = "", CallbackInt callback = [](int) {});

		void addBool(const std::string& label, bool& value, const std::string& desc = "");
		
		void addVec3(const std::string& label, glm::vec3& value, const std::string& desc = "");
		
		/*
		* items_separated_by_zeros = "64\0 128\0 256\0\0"
		*/
		void addCombo(const std::string& label, const char* items_separated_by_zeros,
			unsigned int nItems, CallbackCombo callback, const std::string& desc);

		const std::map<std::string, std::shared_ptr<Parameter>>::iterator getParametersBegin();
		const std::map<std::string, std::shared_ptr<Parameter>>::iterator getParametersEnd();

		template<typename T>
		std::shared_ptr<T>& getParameter(const std::string& parameterName)
		{
			auto& parameter = _parameters[parameterName];
			if (auto& parameterInt = std::dynamic_pointer_cast<T>(parameter))
			{
				return parameterInt;
			}
		}


	private:
		std::map<std::string, std::shared_ptr<Parameter>> _parameters;
	};
}