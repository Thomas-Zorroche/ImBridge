#pragma once


#include "Common.hpp"

#include <string>
#include <glm/glm.hpp>

namespace ImBridge {

	void displayHoverDescription(const std::string& desc);

	/*
	* Abstract Parameter Class
	*/
	class Parameter
	{
	public:
		Parameter(const std::string& name, const std::string& desc = "")
			: _name(name), _description(desc)	{};

		virtual ~Parameter() {}

		virtual void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) = 0;

	protected:
		std::string _name = "";
		std::string _description = "";
	};

	/*
	* Concrete Parameter Classes 
	*/
	class ParameterFloat : public Parameter
	{
	public:
		ParameterFloat(const std::string& name, float& value, float min, float max, 
			const std::string& desc = "")
			: Parameter(name, desc), _value(value), _min(min), _max(max) {};

		void render(float sliderSpeed = 0.1f) override;

	private:
		float& _value;
		float _min;
		float _max;
	};

	class ParameterInt : public Parameter
	{
	public:
		ParameterInt(const std::string& name, int& value, int min, int max,
			const std::string& desc = "", CallbackInt callback = [](int) {})
			: Parameter(name, desc), _value(value), minValue(min), maxValue(max), _callback(callback) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override;

	public:
		int minValue;
		int maxValue;

	private:
		int& _value;
		CallbackInt _callback;
	};

	class ParameterBoolean : public Parameter
	{
	public:
		ParameterBoolean(const std::string& name, bool& value, const std::string& desc = "")
			: Parameter(name, desc), _value(value) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override;

	private:
		bool& _value;
	};


	class ParameterVec3 : public Parameter
	{
	public:
		ParameterVec3(const std::string& name, glm::vec3& value, const std::string& desc = "")
			: Parameter(name, desc), _value(value) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override;

	private:
		glm::vec3& _value;
	};


	class ParameterCombo : public Parameter
	{
	public:

		ParameterCombo(const std::string& name, const char* items_separated_by_zeros, 
			unsigned int nItems, CallbackCombo callback, const std::string& desc = "")
			: Parameter(name, desc), _items_separated_by_zeros(items_separated_by_zeros), _nItems(nItems), _callback(callback) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override;

	private:
		const char* _items_separated_by_zeros;
		unsigned int _nItems;
		unsigned int _id = 0;
		CallbackCombo _callback;
	};

}


