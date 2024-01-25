#ifndef PLAYWRIGHT_TEXTBOX_H
#define PLAYWRIGHT_TEXTBOX_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/timer.hpp>

#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {
  class PlaywrightTextbox : public CanvasLayer {
    GDCLASS(PlaywrightTextbox, CanvasLayer)
    
    private:
      MarginContainer* textbox_margin;
      PanelContainer* textbox_panel;
      RichTextLabel* dialogue_label;
      Timer* letter_display_timer;

      Ref<PackedScene> textbox_margin_scene;
      Ref<PackedScene> textbox_panel_scene;
      Ref<PackedScene> dialogue_label_scene;
    
      Ref<RichTextEffect> text_reveal_effect;
      Ref<RichTextEffect> dlg_trigger_effect;
      Ref<RichTextEffect> dlg_end_effect;

    protected:
      static void _bind_methods();

    public:
      PlaywrightTextbox();
      ~PlaywrightTextbox();

      void set_textbox_margin(MarginContainer* _margin_container);
      MarginContainer* get_textbox_margin() const;
      void set_textbox_panel(PanelContainer* _panel_container);
      PanelContainer* get_textbox_panel() const;
      void set_dialogue_label(RichTextLabel* _rich_text_label);
      RichTextLabel* get_dialogue_label() const;
      void set_letter_display_timer(Timer* _timer);
      Timer* get_letter_display_timer() const;
      
    void _ready() override;
  };
}
#endif
