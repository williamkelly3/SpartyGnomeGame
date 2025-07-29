/**
 * @file ItemVisitor.cpp
 * @author Maria Pacifico
 */

#include "ItemVisitor.h"
#include "SpartyGnome.h"
#include "ItemPlatform.h"
#include "ItemVillain.h"

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

void ItemVisitor::VisitPlatform(ItemPlatform* platform){}
void ItemVisitor::VisitWall(ItemWall* wall){}

/**
 * For every other visitor, fall
 */
void ItemVisitor::VisitOther(){}

void ItemVisitor::VisitVillian(ItemVillain *villain)
{
    if (villain->GetGame()->GetInvincibilityStatus()){
        villain->GetGame()->SetLose(false);
    } else {
        villain->GetGame()->SetLose(true);
    }
}