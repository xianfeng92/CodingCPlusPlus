#ifndef A540D205_1B17_4F78_9182_8F4CA55CBCF3
#define A540D205_1B17_4F78_9182_8F4CA55CBCF3

class Tv;// forward declaration

class Remote
{
    public:
        enum State{Off,On};
        enum {MinVal,MaxVal = 20};
        enum {Antenna,Cable};
        enum {TV,DVD};
    private:
        int mode;
    public:
        Remote(int m = TV):mode(m){}
        bool volup(Tv &t);
        bool voldown(Tv &t);
        void onoff(Tv &t);
        void chanup(Tv &t);
        void chandown(Tv &t);
        void setmode(Tv &t);
        void set_input(Tv &t);
        void set_chan(Tv &t, int ch );
};

class Tv
{
    public:
        friend class Remote;// Remote can access Tv private parts
        enum {Off,On};
        enum {MinVal, MaxVal = 20};
        enum {Antenna,Cable};
        enum {TV,DVD};
        Tv(int s = Off,int mc = 125):state(s),volume(5),maxchannel(mc),channel(0),mode(Cable),input(TV){}
        void onoff(){state = (state == On)?Off:On;}
        bool ison(){return state == On;}
        bool volup();
        bool voldown();
        void chanup();
        void chandown();
        void set_mode(){mode = (mode == Antenna)？Cable:Antenna;}
        void set_input(){input = (input == TV) ? DVD:TV;}
        void settings() const;// display all settings

    private:
        int state;
        int volume;
        int maxchannel;
        int channel;
        int mode;
        int input;
};

// remote method as inline function
inline bool Remote::volup(Tv &t)
{
    return t.volup();
}

inline bool Remote::voldown(Tv &t)
{
    return t.voldown();
}

inline void Remote::onoff(Tv &t)
{
     t.onoff();
}

inline void Remote::chanup(Tv &t)
{
     t.chanup();
}

inline void Remote::chandown(Tv &t)
{
     t.chandown();
}

inline void Remote::set_mode(Tv &t)
{
     t.set_mode();
}

inline void Remote::set_input(Tv &t)
{
     t.set_input();
}

inline void Remote::set_chan(Tv &t,int ch )
{
    t.channel = ch;
}

#endif /* A540D205_1B17_4F78_9182_8F4CA55CBCF3 */
