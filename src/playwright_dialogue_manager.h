#ifndef PLAYWRIGHT_DIALOGUE_MANAGER_H
#define PLAYWRIGHT_DIALOGUE_MANAGER_H

#include <godot_cpp/classes/control.hpp>

namespace godot {

	class PlaywrightDialogueManager : public Control {
		GDCLASS(PlaywrightDialogueManager, Control)

		private:
			int branch_index;
				
		protected:
			static void _bind_methods();

		public:
			PlaywrightDialogueManager();
			~PlaywrightDialogueManager();
				
			void _ready() override;
	};

}

#endif
