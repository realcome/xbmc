/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "LanguageHook.h"
#include "utils/GlobalsHandling.h"

namespace XBMCAddon
{
  // just need a place for the vtab
  LanguageHook::~LanguageHook() = default;

  static thread_local LanguageHook* addonLanguageHookTls;
  static bool threadLocalInitialized = false;
  static xbmcutil::InitFlag initer(threadLocalInitialized);

  void LanguageHook::SetLanguageHook(LanguageHook* languageHook)
  {
    XBMC_TRACE;
    languageHook->Acquire();
    addonLanguageHookTls = languageHook;
  }

  LanguageHook* LanguageHook::GetLanguageHook()
  {
    return threadLocalInitialized ? addonLanguageHookTls : NULL;
  }

  void LanguageHook::ClearLanguageHook()
  {
    LanguageHook* lh = addonLanguageHookTls;
    addonLanguageHookTls = NULL;
    if (lh)
      lh->Release();
  }
}
