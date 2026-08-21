#ifndef WEBARCHY_DEFS_H
#define WEBARCHY_DEFS_H

#include "../include/WebArchy.h"
#include "qjs_include.h"

typedef struct 
{
    DWORD x, y;
    DWORD w, h;

    DWORD color; //0xAARRGGBB
} wa_rect_t;

typedef struct
{
    INT (*draw_rect)(DWORD x, DWORD y, DWORD w, DWORD h, DWORD color);
    INT (*draw_string)(const CHAR* string, DWORD color);
    VOID* (*alloc)(DWORD bytes);
    VOID* (*free)(VOID *ptr);
} wa_hall_t;

typedef enum
{
    NODE_ELEMENT, NODE_TEXT
} wa_node_type_t;

typedef struct wa_dom_node
{
    wa_node_type_t type;
    CHAR tag_name[32];
    CHAR text_content[128];
    DWORD color;
    UINT bg_color;

    struct wa_dom_node *first_child;
    struct wa_dom_node *next_sibling;
} wa_dom_node_t;

typedef struct
{
    DWORD w, h;
    wa_dom_node_t *root;
    wa_hall_t hal;

    JSRuntime *js_runtime;
    JSContext *js_ctx;

    DWORD user_data;
} wa_context_t;

#endif