#pragma once

namespace pathfinder{
    class manipulator{

    };
    class map_manipulator{
        public:
            void setHeight(Map& mp, int point, int height);
            void affectHeight(Map& mp, int point, int height);
    };
}