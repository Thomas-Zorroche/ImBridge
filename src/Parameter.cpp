#include "Parameter.hpp"

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

}