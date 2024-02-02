#include "Data/Project.h"
#include <iostream>

Project::Project()
{}

const std::string& Project::getFilePath() const
{
    return m_FilePath;
}

const ProjectSettings& Project::getSettings() const
{
    return m_Settings;
}

ProjectSettings& Project::getSettings()
{
    return m_Settings;
}

bool Project::hasDefinedFilePath() const
{
    return !m_FilePath.empty();
}

void Project::setFilePath(const std::string& filePath)
{
    m_FilePath = filePath;
}

void Project::setSettings(const ProjectSettings& settings)
{
    m_Settings = settings;
}