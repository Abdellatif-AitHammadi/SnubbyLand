
class Graphic;
class Level;
class Player
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &x;
        ar &y;

    }
public:
    int x = 500, y = 500, w = 30, h = 30, p;
    vector<double> input;
    int score = 0;
    double fitness;
    Model brain = Model({44, 40, 20, 4});
    // Level *level;
    bool is_a_life = 1;
    Player(int a, int b)
    {
        x = a;
        y = b;
        brain.init_params();

    }
    bool touche_enemy(pair<int, int> enemy, int r)
    {
        if(     ((enemy.first - r >= x - r) && (enemy.first - r <= x + r ) && (enemy.second - r >= y - r) && ( enemy.second - r <= y + r)) ||
                ((enemy.first + r >= x - r) && (enemy.first + r <= x + r ) && (enemy.second + r >= y - r) && ( enemy.second + r <= y + r)) ||
                ((enemy.first - r >= x - r) && (enemy.first - r <= x + r) && (enemy.second + r >= y - r) && ( enemy.second + r <= y + r))  ||
                ((enemy.first + r >= x - r) && (enemy.first + r <= x + r) && (enemy.second - r >= y - r) && ( enemy.second - r <= y + r))
          )
            return 1;
        return 0;
    };


    void think(Level *level,Graphic*g);

};


class Spiral_dot
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &n;
        ar &R;
        ar &C;
        ar &enemys;

    }
public:
    vector<pair<int, int>> enemys;
    float ongle = 0;
    pair<int, int> C;
    int n;
    int R;
    Spiral_dot() {};
    Spiral_dot(pair<int, int> C, int n, int R)
    {
        this->C = C;
        this->n = n;
        this->R = R;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(C.first + R * cos(i * PI / 2)*j / n, C.second + R * sin(i * PI / 2)*j / n));

            }
        }

    }

    void next_move()
    {
        ongle += PI / 100;
        enemys.clear();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(C.first + R * cos((i * PI / 2) + ongle)*j / n, C.second + R * sin((i * PI / 2) + ongle)*j / n));

            }
        }
    }
    void update()
    {
        enemys.clear();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(C.first + R * cos(i * PI / 2)*j / n, C.second + R * sin(i * PI / 2)*j / n));

            }
        }
    }

};

class Linear_enemy
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &A;
        ar &B;

    }
public:
    pair<int, int> A, B;
    double t = 0;
    int sens = 1;
    Linear_enemy() {};
    Linear_enemy(pair<int, int> a, pair<int, int> b)
    {
        A = a;
        B = b;
    }

    void next_move()
    {
        t += sens * 0.03;


        if(t > 1 or t < 0)
        {
            sens *= -1;
        }
    }

    pair<int, int> enemy()
    {
        return make_pair(t * A.first + (1 - t) * B.first, t * A.second + (1 - t) * B.second);
    }
};





class Coin
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &is_taked;
        ar &x;
        ar &y;


    }
public:
    bool is_taked = 0;
    int x, y;
    int w = 10, h = 10;
    Coin() {};
    Coin(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void take(Player p)
    {
        if( x - w / 2 >= p.x - p.w / 2 && x - w / 2 <= p.x + p.w / 2 && y - (h / 2) >= p.y - p.h / 2 &&  y - h / 2 <= p.y + p.h / 2
                // (x + r >= p.x - p.w/2) && (x + r <= p.x + pr && (y + (h / 2) >= p.y - p.h / 2) && ( y + h / 2 <= p.y + p.h / 2)) ||
                // (x - r >= p.x - p.w/2) && (x - r <= p.x + pr && (y + (h / 2) >= p.y - p.h / 2) && ( y + h / 2 <= p.y + p.h / 2))  ||
                // (x + r >= p.x - p.w/2) && (x + r <= p.x + pr && (y - (h / 2) >= p.y - p.h / 2) && ( y - h / 2 <= p.y + p.h / 2))
          )
        {
            is_taked = 1;
        }
    }
};
class Level
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &map;
        ar &coins;
        ar &player;
        ar &linear_enemys;
        ar &stable_enemys;
        ar &spiral_dots;

    }
public:
    int map[12][20] = {{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
    };
    vector<Coin> coins;
    Player player = Player(500, 500);
    vector<Player> Snubbys;
    int w_enemy = 20;
    pair<int, int> last_touch_on_green_area = make_pair(500, 500);
    vector<Linear_enemy> linear_enemys;
    vector<pair<int, int>> stable_enemys;
    vector<Spiral_dot> spiral_dots;
    vector<pair<int, int>> enemys;
    int n, last_direction = 1;
    Level()
    {
        // player.level = this;
        for(int i = 0; i < 10; i++)
        {
            player.x = 100 + rand() % 500;
            player.y = 100 + rand() % 500;
            Snubbys.push_back(player);
        }
    };
    void make_population()
    {
        Snubbys.empty();
        for(int i = 0; i < N_POPULATION; i++)
        {
            Snubbys.push_back(Player(500, 500));
            Snubbys[i].x = 500;
            Snubbys[i].y = 500;
        }
    }
    vector<pair<int, int>> get_enemys()
    {
        enemys.clear();
        vector<pair<int, int>> v;
        for (auto sp : spiral_dots)
        {
            for(auto e : sp.enemys)
            {
                enemys.push_back(e);
                v.push_back(e);
            }

        }
        for( auto e : linear_enemys)
        {
            enemys.push_back(e.enemy());
            v.push_back(e.enemy());
        }

        return v;
    };
    void random_map()
    {
        int T[3] = {-1, 1, 0};
        int lvl = 10, w = 20, h = 12;
        int **rmap = generateLevel(time(NULL), w, h);

        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                map[i][j] = T[rmap[i][j]];
            }
        }

    }




};

