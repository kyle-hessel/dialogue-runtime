#include "playwright_dialogue_manager.h"

#include "playwright_textbox.h"
#include "playwright_textbox_response.h"
#include "playwright_dialogue.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void PlaywrightDialogueManager::_bind_methods() {
	


	ADD_SIGNAL(MethodInfo("dialogue_complete"));
	ADD_SIGNAL(MethodInfo("dialogue_trigger"));
	ADD_SIGNAL(MethodInfo("end_branch"));
}

PlaywrightDialogueManager::PlaywrightDialogueManager() {
	branch_index = 0;

	player_selection = 0;

	branch_index = 0;
	branch_ended = false;
	line_index = 0;

	is_npc_dialogue_active = false;
	is_player_dialogue_active = false;
	can_advance_line = false;
}

PlaywrightDialogueManager::~PlaywrightDialogueManager() {

}

void PlaywrightDialogueManager::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
	else {
		UtilityFunctions::print("is this thing on?");

		ResourceLoader* re_lo = ResourceLoader::get_singleton();

		textbox_scene = re_lo->load("res://addons/playwright_runtime/scenes/playwright_textbox.tscn");
		textbox_response_scene = re_lo->load("res://addons/playwright_runtime/scenes/playwright_textbox_response.tscn");

		textbox_inst = Object::cast_to<PlaywrightTextbox>(textbox_scene->instantiate());
		textbox_response_inst = Object::cast_to<PlaywrightTextboxResponse>(textbox_response_scene->instantiate());
	}
}
