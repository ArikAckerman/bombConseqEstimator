#include "bomb.h"

Bomb::Bomb(BlastPower blastPower)
    : m_blastPower(blastPower) {}

void Bomb::setBlastPower(BlastPower blastPower) {
    m_blastPower = blastPower;
}

Bomb::BlastPower Bomb::blastPower() const {
    return m_blastPower;
}
