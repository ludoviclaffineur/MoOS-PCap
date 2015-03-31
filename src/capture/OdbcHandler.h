//
//  ODBCHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 13/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__ODBCHandler__
#define __MoOS__ODBCHandler__

#include "CaptureDevice.h"
#include <soci.h>
#include <soci-odbc.h>

#include <stdio.h>
#include <vector>
#include "Grid.h"
#include "ScalingProcessing.h"

namespace capture{
        using namespace processing;
        using namespace mapping;
        class OdbcHandler : public CaptureDevice{
        public:
            OdbcHandler(Grid* g, std::string configFile);
            ~OdbcHandler();
            void init();

            void trig();
        private:
            soci::session* mSql;
            std::vector<std::vector<double>> mRequest;

            std::vector<std::string> mNames;
            void setRow(int identifier);
            int mCurrentRow;
        };
}


#endif /* defined(__MoOS__ODBCHandler__) */
