
class Player
{
public:
    int x = 500, y = 500, w = 30, h = 30, p;
    Model modul1 = Model({2, 4, 4});
    Model modul2 = Model({2 + 4 * 4 * 2, 20, 4});
    Player(int a, int b)
    {
        x = a;
        y = b;
        modul1.W = {{{-0.2767942264507328, 6.397569764399211}, {-6.205135899484164, -1.1632928271471725}, {-0.060290587338257706, 0.029242188070814093}, {2.931469091663114, -1.9599264662647378}}, {{-4.48925451119474, 0.9875516202290665, -0.23075988915545265, 1.6337038811997384}, {4.586166232729524, -0.8734063273189748, 0.35953384663272864, -1.3807384132011944}, {0.047104202448398046, 4.400899499824716, 0.18527900604849584, -2.2548456801674552}, {-0.060970536208957614, -4.419437160813999, 0.10990179452634348, 2.225288653198917}}};
        modul1.b = {{{1.286747995779057}, {1.5472895562023274}, {-0.1924552421136109}, {2.620984854592648}}, {{0.039352427859709604}, {-0.9831595862602918}, {-0.7893033458507539}, {0.9710540018057716}}};

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

    void go_to_coin(int a, int b)
    {
        double dx = x - a, dy = y - b;
        dx = dx / sqrt(pow(dx, 2) + pow(dy, 2));
        dy = dy / sqrt(pow(dx, 2) + pow(dy, 2));

        auto r = modul1.predict({dx, -dy});
        for(auto s : r)cout << s << " ";
        cout << endl;
        if(max(r[0], max(r[1], max(r[2], r[3]))) < 0.5)exit(0);
        if(r[0] == max(r[0], max(r[1], max(r[2], r[3]))))y -= 10; //up
        else if(r[1] == max(r[0], max(r[1], max(r[2], r[3]))) )y += 10; //down
        else if(r[2] == max(r[0], max(r[1], max(r[2], r[3]))))x += 10; //R
        else if(r[3] == max(r[0], max(r[1], max(r[2], r[3]))))x -= 10; //L
    }
    void test_module2()
    {

    }
};


class Spiral_dot
{

public:
    vector<pair<int, int>> enemys;
    float ongle = 0;
    pair<int, int> C;
    int n;
    int R;
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
class H_enemy
{
public:
    pair<int, int> A;
    double t = 0, w = 400, h = 400;
    int sens = 1; //1 or -1
    vector<pair<int, int>> enemys;
    int n = 10;
    H_enemy(pair<int, int> a, int sens)
    {
        A = a;
        this->sens = sens;
        if(sens==1)t=0;
        else t=1;
    }
    void next_move()
    {
        t += 0.03 * sens;
        enemys.clear();
        for(int i = 0; i < n; i++)
        {
            enemys.push_back(make_pair(A.first + t * w, A.second +  h * i / n));

        }
        if(t  >= 1 or t <= 0 )
        {
            sens *= -1;
            t += 0.03 * sens;
        }
    }
    void update()
    {
        enemys.clear();
        for(int i = 0; i < n; i++)
        {
            enemys.push_back(make_pair(A.first + t * w, A.second +  h * i / n));

        }
    }
};

class Coin
{
public:
    bool is_taked = 0;
    int x, y;
    int w = 10, h = 10;
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

public:
    int map[12][20] = {{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
    };
    vector<Coin> coins;
    Player player = Player(500, 500);
    int w_enemy = 20;
    pair<int, int> last_touch_on_green_area = make_pair(500, 500);
    vector<H_enemy> h_enemys;
    // vector<V_enemy> v_enemys;
    vector<Spiral_dot> spiral_dots;

    Level() {};
    vector<pair<int, int>> get_enemys()
    {
        vector<pair<int, int>> v;
        for (auto sp : spiral_dots)
        {
            for(auto e : sp.enemys)
            {
                v.push_back(e);
            }

        }
        for (auto sp : h_enemys)
        {
            for(auto e : sp.enemys)
            {
                v.push_back(e);
            }

        }
        return v;
    };
    void save();
    void load();
};