/**
 * @file ItemVisitor.h
 * @author Maria Pacifico
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H

class ItemBackground;
class ItemDoor;
class ItemInvincibility;
class ItemMoney;
class ItemPlatform;
class ItemTuitionUp;
class ItemVillain;
class ItemWall;
class SpartyGnome;

class ItemVisitor {
private:
    /// Sparty gnome in our game
    SpartyGnome *mGnome;

public:
    virtual ~ItemVisitor() {}

    /**
     * Set Sparty Gnome
     */
     void SetGnome(SpartyGnome *gnome) { mGnome = gnome; }

     SpartyGnome *GetGnome() { return mGnome; }

    /**
     * Visit an ItemPlatform object
     * @param platform Platform we are visiting
     */
    virtual void VisitPlatform(ItemPlatform* platform);

    /**
     * Visit an ItemWall object
     * @param wall Wall we are visiting
     */
    virtual void VisitWall(ItemWall* wall);

    /**
     * Every other object
     */
    virtual void VisitOther();

    virtual void VisitVillian(ItemVillain* villain);

};


#endif //PROJECT1_ITEMVISITOR_H
