#ifndef PDS2_POSITION_H
#define PDS2_POSITION_H

using namespace std;

class Position
{
private:
    bool _self_;
    int _index_;
public:
    Position(bool _self, int _index);
    ~Position();

    bool isSelf();
    int getIndex();
};

#endif /* PDS2_POSITION_H */