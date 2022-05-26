#include "Parameter.hpp"

#include "imgui/imgui.h"

namespace ImBridge {

void displayHoverDescription(const std::string& desc)
{
	if (!desc.empty() && ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

template <typename UIFonction>
void drawParameter(const std::string& name, UIFonction uiFonction, const std::string& desc)
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

void ParameterFloat::render(float sliderSpeed)
{
	drawParameter(_name.c_str(), [this, sliderSpeed]()
		{
			if (ImGui::DragFloat(("##" + _name).c_str(), &_value, sliderSpeed, _min, _max))
			{

			}
		}, _description);
};

void ParameterInt::render(float sliderSpeed)
{
	drawParameter(_name.c_str(), [this]()
		{
			if (ImGui::SliderInt(("##" + _name).c_str(), &_value, minValue, maxValue))
			{
				_callback(_value);
			}
		}, _description);
};

void ParameterBoolean::render(float sliderSpeed)
{
	drawParameter(_name.c_str(), [this]()
		{
			ImGui::Checkbox(_name.c_str(), &_value);
		}, _description);
};

void ParameterVec3::render(float sliderSpeed)
{
	drawParameter(_name, [this]()
		{
			if (ImGui::SliderFloat3(("##" + _name).c_str(), (float*)&(_value), -1000.0f, 1000.0f))
			{

			}
		}, _description);
};

void ParameterCombo::render(float sliderSpeed)
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

void ParameterListBox::render(float sliderSpeed)
{
	drawParameter(_name, [this]()
	{
		if (ImGui::BeginListBox(("##" + _name).c_str()))
		{
			for (int n = 0; n < _items.size(); n++)
			{
				if (_items[n] == "-")
				{
					ImGui::Separator();
					continue;
				}

				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(_items[n].c_str(), is_selected))
				{
					item_current_idx = n;
					_callback(n);
				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndListBox();
		}
	}, _description);
};

}