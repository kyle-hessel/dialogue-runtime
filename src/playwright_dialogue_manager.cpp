#include "playwright_dialogue_manager.h"

#include "playwright_textbox.h"
#include "playwright_textbox_response.h"
#include "playwright_dialogue.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/signal.hpp>

using namespace godot;

void PlaywrightDialogueManager::_bind_methods() {
	
	ClassDB::bind_method(D_METHOD("initiate_dialogue", "dlg", "dlg_index"), &PlaywrightDialogueManager::initiate_dialogue);
	ClassDB::bind_method(D_METHOD("dlg_early_out"), &PlaywrightDialogueManager::dlg_early_out);
	ClassDB::bind_method(D_METHOD("set_can_advance_line_true"), &PlaywrightDialogueManager::set_can_advance_line_true);
	ClassDB::bind_method(D_METHOD("set_is_player_dialogue_active", "_player_dlg_active"), &PlaywrightDialogueManager::set_is_player_dialogue_active);
  	ClassDB::bind_method(D_METHOD("get_is_player_dialogue_active"), &PlaywrightDialogueManager::get_is_player_dialogue_active);
  	ClassDB::add_property("PlaywrightDialogueManager", PropertyInfo(Variant::BOOL, "is_player_dialogue_active"), "set_is_player_dialogue_active", "get_is_player_dialogue_active");
	ClassDB::bind_method(D_METHOD("set_is_npc_dialogue_active", "_npc_dlg_active"), &PlaywrightDialogueManager::set_is_npc_dialogue_active);
  	ClassDB::bind_method(D_METHOD("get_is_npc_dialogue_active"), &PlaywrightDialogueManager::get_is_npc_dialogue_active);
  	ClassDB::add_property("PlaywrightDialogueManager", PropertyInfo(Variant::BOOL, "is_npc_dialogue_active"), "set_is_npc_dialogue_active", "get_is_npc_dialogue_active");
	ClassDB::bind_method(D_METHOD("set_branch_index", "_branch_idx"), &PlaywrightDialogueManager::set_branch_index);
	ClassDB::bind_method(D_METHOD("get_branch_index"), &PlaywrightDialogueManager::get_branch_index);
	ClassDB::add_property("PlaywrightDialogueManager", PropertyInfo(Variant::INT, "branch_index"), "set_branch_index", "get_branch_index");
	ClassDB::bind_method(D_METHOD("set_participants", "_participants"), &PlaywrightDialogueManager::set_participants);
	ClassDB::bind_method(D_METHOD("get_participants"), &PlaywrightDialogueManager::get_participants);
	ClassDB::add_property("PlaywrightDialogueManager", PropertyInfo(Variant::DICTIONARY, "participants"), "set_participants", "get_participants");
	

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
		set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);
		UtilityFunctions::print("is this thing on?");


		ResourceLoader* re_lo = ResourceLoader::get_singleton();

		textbox_scene = re_lo->load("res://addons/playwright_runtime/scenes/playwright_textbox.tscn");
		textbox_response_scene = re_lo->load("res://addons/playwright_runtime/scenes/playwright_textbox_response.tscn");

		textbox_inst = Object::cast_to<PlaywrightTextbox>(textbox_scene->instantiate());
		textbox_response_inst = Object::cast_to<PlaywrightTextboxResponse>(textbox_response_scene->instantiate());
	}
}

void PlaywrightDialogueManager::_unhandled_input(const Ref<InputEvent> &event) {
	// if the right key is pressed, determine how to proceed through dialogue.
	if (event->is_action_pressed("gui_select")) {
		// if there's a player dialogue, pass in the player choice (branch) and reload to continue on.
		if (is_player_dialogue_active) {
			advance_dlg_and_reload_textbox(textbox_response_inst->get_player_selection());
		}
		// if there's an NPC dialogue, decide to reload with the correct branch OR display the rest of the line first.
		else if (is_npc_dialogue_active) {
			if (can_advance_line) {
				advance_dlg_and_reload_textbox(branch_index);
			}
			// if the key is pressed early before the line can be advanced, display the rest of the line all at once.
			else {
				textbox_inst->display_line();
			}
		}
	}
}

void PlaywrightDialogueManager::initiate_dialogue(Ref<PlaywrightDialogue> dlg, int dlg_index) {
	dialogue_initiator = dlg->get_speaker();
	continue_dialogue(dlg, dlg_index);
}

void PlaywrightDialogueManager::end_dialogue() {
	// the five below lines may be redundant.
	is_npc_dialogue_active = false;
	is_player_dialogue_active = false;
	can_advance_line = false;
	line_index = 0;
	branch_index = 0;

	// once dialogue is completely finished, clear participants dictionary.
	participants.clear();
	emit_signal("dialogue_complete");
}

// starts a new dialogue if one isn't active by displaying a textbox with the given dialogue lines.
void PlaywrightDialogueManager::continue_dialogue(Ref<PlaywrightDialogue> dlg, int dlg_index, TypedArray<int> ending_branch_positions) {
	//if branches ended, use the ending_branch_positions array to determine how to offset dialogue_index.
	if (!ending_branch_positions.is_empty()) {
		dlg_index = recalculate_branch_pos(dlg_index, ending_branch_positions);
	}

	bool in_cutscene = get_node<Node3D>(NodePath("/root/GameManager/EventsManager"))->get("in_cutscene");
	if (in_cutscene == false) {
		participants[dialogue_initiator].set("dialogue_branch_pos", dlg_index);
	}

	current_dialogue = dlg;

	if (dlg->get_dialogue_type() != PlaywrightDialogue::DIALOGUE_TYPE::RESPONSE) {
		// overwrite pre-existing dialogue_lines with new lines that were passed to the dialogue manager.
		TypedArray<String> npc_dlg_selection = dlg->get_dialogue_options()[dlg_index];
		npc_dialogue_lines = npc_dlg_selection;
		// mark dialogue as active once a textbox is shown so another can't be instantiated over the existing one.
		is_npc_dialogue_active = true;
	}
	else {
		TypedArray<String> player_dlg_option = dlg->get_dialogue_options()[dlg_index];
		player_response_lines = player_dlg_option;
		is_player_dialogue_active = true;
	}

	// cache the branch_index for reload_textbox in_unhandled_input.
	branch_index = dlg_index;

	show_textbox(dlg->get_dialogue_type());
}

// determine how much to offset the dialogue index by, based on how many branches collapsed.
int PlaywrightDialogueManager::recalculate_branch_pos(int dlg_index, TypedArray<int> ending_branch_positions) {
	int original_dlg_index = dlg_index;

	for (int pos = 0; pos < ending_branch_positions.size(); pos++) {
		if (original_dlg_index > pos) {
			dlg_index--;
		}
	}

	return dlg_index;
}

// determine if an NPC dialogue box or a player dialogue box is going to be shown.
void PlaywrightDialogueManager::show_textbox(PlaywrightDialogue::DIALOGUE_TYPE dlg_type) {
	// if NPC dialogue: instantiate the textbox, hook up a signal for advancing dlg lines, and begin dlg printing to the textbox.
	if (dlg_type != PlaywrightDialogue::DIALOGUE_TYPE::RESPONSE) {
		textbox_inst = Object::cast_to<PlaywrightTextbox>(textbox_scene->instantiate());
		// mark can_advance_line as true again once the textbox deems the current string as finished displaying, using a signal.
		textbox_inst->connect("finished_displaying", Callable(this, "set_can_advance_line_true"));
		add_child(textbox_inst);
		// for consistent naming behind the scenes, probably not necessary but could be useful.
		String inst_name = "TextboxInst" + UtilityFunctions::var_to_str(line_index);
		textbox_inst->set("name", inst_name);
		// using the current line index (incremented using player input), decide which dlg line to print from what was passed into the manager.
		textbox_inst->begin_display_dialogue(npc_dialogue_lines[line_index]);
		// mark can_advance_line to false for now so that the line can't be skipped prematurely.
		can_advance_line = false;
	}
	// if player response: do the same as above but skip some steps regarding line-by-line display, and pass in the whole array of strings at once.
	else {
		textbox_response_inst = Object::cast_to<PlaywrightTextboxResponse>(textbox_response_scene->instantiate());
		add_child(textbox_response_inst);
		String inst_name = "TextboxResponseInst" + UtilityFunctions::var_to_str(line_index);
		textbox_response_inst->set("name", inst_name);
		textbox_response_inst->begin_display_response(player_response_lines);
	}
}

void PlaywrightDialogueManager::set_can_advance_line_true() {
	can_advance_line = true;
}

// deletes the current textbox, increments which dlg string should be fed into the next textbox, and draws the next line with a new textbox if there is one.
void PlaywrightDialogueManager::advance_dlg_and_reload_textbox(int dlg_index) {
	// if there isn't a next dlg queued up, destroy existing textboxes as normal.
	if (current_dialogue->get_next_dialogue() == nullptr) {
		// if the player has an active dlg, destroy that when this function is called before destroying NPC dlg.
		if (is_player_dialogue_active) {
			textbox_response_inst->queue_free();
			is_player_dialogue_active = false;
		}

		textbox_inst->queue_free(); // could add a function here instead that plays an animation before queue_free.
		line_index++;

		// if there is no more dlg, reset to defaults.
		if (line_index >= npc_dialogue_lines.size()) {
			end_dialogue();
			return;
		}
		// otherwise, keep printing dlg.
		else {
			show_textbox(current_dialogue->get_dialogue_type());
		}
	}
	// if there is a dlg queued up, collapse any branches and determine what to do to transition to that dlg, depending on its type.
	else {
		// for branches that resolve earlier than the length of the entire dlg.
		if (is_npc_dialogue_active) {
			TypedArray<String> dlg_option = current_dialogue->get_dialogue_options()[dlg_index];
			String dlg_string = dlg_option[0];
			if (dlg_string.contains("[end]") == true) {
				branch_ended = true;
			}
		}
		else if (is_player_dialogue_active) {
			TypedArray<String> dlg_option = current_dialogue->get_dialogue_options()[dlg_index];
			String dlg_string = dlg_option[dlg_index];
			if (dlg_string.contains("[end]") == true) {
				branch_ended = true;
			}
		}

		// if we are on a branch that ended early, then early out!
		if (branch_ended) {
			textbox_inst->queue_free(); // could add a function here instead that plays an animation before queue_free.
			if (is_player_dialogue_active) {
				textbox_response_inst->queue_free();
			}
			end_dialogue();
			return;
		}
		else {
			// determine which inactive branches ended on this dlg to offset dlg_index later, once continue_dialogue is called.
			TypedArray<int> ending_branches;

			if (is_npc_dialogue_active) {
				TypedArray<Array> dlg_options = current_dialogue->get_dialogue_options();
				for (int options_pos = 0; options_pos < dlg_options.size(); options_pos++) {
					TypedArray<String> dlg_option = dlg_options[options_pos];
					String dlg_string = dlg_option[0];
					if (dlg_string.contains("[end]") == true) {
						ending_branches.append(options_pos);
					}
				}
			}
			else if (is_player_dialogue_active) {
				int pos_tally = 0;
				TypedArray<Array> dlg_options = current_dialogue->get_dialogue_options();
				for (int options_pos = 0; options_pos < dlg_options.size(); options_pos++) {
					TypedArray<String> dlg_option = dlg_options[options_pos];
					for (int lines_pos = 0; lines_pos < dlg_option.size(); lines_pos++) {
						String dlg_string = dlg_option[lines_pos];
						if (dlg_string.contains("[end]") == true) {
							ending_branches.append(pos_tally);
						}
						pos_tally++;
					}
				}
			}

			// lastly, transition to the next dlg.
			PlaywrightDialogue::DIALOGUE_TYPE next_dlg_type = current_dialogue->get_next_dialogue()->get_dialogue_type();
			bool in_cutscene = get_node<Node3D>(NodePath("/root/GameManager/EventsManager"))->get("in_cutscene");
			switch(next_dlg_type) {
				case PlaywrightDialogue::DIALOGUE_TYPE::DEFAULT:
					// if the next dlg is an NPC default dlg and the current dlg is a player response, do the following:
					if (is_player_dialogue_active) {
						// delete the player textbox and mark the player dlg as inactive.
						textbox_response_inst->queue_free();
						is_player_dialogue_active = false;

						// realign dlg_index to align 1D array of NPC dlgs with 1D array of potential player responses.
						dlg_index = realign_npc_dlg_index(dlg_index);
					}

					textbox_inst->queue_free();
					line_index = 0;

					if (in_cutscene == false) {
						// if not in a cutscene, make the new NPC dlg the checkpoint dlg for the initiator of the conversation.
						participants[dialogue_initiator].set("checkpoint_dialogue", current_dialogue->get_next_dialogue());
					}

					continue_dialogue(current_dialogue->get_next_dialogue(), dlg_index, ending_branches);

					break;
				case PlaywrightDialogue::DIALOGUE_TYPE::RESPONSE:

					line_index++;

					// once the NPC dlg lines run out, just start the new dlg chain.
					if (line_index >= npc_dialogue_lines.size()) {
						is_npc_dialogue_active = false;
						can_advance_line = false;
						// don't reset line_index here, as we need that data if textbox_inst remains during a player response in order to properly destroy textbox_inst after the fact.
						// don't mark an NPC dlg checkpoint during a player response, as they aren't speaking (going to try to ensure this isn't needed going forward).

						// realign dlg_index depending on what the upcoming player dlgs contain.
						dlg_index = realign_player_dlg_index(dlg_index);

						continue_dialogue(current_dialogue->get_next_dialogue(), dlg_index, ending_branches);
					
					}
					// otherwise, continue dlg chain.
					else {
						textbox_inst->queue_free();
						show_textbox(current_dialogue->get_dialogue_type());
					}

					break;
				case PlaywrightDialogue::DIALOGUE_TYPE::CALL:

					break;
				case PlaywrightDialogue::DIALOGUE_TYPE::MESSAGE:

					break;
				case PlaywrightDialogue::DIALOGUE_TYPE::SHOUT:

					break;
			}
		}
	}
}

// all functions below are dlg and textbox helper functions.

int PlaywrightDialogueManager::realign_npc_dlg_index(int dlg_index) {
	// if the incoming NPC dlg only has one option, just set dlg_index to 0 as the branching tree is now collapsing back down.
	if (current_dialogue->get_next_dialogue()->get_dialogue_options().size() == 1) {
		dlg_index = 0;
	}
	/* if the incoming NPC dlg has multiple options, determine how to format dlg_index 
	before passing it onto the next NPC dlg if the player had more than one response list from the prior branches. */
	else {
		if (current_dialogue->get_dialogue_options().size() > 1) {
			// map position of player's response in a 2D array back to a 1D array and assign it to dlg_index so that the NPC chooses the correct line of dialogue.
			dlg_index = return_dlg_index_in_1d_array_format(dlg_index);
		}
	}

	return dlg_index;
}

int PlaywrightDialogueManager::realign_player_dlg_index(int dlg_index) {
	// if the incoming player dlg only has one option, just set dlg_index to 0 as the branching tree is now collapsing back down.
	if (current_dialogue->get_next_dialogue()->get_dialogue_options().size() == 1) {
		dlg_index = 0;
	}

	return dlg_index;
}

// break down 2D array of potential player responses from PlaywrightDialogue's dialogue_options into a flat 1D array, and convert the dlg_index accordingly.
int PlaywrightDialogueManager::return_dlg_index_in_1d_array_format(int dlg_index) {
	int temp_pos = 0;
	
	for (int pos = 0; pos < branch_index; pos++) {
		TypedArray<Array> dlg_options = current_dialogue->get_dialogue_options();
		Array dlg_option = dlg_options[pos];
		temp_pos += dlg_option.size();
	}

	return temp_pos + dlg_index;
}

void PlaywrightDialogueManager::destroy_textboxes() {
	if (is_player_dialogue_active) {
		textbox_response_inst->queue_free();
		is_player_dialogue_active = false;
		textbox_inst->queue_free();
		is_npc_dialogue_active = false;
		can_advance_line = false;
		line_index = 0;
		branch_index = 0;
	}
	else {
		textbox_inst->queue_free();
		is_npc_dialogue_active = false;
		can_advance_line = false;
		line_index = 0;
		branch_index = 0;
	}
}

void PlaywrightDialogueManager::dlg_early_out() {
	if (is_player_dialogue_active || is_npc_dialogue_active) {
		line_index = 99; // overload to a value bigger than any array of dlg strings ever ought to be, to force-delete.
		destroy_textboxes();
	}
}

// getters and setters for variables exposed in gdscript

void PlaywrightDialogueManager::set_is_player_dialogue_active(bool _player_dlg_active) {
	is_player_dialogue_active = _player_dlg_active;
}

bool PlaywrightDialogueManager::get_is_player_dialogue_active() const {
	return is_player_dialogue_active;
}

void PlaywrightDialogueManager::set_is_npc_dialogue_active(bool _npc_dlg_active) {
	is_npc_dialogue_active = _npc_dlg_active;
}

bool PlaywrightDialogueManager::get_is_npc_dialogue_active() const {
	return is_npc_dialogue_active;
}

void PlaywrightDialogueManager::set_branch_index(int _branch_idx) {
	branch_index = _branch_idx;
}

int PlaywrightDialogueManager::get_branch_index() const {
	return branch_index;
}

void PlaywrightDialogueManager::set_participants(Dictionary _participants) {
	participants = _participants;
}

Dictionary PlaywrightDialogueManager::get_participants() const {
	return participants;
}