/**
 * @file HorizontalVisit.h
 * @author Maria Pacifico
 */

#ifndef PROJECT1_HORIZONTALVISIT_H
#define PROJECT1_HORIZONTALVISIT_H

class SpartyGnome;

#include "ItemVisitor.h"

class HorizontalVisit : public ItemVisitor{
private:
    /// Sparty gnome in our game
    SpartyGnome *mGnome;
public:
    /**
     * Set Sparty Gnome
     */
    void SetGnome(SpartyGnome *gnome) { mGnome = gnome; }

    void VisitPlatform(ItemPlatform* platform) override;

    void VisitWall(ItemWall* wall) override;

};


#endif //PROJECT1_HORIZONTALVISIT_H
