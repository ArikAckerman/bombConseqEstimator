#ifndef BOMB_H
#define BOMB_H

class Bomb {
public:
    enum BlastPower {
        LOW,
        MEDIUM,
        HIGH
    };

    Bomb(BlastPower blastPower = MEDIUM);

    void setBlastPower(BlastPower blastPower);
    BlastPower blastPower() const;

private:
    BlastPower m_blastPower;
};

#endif // BOMB_H
