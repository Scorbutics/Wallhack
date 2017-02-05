#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "WindowUtils.h"

#define OPACITY_SHORTCUT 20


HWND GetNextVisibleWindow(HWND hwnd)
{
    HWND it = hwnd;
    clock_t t1 = clock();
    clock_t t2 = t1;


    do
    {
        it = GetNextWindow(it, GW_HWNDNEXT);
        t2 = clock();
    }while(!IsWindowVisible(it) && it != NULL && ((t2 - t1)/CLOCKS_PER_SEC < 5));
    return it;
}

void SetWindowOpacity(HWND handle, unsigned int percents)
{
    SetWindowLong(handle, GWL_EXSTYLE, GetWindowLong(handle, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(handle, 0, (percents*255)/100, LWA_ALPHA);
}


void SetWindowCustomMenu(HWND hwnd)
{
    char buffer[512] = {0};
    GetWindowTextA(hwnd, buffer, 512);
    printf("Fenetre de processus trouvee : %s \n", buffer);

        //On récupère le menu système actuel
        //(le menu affiché lorsque l'utilisateur fait un
        //clic droit sur la window title bar par exemple)
        HMENU sysMenu = GetSystemMenu(hwnd, FALSE);

        if(sysMenu)
        {
            int index = GetMenuItemCount(sysMenu);

            HMENU subMenuTransparency = CreatePopupMenu();
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_10, "10%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_20, "20%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_30, "30%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_40, "40%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_50, "50%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_60, "60%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_70, "70%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_80, "80%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_90, "90%" );
            AppendMenuA(subMenuTransparency, MF_STRING, MENU_ITEM_OPACITY_100, "100%" );

            InsertMenuA(sysMenu, index-2, MF_BYPOSITION | MF_POPUP, (UINT_PTR)subMenuTransparency, "Opacity");
        }

}

void SetWindowEXTTransparent(HWNDStack* hSTarget, int state)
{
    if(state)
    {
        //printf("\n\nFenetre %p transparente\nLast window long : 0x%x\n\n", hTarget, GetWindowLong(hTarget, GWL_EXSTYLE));

        BYTE alpha;
        if(!GetLayeredWindowAttributes(hSTarget->hwnd, NULL, &alpha, NULL))
        {
            hSTarget->opacity = 255;
        }
        else
        {
            hSTarget->opacity = 0;
            hSTarget->opacity |= alpha;
        }

        SetWindowLong(hSTarget->hwnd, GWL_EXSTYLE, GetWindowLong(hSTarget->hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
        SetLayeredWindowAttributes(hSTarget->hwnd, 0, (OPACITY_SHORTCUT*255)/100, LWA_ALPHA);
    }
    else
    {
        //printf("\n\nFenetre %p non transparente\nLast window long : 0x%x\n\n", hTarget, GetWindowLong(hTarget, GWL_EXSTYLE));
        SetLayeredWindowAttributes(hSTarget->hwnd, 0, hSTarget->opacity, LWA_ALPHA);
        SetWindowLong(hSTarget->hwnd, GWL_EXSTYLE, (GetWindowLong(hSTarget->hwnd, GWL_EXSTYLE) | WS_EX_LAYERED) & ~WS_EX_TRANSPARENT);


        //Si aucune fenêtre n'est sélectionnée après l'utilisation du raccourci, on remet la fenêtre initiale au premier plan
        if(GetFocus() == GetDesktopWindow())
        {
            SetForegroundWindow(hSTarget->hwnd);
            SetFocus(hSTarget->hwnd);
        }
    }
}
