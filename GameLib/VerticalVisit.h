/**
 * @file VerticalVisit.h
 * @author Maria Pacifico
 */

#ifndef PROJECT1_VERTICALVISIT_H
#define PROJECT1_VERTICALVISIT_H

class SpartyGnome;

#include "ItemVisitor.h"

class VerticalVisit :  public ItemVisitor{
private:
    /// Sparty gnome in our game
    SpartyGnome *mGnome;
public:
    //virtual ~ItemVisitor() {}
    /**
     * Set Sparty Gnome
     */
    void SetGnome(SpartyGnome *gnome) { mGnome = gnome; }

    void VisitPlatform(ItemPlatform* platform) override;

    void VisitWall(ItemWall* wall) override;

    void VisitOther() override;
};


#endif //PROJECT1_VERTICALVISIT_H
