#ifndef __PAGE_BASE_H
#define __PAGE_BASE_H

#include "lvgl.h"

// Class
// Define macro on Header file
///@brief Generate stash area
/*Example
    struct PageStash {
        void* data;
        size_t size;
    };
    int myData = 42;
    PageStash stash = PAGE_STASH_MAKE(myData);
    std::cout << "Data address: " << stash.data << std::endl;
    //Data address: 0x7ffee4c8a5ac
    std::cout << "Data size: " << stash.size << " bytes" << std::endl;
    //Data size: 4 bytes
*/
#define PAGE_STASH_MAKE(data) {&(data), sizeof(data)}

///@brief Get the data from stash area
#define PAGE_STASH_GET(data) {this->GetStash(&(data), sizeof(data))}

/// @brief Define PageManager class
class PageManager;

class PageBase {
    public:
        /// @brief  Page status
        enum PAGESTATUS_t {
            PAGE_STATE_IDLE,
            PAGE_STATE_LOAD,
            PAGE_STATE_WILL_APPEAR,
            PAGE_STATE_DID_APPEAR,
            PAGE_STATE_ACTIVITY,
            PAGE_STATE_WILL_DISAPPEAR,
            PAGE_STATE_DID_DISAPPEAR,
            PAGE_STATE_UNLOAD,
            /* Sentinel value indicating the last valid pages status type */
            _PAGE_STATE_LAST = PAGE_STATE_UNLOAD
        };

        /// @brief Page stash area structure
        struct PAGESTASH_t {
                void* ptrPage;
                uint32_t size;
        };

        /// @brief Page switching animation propertiess
        struct ANIMATTR_t {
                uint8_t animType;
                uint8_t animTime;
                lv_anim_path_cb_t lvAnimPath;
        };

    public:
        ///@brief UI root node pointer
        lv_obj_t* lvRoot;
        ///@brief Page manager pointer
        PageManager* pageManager;
        ///@brief Page name
        const char* pageName;
        ///@brief Page ID
        uint16_t pageID;
        ///@brief Page user data pointer
        void* pageUserData;

        ///@brief Private data, Only page manager access
        struct {
                bool ReqEnableCache;
                bool ReqDisableAutoCache;
                bool IsDisableAutoCache;
                bool IsCached;
                PAGESTATUS_t PageStatus;
                PAGESTASH_t pageStash;
                struct {
                        bool isEnter;
                        bool IsBusy;
                        ANIMATTR_t animAttr;
                } PageAnimInfo;
        } pageManagerPrivate;

    public:
        virtual ~PageBase() {}
        /* Page load */
        virtual void onViewLoad() {}
        /* Page load complete */
        virtual void onViewDidLoad() {}
        /* Page will be displayed soon  */
        virtual void onViewWillAppear() {}
        /* The page is displayed  */
        virtual void onViewDidAppear() {}
        /* Page is about to disappear */
        virtual void onViewWillDisappear() {}
        /* Page disappeared complete  */
        virtual void onViewDidDisappear() {}
        /* Page uninstall complete  */
        virtual void onViewDidUnload() {}
        /* Set whether to manually manage the cache */
        void SetCustomCacheEnable(bool en) {
            SetCustomAutoCacheEnable(false);
            pageManagerPrivate.ReqEnableCache = en;
        }
        /* Set whether to enable automatic cache */
        void SetCustomAutoCacheEnable(bool en) {
            pageManagerPrivate.ReqDisableAutoCache = !en;
        }
        /* Set custom animation properties  */
        void SetCustomLoadAnimType(
            uint8_t animType, uint16_t animTime = 500,
            lv_anim_path_cb_t path = lv_anim_path_ease_out) {
            pageManagerPrivate.PageAnimInfo.animAttr.animType = animType;
            pageManagerPrivate.PageAnimInfo.animAttr.animTime = animTime;
            pageManagerPrivate.PageAnimInfo.animAttr.lvAnimPath = path;
        }

        bool GetStash(void* willAppearPage, uint32_t ptrSize) {
            bool result = false;
            if (pageManagerPrivate.pageStash.ptrPage != nullptr &&
                pageManagerPrivate.pageStash.size == ptrSize) {
                memcpy(willAppearPage, pageManagerPrivate.pageStash.ptrPage,
                       pageManagerPrivate.pageStash.size);
                result = true;
            }
            return result;
        }
};
#endif