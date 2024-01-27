#include "playwright_dialogue_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

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
	if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
	else {
		UtilityFunctions::print("is this thing on?");
	}
}
