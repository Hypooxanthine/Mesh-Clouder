#pragma once

#include <string>
#include <glm/glm.hpp>

struct ProjectSettings
{
    bool realTimePointCloudGeneration = true;
    int selectedView = 0;
    float pointSize = 0.05f;
    float density = 1;
    glm::vec3 minDisturb = {0.f, 0.f, 0.f}, maxDisturb = {0.f, 0.f, 0.f};
    int seed = 0;
};

class Project
{
public:
    Project();

    const std::string& getFilePath() const;
    const ProjectSettings& getSettings() const;
    ProjectSettings& getSettings();
    bool hasDefinedFilePath() const;

    void setFilePath(const std::string& filePath);
    void setSettings(const ProjectSettings& settings);

private:
    ProjectSettings m_Settings;
    std::string m_FilePath;
};