//
//  CsvImporter.h
//  MoOS
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__CsvImporter__
#define __MoOS__CsvImporter__

#include <iostream>
#include "LocationIp.h"
#include <regex>

class CsvImporter{
public:
    static LocationIp** importCsv(std::string &file);
};

#endif /* defined(__MoOS__CsvImporter__) */
