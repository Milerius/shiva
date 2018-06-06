//
// Created by doom on 03/10/17.
//

#pragma once

#define __PP_PASTE_HELPER(a, b)     a##b
#define pp_paste(a, b)              __PP_PASTE_HELPER(a, b)