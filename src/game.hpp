// buttons
#define WIN_LOSE_button_width 100
#define WIN_LOSE_button_height 50
#define WIN_LOSE_button_x (WINDOW_WIDTH-WIN_LOSE_button_width)/2
#define WIN_LOSE_button_margin 20

// restart
#define WIN_LOSE_restart_y (WINDOW_HEIGHT-4*WIN_LOSE_button_height-3*WIN_LOSE_button_margin)/2

// levels
#define WIN_LOSE_levels_y WIN_LOSE_restart_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// quit
#define WIN_LOSE_quit_y  WIN_LOSE_levels_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// prev_next
#define WIN_LOSE_prev_next_y  WIN_LOSE_quit_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// previous
#define WIN_LOSE_previous_x (WINDOW_WIDTH -2*WIN_LOSE_button_width-WIN_LOSE_button_margin)/2

// next
#define WIN_LOSE_next_x WIN_LOSE_previous_x+WIN_LOSE_button_width+WIN_LOSE_button_margin


inline void renderPause_win_lose(SDL_Renderer *render);


void play()
{
    cout << "the game began" << endl;
    is_playing = 1;
    int i = 0;
    while(is_playing)
    {
        if(!is_playing or is_pause)
        {
            SDL_Delay(200);
            continue;
        }
        update();
        check_status_of_playing();

        i++;
        if(i == 300)
        {
            cout << "ADDING...." << endl;
            i = 0;
            for(auto pai : dijkstra(level.map, make_pair(level.player.x, level.player.y)
                                    , level.getCoins())
               )
            {
                level.coins.push_back(Coin(pai.first, pai.second));
                level.n_coins++;
            }
        }

        draw_game();
        rect = {0, 100 + 40 * 12, 1024, 100} ;
        SDL_RenderCopy(render, textureSlides[6], NULL, &rect);
        show();
        SDL_Delay(20);
    }

}

void local_win()
{
    cout << "You win  .." << endl;
    is_pause = 1;
    draw_game();

    renderPause_win_lose(render);

    show();
    while(is_pause)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            coin_sound();
            // restart button
            if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
                    WIN_LOSE_restart_y <= y && y <= WIN_LOSE_restart_y + WIN_LOSE_button_height)
            {
                cout << "RESTART" << endl;
                is_playing = 0;
                load_level(l);
                is_playing = 1;
                is_pause = 0;
            }

            // levels button
            if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
                    WIN_LOSE_levels_y <= y && y <= WIN_LOSE_levels_y + WIN_LOSE_button_height)
            {
                cout << "LEVELS" << endl;
                is_pause = 0;
                is_playing = 0;
                l = get_level();
                load_level(l);
                is_playing = 1;
            }
            // Quit button
            if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
                    WIN_LOSE_quit_y <= y && y <= WIN_LOSE_quit_y + WIN_LOSE_button_height)
            {
                cout << "QUIT" << endl;
                is_pause = 0;
                is_playing = 0;
                return index();
            }

            // Previous button
            if(WIN_LOSE_previous_x <= x && x <= WIN_LOSE_previous_x + WIN_LOSE_button_width &&
                    WIN_LOSE_prev_next_y <= y && y <= WIN_LOSE_prev_next_y + WIN_LOSE_button_height)
            {
                if(!automatique)
                {
                    l--;
                    if(l == 0)l++;
                    cout << "Level " << l << endl;
                    load_level(l);
                    is_playing = 1;
                    is_pause = 0;

                    return;
                }
                cout << "Previous" << endl;
            }
            // Next button
            if(1 == 1)
            {
                // add condition if player wins
                // TODO
                if(WIN_LOSE_next_x <= x && x <= WIN_LOSE_next_x + WIN_LOSE_button_width &&
                        WIN_LOSE_prev_next_y <= y && y <= WIN_LOSE_prev_next_y + WIN_LOSE_button_height)
                {
                    if(!automatique)
                    {
                        l++;
                        if(l == N_LEVELS + 1)l = 1;
                        cout << "Level " << l << endl;
                        load_level(l);
                        is_playing = 1;
                        is_pause = 0;

                        return ;
                    }
                    cout << "NEXT" << endl;
                }
            }



            draw_game();
            rect = {312, 100, 400, 540} ;
            if(automatique)
                SDL_RenderCopy(render, textureSlides[9], NULL, &rect);
            else
                SDL_RenderCopy(render, textureSlides[8], NULL, &rect);
            break;
            show();
        case SDL_QUIT:
            free_memory();

        }
    }
}


void free_memory()
{
    is_playing = 0;
    SDL_RenderCopy(render, texture_wait, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(4);
    cout << "libérer la mémoire ..." << endl;
    SDL_Quit();
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureEnemy);
    for (int i = 0; i < 10; i++) SDL_DestroyTexture(textures[i]);
    for (int i = 0; i < 20; i++) SDL_DestroyTexture(textureSlides[i]);
    SDL_DestroyTexture(textureCoin);
    SDL_FreeSurface(s);
    for (int i = 0; i < 10; i++)SDL_FreeSurface(ss[i]);
    SDL_DestroyTexture(texture_wait);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    exit(1);
}

inline void renderPause_win_lose(SDL_Renderer *render)
{

    static SDL_Texture *WIN_LOSE_resume =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/resume.png"));
    static SDL_Texture *WIN_LOSE_restart =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/restart.png"));
    static SDL_Texture *WIN_LOSE_levels =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/levels.png"));
    static SDL_Texture *WIN_LOSE_quit =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/quit.png"));
    static SDL_Texture *WIN_LOSE_previous =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/previous.png"));
    static SDL_Texture *WIN_LOSE_next =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/next.png"));

    SDL_SetRenderDrawColor(render, 0, 0, 0, 120);
    SDL_RenderFillRect(render, NULL);

    SDL_Rect rect = {WIN_LOSE_button_x, WIN_LOSE_restart_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_restart, NULL, &rect);

    rect = {WIN_LOSE_button_x, WIN_LOSE_levels_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_levels, NULL, &rect);

    rect = {WIN_LOSE_button_x, WIN_LOSE_quit_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_quit, NULL, &rect);

    rect = {WIN_LOSE_previous_x, WIN_LOSE_prev_next_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_previous, NULL, &rect);

    rect = {WIN_LOSE_next_x, WIN_LOSE_prev_next_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_next, NULL, &rect);
    if(1 == 0)
    {
        // add condition if player loses
        // TODO
        SDL_SetRenderDrawColor(render, 0, 0, 0, 0.50);
        SDL_RenderFillRect(render, &rect);
    }
}