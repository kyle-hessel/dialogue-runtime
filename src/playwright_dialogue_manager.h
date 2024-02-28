#ifndef PLAYWRIGHT_DIALOGUE_MANAGER_H
#define PLAYWRIGHT_DIALOGUE_MANAGER_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "playwright_textbox.h"
#include "playwright_textbox_response.h"
#include "playwright_dialogue.h"

#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>

namespace godot {

	class PlaywrightDialogueManager : public Control {
		GDCLASS(PlaywrightDialogueManager, Control)

		private:
			Ref<PackedScene> textbox_scene;
			Ref<PackedScene> textbox_response_scene;

			PlaywrightTextbox* textbox_inst;
			PlaywrightTextboxResponse* textbox_response_inst;

			Dictionary participants;
			String dialogue_initiator;

			TypedArray<String> npc_dialogue_lines;
			TypedArray<String> player_response_lines;
			int player_selection;

			// branch index is used to track which player response branch is chosen (based on NPC dialogue branches) due to how the data is structured.
			// if dialogue_index is the index of the actual dialogue in the nested array, branch_index is the index of which dialogue grouping to select in the outer array.
			int branch_index;
			bool branch_ended;
			Ref<PlaywrightDialogue> current_dialogue;
			int line_index;

			bool is_npc_dialogue_active;
			bool is_player_dialogue_active;
			bool can_advance_line;

			void end_dialogue();
			void continue_dialogue(Ref<PlaywrightDialogue> dlg, int dlg_index = 0, TypedArray<int> ending_branch_positions = {});
			int recalculate_branch_pos(int dlg_index, TypedArray<int> ending_branch_positions);
			void show_textbox(PlaywrightDialogue::DIALOGUE_TYPE dlg_type);
			void advance_dlg_and_reload_textbox(int dlg_index = 0);
			int realign_npc_dlg_index(int dlg_index);
			int realign_player_dlg_index(int dlg_index);
			int return_dlg_index_in_1d_array_format(int dlg_index);
			void destroy_textboxes();

		protected:
			static void _bind_methods();

		public:
			PlaywrightDialogueManager();
			~PlaywrightDialogueManager();
				
			void _ready() override;
			void _unhandled_input(const Ref<InputEvent> &event) override;
			void initiate_dialogue(Ref<PlaywrightDialogue> &dlg, int dlg_index = 0);
			void set_can_advance_line_true();

			void set_is_player_dialogue_active(bool _player_dlg_active);
			bool get_is_player_dialogue_active() const;
			void set_is_npc_dialogue_active(bool _npc_dlg_active);
			bool get_is_npc_dialogue_active() const;
	};

}

#endif
