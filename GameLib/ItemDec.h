/**
 * @file ItemDec.h
 * @author William Alff
 *
 *
 */

#ifndef PROJECT1_ITEMDEC_H
#define PROJECT1_ITEMDEC_H

/**
 * Class that handles XML for items
 */
class ItemDec {
private:
    /// Xml ID
    std::wstring mId;

    /// Filename for an item image
    std::wstring mFilename;
public:
    /**
     * Constructor
     * @param id Id of the item
     * @param filename Image filename of the item
     */
    ItemDec(const std::wstring& id, const std::wstring& filename) : mId(id), mFilename(filename) {}

    /**
     * Gets item filename
     * @return Item filename
     */
    std::wstring& GetFilename() { return mFilename; }

    ItemDec() = default;
};

#endif //PROJECT1_ITEMDEC_H
