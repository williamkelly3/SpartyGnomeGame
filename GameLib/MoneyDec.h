/**
 * @file MoneyDec.h
 * @author William Alff
 *
 *
 */

#ifndef PROJECT1_MONEYDEC_H
#define PROJECT1_MONEYDEC_H

#include "ItemDec.h"

/**
 * Class that handles XML for money
 */
class MoneyDec : public ItemDec {
private:
    /// Xml ID
    std::wstring mId;

    /// Filename for an item image
    std::wstring mFilename;

    /// Value of money
    double mValue = 0;
public:
    /**
     * Constructor
     * @param id Id of the money
     * @param filename Image filename of the money
     * @param value Value of the money
     */
    MoneyDec(const std::wstring& id, const std::wstring& filename,
            double value) : mId(id), mFilename(filename), mValue(value) {};

    /**
     * Gets money filename
     * @return Money filename
     */
    std::wstring& GetFilename() { return mFilename; }

    MoneyDec() = default;

    /**
     * Gets value of the money
     * @return Value of the money
     */
    double GetVal() { return this->mValue; }
};

#endif //PROJECT1_MONEYDEC_H
