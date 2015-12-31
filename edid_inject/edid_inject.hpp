/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4 -*- */
/*
 * EDID injector
 * Copyright © 2015 Nathan Hjelm <hjelmn@cs.unm.edu>
 *
 * This injector matches against the AppleDisplay device and replaces the
 * EDID with the specified EDID. This method works for both audio and video
 * which is an improvement over the video only override provided by the OS.
 *
 * This driver is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#if !defined(EDID_INJECT_H)
#define EDID_INJECT_H

#include <IOKit/IOService.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOTypes.h>

class EDIDInject : public IOService {
    OSDeclareDefaultStructors(EDIDInject);
public:
    virtual IOService *probe (IOService *provider, SInt32 *score) override;
};

#endif /* !defined(EDID_INJECT_H) */