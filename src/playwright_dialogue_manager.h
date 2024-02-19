#ifndef PLAYWRIGHT_DIALOGUE_MANAGER_H
#define PLAYWRIGHT_DIALOGUE_MANAGER_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "playwright_textbox.h"
#include "playwright_textbox_response.h"

namespace godot {

	class PlaywrightDialogueManager : public Control {
		GDCLASS(PlaywrightDialogueManager, Control)

		private:
			int branch_index;

			Ref<PackedScene> textbox_scene;
			Ref<PackedScene> textbox_response_scene;

			PlaywrightTextbox* textbox_inst;
			PlaywrightTextboxResponse* textbox_response_inst;
				
		protected:
			static void _bind_methods();

		public:
			PlaywrightDialogueManager();
			~PlaywrightDialogueManager();
				
			void _ready() override;
	};

}

#endif
