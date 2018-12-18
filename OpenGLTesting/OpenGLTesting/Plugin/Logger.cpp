#include "Logger.hpp"

std::string Logger::tag_;
std::shared_ptr<spdlog::logger> Logger::console_ = nullptr;