#include <SDL2/SDL.h>
#include <emscripten.h>

#include "Atari2600.h"

Atari2600* atari = new Atari2600();

struct context
{
    SDL_Renderer *renderer;
};

extern "C"
{
    void EMSCRIPTEN_KEEPALIVE start()
    {
        atari->start();
    }

    void EMSCRIPTEN_KEEPALIVE stop()
    {
        atari->stop();
    }
}

void mainloop(void *arg)
{
    context *ctx = static_cast<context*>(arg);

    if(atari->isReady()) {
		atari->nextFrame(ctx->renderer);
    }

}

int main()
{
    context ctx;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(341, 262, 0, &window, &renderer);

    ctx.renderer = renderer;

    emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
