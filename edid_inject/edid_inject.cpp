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

#include <edid_inject.hpp>

#define super IOService

OSDefineMetaClassAndStructors(EDIDInject, super);

IOService *EDIDInject::probe (IOService *provider, SInt32 *score) {
    OSData *edid_data = (OSData *) getProperty("EDID");
    unsigned short dispProduct, matchProduct, dispVendor, matchVendor;
    OSNumber *matchVendorN, *matchProductN;

    /* Get match parameters */
    matchVendorN = (OSNumber *) getProperty("DisplayProductID");
    matchProductN = (OSNumber *) getProperty("DisplayVendorID");

    /* Check for valid parameters */
    if (nullptr == matchVendorN || nullptr == matchProductN || nullptr == edid_data) {
        return nullptr;
    }
    
    dispProduct = ((OSNumber *) provider->getProperty("DisplayProductID"))->unsigned16BitValue();
    matchProduct = matchProductN->unsigned16BitValue();

    dispVendor = ((OSNumber *) provider->getProperty("DisplayVendorID"))->unsigned16BitValue();
    matchVendor = matchVendorN->unsigned16BitValue();
    
    if (nullptr == edid_data || (dispProduct != matchProduct) || (dispVendor != matchVendor)) {
        return nullptr;
    }

    /* Inject fake EDID */
    IOLog ("EDIDInject: attempting to inject EDID on device 0x%04x:0x%04x\n", dispVendor, dispProduct);
    
    provider->setProperty ("EDIDInject", "Active");
    provider->setProperty ("IODisplayEDID", edid_data);
    return nullptr;
}
