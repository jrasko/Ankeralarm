#ifndef ANKERALRM_ALARM_H
#define ANKERALRM_ALARM_H

class Alarm : public Zustand
{
private:
    Anzeige anzeige;
public:
    Alarm(Anzeige a){
        anzeige = a;
    }
    ~Alarm();
};



#endif