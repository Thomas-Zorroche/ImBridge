#include "Bridge.hpp"

#include "Parameter.hpp"

namespace ImBridge {

	Bridge::Bridge()
		: _parameters()
	{

	}

	void Bridge::addFloat(const std::string& label, float& value, float min, float max, const std::string& desc)
	{
		auto parameter = std::make_shared<ParameterFloat>(label, value, min, max, desc);
		_parameters.insert({ label, parameter });
	}

	void Bridge::addInt(const std::string& label, int& value, int min, int max, const std::string& desc, CallbackInt callback)
	{
		auto parameter = std::make_shared<ParameterInt>(label, value, min, max, desc, callback);
		_parameters.insert({ label, parameter });
	}

	void Bridge::addBool(const std::string& label, bool& value, const std::string& desc)
	{
		auto parameter = std::make_shared<ParameterBoolean>(label, value, desc);
		_parameters.insert({ label, parameter });
	}

	void Bridge::addVec3(const std::string& label, glm::vec3& value, const std::string& desc)
	{
		auto parameter = std::make_shared<ParameterVec3>(label, value, desc);
		_parameters.insert({ label, parameter });
	}

	void Bridge::addCombo(const std::string& label, const char* items_separated_by_zeros,
		unsigned int nItems, CallbackCombo callback, const std::string& desc)
	{
		auto parameter = std::make_shared<ParameterCombo>(label, items_separated_by_zeros, nItems, callback, desc);
		_parameters.insert({ label, parameter });
	}

	const std::map<std::string, std::shared_ptr<Parameter>>::iterator Bridge::getParametersBegin()
	{
		return _parameters.begin();
	}

	const std::map<std::string, std::shared_ptr<Parameter>>::iterator Bridge::getParametersEnd()
	{
		return _parameters.end();
	}
}

