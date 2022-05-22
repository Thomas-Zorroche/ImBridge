#pragma once

#include "Parameter.hpp"
#include <memory>


namespace ImBridge {

	class ParameterFactory
	{
	public:
		static std::shared_ptr<Parameter>
		Float(const std::string& name, float& value, float min, float max, const std::string& desc = "")
		{
			return std::make_shared<ParameterFloat>(name, value, min, max, desc);
		}

		//static std::shared_ptr<Parameter>
		//Int(const std::string& name, int& value, int min, int max, const std::string& desc = "", CallbackInt callback = [](int) {})
		//{
		//	return std::make_shared<ParameterInt>(name, value, min, max, desc, callback);
		//}

		static std::shared_ptr<Parameter>
		Bool(const std::string& name, bool& value, const std::string& desc = "")
		{
			return std::make_shared<ParameterBoolean>(name, value, desc);
		}

		static std::shared_ptr<Parameter>
		Vec3(const std::string& name, glm::vec3& value, const std::string& desc = "")
		{
			return std::make_shared<ParameterVec3>(name, value, desc);
		}

		static std::shared_ptr<Parameter>
		Combo(const std::string& name, const char* items_separated_by_zeros, unsigned int nItems, CallbackCombo callback, const std::string& desc = "")
		{
			return std::make_shared<ParameterCombo>(name, items_separated_by_zeros, nItems, callback, desc);
		}
	};

}
