#include "ui/tools/Editor.h"
#include "imgui.h"
#include <format>
#include "IconsFontAwesome6.h"
#include <string>
#include <numbers>

void Editor::render() {
    ImGui::Begin("Splines", nullptr);
    ImGui::TextDisabled("Note: You can use 'p' for pi (e.g. 0.5p, p/2)");
    ImGui::BeginChild("Poses");
    for (int i = 0; i < manager->poses.size(); i++) {
        Pose2d& point = manager->poses[i];
        ImGui::PushID(i);

        ImGui::SeparatorText(std::format("Point {}", i).c_str());

        ImGui::SetNextItemWidth(80);
        ImGui::InputDouble("X", &point.position.x(), 0, 0, "%g");
        
        ImGui::SameLine();
        ImGui::SetNextItemWidth(80);
        ImGui::InputDouble("Y", &point.position.y(), 0, 0, "%g");

        ImGui::SameLine();
        ImGui::SetNextItemWidth(80);

        static char angleBuf[64];
        static ImGuiID activeAngleId = 0;
        ImGuiID currentId = ImGui::GetID("RAD");

        char localBuf[64];
        char* pBuf = localBuf;
        if (activeAngleId == currentId) {
            pBuf = angleBuf;
        } else {
            snprintf(localBuf, sizeof(localBuf), "%g", point.rotation);
        }

        if (ImGui::InputText("RAD", pBuf, 64)) {
            try {
                std::string s(pBuf);
                if (!s.empty()) {
                    if (s.find('p') != std::string::npos) {
                        size_t p_idx = s.find('p');
                        double val = 1.0;
                        std::string before = s.substr(0, p_idx);
                        if (!before.empty() && before != "-") val = std::stod(before);
                        else if (before == "-") val = -1.0;
                        val *= std::numbers::pi;
                        std::string after = s.substr(p_idx + 1);
                        if (!after.empty() && after[0] == '/') val /= std::stod(after.substr(1));
                        point.rotation = val;
                    } else {
                        point.rotation = std::stod(s);
                    }
                }
            } catch (...) {}
        }
        if (ImGui::IsItemActive()) {
            activeAngleId = currentId;
            if (pBuf != angleBuf) strcpy(angleBuf, pBuf);
        } else if (activeAngleId == currentId) {
            activeAngleId = 0;
        }
        
        ImGui::SameLine();

        ImGui::Text("|");

        ImGui::SameLine();

        bool disabled = false;

        disabled = i <= 0;
        if (disabled)
            ImGui::BeginDisabled();
        if (ImGui::Button(ICON_FA_CHEVRON_UP, {20, 0})) {
            std::swap(manager->poses[i], manager->poses[i-1]);
        }
        if (disabled)
            ImGui::EndDisabled();

        ImGui::SameLine();

        disabled = i >= manager->poses.size() -1;
        if (disabled)
            ImGui::BeginDisabled();
        if (ImGui::Button(ICON_FA_CHEVRON_DOWN, {20, 0})) {
            std::swap(manager->poses[i], manager->poses[i+1]);
        }
        if (disabled)
            ImGui::EndDisabled();
        ImGui::SameLine();

        disabled = manager->poses.size() <= 1;
        if (disabled)
            ImGui::BeginDisabled();
        ImGui::SetNextItemWidth(25);
        ImGui::PushStyleColor(ImGuiCol_Button, 0xFF0000DD);
        if (ImGui::Button(ICON_FA_XMARK, {20, 0})) {
                manager->poses.erase(manager->poses.begin() + i);
        }
        ImGui::PopStyleColor();
        if (disabled)
            ImGui::EndDisabled();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, 0xFF00DD00);
        if (ImGui::Button(ICON_FA_PLUS, {20, 0})) {
            manager->poses.insert(manager->poses.begin() + i + 1, Pose2d::Zero());
        }
        ImGui::PopStyleColor();

        ImGui::PopID();
    }
    ImGui::EndChild();
    ImGui::End();
}