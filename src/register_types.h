#ifndef PLAYWRIGHT_DIALOGUE_MANAGER_REGISTER_TYPES_H
#define PLAYWRIGHT_DIALOGUE_MANAGER_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_playwright_extension(ModuleInitializationLevel p_level);
void terminate_playwright_extension(ModuleInitializationLevel p_level);

#endif