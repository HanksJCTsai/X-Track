#ifndef __PAGE_MANAGER_H
#define __PAGE_MANAGER_H

#include <stack>
#include <vector>

#include "PageBase.h"
#include "PageFactory.h"

class PageManager {
    public:
        /// @brief Animated setter
        typedef lv_anim_exec_xcb_t lv_anim_setter_t;
        /// @brief Animated getter
        typedef lv_coord_t (*lv_anim_getter_t)(void*);

    public:
        /// @brief Page switching animation type
        enum SWITCHANIMATIONTYPE_t {
            /* Default (global) animation type  */
            LOAD_ANIM_GLOBAL = 0,
            /* New page overwrites old page  */
            LOAD_ANIM_OVER_LEFT,
            LOAD_ANIM_OVER_RIGHT,
            LOAD_ANIM_OVER_TOP,
            LOAD_ANIM_OVER_BOTTOM,
            /* New page pushes old page  */
            LOAD_ANIM_MOVE_LEFT,
            LOAD_ANIM_MOVE_RIGHT,
            LOAD_ANIM_MOVE_TOP,
            LOAD_ANIM_MOVE_BOTTOM,
            /* The new interface fades in, the old page fades out */
            LOAD_ANIM_FADE_ON,
            /* No animation */
            LOAD_ANIM_NONE,
            /* Sentinel value indicating the last valid animation type */
            _LOAD_ANIM_LAST = LOAD_ANIM_NONE
        };
        /// @brief Page dragging direction
        enum ROOTDRAGDIRTYPE_t {
            ROOT_DRAG_NONE,
            ROOT_DRAG_HOR,
            ROOT_DRAG_VER,
            ROOT_DRAG_ALL,
            _ROOT_DRAG_LAST = ROOT_DRAG_ALL

        };
        /// @brief Page switching animation properties
        struct ANIMVALUE_t {
                /// @brief As the entered party
                struct {
                        lv_coord_t start;
                        lv_coord_t end;
                } ENTER;
                /// @brief As the exited party
                struct {
                        lv_coord_t start;
                        lv_coord_t end;
                } EXIT;
        };
        /// @brief Page loading animation properties
        struct LOADANIMATTR_t {
                lv_anim_setter_t setter;
                lv_anim_getter_t getter;
                ROOTDRAGDIRTYPE_t dragDir;
                ANIMVALUE_t push;
                ANIMVALUE_t pop;
        };

    public:
        PageManager(PageFactory* pageFactory = nullptr);
        ~PageManager();

        // Page Loader
        /// @brief Page install
        PageBase* InstallPage(const char* className, const char* pageName);
        /// @brief Page uninstall
        bool UninstallPage(const char* pageName);
        /// @brief Page load
        bool Register(PageBase* pageBase, const char* pageName);
        /// @brief Page unload
        bool Unregister(const char* pageName);

        // Page Router
        PageBase* Push(const char* pageName,
                       const PageBase::PAGESTASH_t* pageStash = nullptr);
        PageBase* Pop();
        bool BackHome();
        const char* GetPagePrevName();

        // Global Page Animation
        void SetGlobalPageAnimation(
            SWITCHANIMATIONTYPE_t anim = LOAD_ANIM_OVER_LEFT,
            uint16_t time = 500,
            lv_anim_path_cb_t path = lv_anim_path_ease_out);

    private:
        PageFactory* pageFactory;
        PageBase* pageCurrent;
        PageBase* pagePrev;
        std::vector<PageBase*> pagePool;
        std::stack<PageBase*> pageStack;

        struct {
                bool IsSwitchReq; // Whether to switch request
                bool IsBusy;      // Is switching
                bool IsPushing;   // Whether it is in push state

                PageBase::ANIMATTR_t Current; // Current animation properties
                PageBase::ANIMATTR_t Global;  // Global animation properties
        } animationState;

    private:
        // About Page Pool
        /// @brief  Find the page in the page pool
        /// @param pageName
        /// @return PageBase*
        PageBase* FindPageInPool(const char* pageName);

        // About Page Stack
        /// @brief  Find the page in the page stack
        /// @param pageName
        /// @return PageBase*
        PageBase* FindPageInStack(const char* pageName);
        PageBase* GetPageStackTop();
        PageBase* GetPageStackTopAfter();
        void SetPageStackClear(bool keepToBottom = true);
        bool FourceUnload(PageBase* pageBase);

        // About Page Animation
        bool GetLoadAnimAttr(uint8_t anim, LOADANIMATTR_t* loadAnimAttr);
        bool GetIsOverAnim(uint8_t anim) {
            return (anim >= LOAD_ANIM_OVER_LEFT &&
                    anim <= LOAD_ANIM_OVER_BOTTOM);
        }
        bool GetIsMoveAnim(uint8_t anim) {
            return (anim >= LOAD_ANIM_MOVE_LEFT &&
                    anim <= LOAD_ANIM_MOVE_BOTTOM);
        }
        void AnimDefaultInit(lv_anim_t* a);
        bool GetCurrentLoadAnimAttr(LOADANIMATTR_t* attr) {
            return GetLoadAnimAttr(GetCurrentLoadAnimType(), attr);
        }
        SWITCHANIMATIONTYPE_t GetCurrentLoadAnimType() {
            return (SWITCHANIMATIONTYPE_t)animationState.Current.animType;
        }

        //About Page Root
        
};
#endif