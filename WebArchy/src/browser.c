#include "browser.h"
#include "render.h"
#include "qjs_port.h"
#include "qjs_runtime.h"

wa_context_t* WA_Init
(
    wa_hall_t hal,
    DWORD w, DWORD h
)
{
    wa_context_t *ctx = (wa_context_t*)hal.alloc(sizeof(wa_context_t));
    if (!ctx) return NULL;

    ctx->hal = hal;
    ctx->w = w;
    ctx->h = h;
    ctx->js_runtime = JS_NewRuntime2
    (
        &WebArchy_JS_Memory_Alloc_Functions,
        NULL
    );
    if (!ctx->js_runtime) return NULL;

    ctx->js_ctx = JS_NewContext(ctx->js_runtime);
    if (!ctx->js_ctx) return NULL;

    JS_SetContextOpaque(ctx->js_ctx, ctx);

    JSValue global_obj = JS_GetGlobalObject(ctx->js_ctx);
    JS_SetPropertyStr
    (
        ctx->js_ctx, global_obj, "drawRect",
        JS_NewCFunction
        (
            ctx->js_ctx, JS_WA_DrawRect,
            "drawRect", 5
        )
    );

    JS_FreeValue(ctx->js_ctx, global_obj);

    return ctx;
}

VOID WA_Load_HTML(wa_context_t *ctx, const CHAR *html_source)
{
    if (!ctx) return;

    wa_dom_node_t *body =
    (wa_dom_node_t*)ctx->hal.alloc(sizeof(wa_dom_node_t));

    body->type = NODE_ELEMENT;
    body->bg_color = 0xFF1E1E1E; // Read the next comment

    /*
        You can change this hexadecimal value
        To other colors

        0xFF1E1E1E = Dark mode background
    */

    wa_dom_node_t *h1 =
    (wa_dom_node_t*)ctx->hal.alloc(sizeof(wa_dom_node_t));

    const char* title = "Your Title Here";
    INT i = 0;

    while (title[i] && i < 127)
    {
        h1->text_content[1] = title[i];
        i++;
    }
    
    h1->text_content[i] = '\0';

    body->first_child = h1;
    h1->next_sibling = NULL;

    ctx->root = body;
}

VOID WA_Render(wa_context_t *ctx)
{
    if (!ctx || !ctx->root)
    {
        return;
    }

    DWORD current_y = 0;
    
    Render_node
    (
        ctx, ctx->root,
        &current_y
    );
}

VOID WA_Destroy(wa_context_t *ctx)
{
    if (!ctx) return;
    if (ctx->js_ctx) JS_FreeContext(ctx->js_ctx);
    if (ctx->js_runtime) JS_FreeRuntime(ctx->js_runtime);
}