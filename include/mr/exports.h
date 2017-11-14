/*
 * This file is part of the Mirim project.
 *
 * Copyright 2018 Arandu Academy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef MR_EXPORTS_H
#define MR_EXPORTS_H

#ifdef _MSC_VER
#ifdef SHARED_EXPORTS_BUILT_AS_STATIC
#  define MR_EXPORTS
#  define MR_CORE_NO_EXPORT
#else
#  ifndef MR_EXPORTS
#    ifdef mr_core_EXPORTS
/* We are building this library */
#      define MR_EXPORTS __declspec(dllexport)
#    else
/* We are using this library */
#      define MR_EXPORTS __declspec(dllimport)
#    endif
#  endif

#  ifndef MR_CORE_NO_EXPORT
#    define MR_CORE_NO_EXPORT
#  endif
#endif

#ifndef MR_CORE_DEPRECATED
#  define MR_CORE_DEPRECATED __declspec(deprecated)
#endif

#ifndef MR_CORE_DEPRECATED_EXPORT
#  define MR_CORE_DEPRECATED_EXPORT MR_EXPORTS MR_CORE_DEPRECATED
#endif

#ifndef MR_CORE_DEPRECATED_NO_EXPORT
#  define MR_CORE_DEPRECATED_NO_EXPORT MR_CORE_NO_EXPORT MR_CORE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MR_CORE_NO_DEPRECATED
#    define MR_CORE_NO_DEPRECATED
#  endif
#endif
#else
# define MR_EXPORTS
#endif


#endif
