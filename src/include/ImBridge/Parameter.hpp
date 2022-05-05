#pragma once

#include "imgui/imgui.h"

#include "Common.hpp"

#include <string>
#include <glm/glm.hpp>

namespace ImBridge {


	void displayHoverDescription(const std::string& desc);

	template <typename UIFonction>
	void drawParameter(const std::string& name, UIFonction uiFonction, const std::string& desc = "")
	{
		if (!name.empty())
		{
			float posX = (ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() * 0.4) - ImGui::CalcTextSize(name.c_str()).x
				- ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
			if (posX > ImGui::GetCursorPosX())
				ImGui::SetCursorPosX(posX);

			ImGui::AlignTextToFramePadding();
			ImGui::Text(name.c_str());
			ImGui::SameLine();
			displayHoverDescription(desc);
		}

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.55f);
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.4);

		uiFonction();

		if (name.empty() && !desc.empty())
		{
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.5, 0.5, 0.5, 1.0 });
			ImGui::Text("(?)");
			ImGui::PopStyleColor();
			displayHoverDescription(desc);
		}

		ImGui::PopItemWidth();
	}


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

		void render(float sliderSpeed = 0.1f) override
		{
			drawParameter(_name.c_str(), [this, sliderSpeed]()
			{
				if (ImGui::DragFloat(("##" + _name).c_str(), &_value, sliderSpeed, _min, _max))
				{

				}
			}, _description);
		};

	private:
		float& _value;
		float _min;
		float _max;
	};

	class ParameterInt : public Parameter
	{
	public:
		ParameterInt(const std::string& name, int& value, int min, int max, 
			const std::string& desc = "")
			: Parameter(name, desc), _value(value), _min(min), _max(max) {};


		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override
		{
			drawParameter(_name.c_str(), [this]()
			{
				if (ImGui::SliderInt(("##" + _name).c_str(), &_value, _min, _max))
				{

				}
			}, _description);

		};

	private:
		int& _value;
		int _min;
		int _max;
	};

	class ParameterBoolean : public Parameter
	{
	public:
		ParameterBoolean(const std::string& name, bool& value, const std::string& desc = "")
			: Parameter(name, desc), _value(value) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override
		{
			drawParameter(_name.c_str(), [this]()
			{
				ImGui::Checkbox(_name.c_str(), &_value);
			}, _description);
		};

	private:
		bool& _value;
	};


	class ParameterVec3 : public Parameter
	{
	public:
		ParameterVec3(const std::string& name, glm::vec3& value, const std::string& desc = "")
			: Parameter(name, desc), _value(value) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override
		{
			drawParameter(_name, [this]()
			{
				if (ImGui::SliderFloat3(("##" + _name).c_str(), (float*)&(_value), -1000.0f, 1000.0f))
				{

				}
			}, _description);
		};

	private:
		glm::vec3& _value;
	};


	class ParameterCombo : public Parameter
	{
	public:

		ParameterCombo(const std::string& name, const char* items_separated_by_zeros, 
			unsigned int nItems, CallbackCombo callback, const std::string& desc = "")
			: Parameter(name, desc), _items_separated_by_zeros(items_separated_by_zeros), _nItems(nItems), _callback(callback) {};

		void render(float sliderSpeed = DEFAULT_SLIDER_SPEED) override
		{
			drawParameter(_name, [this]()
			{

				if (ImGui::Combo(("##" + _name).c_str(), &(int&)_id, _items_separated_by_zeros))
				{
					for (size_t i = 0; i < _nItems; i++)
					{
						if (i == _id)
						{
							_callback(_id);
							break;
						}
					}
				}
			}, _description);
		};


	private:
		const char* _items_separated_by_zeros;
		unsigned int _nItems;
		unsigned int _id = 0;
		CallbackCombo _callback;
	};

}


