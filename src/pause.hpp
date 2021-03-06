// buttons
#define PAUSE_button_width 100
#define PAUSE_button_height 50
#define PAUSE_button_x (WINDOW_WIDTH-PAUSE_button_width)/2
#define PAUSE_button_margin 20

// resume
#define PAUSE_resume_y (WINDOW_HEIGHT-4*PAUSE_button_height-3*PAUSE_button_margin)/2

// restart
#define PAUSE_restart_y PAUSE_resume_y+PAUSE_button_height+PAUSE_button_margin

// levels
#define PAUSE_levels_y PAUSE_restart_y+PAUSE_button_height+PAUSE_button_margin

// quit
#define PAUSE_quit_y  PAUSE_levels_y+PAUSE_button_height+PAUSE_button_margin

inline void renderPause(SDL_Renderer *render);

void pause_game()
{
    cout << "START PAUSE" << endl;
    is_pause = 1;

    interface = PAUSE;
    cout << interface << endl;
    while(is_pause)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;

            // resume button
            if(PAUSE_button_x <= x && x <= PAUSE_button_x + PAUSE_button_width &&
                    PAUSE_resume_y <= y && y <= PAUSE_resume_y + PAUSE_button_height)
            {
                cout << "RESUME" << endl;
                is_pause = 0;
                return;
            }

            // restart button
            if(PAUSE_button_x <= x && x <= PAUSE_button_x + PAUSE_button_width &&
                    PAUSE_restart_y <= y && y <= PAUSE_restart_y + PAUSE_button_height)
            {
                is_playing = 0;
                cout << "RESTART" << endl;
                load_level(l);
                is_playing = 1;
                is_pause = 0;
            }

            // levels button
            if(PAUSE_button_x <= x && x <= PAUSE_button_x + PAUSE_button_width &&
                    PAUSE_levels_y <= y && y <= PAUSE_levels_y + PAUSE_button_height)
            {
                cout << "LEVELS" << endl;
                is_pause = 0;
                is_playing = 0;
                l = get_level();
                load_level(l);
                is_playing = 1;
            }
            // Quit button
            if(PAUSE_button_x <= x && x <= PAUSE_button_x + PAUSE_button_width &&
                    PAUSE_quit_y <= y && y <= PAUSE_quit_y + PAUSE_button_height)
            {
                cout << "QUIT" << endl;
                is_pause = 0;
                is_playing = 0;
                return index();
            }
            break;
        case SDL_QUIT:
            free_memory();
        }
    }
}

inline void renderPause(SDL_Renderer *render)
{

    static SDL_Texture *PAUSE_resume =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/resume.png"));
    static SDL_Texture *PAUSE_restart =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/restart.png"));
    static SDL_Texture *PAUSE_levels =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/levels.png"));
    static SDL_Texture *PAUSE_quit =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/quit.png"));


    SDL_SetRenderDrawColor(render, 0, 0, 0, 185);
    SDL_RenderFillRect(render, NULL);

    SDL_Rect rect = {PAUSE_button_x, PAUSE_resume_y, PAUSE_button_width, PAUSE_button_height};
    SDL_RenderCopy(render, PAUSE_resume, NULL, &rect);

    rect = {PAUSE_button_x, PAUSE_restart_y, PAUSE_button_width, PAUSE_button_height};
    SDL_RenderCopy(render, PAUSE_restart, NULL, &rect);

    rect = {PAUSE_button_x, PAUSE_levels_y, PAUSE_button_width, PAUSE_button_height};
    SDL_RenderCopy(render, PAUSE_levels, NULL, &rect);

    rect = {PAUSE_button_x, PAUSE_quit_y, PAUSE_button_width, PAUSE_button_height};
    SDL_RenderCopy(render, PAUSE_quit, NULL, &rect);
}