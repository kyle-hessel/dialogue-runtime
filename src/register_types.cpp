#include "register_types.h"

#include "playwright_dialogue.h"
#include "playwright_dialogue_manager.h"
#include "playwright_textbox.h"
#include "playwright_textbox_response.h"
#include "rich_text_effect_reveal.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_playwright_extension(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<PlaywrightDialogue>();
	ClassDB::register_class<PlaywrightDialogueManager>();
	ClassDB::register_class<PlaywrightTextbox>();
	ClassDB::register_class<PlaywrightTextboxResponse>();
	ClassDB::register_class<RichTextEffectReveal>();

	// I think this will make these all runtime in Godot 4.3, adding them now:
	// alternatively, use register_class(false, true, true) - perhaps.
	// see https://github.com/godotengine/godot-cpp/pull/1256/commits/fb884573ea1a0ec36d1968bf12a667cd17023d38, specifically the changes to class_db.hpp.
	//ClassDB::register_class<PlaywrightDialogue>(); // not just a runtime class!
	//ClassDB::register_runtime_class<PlaywrightDialogueManager>();
	//ClassDB::register_runtime_class<PlaywrightTextbox>();
	//ClassDB::register_runtime_class<PlaywrightTextboxResponse>();
	//ClassDB::register_runtime_class<RichTextEffectReveal>();
}

void terminate_playwright_extension(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
	// Extension initialization
	GDExtensionBool GDE_EXPORT playwright_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_playwright_extension);
		init_obj.register_terminator(terminate_playwright_extension);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
