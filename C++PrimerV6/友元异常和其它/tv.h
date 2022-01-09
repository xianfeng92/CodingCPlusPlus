#ifndef FFE222F3_8698_413A_ADC2_2A2E8FFF9CB9
#define FFE222F3_8698_413A_ADC2_2A2E8FFF9CB9

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

class Remote
{
    private:
        int mode;
    public:
        Remote(int m = Tv::TV):mode(m){}
        bool volup(Tv &t){ return t.volup();}
        bool voldown(Tv &t){ return t.voldown();}
        void onoff(Tv &t) {t.onoff();}
        void chanup(Tv &t){t.chanup();}
        void chandown(Tv &t) {t.chandown();}
        void set_chan(Tv &t, int c) {t.channel = c;}
        void set_mode(Tv &t){t.set_mode();}
        void set_input(Tv &t){t.set_input();}
        
};

#endif /* FFE222F3_8698_413A_ADC2_2A2E8FFF9CB9 */
