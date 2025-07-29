/**
 * @file PlatformDec.h
 * @author WIlliam Alff
 *
 * Class that handles XML declarations for items.
 */

#ifndef PROJECT1_PLATFORMDEC_H
#define PROJECT1_PLATFORMDEC_H

#include "ItemDec.h"

/**
 * Class that handles XML declarations for items.
 */
class PlatformDec : public ItemDec {
private:
    /// Xml ID
    std::wstring mId;

    /// Middle filename for a platform image
    std::wstring mFilename;

    /// Left filename for a platform image
    std::wstring mLeftImageFilename;

    /// Right filename for a platform image
    std::wstring mRightImageFilename;
public:
    /**
     * Constructor
     * @param id Id of the platform
     * @param filename Middle image filename of the platform
     * @param left_filename Left image filename of the platform
     * @param right_filename Right image filename of the platform
     */
    PlatformDec(std::wstring id, const std::wstring filename, const std::wstring& left_filename,
            const std::wstring right_filename) : mId(id), mLeftImageFilename(filename), mFilename(left_filename),
            mRightImageFilename(right_filename) {};

    PlatformDec() = default;

    /**
     * Gets middle platform filename
     * @return Middle platform filename
     */
    std::wstring& GetFilename() { return mFilename; }

    /**
     * Gets left platform filename
     * @return Left platform filename
     */
    std::wstring& GetLeftImageFilename() { return this->mLeftImageFilename; }

    /**
     * Gets right platform filename
     * @return Right platform filename
     */
    std::wstring& GetRightImageFilename() { return this->mRightImageFilename; }
};

#endif //PROJECT1_PLATFORMDEC_H
