#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 668

// logo
#define HOME_logo_width 100
#define HOME_logo_height 50
#define HOME_logo_x (WINDOW_WIDTH-HOME_logo_width)/2
#define HOME_logo_y 50

// buttons
#define HOME_button_width 100
#define HOME_button_height 50
#define HOME_button_x 51
#define HOME_button_margin 20

// offline
#define HOME_automatic_y WINDOW_HEIGHT-HOME_button_height-HOME_button_margin

// online
#define HOME_online_y HOME_automatic_y-HOME_button_height-HOME_button_margin

// offline
#define HOME_offline_y HOME_online_y-HOME_button_height-HOME_button_margin

// normal
#define HOME_normal_y  HOME_offline_y-HOME_button_height-HOME_button_margin

// createLevel
#define HOME_createLevel_width 100
#define HOME_createLevel_height 50
#define HOME_createLevel_x WINDOW_WIDTH-HOME_button_margin-HOME_createLevel_width
#define HOME_createLevel_y WINDOW_HEIGHT-HOME_createLevel_height-HOME_button_margin

inline void renderHome(SDL_Renderer *render);

void index()
{
    cout << "Hello " << id << endl;
    coin_sound();

    renderHome(render);
    SDL_RenderPresent(render);
    
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            coin_sound();
            x = event.motion.x;
            y = event.motion.y;
            //ONE PLAYER OFFLIN
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_normal_y <= y && y <= HOME_normal_y + HOME_button_height)
            {
                y = 0;
                l = get_level();
                play();
            }
            //TWO PLAYER thread_playing_online
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_online_y <= y && y <= HOME_online_y + HOME_button_height)
            {
                online_game();
            }
            //GENETIC ALGORITHM (n'est pas encore terminé)
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_automatic_y <= y && y <= HOME_automatic_y + HOME_button_height)
            {
                y = 0;
                l = get_level();
                level.get_enemys();
                level.player.update_input(level);
                update();
                automatique = 1;
                //Les joeurs sont en position inital A et leur objectif est d'atteindre la position B (la position de premier coins) todo(Le plus proche)
                level.A = make_pair(level.player.x, level.player.y);
                level.B = make_pair(level.coins[0].x, level.coins[0].y);

                level.init_population(NEURAL_NETWORK);

                play();
            }
            //2Players Offline
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_offline_y <= y && y <= HOME_offline_y + HOME_button_height)
            {
                // TODO 2Players Offline
                cout<<"2Players Offline: TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            }

            //CREATE NEW LEVEL
            if(HOME_createLevel_x <= x && x <= HOME_createLevel_x + HOME_createLevel_width &&
                    HOME_createLevel_y <= y && y <= HOME_createLevel_y + HOME_createLevel_height)
            {
                create_level();
                cout << "le niveau créé avec succès" << endl;
                play();
            }
            break ;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}

inline void renderHome(SDL_Renderer *render)
{

    static SDL_Texture *HOME_normal =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/normal.png"));
    static SDL_Texture *HOME_online =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/online.png"));
    static SDL_Texture *HOME_offline =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/2Players.png"));
    static SDL_Texture *HOME_automatic =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/automatic.png"));
    static SDL_Texture *HOME_createLevel =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/createLevel.png"));
    static SDL_Texture *HOME_logo =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/index.png"));
    static SDL_Texture *HOME_background = SDL_CreateTextureFromSurface(render, IMG_Load("../images/index.png"));


    // SDL_RenderCopy(render, HOME_background, NULL, NULL);

    SDL_Rect rect = {HOME_button_x, HOME_normal_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_normal, NULL, &rect);

    rect = {HOME_button_x, HOME_normal_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_offline, NULL, &rect);

    rect = {HOME_button_x, HOME_offline_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_online, NULL, &rect);

    rect = {HOME_button_x, HOME_online_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_automatic, NULL, &rect);

    rect = {HOME_button_x, HOME_automatic_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_normal, NULL, &rect);

    rect = {HOME_createLevel_x, HOME_createLevel_y, HOME_createLevel_width, HOME_createLevel_height};
    SDL_RenderCopy(render, HOME_createLevel, NULL, &rect);
}