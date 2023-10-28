#pragma once

#include <FileSystem>

class MessageHistory {
public:
	bool LoadMessageHistoryFromFile(const std::filesystem::path& filepath);
};