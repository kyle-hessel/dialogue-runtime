#include "playwright_dialogue_manager.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void PlaywrightDialogueManager::_bind_methods() {

}

PlaywrightDialogueManager::PlaywrightDialogueManager() {
    branch_index = 0;
}

PlaywrightDialogueManager::~PlaywrightDialogueManager() {

}

void PlaywrightDialogueManager::_ready() {
    UtilityFunctions::print("is this thing on?");
}