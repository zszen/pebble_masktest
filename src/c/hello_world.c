#include <pebble.h>
#include "ZApi.h"
// #include <pebble-effect-layer/pebble-effect-layer.h>
#include "pebble-effect-layer.h"

#define BACKGROUND_W 144
#define BACKGROUND_H 168

static Window *s_window;
static TextLayer *s_text_layer;

static BitmapLayer* layerBitmap;
static GBitmap *background;
static GBitmap *background2;

static EffectLayer* effect_layer;
static EffectLayer* effect_layer2;
static EffectMask* effectMask;
static EffectMask* effectMask2;

// void bitmapColorUpdate(struct Layer* layer, GContext* ctx){
// 	graphics_context_set_fill_color(ctx, GColorRed);
// 	graphics_draw_round_rect(ctx, layer_get_frame(layer), 0);
// }

static void init(void) {
	// Create a window and get information about the window
	s_window = window_create();
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	window_set_background_color(s_window, GColorYellow);
	
	
	
// 	BitmapLayer* background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
//     bitmap_layer_set_bitmap(background_layer, background);
//     layer_add_child(window_get_root_layer(s_window), bitmap_layer_get_layer(background_layer));
	
  // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	text_layer_set_text(s_text_layer, "Hi, I'm a Pebble!");
  
  // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);

// 	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));
  
//   // Enable text flow and paging on the text layer, with a slight inset of 10, for round screens
  text_layer_enable_screen_text_flow_and_paging(s_text_layer, 10);
	
	BitmapLayer* bl = ZAPI_ImageCreate(RESOURCE_ID_IMAGE_NUM0, bounds, true);
	layer_add_child(window_get_root_layer(s_window), bitmap_layer_get_layer(bl));

	// Push the window, setting the window animation to 'true'
	window_stack_push(s_window, true);
	{
		effectMask = malloc(sizeof(EffectMask));
		effectMask->mask_colors = malloc(sizeof(GColor)*2);
		effectMask->mask_colors[0] = GColorBlack;
		effectMask->mask_colors[1] = GColorClear;
		effectMask->background_color = GColorClear;
		effectMask->text = NULL;
		effectMask->bitmap_mask = NULL;
		effectMask->bitmap_background = NULL;
		background = ZAPI_ImageResource(RESOURCE_ID_IMAGE_BG_RAINBOW);
		effectMask->bitmap_background = background;
			
		effect_layer = effect_layer_create(GRect(50, 0, 25, 168));
 		effect_layer_add_effect(effect_layer, effect_mask, effectMask);
  		layer_add_child(window_get_root_layer(s_window), effect_layer_get_layer(effect_layer));
		
// 		effectMask2 = malloc(sizeof(EffectMask));
// 		effectMask2->mask_colors = malloc(sizeof(GColor)*2);
// 		effectMask2->mask_colors[0] = GColorBlack;
// 		effectMask2->mask_colors[1] = GColorClear;
// 		effectMask2->background_color = GColorClear;
// 		effectMask2->text = NULL;
// 		effectMask2->bitmap_mask = NULL;
// 		effectMask2->bitmap_background = NULL;
// 		background2 = ZAPI_ImageResource(RESOURCE_ID_IMAGE_BG_RAINBOW);
// 		effectMask2->bitmap_background = background2;
			
// 		effect_layer2 = effect_layer_create(GRect(80, 0, 25, 168));
//  		effect_layer_add_effect(effect_layer2, effect_mask, effectMask2);
//   		layer_add_child(window_get_root_layer(s_window), effect_layer_get_layer(effect_layer2));
		
		
// 		effect_layer = effect_layer_create(GRect(96,139,26,21));
// 		effect_layer_add_effect(effect_layer, effect_invert, NULL);
// 		layer_add_child(window_get_root_layer(s_window), effect_layer_get_layer(effect_layer));
	}
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

static void deinit(void) {
	// Destroy the text layer
	text_layer_destroy(s_text_layer);
	
	// Destroy the window
	window_destroy(s_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
