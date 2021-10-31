#include "Bridge.hpp"

#include "Parameter.hpp"
#include "ParameterFactory.hpp"

namespace ImBridge {

	Bridge::Bridge()
		: _parameters()
	{

	}

	void Bridge::addFloat(const std::string& label, float& value, float min, float max, const std::string& desc)
	{
		_parameters.push_back(ParameterFactory::Float(label, value, min, max, desc));
	}

	void Bridge::addInt(const std::string& label, int& value, int min, int max, const std::string& desc)
	{
		_parameters.push_back(ParameterFactory::Int(label, value, min, max, desc));
	}

	void Bridge::addBool(const std::string& label, bool& value, const std::string& desc)
	{
		_parameters.push_back(ParameterFactory::Bool(label, value, desc));
	}

	void Bridge::addVec3(const std::string& label, glm::vec3& value, const std::string& desc)
	{
		_parameters.push_back(ParameterFactory::Vec3(label, value, desc));
	}

	void Bridge::addCombo(const std::string& label, const char* items_separated_by_zeros,
		unsigned int nItems, CallbackCombo callback, const std::string& desc)
	{
		_parameters.push_back(ParameterFactory::Combo(label, items_separated_by_zeros, nItems, callback, desc));
	}

	std::vector<std::shared_ptr<Parameter> >& Bridge::getParameters()
	{
		return _parameters;
	}

}

