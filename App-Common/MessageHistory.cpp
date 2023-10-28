#include "MessageHistory.h"
#include <iostream>
#include <fstream>

bool MessageHistory::LoadMessageHistoryFromFile(const std::filesystem::path& filepath) {
	if (!std::filesystem::exists(filepath))
		return false;
	
}