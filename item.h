#ifndef D_ITEM_H
#define D_ITEM_H

class Item
{
    public:
        Item(int hp, int str, int dex);
        ~Item();

        inline int GetBonusHp() { return m_bonusHp; }
        inline int GetBonusStr() { return m_bonusStr; }
        inline int GetBonusDex() { return m_bonusDex; }

    private:
        int m_bonusHp;
        int m_bonusStr;
        int m_bonusDex;
};

#endif
